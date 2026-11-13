use crate::window_manager::window_manager::WindowManager;

mod window_manager;
fn main() {
    WindowManager::run().expect("Oak could not be started");
}
