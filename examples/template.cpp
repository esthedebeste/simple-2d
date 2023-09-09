#include <iostream>
#include <simple-2d/2d.h>
#include <simple-2d/setup.h>

int width = 640;
int height = 480;
const char *title = "Template";

void update() {}

void key_pressed(Key key, KeyMods mods) {
  if (key == Key::ESCAPE) {
    exit(0);
  }
}
void init(On on) {
  on.key_pressed = &key_pressed;
  on.mouse_pressed = [](Mouse button, KeyMods mods) {
    std::cout << "Mouse button " << button << " pressed" << std::endl;
  };
}