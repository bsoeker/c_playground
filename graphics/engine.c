#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    SDL_Window *window;
    SDL_GLContext gl_context;
    bool running;
} Engine;

// Initialize engine (window + GL context)
bool engine_init(Engine *eng, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL init failed: %s\n", SDL_GetError());
        return false;
    }

    // Ask SDL for OpenGL 3.3 Core profile (modern pipeline)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    eng->window =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!eng->window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    eng->gl_context = SDL_GL_CreateContext(eng->window);
    if (!eng->gl_context) {
        fprintf(stderr, "OpenGL context failed: %s\n", SDL_GetError());
        return false;
    }

    eng->running = true;
    return true;
}

// Handle input
void engine_process_input(Engine *eng) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            eng->running = false;
        }
    }
}

// Update game logic
void engine_update(Engine *eng, float dt) {
    (void)eng; // unused for now
    (void)dt;
    // TODO: update entities, physics, AI, etc.
}

// Render
void engine_render(Engine *eng) {
    (void)eng;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: draw stuff here (triangles, sprites, models…)

    SDL_GL_SwapWindow(eng->window);
}

// Cleanup
void engine_shutdown(Engine *eng) {
    SDL_GL_DeleteContext(eng->gl_context);
    SDL_DestroyWindow(eng->window);
    SDL_Quit();
}

int main(void) {
    Engine eng;
    if (!engine_init(&eng, "Minimal Engine", 800, 600))
        return -1;

    Uint32 last_ticks = SDL_GetTicks();

    while (eng.running) {
        Uint32 current_ticks = SDL_GetTicks();
        float dt = (current_ticks - last_ticks) / 1000.0f;
        last_ticks = current_ticks;

        engine_process_input(&eng);
        engine_update(&eng, dt);
        engine_render(&eng);
    }

    engine_shutdown(&eng);
    return 0;
}
