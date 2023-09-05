#include <random>

std::random_device rd;
std::mt19937 gen(rd());

double random() { return std::uniform_real_distribution<double>(0, 1)(gen); }
double random(double min, double max) {
  return std::uniform_real_distribution<double>(min, max)(gen);
}
double random(double max) {
  return std::uniform_real_distribution<double>(0.0, max)(gen);
}
float random(float min, float max) {
  return std::uniform_real_distribution<float>(min, max)(gen);
}
float random(float max) {
  return std::uniform_real_distribution<float>(0.0f, max)(gen);
}
int random(int min, int max) {
  return std::uniform_int_distribution<>(min, max)(gen);
}
int random(int max) { return std::uniform_int_distribution<>(0, max)(gen); }