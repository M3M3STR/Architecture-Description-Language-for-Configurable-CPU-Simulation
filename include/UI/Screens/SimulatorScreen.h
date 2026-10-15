#ifndef ADL_SIMULATORSCREEN_H
#define ADL_SIMULATORSCREEN_H

#include "UI/Screen.h"
class SimulatorScreen final : public Screen {
public:
    using Screen::Screen;
    ScreenRequest draw() override;
};

#endif //ADL_SIMULATORSCREEN_H