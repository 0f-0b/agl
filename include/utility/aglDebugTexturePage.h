#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIOReflexible.h>

namespace agl::utl {

class DebugTexturePage : public sead::IDisposer {
public:
    DebugTexturePage();
    void setUp(u32, const sead::SafeString&, sead::Heap* heap);
    void cleanUp();
    void genMessage(sead::hostio::Context* context);
    void genMessagePage_(sead::hostio::Context* context, sead::hostio::Reflexible* reflexible,
                         sead::hostio::PropertyEventListener* listener);
    void genMessagePage(sead::hostio::Context* context, sead::hostio::Reflexible* reflexible);

private:
    sead::hostio::PropertyEventListener _0x20;
    void* _padding_0x28[0x43];
};

static_assert(sizeof(DebugTexturePage) == 0x240);

}  // namespace agl::utl
