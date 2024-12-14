#CLIENT COMPILER
#!/bin/bash

#BUILD_DIR="./build"
SRC_DIR="./src"
INCLUDE_DIR="./include"

OUTPUT="CLIENT_EXEC"

CXX="g++"
CXXFLAGS="-ggdb -Wall -Wextra -m64 -I$INCLUDE_DIR"


SOURCE_FILES=("$SRC_DIR/mainClient.cpp" "$SRC_DIR/client.cpp")

$CXX $CXXFLAGS "${SOURCE_FILES[@]}" -o $OUTPUT
