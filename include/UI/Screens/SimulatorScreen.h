#ifndef ADL_SIMULATORSCREEN_H
#define ADL_SIMULATORSCREEN_H

#include "UI/Screen.h"
class SimulatorScreen final : public Screen {
public:
    using Screen::Screen;

    ScreenRequest draw() override;

    void headerWidget(ScreenRequest &result);

    void AssemblyWidget(ScreenRequest &result);

    void CPUVisualizationWidget(ScreenRequest &result);

    void ControlCenterWidget(ScreenRequest &result);
};

#endif //ADL_SIMULATORSCREEN_H