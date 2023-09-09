#include <optional>
#include <simple-2d/2d.h>
#include <simple-2d/random.h>
#include <simple-2d/setup.h>
#include <vector>

int width = 640;
int height = 480;
const char *title = "Constellations";

float star_r = 1, star_g = 1, star_b = 1;
struct Star;
extern std::vector<Star> stars;
struct Star : CircleD {
  double time_created;
  void draw_star() {
    push_matrix();
    translate(center());
    rotate((current_time - time_created) * 180 *
           (std::fmod(time_created, 2) - 1));
    circle(.3, 0, radius());
    pop_matrix();
  }
  void draw_lines() {
    for (auto &other : stars)
      if (this != &other) {
        auto distance = 200 - center().distance(other.center());
        if (distance < 0)
          continue;
        line_width(distance / 40);
        color(star_r, star_g, star_b, distance / 200);
        line(center(), other.center());
      }
  }
};
std::vector<Star> stars{};
std::optional<Star> current_star{};

void update() {
  background(0, 0, 0);
  color(0, 0, 0, 1);
  rect(0, 0, width, height);

  for (auto &star : stars)
    star.draw_lines();
  if (current_star)
    current_star->draw_lines();

  color(star_r, star_g, star_b, 1);
  for (auto &star : stars)
    star.draw_star();
  if (current_star)
    current_star->draw_star();
}

void init(On on) {
  on.key_pressed = [](Key key, KeyMods mods) {
    if (key == Key::ESCAPE)
      exit(0);
    if (key == Key::SPACE)
      stars.clear();
    if (key == Key::R) {
      float r = random(), g = random(), b = random();
      star_r = r / std::max(r, std::max(g, b));
      star_g = g / std::max(r, std::max(g, b));
      star_b = b / std::max(r, std::max(g, b));
    }
  };
  on.mouse_pressed = [](Mouse button, KeyMods mods) {
    if (button == Mouse::MB1) {
      current_star = Star{CircleD{mouse_x, mouse_y, 10}, current_time};
    }
  };
  on.mouse_moved = [](double x, double y) {
    if (current_star) {
      current_star->x(x);
      current_star->y(y);
    }
  };
  on.mouse_released = [](Mouse button, KeyMods mods) {
    if (button == Mouse::MB1) {
      if (current_star) {
        stars.push_back(*current_star);
        current_star = std::nullopt;
      }
    }
  };
}