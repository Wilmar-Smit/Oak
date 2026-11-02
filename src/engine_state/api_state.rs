use crate::engine_state::wgpu_state::wgpu_state;

pub enum ApiState {
    WgpuState { state: wgpu_state },
}
