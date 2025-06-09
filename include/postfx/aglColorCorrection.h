#pragma once

#include <hostio/seadHostIOCurve.h>
#include <hostio/seadHostIONode.h>

#include "utility/aglParameterIO.h"

namespace agl {
class DrawContext;
class RenderBuffer;
class TextureData;
class TextureSampler;

namespace pfx {

class ColorCorrection : public sead::hostio::Node, public utl::IParameterIO {
public:
    ColorCorrection();
    ~ColorCorrection() override;

    void resetAll();
    void initialize(s32, sead::Heap*, bool);

    void drawMap(DrawContext*) const;
    void draw(DrawContext*, s32, const RenderBuffer&) const;
    void draw(DrawContext*, s32, const RenderBuffer&, const TextureData&) const;
    void draw(DrawContext*, s32, const RenderBuffer&, const TextureSampler&) const;

    void genMessage(sead::hostio::Context*);
    void genMessageParameters(sead::hostio::Context*);
    void genMessageToyCameraParameters(sead::hostio::Context*);
    void genMessageHsbParameters(sead::hostio::Context*);
    void listenPropertyEvent(const sead::hostio::PropertyEvent*);
    void listenNodeEvent(const sead::hostio::NodeEvent*);

    void setHue(f32);
    void setSaturation(f32);
    void setBrightness(f32);
    void setGamma(f32);
    void setLevelCurve_(u32, sead::hostio::CurveType, const f32*, u32);
    void convRGB_(u32*, f32, f32, f32) const;
    void calcToyCamera_(f32*, f32*, f32*) const;
    void calcHue_(f32, f32, f32) const;
    void calcRGB_(u32*, f32, f32, f32) const;
    void calcSaturation_(f32*, f32*, f32*, f32) const;
    void calcContrast_(f32*, f32, f32) const;

private:
    void destroy_();
    void updateProgram_() const;
    void updateCurves_();
    void updateFlags_();
    void postRead_() override;
    void enablePassHue_() const;
    void enablePassSaturation_() const;
    void enablePassGamma_() const;
    void enablePassBrightness_() const;
    void updateMapCPU_();

    void* _padding[0x29e];
};

static_assert(sizeof(ColorCorrection) == 0x16c8);

}  // namespace pfx
}  // namespace agl
