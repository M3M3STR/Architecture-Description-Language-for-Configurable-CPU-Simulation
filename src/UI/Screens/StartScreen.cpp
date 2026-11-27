
#include "UI/Screens/StartScreen.h"

#include <fstream>
#include <iostream>

#include "imgui.h"
#include <string>
#include "misc/cpp/imgui_stdlib.h"
#include "SDL3/SDL_dialog.h"

#include "LoadFile.h"
#include "TextEditor.h"


StartScreen::StartScreen(ApplicationContext& context): Screen(context){
    text_editor_.SetText(adlSource);
    text_editor_.SetReadOnly(false);
    text_editor_.SetShowWhitespaces(false);
    text_editor_.SetTabSize(4);

    error_viewer_.SetText(errorOutput);
    error_viewer_.SetReadOnly(true);
    error_viewer_.SetShowWhitespaces(false);
}

void SDLCALL StartScreen::callback(void *userdata, const char * const *filelist, int filter) {
    // If a file was selected
    if (filelist && filelist[0]) {
        std::cout << filelist[0] << std::endl;
        std::ifstream file(filelist[0]);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filelist[0] << "\n";
            return;
        }

        // Read the entire file line by line into the reference variable
        std::string line;

        std::string output;
        while (std::getline(file, line)) {
            output += line + "\n";
        }


        auto* screen = static_cast<StartScreen*>(userdata);
        screen->adlSource = output;
        screen->text_editor_.SetText(screen->adlSource);

        if (!screen->errorOutput.empty()) {
            screen->errorOutput = "";
            screen->error_viewer_.SetText("");
            screen->text_editor_.SetErrorMarkers({});
        }
    }
}
void StartScreen::headerWidget() {

    ImGui::BeginChild("headerWidget",  ImVec2(0, 25));

    if (ImGui::BeginTable("headerGridTable", 2, ImGuiTableFlags_Borders))
    {
        // Optional: Set up headers (The top row)
        //ImGui::TableSetupColumn("ID");
        //ImGui::TableSetupColumn("Name");
        //ImGui::TableSetupColumn("Action");
        //ImGui::TableHeadersRow();

        // Row 1
        ImGui::TableNextColumn(); ImGui::Text("Ricky Chat");
        ImGui::TableNextColumn(); ImGui::TextLinkOpenURL("ADL Wiki", "https://github.com/M3M3STR/Architecture-Description-Language-for-Configurable-CPU-Simulation.git");

        ImGui::EndTable();
    }
    //ImGui::Separator();

    ImGui::EndChild();
}

ScreenRequest StartScreen::DescriptionWidget() {

    ImGui::BeginChild("DescriptionWidget",  ImVec2(0, 65));

    if (ImGui::BeginTable("descriptionGridTable", 2, ImGuiTableFlags_Borders))
    {
        // Row 1
        ImGui::TableNextColumn();


        ImGui::Text("Start with your architecture.");
        ImGui::Text("Write an ADL or Load a File");
        ImGui::TextWrapped("Uploading replaces the editor contents. You can keep editing after upload; it does not run the parser.");


        ImGui::TableNextColumn();
        if (ImGui::Button("Load a File")) {
            SDL_ShowOpenFileDialog(
                callback,
                this,
                activeWindow,
                filters,
                SDL_arraysize(filters),
                nullptr,
                false
            );
        }

        ImGui::SameLine();

        if (ImGui::Button("Build Simulator") && !adlSource.empty()) {
            // TODO this is fore debug, remove when unneeded
			std::cout << "pre parse input: " << text_editor_.GetText() << std::endl;
            auto result = parser.parseFromString(text_editor_.GetText());
            if (result) {
                std::cout << "parsing was successful" << std::endl;
                ImGui::EndTable();
                ImGui::EndChild();
                return ScreenRequest::Loading;
            }
            else {
                std::vector<SyntaxError> errorsList = result.error();
                TextEditor::ErrorMarkers markers;

                errorOutput = "";
                for (auto error : errorsList) {
                    errorOutput += std::format("On Line: {} there is an error: {}\n", error.line, error.msg);
                    markers.insert(std::make_pair<int, std::string>(error.line, std::move(error.msg)));
                }
                error_viewer_.SetText(errorOutput);
                text_editor_.SetErrorMarkers(markers);
                std::cout << "parsing was not successful" << std::endl;
            }
        }


        ImGui::EndTable();
    }

    ImGui::EndChild();
    return ScreenRequest::None;
}
void StartScreen::UserInteractionWidget() {

    //Get the total space from the window {x,y} window
    ImVec2 avail_size = ImGui::GetContentRegionAvail();

    ImGui::BeginChild("UserInteractionWidget",  ImVec2(0, avail_size.y));

    if (ImGui::BeginTable("UserInteractionGridTable", 2, ImGuiTableFlags_Borders))
    {

        ImGui::TableSetupColumn(
            "ADL Source",
            ImGuiTableColumnFlags_WidthStretch
        );

        ImGui::TableSetupColumn(
            "Parser Output",
            ImGuiTableColumnFlags_WidthStretch
        );
        // column 1
        ImGui::TableNextColumn();
        ImVec2 editorSize = ImGui::GetContentRegionAvail();
        editorSize.y = 480.0f;

        text_editor_.Render("##ADLEditor", editorSize );

        ImGui::TableNextColumn();
        ImVec2 outputSize = ImGui::GetContentRegionAvail();
        outputSize.y = 480.0f;

        error_viewer_.Render("##ADLErrorViwer", outputSize);

        ImGui::EndTable();
    }

    ImGui::EndChild();
}

void StartScreen::UserInteractionWidget2() {

    //Get the total space from the window {x,y} window
    ImVec2 avail_size = ImGui::GetContentRegionAvail();

    ImGui::BeginChild("UserInteractionWidget2",  ImVec2(0, avail_size.y));

    ImVec2 editorSize = ImGui::GetContentRegionAvail();
    editorSize.y = 480.0f;

    text_editor_.Render("##ADLEditor", editorSize );

    // ImVec2 outputSize = ImGui::GetContentRegionAvail();
    // outputSize.y = 480.0f;
    //
    // error_viewer_.Render("##ADLErrorViwer", outputSize);

    ImGui::EndChild();
}

ScreenRequest StartScreen::draw() {
    // TODO gotta find a way to make all of the screens have this, maybe add it to the constructor?
    // for now this will do
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Start", nullptr, window_flags);

    headerWidget();

    if (DescriptionWidget() == ScreenRequest::Loading) {
        ImGui::End();
        return ScreenRequest::Loading;
    }

    UserInteractionWidget();

    ImGui::End();
    return ScreenRequest::None;
}
