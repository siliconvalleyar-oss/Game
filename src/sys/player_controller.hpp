#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "../util/gamecontext.hpp"

namespace ECS {

struct PlayerController_t {
    bool left { false }, right { false }, up { false }, down { false };
    
    void update(GameContext_t& g) {
        Entity_t* player = g.getPlayer();
        if (!player) return;
        
        // Velocidad del jugador
        const int SPEED = 5;
        
        // Obtener estado del teclado
        Display* display = XOpenDisplay(nullptr);
        if (display) {
            char keys[32];
            XQueryKeymap(display, keys);
            
            auto isKeyPressed = [&](KeySym ks) -> bool {
                KeyCode kc = XKeysymToKeycode(display, ks);
                return (kc < 256) && (keys[kc >> 3] & (1 << (kc & 7)));
            };
            
            left = isKeyPressed(XK_Left);
            right = isKeyPressed(XK_Right);
            up = isKeyPressed(XK_Up);
            down = isKeyPressed(XK_Down);
            
            XCloseDisplay(display);
        }
        
        // Aplicar movimiento
        player->vx = 0;
        player->vy = 0;
        if (left) player->vx = -SPEED;
        if (right) player->vx = SPEED;
        if (up) player->vy = -SPEED;
        if (down) player->vy = SPEED;
    }
};

}
