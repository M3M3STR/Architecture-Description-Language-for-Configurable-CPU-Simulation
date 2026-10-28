//
// Created by Diego Gayosso Hernandez on 9/30/26.
//

#include "UI/Application.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"



#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

Application::Application(): screenManager(context){}


Application::~Application()
{
    cleanup();
}


bool Application::initialize()
{
    // --------------------------------------------------
    // SDL
    // --------------------------------------------------

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr
            << "Failed to initialize SDL: "
            << SDL_GetError()
            << '\n';

        return false;
    }


    // --------------------------------------------------
    // OpenGL configuration
    //
    // OpenGL 3.2 Core corresponds to GLSL 150.
    // This configuration works with macOS.
    // --------------------------------------------------

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION,
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION,
        2
    );

    SDL_GL_SetAttribute(
        SDL_GL_DOUBLEBUFFER,
        1
    );

    SDL_GL_SetAttribute(
        SDL_GL_DEPTH_SIZE,
        24
    );

    SDL_GL_SetAttribute(
        SDL_GL_STENCIL_SIZE,
        8
    );


    // --------------------------------------------------
    // SDL Window
    // --------------------------------------------------

    window = SDL_CreateWindow(
        "Architecture Description Language CPU Simulator",
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        std::cerr
            << "Failed to create SDL window: "
            << SDL_GetError()
            << '\n';

        return false;
    }


    // --------------------------------------------------
    // OpenGL Context
    // --------------------------------------------------

    glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr) {
        std::cerr
            << "Failed to create OpenGL context: "
            << SDL_GetError()
            << '\n';

        return false;
    }


    if (!SDL_GL_MakeCurrent(window, glContext)) {
        std::cerr
            << "Failed to make OpenGL context current: "
            << SDL_GetError()
            << '\n';

        return false;
    }


    // Enable VSync
    if (!SDL_GL_SetSwapInterval(1)) {
        std::cerr
            << "Warning: Could not enable VSync: "
            << SDL_GetError()
            << '\n';
    }


    // --------------------------------------------------
    // Dear ImGui
    // --------------------------------------------------

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();


    // SDL backend
    if (!ImGui_ImplSDL3_InitForOpenGL(window, glContext)) {
        std::cerr
            << "Failed to initialize ImGui SDL3 backend."
            << '\n';

        return false;
    }


    // OpenGL backend
    if (!ImGui_ImplOpenGL3_Init("#version 150")) {
        std::cerr
            << "Failed to initialize ImGui OpenGL3 backend."
            << '\n';

        return false;
    }

    imguiContextCreated = true;
    imguiSDLInitialized = true;
    imguiOpenGLInitialized = true;
    running = true;

    return true;
}


void Application::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        // Give SDL events to ImGui.
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        // Also handle the user clicking the window's close button.
        if (
            event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
            event.window.windowID == SDL_GetWindowID(window)
        ) {
            running = false;
        }
    }
}


int Application::run()
{
    if (!initialize()) {
        return 1;
    }

    screenManager.initialize();

    // ==================================================
    // MAIN APPLICATION LOOP
    // ==================================================

    while (running) {

        // ----------------------------------------------
        // Events
        // ----------------------------------------------

        processEvents();

        if (!running) {
            break;
        }

        screenManager.update();

        // ----------------------------------------------
        // Begin ImGui frame
        // ----------------------------------------------

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();


        // ==============================================
        // UI
        // ==============================================
 
        screenManager.draw();

        ImGui::Render();


        // ----------------------------------------------
        // Clear OpenGL framebuffer
        // ----------------------------------------------

        int width;
        int height;

        SDL_GetWindowSizeInPixels(
            window,
            &width,
            &height
        );

        glViewport(
            0,
            0,
            width,
            height
        );

        glClearColor(
            0.10f,
            0.10f,
            0.10f,
            1.00f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        // ----------------------------------------------
        // Render ImGui
        // ----------------------------------------------

        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData()
        );


        // ----------------------------------------------
        // Display completed frame
        // ----------------------------------------------

        SDL_GL_SwapWindow(window);

        screenManager.applyPendingTransition();
    }


    return 0;
}


void Application::cleanup()
{
    running = false;


    // --------------------------------------------------
    // ImGui
    // --------------------------------------------------

    // if (imguiInitialized) {
    //
    //     ImGui_ImplOpenGL3_Shutdown();
    //     ImGui_ImplSDL3_Shutdown();
    //
    //     ImGui::DestroyContext();
    //
    //     imguiInitialized = false;
    // }

    if (imguiOpenGLInitialized) {
        ImGui_ImplOpenGL3_Shutdown();
        imguiOpenGLInitialized = false;
    }

    if (imguiSDLInitialized) {
        ImGui_ImplSDL3_Shutdown();
        imguiSDLInitialized = false;
    }

    if (imguiContextCreated) {
        ImGui::DestroyContext();
        imguiContextCreated = false;
    }
    // --------------------------------------------------
    // OpenGL
    // --------------------------------------------------

    if (glContext != nullptr) {

        SDL_GL_DestroyContext(glContext);

        glContext = nullptr;
    }


    // --------------------------------------------------
    // SDL Window
    // --------------------------------------------------

    if (window != nullptr) {

        SDL_DestroyWindow(window);

        window = nullptr;
    }


    // --------------------------------------------------
    // SDL
    // --------------------------------------------------

    SDL_Quit();
}
