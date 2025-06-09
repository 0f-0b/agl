#pragma once

#include <nn/gfx/gfx_Types.h>
#include <prim/seadSafeString.h>

#include "common/aglGPUMemAddr.h"
#include "detail/aglSurface.h"
#include "driver/aglNVNtexture.h"

namespace agl {
class DrawContext;

// TODO
struct TextureCompSel {};

class TextureData {
public:
    TextureData();

    void initialize_(TextureType, TextureFormat, u32, u32, u32, u32, TextureAttribute,
                     MultiSampleType, bool);
    void initializeSize_(u32, u32, u32);
    void setMipLevelNum_(u32, bool);
    void getMinHeight_() const;
    u16 getMinSlice_() const;
    void getTextureFormatName() const;
    u32 calcMipByteSize(u32) const;
    bool isCompressedFormat() const;
    bool isRenderTargetCompressAvailable() const;
    bool isDepthFormat() const;
    bool hasStencil() const;
    void invalidateCPUCache() const;
    void flushCPUCache() const;
    void copyToAll(DrawContext* ctx, const TextureData* data) const;
    void copyTo_(DrawContext* ctx, const TextureData* data, s32, s32, s32, s32, bool) const;
    void copyTo(DrawContext* ctx, const TextureData* data, s32, s32) const;
    void copyTo(DrawContext* ctx, const TextureData* data, s32, s32, s32, s32) const;
    void compressTo(DrawContext* ctx, const TextureData* data, s32, s32) const;
    void compressTo(DrawContext* ctx, const TextureData* data, s32, s32, s32, s32) const;
    void compressToHQ(DrawContext* ctx, const TextureData* data, s32, s32) const;
    void compressToHQ(DrawContext* ctx, const TextureData* data, s32, s32, s32, s32) const;
    void setDebugLabel(const sead::SafeString& label);
    void getDebugLabel() const;
    void compressToAll(DrawContext* ctx, const TextureData* data) const;

    class CompressToWork {
    public:
        explicit CompressToWork(const TextureData& data);

        void* _0;
        void* _8;
        void* _10;
        void* _18;
        u32 _20;
        void* _28;
        void* _30;
        u32 _38;
        void* _40;
        detail::Surface mSurface;
        driver::NVNtexture_ mTexture;
    };

    void compressTo_(DrawContext* ctx, CompressToWork&, bool) const;
    void compressToAllHQ(DrawContext* ctx, const TextureData* data) const;
    void compressToForce(DrawContext* ctx, const TextureData* data, s32, s32, s32, s32, s32,
                         s32) const;
    void generateMipMap(DrawContext* ctx) const;
    void generateMipMapMinMax(DrawContext* ctx, bool) const;
    void setImagePtr(GPUMemVoidAddr, u32);
    void updateNVNtexture();
    void shareImagePtr(const TextureData&);
    void setMipPtr(GPUMemVoidAddr);
    void setCompSel(TextureCompSel, TextureCompSel, TextureCompSel, TextureCompSel);
    void setCompSelDefault();
    void initializeFromNVNtexture(const NVNtexture&);
    void initializeNVNtexture(NVNtexture*, GPUMemVoidAddr) const;
    void updateNVNtextureView(const NVNtextureView*);
    void initializeNVNtextureBuilder(NVNtextureBuilder*) const;
    void initializeGfxTexture(nn::gfx::Texture*) const;
    void forceChangeUNormToSRGB();
    void forceChangeSRGBToUNorm();
    bool isSRGB() const;
    bool isUNorm() const;
    bool isEnableChangeToSRGB() const;
    bool isEnableChangeToUNorm() const;
    void initializeCubeMapArray(TextureFormat, u32, u32, u32, u32, TextureAttribute);

    GPUMemAddr<void> getAddr() const { return mAddr; }

private:
    GPUMemAddr<void> mAddr;
    void* _0x18;
    void* _0x20;
    void* _0x28;
    detail::Surface mSurface;
    TextureFormat mTextureFormat;
    s8 _0x55;
    s8 _0x56;
    driver::NVNtexture_ mTexture;
    const char* mDebugLabel;  // "TextureData string"
};

static_assert(sizeof(TextureData) == 0x128);

}  // namespace agl
