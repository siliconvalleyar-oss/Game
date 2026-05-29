#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>

namespace ECS {

struct InputSystem_t {
    bool left { false }, right { false }, up { false }, down { false };
    bool space { false };
    
    void update() {
        // Usar X11 para input no bloqueante
        Display* display = XOpenDisplay(nullptr);
        if (display) {
            XQueryKeymap(display, keys);
            left = keys[KeyCodeToIndex(XK_Left)];
            right = keys[KeyCodeToIndex(XK_Right)];
            up = keys[KeyCodeToIndex(XK_Up)];
            down = keys[KeyCodeToIndex(XK_Down)];
            space = keys[KeyCodeToIndex(XK_space)];
            XCloseDisplay(display);
        }
    }
    
private:
    char keys[32];
    
    int KeyCodeToIndex(KeySym ks) {
        Display* d = XOpenDisplay(nullptr);
        if (!d) return 0;
        KeyCode kc = XKeysymToKeycode(d, ks);
        XCloseDisplay(d);
        return (kc >> 3);
    }
};

}
