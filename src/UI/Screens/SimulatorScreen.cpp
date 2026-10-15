#include "UI/Screens/SimulatorScreen.h"
#include "imgui.h"

ScreenRequest SimulatorScreen::draw() {
    ImGui::Begin("Simulator", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::TextUnformatted("Simulator screen (placeholder)");
    ImGui::Text("Processing complete: %s", context.processingComplete ? "yes" : "no");
    ScreenRequest result = ScreenRequest::None;
    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;
    ImGui::End();
    return result;
}
