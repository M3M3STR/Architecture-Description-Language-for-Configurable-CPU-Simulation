#ifndef ADL_SCREENMANAGER_H
#define ADL_SCREENMANAGER_H

#include <memory>
#include <optional>
#include "UI/Screen.h"
class ScreenManager {
public:
    explicit ScreenManager(ApplicationContext& context);
    void initialize();
    void update();
    void draw();
    void applyPendingTransition();
private:
    void request(ScreenRequest request);
    void changeScreen(ScreenType type);
    ApplicationContext& context;
    std::unique_ptr<Screen> currentScreen;
    std::optional<ScreenType> pendingScreen;
};

#endif //ADL_SCREENMANAGER_H