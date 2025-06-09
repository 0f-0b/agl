#pragma once

#include <basis/seadTypes.h>

#include "common/aglTextureEnum.h"

namespace agl::detail {

class CompSel {
public:
    CompSel();
    void setDefault(TextureFormat);

private:
    s8 _0x0 = 2;
    s8 _0x1 = 3;
    s8 _0x2 = 4;
    s8 _0x3 = 5;
};

static_assert(sizeof(CompSel) == 0x4);

}  // namespace agl::detail
