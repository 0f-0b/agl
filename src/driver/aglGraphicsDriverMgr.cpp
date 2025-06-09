#include "driver/aglGraphicsDriverMgr.h"

#include "common/aglDrawContext.h"

namespace agl::driver {
SEAD_SINGLETON_DISPOSER_IMPL(GraphicsDriverMgr)

GraphicsDriverMgr::GraphicsDriverMgr() {
    mDefaultCommandBuffer = nullptr;
    _30 = nullptr;
}

GraphicsDriverMgr::~GraphicsDriverMgr() = default;

void GraphicsDriverMgr::waitDrawDone() const {
    DrawContext draw_context;
    draw_context.setCommandBufferTemporary();
    waitDrawDone(&draw_context);
}
}  // namespace agl::driver
