default: build

configure:
    cmake --preset dev
    ln -sf build/dev/compile_commands.json compile_commands.json

configure-release:
    cmake --preset release

configure-sanitize:
    cmake --preset sanitize
    ln -sf build/sanitize/compile_commands.json compile_commands.json

build: configure
    cmake --build --preset dev

build-sanitize: configure-sanitize
    cmake --build --preset sanitize

build-release: configure-release
    cmake --build --preset release

run-sanitize: build-sanitize
    ./build/sanitize/src/oak

run: build
    ./build/dev/src/oak

test-sanitize: build-sanitize
    ctest --preset sanitize

test-sanitize-headless: build-sanitize
    xvfb-run -a ctest --preset sanitize

clean:
    rm -rf build compile_commands.json

test: build
    ctest --preset dev

test-headless: build
    xvfb-run -a ctest --preset dev

format:
    find include src tests -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format --style=file:.clang/.clang-format -i {} +

lint:
    @if [ ! -f build/dev/compile_commands.json ]; then just configure; fi
    git ls-files 'src/*.cpp' 'src/*.hpp' 'src/*.h' 'tests/*.cpp' 'tests/*.hpp' | xargs -P $(nproc) -I {} clang-tidy --quiet --config-file=.clang/.clang-tidy -p build/dev --header-filter='^.*/Projects/Oak/(src|include|tests)/' {}

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

dawn-init:
    mkdir -p .webgpu
    if [ ! -d ".webgpu/source" ]; then \
        git clone https://dawn.googlesource.com/dawn .webgpu/source; \
    fi
    cd .webgpu/source && python3 tools/fetch_dawn_dependencies.py

dawn-build:
    @if [ -f ".webgpu/install/include/webgpu/webgpu.h" ]; then \
        echo "Dawn is already built and installed. Skipping compilation."; \
    else \
        echo "Initializing and downloading Dawn..."; \
        mkdir -p .webgpu; \
        if [ ! -d ".webgpu/source" ]; then git clone https://dawn.googlesource.com/dawn .webgpu/source; fi; \
        cd .webgpu/source && python3 tools/fetch_dawn_dependencies.py; \
        echo "Configuring and building Dawn from source..."; \
        cmake -S .webgpu/source -B .webgpu/build \
            -G Ninja \
            -DCMAKE_C_COMPILER=gcc \
            -DCMAKE_CXX_COMPILER=g++ \
            -DDAWN_BUILD_TESTS=OFF \
            -DDAWN_FETCH_DEPENDENCIES=ON \
            -DDAWN_ENABLE_INSTALL=ON \
            -DTINT_BUILD_TESTS=OFF \
            -DTINT_BUILD_CMD_TOOLS=OFF \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_INSTALL_PREFIX="{{ invocation_directory() }}/.webgpu/install"; \
        cmake --build .webgpu/build --config Release --parallel $(nproc); \
        cmake --install .webgpu/build --config Release; \
        echo "Cleaning up source and build directories to save space..."; \
        rm -rf .webgpu/source .webgpu/build; \
        echo "Dawn built, installed, and cleaned up successfully!"; \
    fi
