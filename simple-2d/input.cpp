#include <simple-2d/input.h>
#include <simple-2d/setup.h>

double mouse_x, mouse_y;
bool is_pressed(Key key) { return glfwGetKey(window, key) == GLFW_PRESS; }

KeyMods::KeyMods(int mods) : mods{mods} {}
bool KeyMods::shift() { return (mods & GLFW_MOD_SHIFT) != 0; }
bool KeyMods::control() { return (mods & GLFW_MOD_CONTROL) != 0; }
bool KeyMods::alt() { return (mods & GLFW_MOD_ALT) != 0; }
bool KeyMods::super() { return (mods & GLFW_MOD_SUPER) != 0; }
bool KeyMods::caps_lock() { return (mods & GLFW_MOD_CAPS_LOCK) != 0; }
bool KeyMods::num_lock() { return (mods & GLFW_MOD_NUM_LOCK) != 0; }