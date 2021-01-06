#include "gui.hpp"

GUI::GUI()
{
    workspaceTableFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY;
    windowFlags = ImGuiWindowFlags_NoTitleBar;
    active_tab = 0;
    active_response = "If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them";
    Tab t;
    tabs.push_back(t);
    Tab t2;
    t2.title = "Title2";
    tabs.push_back(t2);
}
void GUI::responseArea()
{

    if (ImGui::BeginTabBar("ResponseBar"))
    {
        if (ImGui::BeginTabItem("Body"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Headers"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Cookies"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Test Results"))
        {

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::TextWrapped("%s", active_response.c_str());
}

void GUI::workspaceBar()
{
    if (ImGui::Button("Preferences"))
    {
        ImGui::OpenPopup("Edit Preferences");
    }
    // auto f_settings_popup = pool.enqueue(&GUI::settingsPopup, this);
    this->settingsPopup();
    // settingsPopup();
    ImGui::SameLine();
    if (ImGui::Button("History"))
    {
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1fFPS", ImGui::GetIO().Framerate);
    // f_settings_popup.get();
}

void GUI::settingsPopup()
{
    centerModal();

    if (ImGui::BeginPopupModal("Edit Preferences", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Changes will be saved automatically");
        ImGui::Separator();

        ImGui::InputInt("URL Max Size", &constants->MAX_URL_SIZE);
        //  THEMES
        ImGui::Separator();
        ImGui::Text("Theme");
        if (ImGui::BeginCombo("Theme", constants->THEMES[constants->CURRENT_THEME]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(constants->THEMES); n++)
            {
                const bool is_selected = (constants->CURRENT_THEME == n);
                if (ImGui::Selectable(constants->THEMES[n], is_selected))
                    constants->CURRENT_THEME = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::ColorEdit3("Background", (float *)&constants->TEMP_BG_COLOR);
        // THEMES
        ImGui::Separator();
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            constants->setTheme();
            constants->clear_color = constants->TEMP_BG_COLOR;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            constants->TEMP_BG_COLOR = constants->clear_color;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void GUI::centerModal()
{
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void GUI::tabConfig()
{
    if (ImGui::BeginTabBar("TabItemConfig"))
    {
        static bool x = false;
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        ImVec2 WorkspaceTableSize = ImVec2(-FLT_MIN, TEXT_BASE_HEIGHT * 8);

        if (ImGui::BeginTabItem("Params"))
        {
            ImGui::Text("Query Params");
            if (ImGui::BeginTable("##table1", 5, workspaceTableFlags, WorkspaceTableSize))
            {

                ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Key");
                ImGui::TableSetupColumn("Value");
                ImGui::TableSetupColumn("Description");
                ImGui::TableSetupColumn("Del", ImGuiTableColumnFlags_WidthFixed);

                ImGui::TableHeadersRow();
                std::vector<KeyValuePair> *kvp;
                kvp = &tabs.at(active_tab).queryParams;
                for (int row = 0; row < tabs.at(active_tab).queryParams.size(); row++)
                {
                    // printf("row: %d, active_tab:%d, paramSize: %d\n", row, active_tab, tabs.at(active_tab).queryParams.size());
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::PushID(row);
                    ImGui::Checkbox("", tabs.at(active_tab).queryParams.at(row).getEnableRef());
                    ImGui::PopID();

                    ImGui::TableSetColumnIndex(1);
                    // ImGui::InputTextWithHint(" ", "some hint", tabs.at(active_tab).queryParams.at(row).getKey(), 128);
                    ImGui::PushID(tabs.at(active_tab).queryParams.at(row)._id);
                    ImGui::InputText("Key", (char *)tabs.at(active_tab).queryParams.at(row).key.c_str(), 128);
                    ImGui::PopID();

                    ImGui::TableSetColumnIndex(2);
                    ImGui::PushID(tabs.at(active_tab).queryParams.at(row)._id);
                    ImGui::InputText("Value", tabs.at(active_tab).queryParams.at(row).getValue(), 128);
                    ImGui::PopID();

                    ImGui::TableSetColumnIndex(3);
                    ImGui::PushID(tabs.at(active_tab).queryParams.at(row)._id);
                    ImGui::InputText("Description", tabs.at(active_tab).queryParams.at(row).getDescription(), 128);
                    ImGui::PopID();


                    ImGui::TableSetColumnIndex(4);

                    ImGui::PushID(row);
                    if (ImGui::Button("X"))
                    {
                        // tabs.erase(tabs.begin() + n);
                        // tabs.at(active_tab).queryParams.erase(tabs.at(active_tab).queryParams.begin() + row);
                    }
                    ImGui::PopID();
                    // ImGui::TableSetColumnIndex(column);
                    // for (int column = 1; column < 4; column++)
                    // {
                    //     ImGui::TableSetColumnIndex(column);
                    //     // ImGui::InputText("Key");
                    //     char buf[32];
                    //     sprintf(buf, "Hello %d,%d", column, row);
                    //     ImGui::TextUnformatted(buf);
                    // }
                }
                ImGui::EndTable();
                if (ImGui::Button("+"))
                {
                    KeyValuePair kvp;
                    tabs.at(active_tab).queryParams.push_back(kvp);
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Authorization"))
        {
            ImGui::Text("Authorization goes here");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Headers"))
        {
            ImGui::Text("headers go here");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Body"))
        {
            ImGui::Text("Body goes here");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Pre-Request Script"))
        {
            ImGui::Text("Pre-Requests Script goes here");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Tests"))
        {
            ImGui::Text("Tests go here");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Settings"))
        {
            ImGui::Text("Settings go here");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void GUI::render()
{
    if (ImGui::Begin("xP", NULL, windowFlags))
    {
        ImGui::BeginGroup();
        this->workspaceBar();
        ImGui::EndGroup();

        ImGui::NewLine();
        // Left Vertical
        ImGui::BeginGroup();
        {

            workspaceArea();

            // ImGui::Separator();
            // ImGui::SameLine();
        }

        ImGui::EndGroup();

        // pool.enqueue(&GUI::responseArea, this).get();
        ImGui::NewLine();
        responseArea();
        ImGui::End();
    }
    // Main Workspace
}
void GUI::workspaceArea()
{
    if (ImGui::BeginTabBar("TabItem"))
    {
        if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
        {
            Tab t;
            tabs.push_back(t);
        }
        for (size_t n = 0; n < tabs.size(); n++)
        {
            if (ImGui::BeginTabItem(tabs.at(n).title.c_str(), &tabs.at(n).isOpen, ImGuiTabItemFlags_None))
            {
                active_tab = n;
                ImGui::Text("Method");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::Combo(" ", &tabs.at(n).current_http_method, constants->REQUEST_TYPE, IM_ARRAYSIZE(constants->REQUEST_TYPE));
                ImGui::SameLine();
                ImGui::InputText("URL", (char *)tabs.at(n).getUrl(), constants->MAX_URL_SIZE);
                ImGui::SameLine();
                if (ImGui::Button("Send"))
                {
                }
                ImGui::NewLine();
                this->tabConfig();
                ImGui::EndTabItem();
            }

            if (!tabs.at(n).isOpen)
            {
                tabs.erase(tabs.begin() + n);
            }
        }
        ImGui::EndTabBar();
    }
}