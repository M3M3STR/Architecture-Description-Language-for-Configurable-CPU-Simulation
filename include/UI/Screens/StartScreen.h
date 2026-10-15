#ifndef ADL_STARTSCREEN_H
#define ADL_STARTSCREEN_H

#include "UI/Screen.h"
class StartScreen final : public Screen {
public:
    using Screen::Screen;
    ScreenRequest draw() override;
};

#endif //ADL_STARTSCREEN_H