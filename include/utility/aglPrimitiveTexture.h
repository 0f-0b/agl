#pragma once

#include <hostio/seadHostIONode.h>

#include "utility/aglDebugTexturePage.h"

namespace agl {
class TextureSampler;

namespace utl {

class PrimitiveTexture : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(PrimitiveTexture)
    PrimitiveTexture();
    virtual ~PrimitiveTexture();
    void destroy_();

public:
    void initialize(sead::Heap* heap);
    void entryDebugPage();
    void genMessage(sead::hostio::Context* context);
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event);

    TextureSampler* get(s32 index) { return mSamplers[index]; }

private:
    TextureSampler* mSamplers[26];
    DebugTexturePage mDebugPage;
};

static_assert(sizeof(PrimitiveTexture) == 0x338);

}  // namespace utl
}  // namespace agl
