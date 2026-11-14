default: build

configure:
    cmake --preset dev
    ln -sf build/dev/compile_commands.json compile_commands.json

configure-release:
    cmake --preset release

configure-test:
    cmake --preset test

build: configure
    cmake --build --preset dev

build-release: configure-release
    cmake --build --preset release

build-test: configure-test
    cmake --build --preset test

run: build
    ./build/dev/src/oak

clean:
    rm -rf build

test: build-test
    ctest --preset test

test-headless: build-test
    xvfb-run -a ctest --preset test

format:
    find include src tests -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -i {} +

lint: configure
    find src tests -type f -name "*.cpp" -exec clang-tidy --quiet -p build/dev {} +

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
