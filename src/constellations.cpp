#include <optional>
#include <simple-2d/2d.h>
#include <simple-2d/setup.h>
#include <vector>

int width = 640;
int height = 480;
const char *title = "Constellations";

std::vector<CircleD> stars{};
std::optional<CircleD> current_star{};

void draw_from(CircleD &from) {
  for (auto &other : stars)
    if (&from != &other) {
      auto distance = 200 - from.center().distance(other.center());
      if (distance < 0)
        continue;
      line_width(distance / 40);
      color(1, 1, 1, distance / 200);
      line(from.center(), other.center());
    }
}

void update() {
  background(0, 0, 0);
  color(0, 0, 0, 1);
  rect(0, 0, width, height);

  for (auto &star : stars)
    draw_from(star);
  if (current_star)
    draw_from(*current_star);

  color(1, 1, 1, 1);
  for (auto &star : stars)
    circle(star);
  if (current_star)
    circle(*current_star);
}

void init(On on) {
  on.key_pressed = [](Key key, KeyMods mods) {
    if (key == Key::ESCAPE)
      exit(0);
    if (key == Key::SPACE)
      stars.clear();
  };
  on.mouse_pressed = [](Mouse button, KeyMods mods) {
    if (button == Mouse::MB1) {
      current_star = CircleD{mouse_x, mouse_y, 10};
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