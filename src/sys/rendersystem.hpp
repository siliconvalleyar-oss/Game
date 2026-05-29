#pragma once
#include <cstdint>
#include <memory>
#include <algorithm>
#include "../util/typealiases.hpp"
#include "../cmp/entity.hpp"

namespace ECS {

struct GameContext_t;

struct RenderSystem_t {
    explicit RenderSystem_t(uint32_t w, uint32_t h);
    ~RenderSystem_t();
    bool update(const GameContext_t& g) const;
    void drawAllEntities(const Vect_t<Entity_t>& entities) const;

private:
    const uint32_t m_w { 0 }, m_h { 0 };
    mutable std::unique_ptr<uint32_t[]> m_framebuffer{ nullptr };
};

}
