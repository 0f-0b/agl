#include "common/aglGPUMemAddr.h"

namespace agl {

GPUMemAddrBase::GPUMemAddrBase(const GPUMemBlockBase& mem_block, u64 offset)
    : mOffset(offset), mMemBlock(&mem_block) {
    mMemoryPool = mMemBlock->getMemoryPool();
    mOffset = mMemBlock->getByteOffset() + offset;
    verify_();
}

u32 GPUMemAddrBase::verify_() const {
    if (mMemBlock) {
        if (mMemBlock->getSize() == 0) {
            if (mMemoryPool)
                return 2;
        } else {
            if (mMemBlock->getEnd() < mOffset)
                return 1;
            if (mMemBlock->getMemoryPool() != mMemoryPool)
                return 2;
        }
    }
    return 0;
}

void GPUMemAddrBase::deleteGPUMemBlock() const {
    delete mMemBlock;
}

void GPUMemAddrBase::invalidate() {
    mMemoryPool = nullptr;
    mOffset = 0;
    mMemBlock = nullptr;
}

s32 GPUMemAddrBase::getAlignmentAddress() const {
    return mOffset;
}

void GPUMemAddrBase::setByteOffsetByPtr(void* ptr) {
    mOffset = sead::PtrUtil::diff(ptr, mMemoryPool ? mMemoryPool->map() : nullptr);
}

void GPUMemAddrBase::roundUp(s32 alignment) {
    mOffset = (mOffset + alignment - 1) & -alignment;
}

void GPUMemAddrBase::flushCPUCache(u64 size) const {
    if (mMemoryPool && mMemoryPool->isCPUCached())
        mMemoryPool->flushMappedRange(mOffset, size);
}

void GPUMemAddrBase::invalidateCPUCache(u64 size) const {
    if (mMemoryPool && mMemoryPool->isCPUCached())
        mMemoryPool->invalidateMappedRange(mOffset, size);
}

}  // namespace agl
