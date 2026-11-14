default: build

build:
    echo "add cpp build"

build-release:
    echo "add cpp build-release"

run:
    echo "add cpp run"

clean:
    echo "add cpp clean"

test:
    echo "add cpp test"

test-headless:
    xvfb-run -a cargo test

format:
    echo "cpp format"

lint:
    echo "cpp lint"

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
