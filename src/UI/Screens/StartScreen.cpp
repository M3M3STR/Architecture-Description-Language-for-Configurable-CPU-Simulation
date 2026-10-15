#include "UI/Screens/StartScreen.h"
#include "imgui.h"
#include <string>

ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar;


ScreenRequest StartScreen::draw() {
    ImGui::Begin("Start", nullptr, window_flags);

    ImGui::TextUnformatted("Architecture Description Language CPU Simulator");

    ImGui::Separator();

    ImGui::TextUnformatted("ADL input (placeholder)");

    if (ImGui::Button("Use sample ADL")) context.adlSource = "sample ADL";

    ImGui::Text("Current input length: %zu", context.adlSource.size());

    if (ImGui::Button("Continue to Loading") && !context.adlSource.empty()) {
        ImGui::End();
        return ScreenRequest::Loading;
    }

    ImGui::End();
    return ScreenRequest::None;
}
