default: build

build:
    cargo build

build-release:
    cargo build --release

run:
    cargo run

clean:
    cargo clean

test:
    cargo test

test-headless:
    xvfb-run -a cargo test

format:
    cargo fmt

format-check:
    cargo fmt --check

lint:
    cargo clippy --all-targets --all-features

ci: format-check lint test-headless


nix-update:
    nix flake update

dev: nix-update
    nix develop

plantuml:
    @mkdir -p docs/plantuml/images
    @find docs/plantuml -name "*.plantuml" -exec plantuml -tpng {} +
    @find docs/plantuml -type f -name "*.png" ! -path "docs/plantuml/images/*" -exec mv {} docs/plantuml/images/ \;
    @echo "PlantUML diagrams generated successfully in docs/plantuml/images!"
