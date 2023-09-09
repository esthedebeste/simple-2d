#include <iostream>
#include <simple-2d/setup.h>

GLFWwindow *window;
double start_time;
double current_time;
double delta_time;

static void update_window_size() {
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  if (w != width || h != height) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    width = w;
    height = h;
  }
}

Callbacks callbacks{};
int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW!";
    return 1;
  }
  init(callbacks);
  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create window!";
    return 1;
  }
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glOrtho(0, width, 0, height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_BLEND);
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, [](GLFWwindow *window, int intkey, int scancode,
                                int action, int mods) {
    Key key = static_cast<Key>(intkey);
    if (action == GLFW_PRESS)
      callbacks.key_pressed(key, KeyMods{mods});
    else if (action == GLFW_RELEASE)
      callbacks.key_released(key, KeyMods{mods});
    else if (action == GLFW_REPEAT)
      callbacks.key_held(key, KeyMods{mods});
  });
  glfwSetMouseButtonCallback(
      window, [](GLFWwindow *window, int button, int action, int mods) {
        Mouse mouse = static_cast<Mouse>(button);
        if (action == GLFW_PRESS)
          callbacks.mouse_pressed(mouse, KeyMods{mods});
        else if (action == GLFW_RELEASE)
          callbacks.mouse_released(mouse, KeyMods{mods});
      });
  glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
    y = height - y;
    mouse_x = x;
    mouse_y = y;
    callbacks.mouse_moved(x, y);
  });
  double last_time = glfwGetTime();
  start_time = last_time;
  while (!glfwWindowShouldClose(window)) {
    update_window_size();
    glLoadIdentity();
    current_time = glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;
    update();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  std::cout << "Closing...";
  return 0;
}