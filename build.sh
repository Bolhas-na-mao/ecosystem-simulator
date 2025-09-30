
BUILD_DIR="build"
WEB_DIR="web"
SRC_DIR="src"

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

build_project() {
    echo -e "${BLUE}Building project...${NC}"
    
    mkdir -p $BUILD_DIR $WEB_DIR
    
    CPP_FILES=$(find $SRC_DIR -name "*.cpp")
    
    emcc $CPP_FILES \
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
