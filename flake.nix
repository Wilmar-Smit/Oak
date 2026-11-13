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
        wayland
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
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          git
          just
          fish
          glibcLocales
          cargo
          rustc
          rustfmt
          clippy
          lefthook
          xvfb-run
          mesa
          pkg-config
          plantuml
        ];

        GLIBC_LOCALES_PATH = "${pkgs.glibcLocales}";


        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath runtimeLibs
          + (if builtins.pathExists /run/opengl-driver then ":/run/opengl-driver/lib:/run/opengl-driver-32/lib" else "")
          + (if builtins.pathExists /usr/lib/x86_64-linux-gnu then ":/usr/lib/x86_64-linux-gnu" else "")
          + (if builtins.pathExists /usr/lib64 then ":/usr/lib64" else "");


        VK_ICD_FILENAMES =
          let
            hostIcdPaths =
              if builtins.pathExists /run/opengl-driver/share/vulkan/icd.d
              then "/run/opengl-driver/share/vulkan/icd.d"
              else if builtins.pathExists /usr/share/vulkan/icd.d
              then "/usr/share/vulkan/icd.d"
              else "";
          in
          "${pkgs.mesa}/share/vulkan/icd.d/radeon_icd.x86_64.json:${pkgs.mesa}/share/vulkan/icd.d/intel_icd.x86_64.json" +
          (if hostIcdPaths != "" then ":${hostIcdPaths}" else "");

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
