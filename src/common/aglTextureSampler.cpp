#include "common/aglTextureSampler.h"

#include "utility/aglPrimitiveTexture.h"

namespace agl {

TextureSampler::TextureSampler() {
    auto* primitive_texture = utl::PrimitiveTexture::instance();
    if (primitive_texture) {
        TextureSampler* sampler = primitive_texture->get(2);
        mTextureData = sampler->mTextureData;
        _0x160.setBitOn(0);
    }
}

}  // namespace agl
