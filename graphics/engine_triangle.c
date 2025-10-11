#include <GL/glew.h> // helper to load modern OpenGL funcs
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    SDL_Window *window;
    SDL_GLContext gl_context;
    bool running;
} Engine;

// ========== SHADER UTILS ==========
GLuint compile_shader(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        fprintf(stderr, "Shader compile error: %s\n", log);
    }
    return shader;
}

GLuint create_shader_program() {
    const char *vertex_src = "#version 330 core\n"
                             "layout (location = 0) in vec2 aPos;\n"
                             "void main() {\n"
                             "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
                             "}\n";

    const char *fragment_src = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main() {\n"
                               "   FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
                               "}\n";

    GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_src);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_src);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    int success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(prog, 512, NULL, log);
        fprintf(stderr, "Program link error: %s\n", log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

// ========== ENGINE CORE ==========
bool engine_init(Engine *eng, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL init failed: %s\n", SDL_GetError());
        return false;
    }

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

    // init GLEW after context
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW init failed\n");
        return false;
    }

    eng->running = true;
    return true;
}

void engine_process_input(Engine *eng) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            eng->running = false;
    }
}

void engine_shutdown(Engine *eng) {
    SDL_GL_DeleteContext(eng->gl_context);
    SDL_DestroyWindow(eng->window);
    SDL_Quit();
}

// ========== MAIN ==========
int main(void) {
    Engine eng;
    if (!engine_init(&eng, "Triangle Engine", 800, 600))
        return -1;

    // Triangle vertex data
    float vertices[] = {
        0.0f,  0.5f,  // top
        -0.5f, -0.5f, // left
        0.5f,  -0.5f  // right
    };

    // Setup VAO + VBO
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Shader program
    GLuint shader = create_shader_program();

    // Game loop
    while (eng.running) {
        engine_process_input(&eng);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(eng.window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    engine_shutdown(&eng);
    return 0;
}
