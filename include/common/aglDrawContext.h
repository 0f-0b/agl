#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadDrawContext.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>

#include "common/aglShaderEnum.h"

namespace agl {

class RenderBuffer;
class DisplayList;
enum ShaderOptimizeType {};

class DrawContext : public sead::DrawContext {
    SEAD_RTTI_OVERRIDE(DrawContext, sead::DrawContext)
public:
    DrawContext();
    ~DrawContext() override;

    void setCommandBuffer(DisplayList* buffer);
    void flushCommandBuffer();
    void setBoundRenderBuffer(const RenderBuffer* buffer);
    void barrierTexture(u32 flags);
    void barrierShader(u32 flags);
    bool isTextureDirty(u32 unused, s32 index) const;
    void setTextureDirty(s32 index);
    void changeShaderType(ShaderMode mode, ShaderOptimizeType optimizeType);
    void setCommandBufferTemporary();

private:
    void* _padding[0x18];
};

static_assert(sizeof(DrawContext) == 0x1b0);

}  // namespace agl
