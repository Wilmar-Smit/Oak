impl State {
    pub fn render(&self) -> anyhow::Result<()> {
        self.window.request_redraw();

        if !self.is_surface_configured {
            return Ok(());
        }

        let Some(output) = self.create_output()? else {
            return Ok(());
        };

        let view = output
            .texture
            .create_view(&wgpu::TextureViewDescriptor::default());

        let mut encoder = self
            .device
            .create_command_encoder(&wgpu::CommandEncoderDescriptor {
                label: Some("Render Encoder"),
            });

        {
            let mut render_pass = encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
                label: Some("Render Pass"),
                color_attachments: &[Some(wgpu::RenderPassColorAttachment {
                    view: &view,
                    resolve_target: None,
                    depth_slice: None,
                    ops: wgpu::Operations {
                        load: wgpu::LoadOp::Clear(wgpu::Color {
                            r: 0.1,
                            g: 0.2,
                            b: 0.3,
                            a: 1.0,
                        }),
                        store: wgpu::StoreOp::Store,
                    },
                })],
                depth_stencil_attachment: None,
                occlusion_query_set: None,
                timestamp_writes: None,
                multiview_mask: None,
            });
            render_pass.set_pipeline(&self.render_pipeline);
            render_pass.draw(0..3, 0..1);
        }

        self.queue.submit(std::iter::once(encoder.finish()));
        self.queue.present(output);

        Ok(())
    }

    fn create_output(&self) -> anyhow::Result<Option<wgpu::SurfaceTexture>> {
        match self.surface.get_current_texture() {
            wgpu::CurrentSurfaceTexture::Success(surface_texture)
            | wgpu::CurrentSurfaceTexture::Suboptimal(surface_texture) => Ok(Some(surface_texture)),
            wgpu::CurrentSurfaceTexture::Timeout
            | wgpu::CurrentSurfaceTexture::Occluded
            | wgpu::CurrentSurfaceTexture::Validation => {
                Ok(None) // Signals "skip this frame"
            }
            wgpu::CurrentSurfaceTexture::Outdated => {
                self.surface.configure(&self.device, &self.config);
                Ok(None) // Signals "skip this frame"
            }
            wgpu::CurrentSurfaceTexture::Lost => {
                anyhow::bail!("Lost device");
            }
        }
    }
}
