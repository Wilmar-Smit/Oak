default: build

configure:
    cmake --preset dev
    ln -sf build/dev/compile_commands.json compile_commands.json

configure-release:
    cmake --preset release

build: configure
    cmake --build --preset dev

build-release: configure-release
    cmake --build --preset release

run: build
    ./build/dev/src/oak

clean:
    rm -rf build compile_commands.json

test: build
    ctest --preset dev

test-headless: build
    xvfb-run -a ctest --preset dev

format:
    find include src tests -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format --style=file:.clang/clang-format -i {} +

lint: configure
    find src tests -type f -name "*.cpp" -exec clang-tidy --quiet --config-file=.clang/clang-tidy -p build/dev {} +

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
