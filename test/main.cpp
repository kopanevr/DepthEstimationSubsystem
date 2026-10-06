/**
 * @file
 * @brief
 */

//

#include "Application.hpp"

//

/// @brief
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[]) {
  auto *const app = app::Application::getInstance(argc, argv);
  if (app) {
    app->exec();
  }
  return {};
}
