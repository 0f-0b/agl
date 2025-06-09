#pragma once

#include <thread/seadAtomic.h>

#include "common/aglTextureData.h"
#include "detail/aglCompSel.h"
#include "detail/aglSamplerObject.h"
#include "driver/aglNVNsampler.h"

namespace agl {
class DrawContext;
class ShaderLocation;
class TextureData;

class TextureSampler {
public:
    TextureSampler();
    void applyTextureData(const TextureData& data);
    TextureSampler(const TextureData& data);
    void activate(DrawContext* ctx, const ShaderLocation& loc, s32, bool) const;
    void setReference() const;

    const TextureData& getTextureData() const { return mTextureData; }

    void set_0x138(const sead::Color4f& color) {
        _0x138.set_0x0(color);
        _0x160.setBitOn(5);
    }

    void set_0x154() {
        _0x138.set_0x1c();
        _0x160.setBitOn(2);
    }

    void set_0x157(s8 _w0) {
        _0x138.set_0x1f(_w0);
        _0x160.setBitOn(1);
    }

private:
    void initRegs_(u32) const;

    driver::NVNsampler_ _0x0;
    TextureData mTextureData;
    detail::SamplerObject _0x138;
    detail::CompSel _0x15c;
    sead::Atomic<u32> _0x160 = 0xff;
    s8 _0x164 = 32;
    const char* mDebugLabel = "agl::TextureSampler";
};

static_assert(sizeof(TextureSampler) == 0x170);

}  // namespace agl
