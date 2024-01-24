#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void Init(void);
void ProcessEvents(void);
void Update(float);     // Update and Draw one frame
void Draw(void);

int main(void)
{
    srand(time(NULL));

    Init();

    // Main game loop
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        ProcessEvents();

        float dt = GetFrameTime();
        Update(dt);

        BeginDrawing();
            DrawFPS(10, 10);
            Draw();
        EndDrawing();

    }
#endif

    CloseWindow();

    return 0;
}

