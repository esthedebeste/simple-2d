#pragma once
#include "gl.h"
#include "input.h"

struct Callbacks {
  void (*key_pressed)(Key key, KeyMods mods) = [](Key, KeyMods) {};
  void (*key_held)(Key key, KeyMods mods) = [](Key, KeyMods) {};
  void (*key_released)(Key key, KeyMods mods) = [](Key, KeyMods) {};
  void (*mouse_pressed)(Mouse button, KeyMods mods) = [](Mouse, KeyMods) {};
  void (*mouse_released)(Mouse button, KeyMods mods) = [](Mouse, KeyMods) {};
  void (*mouse_moved)(double x, double y) = [](double, double) {};
};
using On = Callbacks &;

// expected in the game .cpp itself
extern int width;
extern int height;
extern const char *title;
void init(Callbacks &on);
void update();

extern GLFWwindow *window;
/// The time that the program started, in seconds.
/// Not necessarily bound to an epoch.
extern double start_time;
/// The current time, in seconds.
/// Not necessarily bound to an epoch.
extern double current_time;
/// The time since the last frame, in seconds.
extern double delta_time;
