#ifndef ADL_LOADINGSCREEN_H
#define ADL_LOADINGSCREEN_H

#include "UI/Screen.h"
class LoadingScreen final : public Screen {
public:
    using Screen::Screen;
    void onEnter() override;

    void LoadingSpinner(const char *label, float radius, float thickness, ImU32 color);
    double startTime = 0.0;
    static constexpr double loadingDuration = 3.0;

    ScreenRequest draw() override;
};

#endif //ADL_LOADINGSCREEN_H