use crate::window_manager::window_manager::WindowManager;

mod window_manager;
fn main() {
    env_logger::Builder::from_env(env_logger::Env::default().default_filter_or("info")).init();
    log::info!("Starting Oak...");
    WindowManager::run().expect("Oak could not be started");
}
