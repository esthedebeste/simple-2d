#include <cmath>
#include <numbers>
#include <simple-2d/2d.h>
#include <simple-2d/gl.h>

void color(float r, float g, float b) { glColor3f(r, g, b); }
void color(float r, float g, float b, float a) { glColor4f(r, g, b, a); }
void line_width(float width) { glLineWidth(width); }
void rect(int x, int y, int w, int h) { rect(RectI::fromXYWH(x, y, w, h)); }
void rect(Vec2I pos, int w, int h) {
  rect(RectI::fromXYWH(pos.x(), pos.y(), w, h));
}
void rect(RectI rect) {
  glBegin(GL_TRIANGLES);
  // bottom-left triangle '|\'
  glVertex3i(rect.left(), rect.top(), 0);
  glVertex3i(rect.left(), rect.bottom(), 0);
  glVertex3i(rect.right(), rect.bottom(), 0);
  // top-right triangle `\|'
  glVertex3i(rect.right(), rect.bottom(), 0);
  glVertex3i(rect.right(), rect.top(), 0);
  glVertex3i(rect.left(), rect.top(), 0);
  glEnd();
}

constexpr double two_pi = std::numbers::pi * 2;
void circle(int x, int y, int radius, int iters) {
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= iters; i++)
    glVertex2f(x + (radius * std::cos(i * two_pi / iters)),
               y + (radius * std::sin(i * two_pi / iters)));
  glEnd();
}
void circle(Vec2I center, int radius, int iters) {
  circle(center.x(), center.y(), radius, iters);
}
void circle(CircleI circle_, int iters) {
  circle(circle_.x(), circle_.y(), circle_.radius(), iters);
}

void background(float r, float g, float b) {
  glClearColor(r, g, b, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}
void line(int x1, int y1, int x2, int y2) {
  glBegin(GL_LINES);
  glVertex2i(x1, y1);
  glVertex2i(x2, y2);
  glEnd();
}
void line(Vec2I p1, Vec2I p2) { line(p1.x(), p1.y(), p2.x(), p2.y()); }
void line(LineI line_) { line(line_.start(), line_.end()); }