extern "C" {
    #include "../../lib/tinyPTC/src/tinyptc.h"
}
#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include "rendersystem.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

RenderSystem_t::RenderSystem_t(uint32_t w, uint32_t h)
    : m_w(w), m_h(h)
    , m_framebuffer(std::make_unique<uint32_t[]>(w * h)) {
    ptc_open("RetroMan - Juego con Assets", w, h);
}

RenderSystem_t::~RenderSystem_t() {
    ptc_close();
}

void RenderSystem_t::drawAllEntities(const Vect_t<Entity_t>& entities) const {
    auto screen = m_framebuffer.get();
    const auto screenWidth = m_w;
    
    for (const auto& entity : entities) {
        if (!entity.active || entity.sprite.empty()) continue;
        
        for (uint32_t y = 0; y < entity.h && (uint32_t)(entity.y + y) < m_h; ++y) {
            int destY = (int)(entity.y + y);
            if (destY < 0) continue;
            
            uint32_t* dest = screen + destY * screenWidth + (int)entity.x;
            for (uint32_t x = 0; x < entity.w && (uint32_t)(entity.x + x) < m_w; ++x) {
                size_t idx = y * entity.w + x;
                if (idx < entity.sprite.size()) {
                    uint32_t pixel = entity.sprite[idx];
                    if ((pixel >> 24) > 128) {
                        dest[x] = pixel;
                    }
                }
            }
        }
    }
}

bool RenderSystem_t::update(const GameContext_t& g) const {
    auto screen = m_framebuffer.get();
    const auto size = m_w * m_h;
    
    std::fill(screen, screen + size, m_bgColor);
    drawAllEntities(g.getEntities());
    
    // Mostrar puntuación simple
    std::string scoreText = "SCORE: " + std::to_string(g.getScore());
    for (size_t i = 0; i < scoreText.size() && i < 50; i++) {
        screen[20 * m_w + 10 + i * 8] = 0xFFFFFFFF;
        screen[20 * m_w + 10 + i * 8 + 1] = 0xFFFFFFFF;
    }
    
    ptc_update(screen);
    return !ptc_process_events();
}

}
