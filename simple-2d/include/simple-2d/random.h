#pragma once

/// @return a random number between 0 and 1
double random();
/// @param min the minimum value (inclusive)
/// @param max the maximum value (exclusive)
/// @return a random number between min and max
double random(double min, double max);
/// @param max the maximum value (exclusive)
/// @return a random number between 0 (inclusive) and max
double random(double max);
/// @param min the minimum value (inclusive)
/// @param max the maximum value (exclusive)
/// @return a random number between min and max
float random(float min, float max);
/// @param max the maximum value (exclusive)
/// @return a random number between 0 (inclusive) and max
float random(float max);
/// @param min the minimum value (inclusive)
/// @param max the maximum value (exclusive)
/// @return a random number between min and max
int random(int min, int max);
/// @param max the maximum value (exclusive)
/// @return a random number between 0 (inclusive) and max
int random(int max);