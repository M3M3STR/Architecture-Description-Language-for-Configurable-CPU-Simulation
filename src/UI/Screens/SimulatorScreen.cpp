#include "UI/Screens/SimulatorScreen.h"
#include "imgui.h"

ScreenRequest SimulatorScreen::draw() {
    ScreenRequest result = ScreenRequest::None;

    AssemblyWidget(result);
    CPUVisualizationWidget(result);
    ControlCenterWidget(result);
    headerWidget(result);

    return result;
}
void SimulatorScreen::headerWidget(ScreenRequest &result) {
    ImGui::Begin("headerWidget", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::TextUnformatted("Simulator screen (placeholder)");
    ImGui::Text("Processing complete: %s", context.processingComplete ? "yes" : "no");

    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;

    ImGui::End();
}

void SimulatorScreen::AssemblyWidget(ScreenRequest &result) {
    ImGui::Begin("AssemblyWidget", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::TextUnformatted("Simulator screen (placeholder)");
    ImGui::Text("Processing complete: %s", context.processingComplete ? "yes" : "no");

    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;

    ImGui::End();
}

void SimulatorScreen::CPUVisualizationWidget(ScreenRequest &result) {
    ImGui::Begin("CPUVisualizationWidget", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::TextUnformatted("Simulator screen (placeholder)");
    ImGui::Text("Processing complete: %s", context.processingComplete ? "yes" : "no");

    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;

    ImGui::End();
}

void SimulatorScreen::ControlCenterWidget(ScreenRequest &result) {
    ImGui::Begin("ControlCenterWidget", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::TextUnformatted("Simulator screen (placeholder)");
    ImGui::Text("Processing complete: %s", context.processingComplete ? "yes" : "no");

    if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;

    ImGui::End();
}