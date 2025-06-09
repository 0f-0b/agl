#pragma once

#include <basis/seadTypes.h>

#include "detail/aglGPUMemBlockMgr.h"

namespace agl {
class GPUMemBlockBase;

namespace detail {
class GPUMemBlockMgrHeapEx;
class MemoryPoolType;

class MemoryPoolHeap {
public:
    MemoryPoolHeap(void*, u64, u64, const MemoryPoolType&, void*, u64, GPUMemBlockMgrHeapEx*);
    ~MemoryPoolHeap();

    static MemoryPoolHeap* create(u64, s32, u64, s32, u64, u64, const MemoryPoolType&,
                                  GPUMemBlockMgrHeapEx*);
    static void destroy(MemoryPoolHeap*);

    void pushBack(GPUMemBlockBase*);
    u64* allocFromMemoryPool(u64, s32);
    void freeToHeap(GPUMemBlockBase*);
    bool isAllocatable(const MemoryPoolType&, u64, s32) const;

    void* get_0x10() { return _0x10; }

    MemoryPool* get_0x18() { return &_0x18; }

private:
    void* _padding_0x0[0x2];
    void* _0x10;
    MemoryPool _0x18;
    void* _padding_0x120[0x2];
};

// TODO not sure
static_assert(sizeof(MemoryPoolHeap) == 0x130);

}  // namespace detail
}  // namespace agl
