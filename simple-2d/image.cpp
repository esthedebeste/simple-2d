#include <fstream>
#include <iostream>
#include <lodepng/lodepng.h>
#include <optional>
#include <simple-2d/gl.h>
#include <simple-2d/image.h>

// some std::filesystem::path implementations have a `wchar_t` c_str return
// type, which ifstream supports.
template <typename T> inline std::optional<Image> load_image_template(T path) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    return std::nullopt;
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<uint8_t> png(size);
  file.read(reinterpret_cast<char *>(png.data()), size);
  return decode_image(png);
}

std::optional<Image> load_image(std::filesystem::path path) {
  return load_image_template(path.c_str());
}
std::optional<Image> load_image(const std::string &path) {
  return load_image_template(path.c_str());
}
std::optional<Image> load_image(const char *path) {
  return load_image_template(path);
}

std::optional<Image> decode_image(const std::vector<uint8_t> &png_data) {
  Image image{};
  unsigned error = lodepng::decode(image.data, image.width, image.height,
                                   png_data, LCT_RGBA, 8);
  if (error)
    return std::nullopt;
  return image;
}

void image(const Image &image, int x, int y, int w, int h) {
  if (image.gl_texture_id == UINT_MAX) {
    glGenTextures(1, &image.gl_texture_id);
    glBindTexture(GL_TEXTURE_2D, image.gl_texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image.data.data());
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           image.gl_texture_id, 0);
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
      std::cerr << "Framebuffer not complete" << std::endl;
    else
      std::cerr << "Framebuffer complete" << std::endl;
    glEnable(GL_TEXTURE_2D);
  }
  if (w == -1)
    w = image.width;
  if (h == -1)
    h = image.height;
  glBindTexture(GL_TEXTURE_2D, image.gl_texture_id);
  glBegin(GL_TRIANGLES);
  // bottom-left triangle '|\'
  glTexCoord2f(0, 1);
  glVertex3i(x, y, 0);
  glTexCoord2f(0, 0);
  glVertex3i(x, y + h, 0);
  glTexCoord2f(1, 0);
  glVertex3i(x + w, y + h, 0);
  // top-right triangle `\|'
  glTexCoord2f(1, 0);
  glVertex3i(x + w, y + h, 0);
  glTexCoord2f(1, 1);
  glVertex3i(x + w, y, 0);
  glTexCoord2f(0, 1);
  glVertex3i(x, y, 0);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}