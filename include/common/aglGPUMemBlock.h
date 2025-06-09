#pragma once

#include <nn/gfx/gfx_Types.h>
#include <heap/seadHeap.h>

#include "common/aglGPUCommon.hpp"
#include "detail/aglGPUMemBlockMgr.h"

namespace agl {
namespace detail {
class MemoryPool;
class MemoryPoolHeap;
}  // namespace detail

class GPUMemBlockBase {
public:
    GPUMemBlockBase();
    virtual ~GPUMemBlockBase();
    void clear();
    void freeBuffer();
    void free();
    void allocBuffer_(u64 size, sead::Heap* heap, s32 alignment, MemoryAttribute attribute);
    bool tryAllocBuffer_(u64 size, sead::Heap* heap, s32 alignment, MemoryAttribute attribute);
    void setBuffer_(u64 size, void* buffer, void* memory_pool_storage, MemoryAttribute attribute);
    void setVirtual_(u64 size, sead::Heap* heap, MemoryAttribute attribute, GPUMemVoidAddr parent,
                     s32 alignment);
    void initializeGfxMemoryPool(nn::gfx::MemoryPool*) const;
    s32 addList(GPUMemBlockBase*);
    void setMemoryPool(void* bufer, u64 size, detail::MemoryPool* pool);
    void setMemoryPoolHeap(void* bufer, u64 size, detail::MemoryPoolHeap* pool_heap);
    u64 getByteOffset() const;
    u32 getMemoryPoolType() const;

    u64 getSize() const { return mSize; }

    u64 getEnd() const { return getByteOffset() + getSize(); };

    detail::MemoryPool* getMemoryPool() const { return mMemoryPool; }

private:
    void* mBuffer;
    u64 mSize;
    detail::MemoryPool* mMemoryPool;
    detail::MemoryPoolHeap* mMemoryPoolHeap;
    u8 mFlags = 0;
    u16 mAlignment;
    GPUMemBlockBase* mNext;
};

static_assert(sizeof(GPUMemBlockBase) == 0x38);

template <typename T>
class GPUMemBlockT : public GPUMemBlockBase {
public:
    ~GPUMemBlockT() override { ; }
};

template <typename T>
class GPUMemBlock : public GPUMemBlockT<T> {
public:
    ~GPUMemBlock() override { ; }
};

}  // namespace agl
