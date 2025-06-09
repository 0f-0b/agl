#include "utility/aglDebugTexturePage.h"

namespace agl::utl {

void DebugTexturePage::genMessage(sead::hostio::Context* context) {
    genMessagePage_(context, nullptr, nullptr);
}

void DebugTexturePage::genMessagePage(sead::hostio::Context* context,
                                      sead::hostio::Reflexible* reflexible) {
    genMessagePage_(context, reflexible, &_0x20);
}

}  // namespace agl::utl
