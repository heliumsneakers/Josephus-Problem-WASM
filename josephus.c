#include "raylib.h"
#include "logic.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h> 
#endif

void MainLoop(void);

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Josephus Problem");
    SetTargetFPS(60);

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(MainLoop, 0, 1);
#else
    while (!WindowShouldClose()) {
        MainLoop();
    }
#endif
    CloseWindow();
    return 0;
}

void MainLoop(void) {
    BeginDrawing();

    ClearBackground(RAYWHITE);	

    if (!problemState && !restart) {
        Intro();
    } else {
        JosephusProblem();
    }

    EndDrawing();
}
