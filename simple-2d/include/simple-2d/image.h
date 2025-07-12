#pragma once
#include <filesystem>
#include <optional>
#include <vector>

struct Image {
  mutable unsigned int gl_texture_id = UINT_MAX;
  unsigned width{};
  unsigned height{};
  // RGBA8 format
  std::vector<uint8_t> data{};
};

/// @brief Loads an image from a file. Only PNG images are supported.
/// @param path The path to the image file.
/// @return The image, or std::nullopt if the image could not be loaded.
std::optional<Image> load_image(std::filesystem::path path);
/// @brief Loads an image from a file. Only PNG images are supported.
/// @param path The path to the image file.
/// @return The image, or std::nullopt if the image could not be loaded.
std::optional<Image> load_image(const std::string &path);
/// @brief Loads an image from a file.
/// @param path The path to the image file. Only PNG images are supported.
/// @return The image, or std::nullopt if the image could not be loaded.
std::optional<Image> load_image(const char *path);

/// @brief Decodes a PNG image.
/// @param png The PNG image data.
/// @return The image, or std::nullopt if the image could not be decoded.
std::optional<Image> decode_image(const std::vector<uint8_t> &png);

/// @brief Draws an image.
/// @param image The image to draw.
/// @param x The x coordinate of the image.
/// @param y The y coordinate of the image.
/// @param w The width to draw the image. default: -1 to use the image's width
/// @param h The height to draw the image. default: -1 to use the image's height
void image(const Image &image, int x, int y, int w = -1, int h = -1);