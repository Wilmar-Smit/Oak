{
  description = "Oak dev Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};

      runtimeLibs = with pkgs; [
        vulkan-loader
        vulkan-headers
        wayland
        wayland-protocols
        libxkbcommon
        libX11
        libXcursor
        libXrandr
        libXi
        libGL
        mesa
      ];
    in
    {
      devShells.${system}.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
        packages = with pkgs; [
          git
          cmake
          ninja
          pkg-config
          python3       
          cacert        
          clang-tools   
          lldb       
          just
          fish
          glibcLocales
          lefthook
          xvfb-run
          plantuml
          sdl3
          spdlog
          glm
          catch2_3
        ] ++ runtimeLibs;

        GLIBC_LOCALES_PATH = "${pkgs.glibcLocales}";

        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath runtimeLibs
          + (if builtins.pathExists /run/opengl-driver then ":/run/opengl-driver/lib:/run/opengl-driver-32/lib" else "")
          + (if builtins.pathExists /usr/lib/x86_64-linux-gnu then ":/usr/lib/x86_64-linux-gnu" else "")
          + (if builtins.pathExists /usr/lib64 then ":/usr/lib64" else "");

        VK_DRIVER_FILES =
          let
            nvidiaIcd = "/run/opengl-driver/share/vulkan/icd.d/nvidia_icd.x86_64.json";
            hostIcd = if builtins.pathExists nvidiaIcd then "${nvidiaIcd}:" else "";
          in
          "${hostIcd}${pkgs.mesa}/share/vulkan/icd.d/radeon_icd.x86_64.json:${pkgs.mesa}/share/vulkan/icd.d/intel_icd.x86_64.json:${pkgs.mesa}/share/vulkan/icd.d/lvp_icd.x86_64.json";

        shellHook = ''
          lefthook install > /dev/null 2>&1

          if [ -t 0 ] && [ -f ./nix_scripts/fishShell.sh ]; then
            chmod +x ./nix_scripts/fishShell.sh
            exec ./nix_scripts/fishShell.sh
          fi
        '';
      };
    };
}
