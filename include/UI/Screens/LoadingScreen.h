#ifndef ADL_LOADINGSCREEN_H
#define ADL_LOADINGSCREEN_H

#include "UI/Screen.h"
class LoadingScreen final : public Screen {
public:
    using Screen::Screen;
    void onEnter() override;
    ScreenRequest draw() override;
};

#endif //ADL_LOADINGSCREEN_H