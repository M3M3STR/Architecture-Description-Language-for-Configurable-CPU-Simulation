#include "UI/Screens/LoadingScreen.h"
#include "imgui.h"
void LoadingScreen::onEnter() {
    context.processingComplete = false;
    context.errors.clear();
}
ScreenRequest LoadingScreen::draw() {
    ImGui::Begin("Loading", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::TextUnformatted("Loading / validation (placeholder)");
    ImGui::Text("ADL input length: %zu", context.adlSource.size());
    ScreenRequest result = ScreenRequest::None;
    if (ImGui::Button("Simulate validation success")) {
        context.processingComplete = true;
        result = ScreenRequest::Simulator;
    }
    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;
    ImGui::End();
    return result;
}
