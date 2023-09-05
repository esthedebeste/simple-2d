#pragma once
#include <cmath>

template <typename T> class Vec2 {
  T mx, my;

public:
  template <typename U>
  Vec2(Vec2<U> other)
      : mx(static_cast<T>(other.x())), my(static_cast<T>(other.y())) {}
  Vec2(T x, T y) : mx(x), my(y) {}
  Vec2() : mx(0), my(0) {}

  inline T x() { return mx; }
  inline void x(T x) { mx = x; }
  inline T y() { return my; }
  inline void y(T y) { my = y; }

  T distanceSq(Vec2<T> other) {
    T dx = mx - other.mx;
    T dy = my - other.my;
    return dx * dx + dy * dy;
  }

  T distance(Vec2<T> other) { return std::sqrt(distanceSq(other)); }

  inline Vec2<T> operator+(Vec2<T> other) {
    return Vec2<T>{mx + other.x(), my + other.y()};
  }
  inline Vec2<T> operator-(Vec2<T> other) {
    return Vec2<T>{mx - other.x(), my - other.y()};
  }
  inline Vec2<T> operator*(T scalar) {
    return Vec2<T>{mx * scalar, my * scalar};
  }
};

using Vec2I = Vec2<int>;
using Vec2F = Vec2<float>;
using Vec2D = Vec2<double>;

template <typename T> class Circle;
template <typename T> class Rect {
  T mleft, mtop, mright, mbottom;
  Rect(T left, T top, T right, T bottom)
      : mleft(left), mtop(top), mright(right), mbottom(bottom) {}

public:
  template <typename U>
  Rect(Rect<U> other)
      : mleft(static_cast<T>(other.left())), mtop(static_cast<T>(other.top())),
        mright(static_cast<T>(other.right())),
        mbottom(static_cast<T>(other.bottom())) {}

  /// @brief Creates a "zero" Rect
  /// @return a new Rect with all values set to 0
  inline Rect() : mleft(0), mtop(0), mright(0), mbottom(0) {}

  /// @brief Creates a Rect from left, top, right, bottom
  /// @param left the left x
  /// @param top the top y
  /// @param right the right x
  /// @param bottom the bottom y
  /// @return a new Rect
  inline static Rect<T> fromLTRB(T left, T top, T right, T bottom) {
    return Rect<T>{left, top, right, bottom};
  }
  /// @brief Creates a Rect from left, bottom, right, top
  /// @param left the left x
  /// @param bottom the bottom y
  /// @param right the right x
  /// @param top the top y
  /// @return a new Rect
  inline static Rect<T> fromLBRT(T left, T bottom, T right, T top) {
    return Rect<T>{left, top, right, bottom};
  }

  /// @brief Creates a Rect from x, y, w, h
  /// @param x the left x
  /// @param y the top y
  /// @param w the width of the rect
  /// @param h the height of the rect
  /// @return a new Rect
  inline static Rect<T> fromXYWH(T x, T y, T w, T h) {
    return Rect<T>{x, y, x + w, y + h};
  }

  /// @brief Creates a Rect from left, bottom, width, height
  /// @param x the left x
  /// @param y the bottom y
  /// @param w the width of the rect
  /// @param h the height of the rect
  /// @return a new Rect
  inline static Rect<T> fromLBWH(T x, T y, T w, T h) {
    return Rect<T>{x, y + h, x + w, y};
  }

  bool intersects(Rect<T> other) {
    return mleft < other.mright && mright > other.mleft &&
           mtop < other.mbottom && mbottom > other.mtop;
  }

  bool intersects(Circle<T> other) {
    T dx = other.x() - std::max(mleft, std::min(other.x(), mright));
    T dy = other.y() - std::max(mtop, std::min(other.y(), mbottom));
    T distanceSq = dx * dx + dy * dy;
    T radiusSq = other.radius() * other.radius();
    return distanceSq <= radiusSq;
  }

  /// @brief Shifts the Rect
  /// @param x the x to move to the right by
  /// @param y the y to move up by
  void shift(T x, T y) {
    mleft += x;
    mright += x;
    mtop += y;
    mbottom += y;
  }
  /// @brief Shifts the Rect
  /// @param pos the position to shift by
  void shift(Vec2<T> pos) { shift(pos.x(), pos.y()); }

  /// @brief `shift` without modifying `this`
  /// @param x the x to move to the right by
  /// @param y the y to move up by
  /// @return a shifted version of this Rect
  Rect<T> shifted(T x, T y) {
    return Rect<T>{mleft + x, mtop + y, mright + x, mbottom + y};
  }
  /// @brief `shift` without modifying `this`
  /// @param pos the position to shift by
  /// @return a shifted version of this Rect
  Rect<T> shifted(Vec2<T> pos) { return shifted(pos.x(), pos.y()); }

  /// @brief Shifts the Rect by x
  /// @param x the x to move by
  void shift_right(T x) {
    mleft += x;
    mright += x;
  }
  /// @brief `shift_right` without modifying `this`
  /// @param x the x to move by
  /// @return a shifted version of this Rect
  Rect<T> shifted_right(T x) {
    return Rect<T>{mleft + x, mtop, mright + x, mbottom};
  }
  /// @brief Shifts the Rect by y
  /// @param y the y to move by
  void shift_up(T y) {
    mtop += y;
    mbottom += y;
  }
  /// @brief `shift_up` without modifying `this`
  /// @param y the y to move by
  /// @return a new Rect
  Rect<T> shifted_up(T y) {
    return Rect<T>{mleft, mtop + y, mright, mbottom + y};
  }
  /// @brief Moves the top left corner of the Rect to x and y, keeping the width
  /// and height intact.
  /// @param left the x to move the left side to
  /// @param top the y to move the top side to
  void move_to(T left, T top) {
    mright = left + width();
    mbottom = top + height();
    mleft = left;
    mtop = top;
  }
  /// @brief Moves the top left corner of the Rect to `pos`, keeping the width
  /// and height intact.
  /// @param pos the position to move the top left corner to
  void move_to(Vec2<T> pos) { move_to(pos.x(), pos.y()); }

  /// @brief `move_to` without modifying `this`
  /// @param left the x to move the left side to
  /// @param top the y to move the top side to
  /// @return a new Rect
  Rect<T> moved_to(T left, T top) {
    return Rect<T>{left, top, left + width(), top + height()};
  }

  /// @brief `move_to` without modifying `this`
  /// @param pos the position to move the top left corner to
  /// @return a new Rect
  Rect<T> moved_to(Vec2<T> pos) { return moved_to(pos.x(), pos.y()); }

  /// @brief Moves the left side of the Rect to x, keeping the width
  /// intact.
  /// @param x the x to move to
  void move_to_x(T x) {
    mright = x + width();
    mleft = x;
  }
  /// @brief `move_to_x` without modifying `this`
  /// @param x the x to move the left side to
  /// @return a new Rect
  Rect<T> moved_to_x(T x) {
    return Rect<T>::fromLBWH(x, mtop, width(), height());
  }
  /// @brief Moves the top left corner of the Rect to y, keeping the height
  /// intact.
  /// @param y the y to move to
  void move_to_y(T y) {
    mbottom = y + height();
    mtop = y;
  }
  /// @brief `move_to_y` without modifying `this`
  /// @param y the y to move the bottom to
  /// @return a new Rect
  Rect<T> moved_to_y(T y) {
    return Rect<T>::fromLBWH(mleft, y, width(), height());
  }

  Vec2<T> center() {
    return Vec2<T>{(mleft + mright) / 2, (mtop + mbottom) / 2};
  }
  Vec2<T> top_left() { return Vec2<T>{mleft, mtop}; }
  Vec2<T> top_right() { return Vec2<T>{mright, mtop}; }
  Vec2<T> bottom_left() { return Vec2<T>{mleft, mbottom}; }
  Vec2<T> bottom_right() { return Vec2<T>{mright, mbottom}; }
  inline T left() { return mleft; }
  inline T top() { return mtop; }
  inline T right() { return mright; }
  inline T bottom() { return mbottom; }
  inline T width() { return mright - mleft; }
  inline T height() { return mbottom - mtop; }
};

using RectI = Rect<int>;
using RectD = Rect<double>;

template <typename T> class Circle {
  T mx, my, mradius;

public:
  template <typename U>
  Circle(Circle<U> other)
      : mx(static_cast<T>(other.x())), my(static_cast<T>(other.y())),
        mradius(static_cast<T>(other.radius())) {}

  Circle(T x, T y, T radius) : mx(x), my(y), mradius(radius) {}

  /// @brief Creates a "zero" Circle
  /// @return a new Circle with all values set to 0
  inline Circle() : mleft(0), mtop(0), mright(0), mbottom(0) {}

  bool intersects(Circle<T> other) {
    T dx = mx - other.mx;
    T dy = my - other.my;
    T distanceSq = dx * dx + dy * dy;
    T radiusSum = mradius + other.mradius;
    T radiusSumSq = radiusSum * radiusSum;
    return distanceSq <= radiusSumSq;
  }

  bool intersects(Rect<T> other) { return other.intersects(*this); }

  Vec2<T> center() { return Vec2<T>{mx, my}; }
  void center(Vec2<T> center) {
    mx = center.x();
    my = center.y();
  }
  inline T x() { return mx; }
  inline void x(T x) { mx = x; }
  inline T y() { return my; }
  inline void y(T y) { my = y; }
  inline T radius() { return mradius; }
  inline void radius(T radius) { mradius = radius; }
};

using CircleI = Circle<int>;
using CircleF = Circle<float>;
using CircleD = Circle<double>;

template <typename T> class Line {
  Vec2<T> mstart, mend;

public:
  template <typename U>
  Line(Line<U> other)
      : mstart(static_cast<T>(other.start())),
        mend(static_cast<T>(other.end())) {}
  Line(Vec2<T> start, Vec2<T> end) : mstart(start), mend(end) {}
  Line(T x1, T y1, T x2, T y2)
      : mstart(Vec2<T>{x1, y1}), mend(Vec2<T>{x2, y2}) {}
  Line() : mstart(Vec2<T>{}), mend(Vec2<T>{}) {}

  inline Vec2<T> start() { return mstart; }
  inline void start(Vec2<T> start) { mstart = start; }
  inline Vec2<T> end() { return mend; }
  inline void end(Vec2<T> end) { mend = end; }
};

using LineI = Line<int>;
using LineD = Line<double>;