#pragma once

#include <nvn/nvn.h>
#include <heap/seadHeap.h>
#include <math/seadVector.h>

#include "common/aglGPUMemAddr.h"

namespace al {
class UniformBlockSetter;
}

namespace agl {
class DrawContext;
class ShaderLocation;

class UniformBlock {
public:
    enum class Type { _6 = 6 };

    UniformBlock();
    virtual ~UniformBlock();
    void destroy();
    void startDeclare(s32, sead::Heap*);
    void declare_(Type, s32, u64, u64);
    void declare(const UniformBlock&);
    void calcRequiredBufferSize(s32, s32) const;
    void create(sead::Heap*, s32, s32);
    void setBuffer(GPUMemVoidAddr, s32, s32);
    void createWithBuffer(GPUMemVoidAddr, s32, s32);
    void createWithoutBuffer();
    void createDirect(GPUMemVoidAddr, u64);
    void copyAllTo(UniformBlock*, s32, s32) const;
    void copyPartialTo(UniformBlock*, s32, s32, s32, s32, s32, s32) const;
    void fill(u32, s32);
    void writeMemory(u32*, const u32*, s32, s32, s32, const void*);
    void dcbz(s32) const;
    void dcbz(u32, s32) const;
    virtual void invalidateGPUCache(DrawContext*, s32) const;
    inline void setUniform(DrawContext*, const u64&, const ShaderLocation&, u32, u64) const;

    void setV4f(s32 _w1, const sead::Vector4f& vec) const { setData_(_0x10, _w1, &vec, 0, 1); }

    void flush(s32 _w1) const {
        mMemAddr.offset((_0x41 * _0x44 + _w1) * _0x1c).flushCPUCache(_0x18);
    }

protected:
    virtual void getStrideArray_(u8) const;
    virtual void getBlockAlignment_() const;
    virtual void getBlockSizeMax_() const;
    virtual void verifyStructSize_(u32) const;
    virtual void bindBufferNVN_(NVNcommandBuffer*, NVNshaderStage, s32, u64, u64) const;

private:
    // TODO hack
    friend class al::UniformBlockSetter;

    void setData_(void*, s32, const void*, s32, s32) const;
    void setDataStruct_(void*, s32, const void*, s32, s32, u32) const;

    u8** _0x8 = nullptr;
    void* _0x10 = nullptr;
    u32 _0x18 = 0;
    s32 _0x1c = 0;
    s32 _0x20 = 0;
    GPUMemAddrBase mMemAddr;
    bool _0x40 = true;
    u8 _0x41 = 0;
    u8 _0x42 = 0;
    u16 _0x44 = 1;
    NVNbuffer _0x48 alignas(8);
};

static_assert(sizeof(UniformBlock) == 0x78);

}  // namespace agl
