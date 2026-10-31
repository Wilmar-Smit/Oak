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

format:
    cargo fmt

lint:
    cargo clippy --all-targets --all-features 

ci: format lint test
