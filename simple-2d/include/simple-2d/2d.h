#pragma once
#include "shapes.h"

// processing-inspired API
void color(float r, float g, float b);
void color(float r, float g, float b, float a);
void line_width(float width);
void rect(int x, int y, int w, int h);
void rect(Vec2I pos, int w, int h);
void rect(RectI rect);
void circle(int x, int y, int radius, int iters = 32);
void circle(Vec2I center, int radius, int iters = 32);
void circle(CircleI circle, int iters = 32);
void line(int x1, int y1, int x2, int y2);
void line(Vec2I p1, Vec2I p2);
void line(LineI line);
void background(float r, float g, float b);