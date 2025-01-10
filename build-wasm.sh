#!/bin/bash
set -euo pipefail

# Path to Emscripten
EMSDK_PATH="emsdk/"

# Source the Emscripten environment
cd $EMSDK_PATH
source emsdk_env.sh

# Navigate back to your project directory
cd ..

# Build to WebAssembly
emcc -o ./build_web/index.html \
    josephus.c logic.c \
    -Os -Wall \
    -I./ \
    -I../../src \
    -I raygui/src \
    -L../../src \
    ../../src/libraylib.a \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    --shell-file ./shell.html \
    -s TOTAL_STACK=64MB \
    -s INITIAL_MEMORY=128MB \
    -s ASSERTIONS=1 \
    -DPLATFORM_WEB

emrun --no_browser --port 8080 build_web/index.html
