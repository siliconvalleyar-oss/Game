#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>

namespace ECS {
struct InputSystem_t {
    bool isKeyPressed(KeySym key) const { return false; }
};
}
