#ifndef ADL_STARTSCREEN_H
#define ADL_STARTSCREEN_H

#include "SDL3/SDL_dialog.h"
#include "SDL3/SDL_keyboard.h"
#include "UI/Screen.h"

class StartScreen final : public Screen {
    public:
        using Screen::Screen;
        ScreenRequest draw() override;
    private:
        static constexpr  SDL_DialogFileFilter filters[] = {
            { "Architecture Description Language ", "adl" }
        };

        // TODO
        // for the opendialog it needs a pointer to the window who called it, this is a way to get the pointer without passing it through layers to classes
        // maybe somepoint change this to an actual pointer set from the parent
        SDL_Window* activeWindow = SDL_GetKeyboardFocus();

        static void SDLCALL callback(void *userdata, const char * const *filelist, int filter);

};

#endif //ADL_STARTSCREEN_H