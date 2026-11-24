#pragma once

#include "Renderer/ResourceManager/ResourceManager.hpp"
#include <expected>
#include <memory>
#include <string>

using std::expected;
using std::string;
namespace oak {
class Iwindow;

/**
 * @brief Manages resources between window, engine and renderer
 */
class App final {
  private:
    std::unique_ptr<ResourceManager> gpu_resources;
    std::unique_ptr<Iwindow> window;

  public:
    explicit App();
    /**
     * @brief Inializes App based on the window manager provided
     */
    expected<bool, string> init(Iwindow* window);

    /**
     * @brief here game loop is started with engine and renderer this is the actual engine loop
     * @note This will likely just port over events to the engine using some query function
     * @returns True for everything finished as expected string for errors (error message is string
     * )
     */
    expected<bool, string> start_loop();
};
} // namespace oak
