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
    ptc_open("RetroMan - Juego con Jugador y Enemigos", w, h);
}

RenderSystem_t::~RenderSystem_t() {
    ptc_close();
}

void RenderSystem_t::drawAllEntities(const Vect_t<Entity_t>& entities) const {
    auto screen = m_framebuffer.get();
    const auto screenWidth = m_w;
    
    for (const auto& entity : entities) {
        if (!entity.active || entity.sprite.empty()) continue;
        
        for (uint32_t y = 0; y < entity.h && entity.y + y < m_h; ++y) {
            uint32_t* dest = screen + (entity.y + y) * screenWidth + entity.x;
            for (uint32_t x = 0; x < entity.w && entity.x + x < m_w; ++x) {
                size_t idx = y * entity.w + x;
                if (idx < entity.sprite.size()) {
                    dest[x] = entity.sprite[idx];
                }
            }
        }
    }
    
    // Dibujar HUD
    int hudY = 5;
    int hudX = 5;
    for (int i = 0; i < 200; i++) {
        screen[hudY * m_w + hudX + i] = 0xFFFFFFFF;
    }
    for (int i = 0; i < 20; i++) {
        screen[(hudY + i) * m_w + hudX] = 0xFFFFFFFF;
        screen[(hudY + i) * m_w + hudX + 200] = 0xFFFFFFFF;
    }
    for (int i = 0; i < 200; i++) {
        screen[(hudY + 20) * m_w + hudX + i] = 0xFFFFFFFF;
    }
}

bool RenderSystem_t::update(const GameContext_t& g) const {
    auto screen = m_framebuffer.get();
    const auto size = m_w * m_h;
    
    // Fondo negro
    std::fill(screen, screen + size, 0xFF000000);
    
    drawAllEntities(g.getEntities());
    ptc_update(screen);
    return !ptc_process_events();
}

}
