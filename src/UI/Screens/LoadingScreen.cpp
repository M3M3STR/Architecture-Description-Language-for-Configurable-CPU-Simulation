#include "UI/Screens/LoadingScreen.h"
#include "imgui.h"
void LoadingScreen::onEnter() {
    context.processingComplete = false;
    context.errors.clear();
}
ScreenRequest LoadingScreen::draw() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Loading", nullptr, window_flags);

    ImGui::TextUnformatted("Loading / validation (placeholder)");

    ScreenRequest result = ScreenRequest::None;
    if (ImGui::Button("Simulate validation success")) {
        context.processingComplete = true;
        result = ScreenRequest::Simulator;
    }

    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;
    ImGui::End();
    return result;
}
