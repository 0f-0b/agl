#pragma once

#include "common/aglGPUMemBlock.h"

namespace al {
class UniformBlockSetter;
}

namespace agl {

class GPUMemAddrBase {
public:
    GPUMemAddrBase() = default;
    GPUMemAddrBase(const GPUMemBlockBase& mem_block, u64 offset);
    void deleteGPUMemBlock() const;
    void invalidate();
    s32 getAlignmentAddress() const;
    void setByteOffsetByPtr(void* ptr);
    void roundUp(s32 alignment);
    void flushCPUCache(u64 size) const;
    void invalidateCPUCache(u64 size) const;

    GPUMemAddrBase offset(s32 offset) const { return {mMemoryPool, mOffset + offset, mMemBlock}; }

    bool _hasMemoryPool() const { return mMemoryPool != nullptr; }

private:
    // TODO hack
    friend class al::UniformBlockSetter;

    GPUMemAddrBase(detail::MemoryPool* memory_pool, u32 offset, const GPUMemBlockBase* mem_block)
        : mMemoryPool(memory_pool), mOffset(offset), mMemBlock(mem_block) {}
    u32 verify_() const;

    detail::MemoryPool* mMemoryPool = nullptr;
    u32 mOffset = 0;
    const GPUMemBlockBase* mMemBlock = nullptr;
};

template <typename T>
class GPUMemAddr : public GPUMemAddrBase {};

}  // namespace agl
