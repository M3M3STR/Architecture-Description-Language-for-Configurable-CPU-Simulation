#ifndef ADL_SCREEN_H
#define ADL_SCREEN_H

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
};

#endif //ADL_SCREEN_H