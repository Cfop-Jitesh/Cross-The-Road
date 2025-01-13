
export LD_LIBRARY_PATH=/home/jitesh/game/raylib/lib:$LD_LIBRARY_PATH

# Paths to Raylib headers and libraries
RAYLIB_INCLUDE=/home/jitesh/game/raylib/include
RAYLIB_LIB=/home/jitesh/game/raylib/lib

# Compiler and flags
CC=gcc
CFLAGS="-Wall -std=c99 -I$RAYLIB_INCLUDE"
LDFLAGS="-L$RAYLIB_LIB -lraylib -lraygui -lm -ldl -lpthread"

# Files
SRC="raylib_game.c screen_logo.c screen_gameplay.c screen_options.c screen_title.c screen_ending.c function.c"
OUTPUT="game"

# Compile
echo "Compiling..."
$CC $CFLAGS $SRC -o $OUTPUT $LDFLAGS

# Check if compile was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Running the game..."
    # Run the game
    ./game
else
    echo "Build failed."
fi

