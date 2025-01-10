#include "raylib.h"
#include "logic.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h> // Required for WebAssembly main loop
#endif

// Function to handle the game loop
void MainLoop(void);

int main(void) {
    // Initialize the window
    InitWindow(WIDTH, HEIGHT, "Josephus Problem");
    SetTargetFPS(60);

#ifdef PLATFORM_WEB
    // Use Emscripten's main loop for web builds
    emscripten_set_main_loop(MainLoop, 0, 1);
#else
    // Standard infinite loop for desktop builds
    while (!WindowShouldClose()) {
        MainLoop();
    }
#endif

    // Clean up resources
    CloseWindow();
    return 0;
}

// Main game loop function
void MainLoop(void) {
    BeginDrawing();

    ClearBackground(RAYWHITE);	

    // Call appropriate game state logic
    if (!problemState && !restart) {
        Intro();
    } else {
        JosephusProblem();
    }

    EndDrawing();
}
