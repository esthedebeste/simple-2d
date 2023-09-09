#include <iostream>
#include <simple-2d/2d.h>
#include <simple-2d/image.h>
#include <simple-2d/setup.h>

int width = 640;
int height = 480;
const char *title = ":3Hop";
Image colon3;

void init(On on) {
  auto maybe_colon3 = load_image("../assets/colon3.png");
  if (!maybe_colon3) {
    std::cerr << "Could not load image" << std::endl;
    exit(1);
  }
  colon3 = *maybe_colon3;
  on.key_pressed = [](Key key, KeyMods mods) {
    if (key == Key::ESCAPE) {
      exit(0);
    }
  };
}
void update() {
  background(1, 1, 1);
  auto y = std::abs(std::sin(current_time * 5) * (height / 16));
  image(colon3, 0, y, width, height / 4 * 3);
}
