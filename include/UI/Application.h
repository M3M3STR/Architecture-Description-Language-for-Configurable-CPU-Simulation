//
// Created by Diego Gayosso Hernandez on 9/30/26.
//

#ifndef ADL_APPLICATION_H
#define ADL_APPLICATION_H

#include <SDL3/SDL.h>

class Application {
public:
    Application();
    ~Application();

    int run();

private:
    bool initialize();
    void processEvents();
    void cleanup();
    bool imguiInitialized = false;
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    bool running = false;
};



#endif //ADL_APPLICATION_H