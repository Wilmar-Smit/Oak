#pragma once
#include <expected>
#include <string>

using std::expected;
using std::string;
namespace oak {
/**
 * @brief this class will manage the game resources Window (SDL3 for now),
 * Engine (depends on the version)
 * V1 for instance will use basic tree (no multi-thread search / command buffer
 * control)
 * Interface is irrelevant since visitors will be used to interact
 * with versions anyway
 * Will also manage GPU resources created by window (window will relinquesh those resources)
 * Window created due to SDL3 surface reliance
 * Renderer will be owned by app aswell Engine will have atleast one simple interface
 * That will be the to produce all the buffer objects for the renderer to be submitted in something
 * that can be efficiently moved
 */
class App final {

    expected<bool, string> init(/* Window class will go here  */);
    // init with the window manager provided

    /**
    @brief here game loop is started with engine and renderer this is the actual engine loop
    interface might change based on info needing to be sent into the engine however its likely the
    engine will just be the one to have changes made since anything else will need window to close
    anyway
    @note This will likely just port over events to the engine using some query function
    @returns True for everything finished as expected string for errors (error message is string )
    */
    expected<bool, string> start_loop();
};
} // namespace oak
