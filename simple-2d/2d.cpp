#include <cmath>
#include <numbers>
#include <simple-2d/2d.h>
#include <simple-2d/gl.h>

void color(float r, float g, float b) { glColor3f(r, g, b); }
void color(float r, float g, float b, float a) { glColor4f(r, g, b, a); }
void line_width(float width) { glLineWidth(width); }
void rect(int x, int y, int w, int h) { rect(RectI::fromLBWH(x, y, w, h)); }
void rect(Vec2I pos, int w, int h) {
  rect(RectI::fromLBWH(pos.x(), pos.y(), w, h));
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
void circle(float x, float y, float radius, int iters) {
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= iters; i++)
    glVertex2f(x + (radius * std::cos(i * two_pi / iters)),
               y + (radius * std::sin(i * two_pi / iters)));
  glEnd();
}
void circle(Vec2F center, float radius, int iters) {
  circle(center.x(), center.y(), radius, iters);
}
void circle(CircleF circle_, int iters) {
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

void push_matrix() { glPushMatrix(); }
void pop_matrix() { glPopMatrix(); }
void translate(float x, float y) { glTranslatef(x, y, 0); }
void translate(Vec2F pos) { glTranslatef(pos.x(), pos.y(), 0); }
void rotate_x(float angle) { glRotatef(angle, 1, 0, 0); }
void rotate_y(float angle) { glRotatef(angle, 0, 1, 0); }
void rotate_z(float angle) { glRotatef(angle, 0, 0, 1); }
void rotate(float angle) { rotate_z(angle); }
void scale(float x, float y, float z) { glScalef(x, y, z); }
void scale(float scale) { glScalef(scale, scale, scale); }