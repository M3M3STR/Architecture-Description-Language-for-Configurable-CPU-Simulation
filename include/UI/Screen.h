#ifndef ADL_SCREEN_H
#define ADL_SCREEN_H

#include "imgui.h"
#include "UI/ApplicationContext.h"
#include "UI/ScreenType.h"

class Screen {
public:
    explicit Screen(ApplicationContext& context)
        : context(context) {}

    virtual ~Screen() = default;

    virtual void onEnter() {}
    virtual void onExit() {}

    virtual ScreenRequest update() {
        return ScreenRequest::None;
    }

    virtual ScreenRequest draw() = 0;

protected:
    ApplicationContext& context;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;
};

#endif //ADL_SCREEN_H