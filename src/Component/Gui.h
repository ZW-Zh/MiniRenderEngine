#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"
#include <locale>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include "Structure/d3dUtil.h"
using namespace std;

class Gui
{
    
    public:
    static unordered_map<int,wstring> modelFilePath;
    static int currentModelIndex;
    static int currentCameraIndex;
    static void GetModel()
    {
        int index = 0;
        for (auto& i : filesystem::directory_iterator("./model/")) {
            cout << i.path().string()<< endl;
            wstring fileName = i.path().wstring().substr(8).c_str();
            wcout << i.path().wstring().substr(8).c_str() << endl;
            modelFilePath.insert({index++, i.path().wstring()});
        }
    }
    
    static void setGUI()
    {
        float v = 0.5;
        static int counter = 0;
        //ImGui::Begin("Hello, world!");   
                               // Create a window called "Hello, world!" and append into it.
        bool a = true;
        ImGui::ShowDemoWindow(&a);

        //在begin之前set位置
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        //ImGuiCond_FirstUseEver会记录第一次的大小位置，之后每次打开都是上一次设置的
        //ImGuiCond_Always改变不了位置大小
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkSize.x / 3,main_viewport->WorkSize.y / 3), ImGuiCond_Once);
        
        ImGui::Begin("choose Model");
        
        vector<string> modelNames;
        for(auto& i : Gui::modelFilePath)
        {   
            wstring str = i.second.substr(8);
            string res = d3dUtil::wstringTostring(str);
            
            modelNames.push_back(res);
        }

        //static int item_current_idx = 0; // Here we store our selection data as an index.
        string combo_preview_value = modelNames[currentModelIndex];  // Pass in the preview value visible before opening the combo (it could be anything)
        if (ImGui::BeginCombo("combo 1", combo_preview_value.c_str(), ImGuiComboFlags_None))
        {
            for (int n = 0; n < modelNames.size(); n++)
            {
                const bool is_selected = (currentModelIndex == n);
                if (ImGui::Selectable(modelNames[n].c_str(), is_selected))
                    currentModelIndex = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        
        const char* cameraItems[] = {"Common Camera","FPS Camera"};
        ImGui::Combo("Camera Type", &currentCameraIndex, cameraItems, IM_ARRAYSIZE(cameraItems));

        ImGui::End();
    }
    ~Gui()
    {
        
    }

};
