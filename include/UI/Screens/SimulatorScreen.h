#ifndef ADL_SIMULATORSCREEN_H
#define ADL_SIMULATORSCREEN_H

#include "TextEditor.h"
#include "UI/Screen.h"

class SimulatorScreen final : public Screen {
public:
    using Screen::Screen;

    ScreenRequest draw() override;

    void headerWidget(ScreenRequest &result);
    void AssemblyWidget(ScreenRequest &result);

    void UserWidget(ScreenRequest &result);

    void CPUVisualizationWidget(ScreenRequest &result);
    void ControlCenterWidget(ScreenRequest &result);

    TextEditor assembly_editor_;
};

#endif //ADL_SIMULATORSCREEN_H