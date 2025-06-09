#include "common/aglUniformBlock.h"

#include <nvn/nvn_FuncPtrInline.h>

namespace agl {

UniformBlock::UniformBlock() = default;

UniformBlock::~UniformBlock() {
    destroy();
}

void UniformBlock::destroy() {
    if (_0x42 & 4) {
        nvnBufferFinalize(&_0x48);
        _0x42 &= ~4;
    }

    _0x10 = nullptr;
    _0x18 = 0;
    _0x1c = 0;
    _0x20 = 0;

    if (_0x42 & 1) {
        delete *_0x8;
        delete _0x8;
        _0x42 &= ~1;
    }
    _0x8 = nullptr;

    if (_0x42 & 2) {
        if (mMemAddr.isValid()) {
            mMemAddr.deleteGPUMemBlock();
            mMemAddr.invalidate();
        }
        _0x42 &= ~2;
    }
}

}  // namespace agl
