use crate::gpu_api::adapter::run;

mod gpu_api;
fn main() {
    run().expect("Run failed");
}
