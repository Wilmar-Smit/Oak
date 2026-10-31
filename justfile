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
    cargo clippy --lib --bins

ci: format-check lint test-headless
