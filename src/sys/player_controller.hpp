#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include "../util/gamecontext.hpp"

namespace ECS {

struct PlayerController_t {
    bool left { false }, right { false }, up { false }, down { false };
    Display* display { nullptr };
    
    PlayerController_t() {
        display = XOpenDisplay(nullptr);
    }
    
    ~PlayerController_t() {
        if (display) XCloseDisplay(display);
    }
    
    void update(GameContext_t& g) {
        Entity_t* player = g.getPlayer();
        if (!player || !player->active) return;
        
        const float SPEED = 4.0f;
        
        if (!display) {
            display = XOpenDisplay(nullptr);
            if (!display) return;
        }
        
        char keys[32];
        XQueryKeymap(display, keys);
        
        auto isKeyPressed = [&](KeySym ks) -> bool {
            KeyCode kc = XKeysymToKeycode(display, ks);
            return (keys[kc >> 3] & (1 << (kc & 7))) != 0;
        };
        
        left = isKeyPressed(XK_Left);
        right = isKeyPressed(XK_Right);
        up = isKeyPressed(XK_Up);
        down = isKeyPressed(XK_Down);
        
        player->vx = 0;
        player->vy = 0;
        if (left) player->vx = -SPEED;
        if (right) player->vx = SPEED;
        if (up) player->vy = -SPEED;
        if (down) player->vy = SPEED;
    }
};

}
