#SERVER COMPILER
#!/bin/bash

#BUILD_DIR="./build"
SRC_DIR="./src"
INCLUDE_DIR="./include"

OUTPUT="SERVER_EXEC"

CXX="g++"
CXXFLAGS="-ggdb -Wall -Wextra -m64 -I$INCLUDE_DIR"


SOURCE_FILES=("$SRC_DIR/mainServer.cpp" "$SRC_DIR/server.cpp")

$CXX $CXXFLAGS "${SOURCE_FILES[@]}" -o $OUTPUT
