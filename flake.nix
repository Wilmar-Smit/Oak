{
  description = "Oak dev Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
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
        ];

        GLIBC_LOCALES_PATH = "${pkgs.glibcLocales}";

        shellHook = ''
          #for lefthook
          lefthook install > /dev/null 2>&1

          # for fish shell
          chmod +x nix_scripts/fishShell.sh
          exec ./nix_scripts/fishShell.sh
        '';
      };
    };
}
