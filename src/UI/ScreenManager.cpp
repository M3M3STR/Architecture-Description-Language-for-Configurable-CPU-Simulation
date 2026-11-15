#include "UI/ScreenManager.h"
#include "UI/Screens/StartScreen.h"
#include "UI/Screens/LoadingScreen.h"
#include "UI/Screens/SimulatorScreen.h"
#include <utility>

ScreenManager::ScreenManager(ApplicationContext& context) : context(context) {}

void ScreenManager::initialize() {
    changeScreen(ScreenType::Start);
}

void ScreenManager::request(ScreenRequest request) {
    switch (request) {
        case ScreenRequest::None: break;
        case ScreenRequest::Start: pendingScreen = ScreenType::Start; break;
        case ScreenRequest::Loading: pendingScreen = ScreenType::Loading; break;
        case ScreenRequest::Simulator: pendingScreen = ScreenType::Simulator; break;
    }
}
void ScreenManager::changeScreen(ScreenType type) {
    if (currentScreen) currentScreen->onExit();
    std::unique_ptr<Screen> next;
    switch (type) {
        case ScreenType::Start: next = std::make_unique<StartScreen>(context); break;
        case ScreenType::Loading: next = std::make_unique<LoadingScreen>(context); break;
        case ScreenType::Simulator: next = std::make_unique<SimulatorScreen>(context); break;
    }
    currentScreen = std::move(next);
    if (currentScreen) currentScreen->onEnter();
}
void ScreenManager::update() {
    if (currentScreen) {
        request(currentScreen->update());
    }
}
void ScreenManager::draw() {
    if (currentScreen) {
        request(currentScreen->draw());
    }
}
void ScreenManager::applyPendingTransition() {
    if (!pendingScreen) return;
    auto next = *pendingScreen;
    pendingScreen.reset();
    changeScreen(next);
}