#include "UI/Screens/StartScreen.h"

#include <fstream>
#include <iostream>

#include "imgui.h"
#include <string>
#include "misc/cpp/imgui_stdlib.h"
#include "SDL3/SDL_dialog.h"

#include "LoadFile.h"


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

        std::string output; // Clear any existing data
        while (std::getline(file, line)) {
            output += line + "\n";
        }


        auto* path = static_cast<std::string*>(userdata);
        *path = output;
    }

    FileLoader::some();
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
        ImGui::TableNextColumn(); ImGui::Text("ADL Wiki");

        ImGui::EndTable();
    }
    //ImGui::Separator();

    ImGui::EndChild();
}
void StartScreen::DescriptionWidget() {

    ImGui::BeginChild("DescriptionWidget",  ImVec2(0, 55));

    if (ImGui::BeginTable("descriptionGridTable", 2, ImGuiTableFlags_Borders))
    {
        // Optional: Set up headers (The top row)
        //ImGui::TableSetupColumn("ID");
        //ImGui::TableSetupColumn("Name");
        //ImGui::TableSetupColumn("Action");
        //ImGui::TableHeadersRow();

        // Row 1
        ImGui::TableNextColumn();


        ImGui::Text("Start with your architecture.");
        ImGui::Text("Write an ADL or Load a File");
        ImGui::Text("Uploading replaces the editor contents. You can keep editing after upload; it does not run the parser.");


        ImGui::TableNextColumn();
        if (ImGui::Button("Load a File")) {
            SDL_ShowOpenFileDialog(
                callback,
                &context.adlSource,
                activeWindow,
                filters,
                SDL_arraysize(filters),
                nullptr,
                false
            );

        }

        ImGui::EndTable();
    }
    //ImGui::Separator();

    ImGui::EndChild();
}
void StartScreen::UserInteractionWidget() {

    //Get the total space from the window {x,y} window
    ImVec2 avail_size = ImGui::GetContentRegionAvail();

    ImGui::BeginChild("UserInteractionWidget",  ImVec2(0, avail_size.y));

    if (ImGui::BeginTable("UserInteractionGridTable", 2, ImGuiTableFlags_Borders, ImVec2(0, 500)))
    {
        // Optional: Set up headers (The top row)
        //ImGui::TableSetupColumn("ID");
        //ImGui::TableSetupColumn("Name");
        //ImGui::TableSetupColumn("Action");
        //ImGui::TableHeadersRow();

        // Row 1
        ImGui::TableNextColumn();
        /*TODO ideally this should be hidden and calculating only when the screen changes,
        * I found that you can store things in the imgui heap, maybe I can store this info, there? and be able to
        * notify when changes occur? idk yet that should be added in the tasks
        */


        //get half of the window
        float target_width = avail_size.x * 0.5f;

        //get the full height of window
        float target_height = avail_size.y - 30.0f;

        if (ImGui::InputTextMultiline("##InputBox", &context.adlSource, ImVec2(target_width, target_height))) {}

        ImGui::TableNextColumn(); ImGui::Text("ADL Wiki");

        ImGui::EndTable();
    }
    //ImGui::Separator();

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
    DescriptionWidget();
    UserInteractionWidget();

    /*TODO ideally this should be hidden and calculating only when the screen changes,
    * I found that you can store things in the imgui heap, maybe I can store this info, there? and be able to
    * notify when changes occur? idk yet that should be added in the tasks
    */
    //Get the total space from the window {x,y} window
    // ImVec2 avail_size = ImGui::GetContentRegionAvail();
    //
    // //get half of the window
    // float target_width = avail_size.x * 0.5f;
    //
    // //get the full height of window
    // float target_height = avail_size.y;
    //
    // if (ImGui::InputTextMultiline("##InputBox", &context.adlSource, ImVec2(target_width, target_height))) {}
    // ImGui::SameLine();
    //
    // ImGui::BeginChild("Selection",  ImVec2(0, 100));
    // // just a helper to make sure things are properly updating
    // ImGui::Text("Current input length: %zu", context.adlSource.size());
    //
    // if (ImGui::Button("Load a File")) {
    //     SDL_ShowOpenFileDialog(
    //         callback,
    //         &context.adlSource,
    //         activeWindow,
    //         filters,
    //         SDL_arraysize(filters),
    //         nullptr,
    //         false
    //     );
    //
    // }
    // ImGui::SameLine();
    //
    // if (ImGui::Button("Build Simulator") && !context.adlSource.empty()) {
    //
    // // TODO change this soon, when std::expect is implemented
    //     auto* result = parser.parseFromString(context.adlSource);
    //     if (result) {
    //         std::cout << "parsing was successful" << std::endl;
    //     }
    //     else {
    //         std::cout << "parsing was not successful" << std::endl;
    //
    //     }
    //
    //     ImGui::EndChild();
    //     ImGui::End();
    //
    //     return ScreenRequest::Loading;
    // }

    //ImGui::EndChild();
    ImGui::End();
    return ScreenRequest::None;
}
