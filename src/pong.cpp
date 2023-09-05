#include <simple-2d/2d.h>
#include <simple-2d/setup.h>

const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 80;
const int BALL_SIZE = 15;
const double MOVE_SPEED = 4.25;
const double BALL_SPEED = 5;

int width = 640;
int height = 480;
const char *title = "Pong";

double player_y = height / 2 - PADDLE_HEIGHT / 2;
double ai_y = height / 2 - PADDLE_HEIGHT / 2;

double ball_x = width / 2;
double ball_y = height / 2;
double ball_xvel = BALL_SPEED;
double ball_yvel = BALL_SPEED;

void reset() {
  player_y = height / 2 - PADDLE_HEIGHT / 2;
  ai_y = height / 2 - PADDLE_HEIGHT / 2;
  ball_x = width / 2;
  ball_y = height / 2;
  ball_xvel = BALL_SPEED;
  ball_yvel = BALL_SPEED;
}

void init(On on) {
  on.key_pressed = [](Key key, KeyMods mods) {
    if (key == Key::R)
      reset();
    else if (key == Key::ESCAPE)
      exit(0);
  };
}

void update() {
  double delta_multiplier =
      delta_time * (60 + (current_time - start_time) / 100);

  int player_x = 40 - PADDLE_WIDTH;
  int ai_x = width - 40;

  background(0.2, 0.2, 0.2);
  if (is_pressed(Key::W) || is_pressed(Key::UP))
    player_y += MOVE_SPEED * delta_multiplier;
  if (is_pressed(Key::S) || is_pressed(Key::DOWN))
    player_y -= MOVE_SPEED * delta_multiplier;
  // Draw player paddle
  color(0, 1, 0);
  auto player_rect =
      RectD::fromLBWH(player_x, player_y, PADDLE_WIDTH, PADDLE_HEIGHT);
  rect(player_rect);

  if (ball_y > ai_y + PADDLE_HEIGHT / 2)
    ai_y += MOVE_SPEED * delta_multiplier;
  if (ball_y < ai_y + PADDLE_HEIGHT / 2)
    ai_y -= MOVE_SPEED * delta_multiplier;
  // Draw AI paddle
  color(1, 0, 0);
  auto ai_rect = RectD::fromLBWH(ai_x, ai_y, PADDLE_WIDTH, PADDLE_HEIGHT);
  rect(ai_rect);

  // Draw ball
  ball_x += ball_xvel * delta_multiplier;
  ball_y += ball_yvel * delta_multiplier;
  CircleD ball_circle(ball_x, ball_y, BALL_SIZE);
  if (ball_y + BALL_SIZE >= height)
    ball_yvel = -abs(ball_yvel);
  if (ball_y - BALL_SIZE <= 0)
    ball_yvel = abs(ball_yvel);

  if (ball_circle.intersects(player_rect)) {
    ball_xvel = abs(ball_xvel);
    auto player_middle = player_y + PADDLE_HEIGHT / 2;
    if (ball_y > player_middle)
      ball_yvel = abs(ball_yvel); // go up
    if (ball_y < player_middle)
      ball_yvel = -abs(ball_yvel); // go down
  }

  if (ball_circle.intersects(ai_rect)) {
    ball_xvel = -abs(ball_xvel);
    auto ai_middle = ai_y + PADDLE_HEIGHT / 2;
    if (ball_y > ai_middle)
      ball_yvel = abs(ball_yvel); // go up
    if (ball_y < ai_middle)
      ball_yvel = -abs(ball_yvel); // go down
  }

  color(1, 1, 1);
  circle(ball_circle);
  if (!ball_circle.intersects(RectD::fromLBWH(0, 0, width, height))) {
    reset();
  }
}
