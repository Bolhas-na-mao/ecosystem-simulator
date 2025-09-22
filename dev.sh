#!/bin/bash

PORT=8001
BUILD_DIR="build"
WEB_DIR="web"
SRC_DIR="src"

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

if ! command -v inotifywait &> /dev/null; then
    echo -e "${YELLOW}Installing inotify-tools for file watching...${NC}"
    sudo apt install -y inotify-tools
fi

build_project() {
    echo -e "${BLUE}Building project...${NC}"
    
    mkdir -p $BUILD_DIR $WEB_DIR
    
    emcc src/main.cpp \
        -o $WEB_DIR/ecosystem.js \
        -s WASM=1 \
        -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
        -s ALLOW_MEMORY_GROWTH=1 \
        --bind
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✅ Build successful! $(date '+%H:%M:%S')${NC}"
        return 0
    else
        echo -e "${RED}❌ Build failed! $(date '+%H:%M:%S')${NC}"
        return 1
    fi
}

build_project

if [ $? -ne 0 ]; then
    exit 1
fi

echo -e "${BLUE}Starting server on port $PORT...${NC}"

pkill -f "python3 -m http.server $PORT" 2>/dev/null

cd $WEB_DIR
python3 -m http.server $PORT > /dev/null 2>&1 &
SERVER_PID=$!
cd ..

sleep 2

if command -v xdg-open > /dev/null; then
    xdg-open "http://localhost:$PORT"
fi

echo -e "${GREEN}Development server running${NC}"
echo -e "${BLUE}Watching $SRC_DIR/ for changes${NC}"
echo -e "${YELLOW}Press Ctrl+C to stop${NC}"

trap "echo -e '\n${RED}🛑 Stopping server...${NC}'; kill $SERVER_PID 2>/dev/null; exit 0" INT

inotifywait -m -r -e modify,create,delete $SRC_DIR/ --format '%w%f %e' |
while read file event; do
    if [[ $file == *.cpp ]] || [[ $file == *.c ]] || [[ $file == *.h ]]; then
        echo -e "${YELLOW}Changed: $file${NC}"
        build_project
    fi
done