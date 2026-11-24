#pragma once
#include <expected>
#include <string>

using std::expected;
using std::string;
namespace oak {
/**
 * @brief Manages resources between window, engine and renderer
 */
class App final {
  public:
    /**
     * @brief Inializes App based on the window manager provided
     */
    expected<bool, string> init(/* Window class will go here  */);

    /**
     * @brief here game loop is started with engine and renderer this is the actual engine loop
     * @note This will likely just port over events to the engine using some query function
     * @returns True for everything finished as expected string for errors (error message is string
     * )
     */
    expected<bool, string> start_loop();
};
} // namespace oak
