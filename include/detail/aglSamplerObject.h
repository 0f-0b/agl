#pragma once

#include <gfx/seadColor.h>

namespace agl::detail {

class SamplerObject {
public:
    SamplerObject();

    void set_0x0(const sead::Color4f& color) { _0x0 = color; }

    void set_0x1c() {
        _0x1c = true;
        _0x1d = true;
        _0x1e = 0;
    }

    void set_0x1f(s8 _w0) {
        _0x1f = _w0;
        _0x20 = _w0;
        _0x21 = _w0;
    }

private:
    sead::Color4f _0x0 = {0, 0, 0, 1};
    s32 _0x10 = 0;
    f32 _0x14 = 14;
    s32 _0x18 = 0;
    bool _0x1c = true;
    bool _0x1d = true;
    s8 _0x1e = 2;
    s8 _0x1f = 7;
    s8 _0x20 = 7;
    s8 _0x21 = 7;
    bool _0x22 = true;
    bool _0x23 = true;
};

static_assert(sizeof(SamplerObject) == 0x24);

}  // namespace agl::detail
