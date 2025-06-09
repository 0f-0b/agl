#include "common/aglGPUMemBlock.h"

#include <heap/seadHeapMgr.h>

#include "detail/aglGPUMemBlockMgr.h"
#include "detail/aglMemoryPoolHeap.h"

namespace agl {

GPUMemBlockBase::GPUMemBlockBase() {
    clear();
}

void GPUMemBlockBase::clear() {
    mNext = nullptr;
    mBuffer = nullptr;
    mSize = 0;
    mMemoryPool = nullptr;
    mMemoryPoolHeap = nullptr;
    mFlags &= ~1;
    mAlignment = 0;
}

GPUMemBlockBase::~GPUMemBlockBase() {
    free();

    if (mFlags & 2) {
        mMemoryPool->finalize();
        delete mMemoryPool;
        mMemoryPool = nullptr;
    }
}

void GPUMemBlockBase::freeBuffer() {
    if (!mBuffer)
        return;
    if (mMemoryPoolHeap) {
        mMemoryPoolHeap->freeToHeap(this);
    } else {
        mMemoryPool->finalize();
        if (!(mFlags & 3) && mBuffer)
            operator delete(mBuffer);
    }
    clear();
}

void GPUMemBlockBase::free() {
    freeBuffer();
}

void GPUMemBlockBase::allocBuffer_(u64 size, sead::Heap* heap, s32 alignment,
                                   MemoryAttribute attribute) {
    if (!heap)
        heap = sead::HeapMgr::instance()->getCurrentHeap();
    tryAllocBuffer_(size, heap, alignment, attribute);
    mAlignment = alignment;
}

bool GPUMemBlockBase::tryAllocBuffer_(u64 size, sead::Heap* heap, s32 alignment,
                                      MemoryAttribute attribute) {
    clear();
    if (size == 0)
        return true;
    if (!detail::GPUMemBlockMgr::instance()->tryAllocMemory(this, heap, size, alignment, attribute))
        return false;
    mAlignment = alignment;
    return true;
}

static void* align(void* ptr, s32 alignment) {
    s32 mask = alignment - 1;
    return reinterpret_cast<void*>((reinterpret_cast<u64>(ptr) + mask) & ~mask);
}

void GPUMemBlockBase::setBuffer_(u64 size, void* buffer, void* memory_pool_storage,
                                 MemoryAttribute attribute) {
    clear();
    if (size == 0)
        return;
    mBuffer = buffer;
    mSize = size;
    mMemoryPool = new (align(memory_pool_storage, 8)) detail::MemoryPool;
    mMemoryPool->initialize(mBuffer, size, detail::MemoryPoolType::convert(attribute));
    mFlags |= 1;
}

void GPUMemBlockBase::setVirtual_(u64 size, sead::Heap* heap, MemoryAttribute attribute,
                                  GPUMemVoidAddr parent, s32 alignment) {
    if (size == 0)
        return;
    mBuffer = parent.mem_block->mBuffer;
    mSize = size;
    mMemoryPool = new (heap) detail::MemoryPool;
    mMemoryPool->initialize(mBuffer, size, detail::MemoryPoolType::convert(attribute),
                            *parent.mem_block->mMemoryPool, alignment);
    mFlags |= 2;
}

// void GPUMemBlockBase::initializeGfxMemoryPool(nn::gfx::MemoryPool* pool) const {
//     if (pool->state)
//         pool->state = 0;
//     nn::gfx::Interoperation::ConvertToGfxMemoryPool(pool, &mMemoryPool->mDriverPool, mBuffer);
// }

s32 GPUMemBlockBase::addList(GPUMemBlockBase* block) {
    GPUMemBlockBase* last = this;
    s32 count = 1;
    while (last->mNext) {
        last = last->mNext;
        ++count;
    }
    last->mNext = block;
    return ++count;
}

void GPUMemBlockBase::setMemoryPool(void* buffer, u64 size, detail::MemoryPool* pool) {
    mBuffer = buffer;
    mSize = size;
    mMemoryPool = pool;
}

void GPUMemBlockBase::setMemoryPoolHeap(void* buffer, u64 size, detail::MemoryPoolHeap* pool_heap) {
    setMemoryPool(buffer, size, pool_heap->get_0x18());
    mMemoryPoolHeap = pool_heap;
    mMemoryPoolHeap->pushBack(this);
}

u64 GPUMemBlockBase::getByteOffset() const {
    return mMemoryPoolHeap ? sead::PtrUtil::diff(mBuffer, mMemoryPoolHeap->get_0x10()) : 0;
}

u32 GPUMemBlockBase::getMemoryPoolType() const {
    u32 type = mMemoryPool ? mMemoryPool->getType() : detail::MemoryPoolType::cInvalidPoolType;
    return type & ~detail::cGPUAccessMask;
}

}  // namespace agl
