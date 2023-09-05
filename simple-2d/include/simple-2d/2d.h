#pragma once
#include "shapes.h"

// processing-inspired API

/// @brief Set the current color
/// @param r red component, 0-1
/// @param g green component, 0-1
/// @param b blue component, 0-1
void color(float r, float g, float b);
/// @brief Set the current color
/// @param r red component, 0-1
/// @param g green component, 0-1
/// @param b blue component, 0-1
/// @param a opacity component, 0-1 (0 is transparent, 1 is opaque)
void color(float r, float g, float b, float a);
/// @brief Set the current line width (for drawing lines)
/// @see line
void line_width(float width);
/// @brief Draw a rectangle
/// @param x x-coordinate of the top-left corner
/// @param y y-coordinate of the top-left corner
/// @param w width of the rectangle
/// @param h height of the rectangle
void rect(int x, int y, int w, int h);
/// @brief Draw a rectangle
/// @param pos top-left corner of the rectangle
/// @param w width of the rectangle
/// @param h height of the rectangle
void rect(Vec2I pos, int w, int h);
/// @brief Draw a rectangle
/// @param rect rectangle to draw
void rect(RectI rect);
/// @brief Draw a circle
/// @param x x-coordinate of the center
/// @param y y-coordinate of the center
/// @param radius radius of the circle
/// @param iters number of iterations to use when drawing the circle (higher
/// means smoother, default should be fine)
void circle(float x, float y, float radius, int iters = 32);
/// @brief Draw a circle
/// @param center center of the circle
/// @param radius radius of the circle
/// @param iters number of iterations to use when drawing the circle (higher
/// means smoother, default should be fine)
void circle(Vec2F center, float radius, int iters = 32);
/// @brief Draw a circle
/// @param circle circle to draw
/// @param iters number of iterations to use when drawing the circle (higher
/// means smoother, default should be fine)
void circle(CircleF circle, int iters = 32);
/// @brief Draw a line
/// @param x1 the start x-coordinate
/// @param y1 the start y-coordinate
/// @param x2 the end x-coordinate
/// @param y2 the end y-coordinate
void line(int x1, int y1, int x2, int y2);
/// @brief Draw a line
/// @param p1 the start point
/// @param p2 the end point
void line(Vec2I p1, Vec2I p2);
/// @brief Draw a line
/// @param line the line to draw
void line(LineI line);
/// @brief Set the background color
/// @param r red component, 0-1
/// @param g green component, 0-1
/// @param b blue component, 0-1
void background(float r, float g, float b);

/// @brief Push the current matrix onto the stack
/// @see pop_matrix
void push_matrix();
/// @brief Pop the current matrix from the stack
/// @see push_matrix
void pop_matrix();
/// @brief Translate the matrix
/// @param x x-coordinate to translate by
/// @param y y-coordinate to translate by
void translate(float x, float y);
/// @brief Translate the matrix
/// @param pos position to translate by
void translate(Vec2F pos);
/// @brief Rotate the matrix around the x-axis
/// @param angle Angle in degrees
void rotate_x(float angle);
/// @brief Rotate the matrix around the y-axis
/// @param angle Angle in degrees
void rotate_y(float angle);
/// @brief Rotate the matrix around the z-axis
/// @param angle Angle in degrees
void rotate_z(float angle);
/// @brief Rotate 2D (alias for rotate_z)
/// @param angle Angle in degrees
/// @see rotate_z
void rotate(float angle);
/// @brief Scale the matrix
/// @param x x-coordinate to scale by
/// @param y y-coordinate to scale by
/// @param z z-coordinate to scale by (default 1)
void scale(float x, float y, float z = 1);
/// @brief Scale the matrix
/// @param scale scale factor to scale the x, y, and z coordinates by
void scale(float scale);