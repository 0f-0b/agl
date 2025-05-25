#pragma once

#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrInline.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "common/aglGPUCommon.hpp"

namespace agl {
class GPUMemBlockBase;

namespace detail {

using MemoryPoolDriverBitFlag = sead::BitFlag32;

constexpr s32 cGPUAccessMask = 0xF0000000;
constexpr u64 cGPUPhysicalMemorySizeAlignment = 0x1000;

class MemoryPoolType : public MemoryPoolDriverBitFlag {
public:
    MemoryPoolType() : MemoryPoolDriverBitFlag() {}
    MemoryPoolType(s32 p_value) : MemoryPoolDriverBitFlag(p_value) {}

    static MemoryPoolType convert(MemoryAttribute attribute);

    bool IsValid() const { return (*this & cValidPoolType) == cValidPoolType; }

    void MarkValid() { *this = *this | cValidPoolType; }

    static const MemoryPoolType cInvalidPoolType;
    static const MemoryPoolType cValidPoolType;
};

class MemoryPool {
public:
    MemoryPool();

    void initialize(void* buffer, u64 size, const MemoryPoolType& flags);
    void initialize(void* buffer, u64 size, const MemoryPoolType& flags, const MemoryPool& parent,
                    s32 alignment);

    void finalize();

    void* map() const { return nvnMemoryPoolMap(&mDriverPool); }

    void flushMappedRange(u64 offset, u64 size) const {
        return nvnMemoryPoolFlushMappedRange(&mDriverPool, offset, size);
    }

    void invalidateMappedRange(u64 offset, u64 size) const {
        return nvnMemoryPoolInvalidateMappedRange(&mDriverPool, offset, size);
    }

    bool isCPUCached() const {
        return nvnMemoryPoolGetFlags(&mDriverPool) & NVN_MEMORY_POOL_FLAGS_CPU_CACHED;
    }

    const MemoryPoolType& getType() const { return mMemoryType; }

private:
    NVNmemoryPool mDriverPool;
    MemoryPoolType mMemoryType;
    uint32_t idk;
};
static_assert(sizeof(MemoryPool) == 0x108);

class GPUMemBlockMgrHeapEx : public sead::hostio::Node, public sead::IDisposer {
public:
    GPUMemBlockMgrHeapEx(sead::Heap* p_heap);
    ~GPUMemBlockMgrHeapEx() override;

    void finalize();

private:
    s32 mAllowSharing;
    void* m08;
    void* m10;
    sead::CriticalSection mCS;
};
static_assert(sizeof(GPUMemBlockMgrHeapEx) == 0x80);

enum class GPUMemBlockMgrFlags : u8 {
    MemoryPoolRelated = 1 << 0,
    EnablePoolSharing = 1 << 1,
    Debug = 1 << 2
};

class GPUMemBlockMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(GPUMemBlockMgr)
public:
    GPUMemBlockMgr();
    virtual ~GPUMemBlockMgr();

    void initialize(sead::Heap* heap1, sead::Heap* heap2);
    bool tryAllocMemory(GPUMemBlockBase*, sead::Heap*, u64, s32, MemoryAttribute);
    void enableSharedMemoryPool(bool enabled);
    static u64 calcGPUMemorySize(u64 userSize);
    static s32 calcGPUMemoryAlignment(s32 userAlignment);

#ifdef SEAD_DEBUG
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event) override;
    void genMessage(sead::hostio::Context* context) override;
#endif

private:
    GPUMemBlockMgrHeapEx* findGPUMemBlockMgrHeapEx_(sead::Heap* p_heap, int* p_outIndex);

    sead::CriticalSection mCS;
    sead::PtrArray<GPUMemBlockMgrHeapEx> mMngrHeaps;
    size_t mMinBlockSize;
    sead::TypedBitFlag<GPUMemBlockMgrFlags> mFlags;
};
static_assert(sizeof(GPUMemBlockMgr) == 0x88);

}  // namespace detail
}  // namespace agl
