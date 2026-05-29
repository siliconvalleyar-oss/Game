extern "C" {
    #include "../../lib/tinyPTC/src/tinyptc.h"
}
#include <iostream>
#include <algorithm>
#include <cstring>
#include "rendersystem.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

RenderSystem_t::RenderSystem_t(uint32_t w, uint32_t h)
    : m_w(w), m_h(h)
    , m_framebuffer(std::make_unique<uint32_t[]>(w * h)) {
    ptc_open("RetroMan", w, h);
}

RenderSystem_t::~RenderSystem_t() {
    ptc_close();
}

void RenderSystem_t::drawAllEntities(const Vect_t<Entity_t>& entities) const {
    auto screen = m_framebuffer.get();
    const auto screenWidth = m_w;
    
    for (const auto& entity : entities) {
        if (entity.sprite.empty() || entity.phy == nullptr) continue;
        
        uint32_t* dest = screen + entity.phy->y * screenWidth + entity.phy->x;
        for (uint32_t y = 0; y < entity.h && entity.phy->y + y < m_h; ++y) {
            for (uint32_t x = 0; x < entity.w && entity.phy->x + x < m_w; ++x) {
                size_t idx = y * entity.w + x;
                if (idx < entity.sprite.size()) {
                    dest[x] = entity.sprite[idx];
                }
            }
            dest += screenWidth;
        }
    }
}

bool RenderSystem_t::update(const GameContext_t& g) const {
    auto screen = m_framebuffer.get();
    const auto size = m_w * m_h;
    
    std::fill(screen, screen + size, 0xFF999999);
    drawAllEntities(g.getEntities());
    ptc_update(screen);
    return !ptc_process_events();
}

}
