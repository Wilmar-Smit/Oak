default: build

configure:
    cmake --preset debug

configure-release:
    cmake --preset release

build: configure
    cmake --build --preset debug

build-release: configure-release
    cmake --build --preset release

run: build
    ./build/debug/oak_tests

clean:
    rm -rf build

test: build
    ctest --preset debug

test-headless: build
    xvfb-run -a ctest --preset debug

format:
    find include src tests -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -i {} +

lint: configure
    find src tests -type f -name "*.cpp" -exec clang-tidy -p build/debug {} +

ci: lint test-headless

nix-update:
    nix flake update

dev: nix-update
    nix develop

plantuml:
    @mkdir -p docs/plantuml/images
    @find docs/plantuml -name "*.plantuml" -exec plantuml -tpng {} +
    @find docs/plantuml -type f -name "*.png" ! -path "docs/plantuml/images/*" -exec mv {} docs/plantuml/images/ \;
    @echo "PlantUML diagrams generated successfully in docs/plantuml/images!"
