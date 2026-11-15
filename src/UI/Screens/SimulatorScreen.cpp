#include "UI/Screens/SimulatorScreen.h"
#include "imgui.h"

ScreenRequest SimulatorScreen::draw() {
    ScreenRequest result = ScreenRequest::None;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Simulator", nullptr, window_flags);

    headerWidget(result);

    if (ImGui::BeginTable("VisualTable", 2, ImGuiTableFlags_BordersInnerV |ImGuiTableFlags_SizingStretchSame, ImVec2(0, 500))){
        ImGui::TableNextColumn(); CPUVisualizationWidget(result);
        //ImGui::TableNextColumn(); AssemblyWidget(result);
        ImGui::TableNextColumn(); UserWidget(result);
        ImGui::EndTable();
    }



    ControlCenterWidget(result);


    ImGui::End();

    return result;
}
//TODO find a way to let the width be the current screen width
void SimulatorScreen::headerWidget(ScreenRequest &result) {

    ImGui::BeginChild("headerWidget",  ImVec2(0, 25));

    if (ImGui::BeginTable("MyGridTable", 3, ImGuiTableFlags_Borders))
    {
        // Row 1
        ImGui::TableNextColumn(); ImGui::Text("Ricky Chat");
        ImGui::TableNextColumn();
        ImGui::Button("Start");
        ImGui::SameLine();

        ImGui::Button("Step");
        ImGui::SameLine();

        ImGui::Button("Restart");
        ImGui::SameLine();

        ImGui::TableNextColumn(); ImGui::Text("Processing");
        ImGui::SameLine();        if (ImGui::Button("Back to Start")) result = ScreenRequest::Start;
        ImGui::EndTable();
    }
    //ImGui::Separator();

    ImGui::EndChild();
}

void SimulatorScreen::AssemblyWidget(ScreenRequest &result) {
    ImGui::BeginChild("AssemblyWidget", ImVec2(0, 500), ImGuiChildFlags_Borders);

    ImVec2 editorSize = ImGui::GetContentRegionAvail();
    editorSize.y = 480.0f;

    assembly_editor_.Render("##AssemblyEditor", editorSize );

    ImGui::EndChild();
}

void SimulatorScreen::UserWidget(ScreenRequest &result) {
    ImGui::BeginChild("AssemblyWidget", ImVec2(0, 500), ImGuiChildFlags_Borders);

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Assembly"))
        {
            ImVec2 editorSize = ImGui::GetContentRegionAvail();
            editorSize.y = 480.0f;

            assembly_editor_.Render("##AssemblyEditor", editorSize );
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Registers"))
        {
            ImGui::Text("TODO Show registers");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Memory"))
        {
            ImGui::Text("Todo Show memory");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }


    ImGui::EndChild();
}

void SimulatorScreen::CPUVisualizationWidget(ScreenRequest &result) {
    ImGui::BeginChild("CPUVisualizationWidget", ImVec2(0, 55), ImGuiChildFlags_Borders);

    ImGui::Text("Vizualization widget TODO");

    ImGui::EndChild();
}

void SimulatorScreen::ControlCenterWidget(ScreenRequest &result) {
    ImGui::BeginChild("ControlCenterWidget",  ImVec2(0, 150), ImGuiChildFlags_Borders);

        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Registers"))
            {
                ImGui::Text("TODO Show registers");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Memory"))
            {
                ImGui::Text("Todo Show memory");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }


    ImGui::EndChild();
}