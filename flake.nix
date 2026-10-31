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
        ];

        GLIBC_LOCALES_PATH = "${pkgs.glibcLocales}";
        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath runtimeLibs;

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
