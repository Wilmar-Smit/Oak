use crate::engine_state::wgpu_state::WgpuState;

pub enum ApiState {
    WgpuState { state: WgpuState },
}
