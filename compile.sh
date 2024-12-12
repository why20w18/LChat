#!/bin/bash

BUILD_DIR="./build"
SRC_DIR="./src"
INCLUDE_DIR="./include"

OUTPUT="LCHAT.exe"

CXX="g++"
CXXFLAGS="-ggdb -Wall -Wextra -m64 -I$INCLUDE_DIR"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi

SOURCE_FILES=("$SRC_DIR/main.cpp" "$SRC_DIR/client.cpp" "$SRC_DIR/server.cpp")

$CXX $CXXFLAGS "${SOURCE_FILES[@]}" -o $BUILD_DIR/$OUTPUT

echo "DERLEME TAMAMLANDI ! $BUILD_DIR/$OUTPUT"
