#include "utility/aglPrimitiveTexture.h"

#include <prim/seadEndian.h>
#include <time/seadTickSpan.h>

#include "common/aglTextureData.h"
#include "common/aglTextureSampler.h"

namespace agl::utl {

SEAD_SINGLETON_DISPOSER_IMPL(PrimitiveTexture)

PrimitiveTexture::PrimitiveTexture() {
    for (s32 i = 0; i < 26; ++i)
        mSamplers[i] = nullptr;
}

PrimitiveTexture::~PrimitiveTexture() {
    destroy_();
    mDebugPage.cleanUp();
}

void PrimitiveTexture::destroy_() {
    for (s32 i = 0; i < 26; ++i) {
        mSamplers[i]->getTextureData().getAddr().deleteGPUMemBlock();
        delete mSamplers[i];
        mSamplers[i] = nullptr;
    }
}

// 0x1dd13a0
const char* const DebugLabels[] = {
    "Black1D",    "Black1DArray",   "Black2D",     "Black2DArray",   "Black3D",
    "BlackCube",  "BlackCubeArray", "White2D",     "WhiteCubeArray", "Zero2D",
    "Zero1D",     "Zero1DArray",    "Zero2DArray", "Zero3D",         "Red2D",
    "Green2D",    "Blue2D",         "Gray2D",      "DarkRed2D",      "DarkGreen2D",
    "DarkBlue2D", "Depth32_0",      "Depth32_1",   "DepthShadow",    "DepthShadowArray",
    "MipLevel",
};

void PrimitiveTexture::initialize(sead::Heap* heap) {
    mDebugPage.setUp(1, "agl::utl::PrimitiveTexture", heap);

    TextureData _sp_0x70;

    // x0 = 1.0f
    // x1 = 20
    // x8 = DebugLabels
    // x9 = s64((sead::TickSpan::cFrequency * s128(0x431bde82d7b634db)) >> 82)
    // x10 = 29
    // x19 = 0xffffffef
    // x20 = (extern) 0x1dcea28
    // x21 = 29
    // x23 = 0
    // x25 = (static) 0x191afb8
    // x26 = 0x80000000
    // x27 = 0
    // x29 = sp+0x200
    // sp+0x20 = sead::TickSpan::cFrequency / 1000000
    // sp+0x28 = vtable for agl::GPUMemBlock<u8>
    // sp+0x30 = vtable for sead::SafeString
    // sp+0x38 = this
    // sp+0x48 = heap
    // sp+0x54 = s32(sead::TickSpan::cFrequency / 1000000)

    for (s32 i = 0; i < 26; ++i) {
        _sp_0x70.setDebugLabel(DebugLabels[i]);

        u32 rgba = 0;

        switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            asm("// 7ab914");
            rgba = sead::Endian::swapU32(0x000000ff);
            break;
        case 7:
        case 8:
            asm("// 7ab934");
            rgba = sead::Endian::swapU32(0xffffffff);
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            asm("// 7ab924");
            rgba = sead::Endian::swapU32(0x00000000);
            break;
        case 14:
            asm("// 7aba84");
            rgba = sead::Endian::swapU32(0xff0000ff);
            break;
        case 15:
            asm("// 7aba90");
            rgba = sead::Endian::swapU32(0x006400ff);
            break;
        case 16:
            asm("// 7abaa4");
            rgba = sead::Endian::swapU32(0x0000ffff);
            break;
        case 17:
            asm("// 7abab0");
            rgba = sead::Endian::swapU32(0x808080ff);
            break;
        case 18:
            asm("// 7abac0");
            rgba = sead::Endian::swapU32(0x8b0000ff);
            break;
        case 19:
            asm("// 7abad0");
            rgba = sead::Endian::swapU32(0x006400ff);
            break;
        case 20:
            asm("// 7abae0");
            rgba = sead::Endian::swapU32(0x00008bff);
            break;
        case 21:
            asm("// 7abaf4");
            break;
        case 22:
        case 23:
        case 24:
            asm("// 7ab94c");
            break;
        }

        switch (i) {
        case 0:
        case 10:
            asm("// 7ab9b4");
            break;
        case 1:
        case 11:
            asm("// 7ab9d8");
            break;
        case 2:
        case 7:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
            asm("// 7abaf4");
            break;
        case 3:
        case 12:
        case 24:
            asm("// 7ab97c");
            break;
        case 4:
        case 13:
            asm("// 7ab9f4");
            break;
        case 5:
            asm("// 7aba30");
            break;
        case 6:
        case 8:
            asm("// 7ab98c");
            break;
        case 9:
            asm("// 7aba50");
            break;
        }

        asm("// 7abaf4");
        GPUMemBlock<u8>* block = new (heap) GPUMemBlock<u8>;
        block->allocBuffer_(0, heap, 0, agl::MemoryAttribute::CpuCached);

        // sp+0x58
        GPUMemAddrBase addr{*block, 0};

        // 7abb78
        // x0 = addr
        // w21 = offset
        if (i == 25) {
        } else {
        }

        _sp_0x70.getMinHeight_();
        _sp_0x70.setImagePtr({nullptr, 0, nullptr}, 0);

        mSamplers[i] = new TextureSampler(_sp_0x70);
    }

    asm("// 7ab8b8");
}

void PrimitiveTexture::entryDebugPage() {}

void PrimitiveTexture::genMessage(sead::hostio::Context* context) {
    mDebugPage.genMessagePage(context, this);
}

}  // namespace agl::utl
