#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace agl {
class DrawContext;
class DisplayList;

enum class PrimitiveRestartIndex {};
}  // namespace agl

namespace agl::driver {

class GraphicsDriverMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(GraphicsDriverMgr)
public:
    GraphicsDriverMgr();
    virtual ~GraphicsDriverMgr();

    agl::DisplayList* getDefaultCommandBuffer();
    void waitDrawDone() const;
    void setPointLimits(agl::DrawContext* draw_context, float min, float max) const;
    void setPointSize(agl::DrawContext* draw_context, float point_size) const;
    void setLineWidth(agl::DrawContext* draw_context, float line_width) const;
    void setPrimitiveRestartIndex(agl::DrawContext* draw_context, agl::PrimitiveRestartIndex) const;
    void setDepthClamp(agl::DrawContext* draw_context, bool) const;
    void setPolygonOffset(agl::DrawContext* draw_context, float, float) const;

    virtual void dumpInfo() const {}

    virtual void waitDrawDone(agl::DrawContext*) const {}

#ifdef SEAD_DEBUG
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event) override;
    void genMessage(sead::hostio::Context* context) override;
#endif

protected:
    void initialize_(sead::Heap* p_heap);

private:
    agl::DisplayList* mDefaultCommandBuffer;
    void* _30;
};

static_assert(sizeof(GraphicsDriverMgr) == 0x38);

}  // namespace agl::driver
