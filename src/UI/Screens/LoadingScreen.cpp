#include "UI/Screens/LoadingScreen.h"
#include "imgui.h"
#include <cmath>

void LoadingScreen::onEnter() {
    context.processingComplete = false;

    // to start the 5-second timer
    startTime = ImGui::GetTime();
}


void LoadingScreen::LoadingSpinner( const char* label, float radius = 20.0f, float thickness = 4.0f, ImU32 color = IM_COL32(80, 160, 255, 255) ) {
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // Reserve space in the ImGui layout
    ImGui::Dummy(ImVec2(radius * 2, radius * 2));

    ImVec2 center(
        pos.x + radius,
        pos.y + radius
    );

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    constexpr int segments = 48;
    constexpr float pi = 3.14159265358979323846f;

    float time = static_cast<float>(ImGui::GetTime());

    // Rotating partial circle
    float startAngle = time * 4.0f;
    float arcLength = pi * 1.5f;

    drawList->PathClear();

    for (int i = 0; i <= segments; i++) {
        float angle = startAngle + arcLength * static_cast<float>(i) / segments;

        drawList->PathLineTo(ImVec2(
            center.x + std::cos(angle) * radius,
            center.y + std::sin(angle) * radius
        ));
    }

    drawList->PathStroke(
        color,
        ImDrawFlags_None,
        thickness
    );
}

ScreenRequest LoadingScreen::draw() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Loading", nullptr, window_flags);

    ImVec2 available = ImGui::GetContentRegionAvail();

    constexpr float radius = 25.0f;

    // Center the spinner
    ImGui::SetCursorPos(ImVec2(
        ImGui::GetCursorPosX() + available.x / 2.0f - radius,
        ImGui::GetCursorPosY() + available.y / 2.0f - radius - 20.0f
    ));

    LoadingSpinner("##spinner", radius, 5.0f);

    ImGui::Spacing();

    // Center the text
    const char* message = "Building CPU Simulator...";

    float textWidth = ImGui::CalcTextSize(message).x;

    ImGui::SetCursorPosX(
        ImGui::GetCursorPosX()
        + (ImGui::GetContentRegionAvail().x - textWidth) / 2.0f
    );

    ImGui::TextUnformatted(message);


    double elapsed = ImGui::GetTime() - startTime;

    ImGui::End();


    if (elapsed >= loadingDuration) {
        context.processingComplete = true;
        return ScreenRequest::Simulator;
    }


    return ScreenRequest::None;
}
