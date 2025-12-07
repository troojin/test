diff --git a/Project Reboot 3.0/gui.h b/Project Reboot 3.0/gui.h
index 1ae4782cf3626c8d5e39cb0169e88804f17450c9..021f3c497217cd96036608645b91fdde65dc083c 100644
--- a/Project Reboot 3.0/gui.h	
+++ b/Project Reboot 3.0/gui.h	
@@ -1,40 +1,41 @@
 #pragma once
 
 // TODO: Update ImGUI
 
 #pragma comment(lib, "d3d9.lib")
 
 #include <Windows.h>
 #include <dxgi.h>
 // #include <d3d11.h>
 #include <d3d9.h>
 
 #include <ImGui/imgui.h>
 #include <ImGui/imgui_impl_dx9.h>
 
 #include <string>
+#include <cstring>
 #include <imgui/imgui_impl_win32.h>
 #include <imgui/imgui_stdlib.h>
 #include <vector>
 #include <format>
 #include <imgui/imgui_internal.h>
 #include <set>
 #include <fstream>
 #include <olectl.h>
 
 #include "objectviewer.h"
 #include "FortAthenaMutator_Disco.h"
 #include "globals.h"
 #include "Fonts/ruda-bold.h"
 #include "Vector.h"
 #include "reboot.h"
 #include "botnames.h"
 #include "FortGameModeAthena.h"
 #include "UnrealString.h"
 #include "KismetTextLibrary.h"
 #include "KismetSystemLibrary.h"
 #include "GameplayStatics.h"
 #include "Text.h"
 #include <Images/reboot_icon.h>
 #include "hooking.h"
 #include "FortGadgetItemDefinition.h"
@@ -167,103 +168,193 @@ static inline void Restart() // todo move?
 	*(UNetDriver**)(__int64(LevelCollections.AtPtr(1, LevelCollectionSize)) + 0x10) = nullptr;
 
 	*/
 
 	// UGameplayStatics::OpenLevel(GetWorld(), UKismetStringLibrary::Conv_StringToName(LevelA), true, FString());
 }
 
 static inline std::string wstring_to_utf8(const std::wstring& str)
 {
 	if (str.empty()) return {};
 	const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), nullptr, 0, nullptr, nullptr);
 	std::string str_to(size_needed, 0);
 	WideCharToMultiByte(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), &str_to[0], size_needed, nullptr, nullptr);
 	return str_to;
 }
 
 static inline void InitFont()
 {
 	ImFontConfig FontConfig;
 	FontConfig.FontDataOwnedByAtlas = false;
 	ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)ruda_bold_data, sizeof(ruda_bold_data), 17.f, &FontConfig);
 }
 
 static inline void InitStyle()
 {
-	auto& mStyle = ImGui::GetStyle();
-	mStyle.FramePadding = ImVec2(4, 2);
-	mStyle.ItemSpacing = ImVec2(6, 2);
-	mStyle.ItemInnerSpacing = ImVec2(6, 4);
-	mStyle.Alpha = 0.95f;
-	mStyle.WindowRounding = 4.0f;
-	mStyle.FrameRounding = 2.0f;
-	mStyle.IndentSpacing = 6.0f;
-	mStyle.ItemInnerSpacing = ImVec2(2, 4);
-	mStyle.ColumnsMinSpacing = 50.0f;
-	mStyle.GrabMinSize = 14.0f;
-	mStyle.GrabRounding = 16.0f;
-	mStyle.ScrollbarSize = 12.0f;
-	mStyle.ScrollbarRounding = 16.0f;
-
-	ImGuiStyle& style = mStyle;
-	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
-	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
-	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
-	style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
-	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
-	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
-	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
-	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
-	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
-	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
-	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
-	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
-	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
-	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
-	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
-	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
-	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
-	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
-	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
-	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
-	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
-	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
-	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
-	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
-	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
-	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
-	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
-	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
+        auto& mStyle = ImGui::GetStyle();
+        mStyle.FramePadding = ImVec2(10, 7);
+        mStyle.ItemSpacing = ImVec2(10, 6);
+        mStyle.ItemInnerSpacing = ImVec2(6, 4);
+        mStyle.Alpha = 0.98f;
+        mStyle.WindowRounding = 9.0f;
+        mStyle.FrameRounding = 8.0f;
+        mStyle.ChildRounding = 10.0f;
+        mStyle.IndentSpacing = 14.0f;
+        mStyle.ScrollbarRounding = 8.0f;
+        mStyle.GrabMinSize = 14.0f;
+        mStyle.GrabRounding = 16.0f;
+        mStyle.ScrollbarSize = 12.0f;
+
+        auto& colors = mStyle.Colors;
+        colors[ImGuiCol_Text] = ImVec4(0.92f, 0.95f, 1.00f, 1.00f);
+        colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.64f, 0.72f, 1.00f);
+        colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.05f, 0.07f, 1.00f);
+        colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.08f, 0.12f, 0.65f);
+        colors[ImGuiCol_Border] = ImVec4(0.21f, 0.28f, 0.39f, 1.00f);
+        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
+        colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.14f, 0.18f, 0.90f);
+        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.20f, 0.26f, 0.95f);
+        colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.24f, 0.32f, 1.00f);
+        colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.07f, 0.10f, 1.00f);
+        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.07f, 0.10f, 0.70f);
+        colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.12f, 0.17f, 1.00f);
+        colors[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.09f, 0.13f, 0.95f);
+        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.04f, 0.05f, 0.08f, 0.65f);
+        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.22f, 0.30f, 0.44f, 1.00f);
+        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.27f, 0.36f, 0.51f, 1.00f);
+        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.32f, 0.44f, 0.62f, 1.00f);
+        colors[ImGuiCol_CheckMark] = ImVec4(0.49f, 0.77f, 1.00f, 1.00f);
+        colors[ImGuiCol_SliderGrab] = ImVec4(0.38f, 0.65f, 1.00f, 1.00f);
+        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.53f, 0.79f, 1.00f, 1.00f);
+        colors[ImGuiCol_Button] = ImVec4(0.12f, 0.16f, 0.21f, 1.00f);
+        colors[ImGuiCol_ButtonHovered] = ImVec4(0.18f, 0.24f, 0.32f, 1.00f);
+        colors[ImGuiCol_ButtonActive] = ImVec4(0.23f, 0.31f, 0.41f, 1.00f);
+        colors[ImGuiCol_Header] = ImVec4(0.15f, 0.21f, 0.29f, 1.00f);
+        colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.26f, 0.36f, 1.00f);
+        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.34f, 0.46f, 1.00f);
+        colors[ImGuiCol_Separator] = ImVec4(0.17f, 0.22f, 0.30f, 1.00f);
+        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.27f, 0.35f, 0.46f, 1.00f);
+        colors[ImGuiCol_SeparatorActive] = ImVec4(0.34f, 0.43f, 0.57f, 1.00f);
+        colors[ImGuiCol_ResizeGrip] = ImVec4(0.17f, 0.23f, 0.32f, 1.00f);
+        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.22f, 0.30f, 0.42f, 1.00f);
+        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.40f, 0.54f, 1.00f);
+        colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.78f, 0.94f, 0.63f);
+        colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.40f, 0.78f, 0.94f, 1.00f);
+        colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.78f, 0.94f, 0.63f);
+        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.40f, 0.78f, 0.94f, 1.00f);
+        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.52f, 0.84f, 0.43f);
+        colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.09f, 0.14f, 0.97f);
+}
+
+static inline void SectionTitle(const char* label, const char* hint = "")
+{
+        ImGui::TextColored(ImVec4(0.54f, 0.78f, 1.00f, 1.00f), "%s", label);
+        if (hint && strlen(hint) > 0)
+        {
+                ImGui::SameLine();
+                ImGui::TextDisabled("%s", hint);
+        }
+}
+
+static inline bool NavButton(const char* label, bool selected, const ImVec2& size = ImVec2(-1, 0))
+{
+        ImGui::PushID(label);
+        ImVec2 buttonSize = size;
+        if (buttonSize.x <= 0)
+                buttonSize.x = ImGui::GetContentRegionAvail().x;
+        if (buttonSize.y <= 0)
+                buttonSize.y = ImGui::GetFrameHeightWithSpacing();
+
+        ImVec2 pos = ImGui::GetCursorScreenPos();
+        ImVec2 rectMax = ImVec2(pos.x + buttonSize.x, pos.y + buttonSize.y);
+        ImDrawList* drawList = ImGui::GetWindowDrawList();
+        float rounding = ImGui::GetStyle().FrameRounding;
+
+        ImGui::InvisibleButton("##nav", buttonSize);
+        bool hovered = ImGui::IsItemHovered();
+        bool pressed = ImGui::IsItemClicked();
+
+        ImU32 topColor = ImColor(selected ? ImVec4(0.20f, 0.34f, 0.50f, 1.00f) : ImVec4(0.10f, 0.14f, 0.20f, 1.00f));
+        ImU32 bottomColor = ImColor(selected ? ImVec4(0.12f, 0.22f, 0.36f, 1.00f) : ImVec4(0.07f, 0.10f, 0.15f, 1.00f));
+        ImU32 hoverOverlay = ImColor(hovered ? ImVec4(0.07f, 0.12f, 0.20f, 0.45f) : ImVec4(0, 0, 0, 0));
+
+        drawList->AddRectFilled(pos, rectMax, ImColor(ImVec4(0.08f, 0.11f, 0.16f, 1.00f)), rounding);
+        ImVec2 innerMin = ImVec2(pos.x + 1.0f, pos.y + 1.0f);
+        ImVec2 innerMax = ImVec2(rectMax.x - 1.0f, rectMax.y - 1.0f);
+        drawList->AddRectFilledMultiColor(innerMin, innerMax, topColor, topColor, bottomColor, bottomColor);
+        if (hoverOverlay.Value.w > 0.0f)
+                drawList->AddRectFilled(pos, rectMax, hoverOverlay, rounding);
+
+        drawList->AddRect(pos, rectMax, ImColor(ImVec4(0.18f, 0.28f, 0.42f, 1.00f)), rounding);
+
+        ImVec2 textSize = ImGui::CalcTextSize(label);
+        ImVec2 textPos = ImVec2(pos.x + (buttonSize.x - textSize.x) * 0.5f, pos.y + (buttonSize.y - textSize.y) * 0.5f);
+        drawList->AddText(textPos, ImColor(ImVec4(0.84f, 0.90f, 1.00f, 1.00f)), label);
+
+        if (hovered && ImGui::IsMouseReleased(ImGuiMouseButton_Left) && !pressed)
+                pressed = true;
+
+        ImGui::PopID();
+        return pressed;
+}
+
+static inline void BeginCard(const char* label, const ImVec2& size = ImVec2(0, 0))
+{
+        ImDrawList* drawList = ImGui::GetWindowDrawList();
+        ImVec2 cursor = ImGui::GetCursorScreenPos();
+        ImVec2 avail = ImGui::GetContentRegionAvail();
+        ImVec2 cardSize = size;
+        if (cardSize.x <= 0)
+                cardSize.x = avail.x;
+        if (cardSize.y <= 0)
+                cardSize.y = avail.y;
+
+        ImVec2 cardMax = ImVec2(cursor.x + cardSize.x, cursor.y + cardSize.y);
+        ImU32 accent = ImColor(ImVec4(0.24f, 0.46f, 0.78f, 0.35f));
+        ImU32 top = ImColor(ImVec4(0.08f, 0.11f, 0.17f, 0.95f));
+        ImU32 bottom = ImColor(ImVec4(0.05f, 0.07f, 0.12f, 0.95f));
+
+        float rounding = ImGui::GetStyle().ChildRounding;
+        drawList->AddRectFilled(cursor, cardMax, bottom, rounding);
+        ImVec2 innerMin = ImVec2(cursor.x + 1.0f, cursor.y + 1.0f);
+        ImVec2 innerMax = ImVec2(cardMax.x - 1.0f, cardMax.y - 1.0f);
+        drawList->AddRectFilledMultiColor(innerMin, innerMax, top, top, bottom, bottom);
+        drawList->AddRect(cursor, cardMax, accent, rounding, 0, 1.25f);
+
+        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
+        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, ImGui::GetStyle().ChildRounding);
+        ImGui::BeginChild(label, cardSize, false, ImGuiWindowFlags_MenuBar);
+        ImGui::Dummy(ImVec2(1, 2));
+        ImGui::Separator();
+        ImGui::Dummy(ImVec2(1, 6));
+}
+
+static inline void EndCard()
+{
+        ImGui::EndChild();
+        ImGui::PopStyleVar();
+        ImGui::PopStyleColor();
 }
 
 static inline void TextCentered(const std::string& text, bool bNewLine = true) {
 	if (bNewLine)
 		ImGui::NewLine();
 
 	float win_width = ImGui::GetWindowSize().x;
 	float text_width = ImGui::CalcTextSize(text.c_str()).x;
 
 	// calculate the indentation that centers the text on one line, relative
 	// to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
 	float text_indentation = (win_width - text_width) * 0.5f;
 
 	// if text is too long to be drawn on one line, `text_indentation` can
 	// become too small or even negative, so we check a minimum indentation
 	float min_indentation = 20.0f;
 	if (text_indentation <= min_indentation) {
 		text_indentation = min_indentation;
 	}
 
 	ImGui::SameLine(text_indentation);
 	ImGui::PushTextWrapPos(win_width - text_indentation);
 	ImGui::TextWrapped(text.c_str());
 	ImGui::PopTextWrapPos();
 }
@@ -688,61 +779,128 @@ static inline DWORD WINAPI LateGameThread(LPVOID)
 		static auto Heavy = FindObject<UFortItemDefinition>(L"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsHeavy.AthenaAmmoDataBulletsHeavy");
 
 		WorldInventory->AddItem(WoodItemData, nullptr, 500);
 		WorldInventory->AddItem(StoneItemData, nullptr, 500);
 		WorldInventory->AddItem(MetalItemData, nullptr, 500);
 		WorldInventory->AddItem(Rifle, nullptr, 1);
 		WorldInventory->AddItem(Shotgun, nullptr, 1);
 		WorldInventory->AddItem(SMG, nullptr, 1);
 		WorldInventory->AddItem(MiniShields, nullptr, 6);
 		WorldInventory->AddItem(Shells, nullptr, 999);
 		WorldInventory->AddItem(Medium, nullptr, 999);
 		WorldInventory->AddItem(Light, nullptr, 999);
 		WorldInventory->AddItem(Heavy, nullptr, 999);
 
 		WorldInventory->Update();
 	}
 
 	static auto SafeZonesStartTimeOffset = GameState->GetOffset("SafeZonesStartTime");
 	GameState->Get<float>(SafeZonesStartTimeOffset) = 0.001f;
 
 	return 0;
 }
 
 static inline void MainUI()
 {
-	bool bLoaded = true;
+        bool bLoaded = true;
 
-	if (PlayerTab == -1)
-	{
-		MainTabs();
+        if (Tab == 0)
+                Tab = GAME_TAB;
 
-		if (Tab == GAME_TAB)
-		{
-			if (bLoaded)
-			{
-				StaticUI();
+        if (PlayerTab == -1)
+        {
+                auto SetTabSelection = [&](int NewTab)
+                {
+                        Tab = NewTab;
+                        PlayerTab = -1;
+                        bInformationTab = false;
+                };
+
+                ImGui::BeginChild("Sidebar", ImVec2(280, 0), true);
+                SectionTitle("Control Center", "Session overview");
+                ImGui::Text("State: %s", Globals::bStartedListening ? "Live" : "Idle");
+                ImGui::Text("Late game: %s", Globals::bLateGame.load() ? "Enabled" : "Disabled");
+                ImGui::Text("Playlist: %s", PlaylistName.empty() ? "Default" : PlaylistName.c_str());
+                ImGui::Separator();
+
+                SectionTitle("Navigation");
+                if (NavButton("Game", Tab == GAME_TAB))
+                        SetTabSelection(GAME_TAB);
+
+                if (Globals::bGoingToPlayEvent && NavButton("Event", Tab == EVENT_TAB))
+                        SetTabSelection(EVENT_TAB);
+
+                if (HasAnyCalendarModification() && NavButton("Calendar Events", Tab == CALENDAR_TAB))
+                        SetTabSelection(CALENDAR_TAB);
+
+                if (NavButton("Zone", Tab == ZONE_TAB))
+                        SetTabSelection(ZONE_TAB);
+
+                if (NavButton("Dump", Tab == DUMP_TAB))
+                        SetTabSelection(DUMP_TAB);
+
+                if (NavButton("Fun", Tab == FUN_TAB))
+                        SetTabSelection(FUN_TAB);
+
+                if (Globals::bLateGame.load() && NavButton("Lategame", Tab == LATEGAME_TAB))
+                        SetTabSelection(LATEGAME_TAB);
+
+                if (Globals::bDeveloperMode && NavButton("Developer", Tab == DEVELOPER_TAB))
+                        SetTabSelection(DEVELOPER_TAB);
+
+                if (Globals::bDeveloperMode && NavButton("Debug Logs", Tab == DEBUGLOG_TAB))
+                        SetTabSelection(DEBUGLOG_TAB);
+
+                if (NavButton("Credits", Tab == CREDITS_TAB))
+                        SetTabSelection(CREDITS_TAB);
+
+                if (!Globals::bGoingToPlayEvent && Tab == EVENT_TAB)
+                        Tab = GAME_TAB;
+
+                if (!HasAnyCalendarModification() && Tab == CALENDAR_TAB)
+                        Tab = GAME_TAB;
+
+                if (!Globals::bLateGame.load() && Tab == LATEGAME_TAB)
+                        Tab = GAME_TAB;
+
+                if (!Globals::bDeveloperMode && (Tab == DEVELOPER_TAB || Tab == DEBUGLOG_TAB))
+                        Tab = GAME_TAB;
+
+                ImGui::EndChild();
+
+                ImGui::SameLine();
+
+                ImGui::BeginChild("Content", ImVec2(0, 0), true);
+
+                if (Tab == GAME_TAB)
+                {
+                        SectionTitle("Game", "Match flow");
+                        BeginCard("Game##Card");
+
+                        if (bLoaded)
+                        {
+                                StaticUI();
 
 				if (!bStartedBus)
 				{
 					bool bWillBeLategame = Globals::bLateGame.load();
 					ImGui::Checkbox("Lategame", &bWillBeLategame);
 					SetIsLategame(bWillBeLategame);
 				}
 
 				ImGui::Text(std::format("Joinable {}", Globals::bStartedListening).c_str());
 
 				if (!Globals::bStartedListening) // hm
 				{
 					ImGui::SliderInt("Players required to start the match", &WarmupRequiredPlayerCount, 1, 100);
 				}
 
 				static std::string ConsoleCommand;
 
 				ImGui::InputText("Console command", &ConsoleCommand);
 
 				if (ImGui::Button("Execute console command"))
 				{
 					auto wstr = std::wstring(ConsoleCommand.begin(), ConsoleCommand.end());
 
 					auto aa = wstr.c_str();
 					FString cmd = aa;
@@ -849,189 +1007,201 @@ static inline void MainUI()
 							bStartedBus = true;
 
 							auto GameMode = (AFortGameMode*)GetWorld()->GetGameMode();
 							auto GameState = Cast<AFortGameStateAthena>(GameMode->GetGameState());
 
 							AmountOfPlayersWhenBusStart = GameState->GetPlayersLeft();
 
 							static auto WarmupCountdownEndTimeOffset = GameState->GetOffset("WarmupCountdownEndTime");
 							// GameState->Get<float>(WarmupCountdownEndTimeOffset) = UGameplayStatics::GetTimeSeconds(GetWorld()) + 10;
 
 							float TimeSeconds = GameState->GetServerWorldTimeSeconds(); // UGameplayStatics::GetTimeSeconds(GetWorld());
 							float Duration = 10;
 							float EarlyDuration = Duration;
 
 							static auto WarmupCountdownStartTimeOffset = GameState->GetOffset("WarmupCountdownStartTime");
 							static auto WarmupCountdownDurationOffset = GameMode->GetOffset("WarmupCountdownDuration");
 							static auto WarmupEarlyCountdownDurationOffset = GameMode->GetOffset("WarmupEarlyCountdownDuration");
 
 							GameState->Get<float>(WarmupCountdownEndTimeOffset) = TimeSeconds + Duration;
 							GameMode->Get<float>(WarmupCountdownDurationOffset) = Duration;
 
 							// GameState->Get<float>(WarmupCountdownStartTimeOffset) = TimeSeconds;
 							GameMode->Get<float>(WarmupEarlyCountdownDurationOffset) = EarlyDuration;
 						}
 					}
-				}
-			}
-		}
+                                }
+                        }
 
-		else if (Tab == PLAYERS_TAB)
-		{
+                        EndCard();
+                }
+
+                else if (Tab == PLAYERS_TAB)
+                {
 			
 		}
 
-		else if (Tab == EVENT_TAB)
-		{
-			if (ImGui::Button(std::format("Start {}", GetEventName()).c_str()))
-			{
-				StartEvent();
+                else if (Tab == EVENT_TAB)
+                {
+                        SectionTitle("Event", "Run active live events");
+                        BeginCard("Event##Card");
+
+                        if (ImGui::Button(std::format("Start {}", GetEventName()).c_str()))
+                        {
+                                StartEvent();
 			}
 
 			if (Fortnite_Version == 18.40)
 			{
 				if (ImGui::Button("Remove Storm Effect"))
 				{
 					auto ClientConnections = GetWorld()->GetNetDriver()->GetClientConnections();
 
 					for (int i = 0; i < ClientConnections.Num(); i++)
 					{
 						auto CurrentController = (AFortPlayerControllerAthena*)ClientConnections.At(i)->GetPlayerController();
 
 						static auto StormEffectClass = FindObject<UClass>(L"/Game/Athena/SafeZone/GE_OutsideSafeZoneDamage.GE_OutsideSafeZoneDamage_C");
 						auto PlayerState = CurrentController->GetPlayerStateAthena();
 						PlayerState->GetAbilitySystemComponent()->RemoveActiveGameplayEffectBySourceEffect(StormEffectClass, 1, PlayerState->GetAbilitySystemComponent());
 					}
 				}
 			}
 
 			if (Fortnite_Version == 8.51)
 			{
 				if (ImGui::Button("Unvault DrumGun"))
 				{
 					static auto SetUnvaultItemNameFn = FindObject<UFunction>(L"/Game/Athena/Prototype/Blueprints/White/BP_SnowScripting.BP_SnowScripting_C.SetUnvaultItemName");
 					auto EventScripting = GetEventScripting();
 
 					if (EventScripting)
 					{
 						FName Name = UKismetStringLibrary::Conv_StringToName(L"DrumGun");
 						EventScripting->ProcessEvent(SetUnvaultItemNameFn, &Name);
 
 						static auto PillarsConcludedFn = FindObject<UFunction>(L"/Game/Athena/Prototype/Blueprints/White/BP_SnowScripting.BP_SnowScripting_C.PillarsConcluded");
 						EventScripting->ProcessEvent(PillarsConcludedFn, &Name);
 					}
-				}
-			}
-		}
+                                }
+                        }
 
-		else if (Tab == CALENDAR_TAB)
-		{
-			if (Calendar::HasSnowModification())
-			{
-				static bool bFirst = false;
+                        EndCard();
+                }
+
+                else if (Tab == CALENDAR_TAB)
+                {
+                        SectionTitle("Calendar Events", "Holiday map states");
+                        BeginCard("Calendar##Card");
+
+                        if (Calendar::HasSnowModification())
+                        {
+                                static bool bFirst = false;
 
 				static float FullSnowValue = Calendar::GetFullSnowMapValue();
 				static float NoSnowValue = 0.0f;
 				static float SnowValue = 0.0f;
 
 				ImGui::SliderFloat(("Snow Level"), &SnowValue, 0, FullSnowValue);
 
 				if (ImGui::Button("Set Snow Level"))
 				{
 					Calendar::SetSnow(SnowValue);
 				}
 
 				if (ImGui::Button("Toggle Full Snow Map"))
 				{
 					bFirst ? Calendar::SetSnow(NoSnowValue) : Calendar::SetSnow(FullSnowValue);
 
 					bFirst = !bFirst;
 				}
 			}
 
 			if (Calendar::HasNYE())
 			{
 				if (ImGui::Button("Start New Years Eve Event"))
 				{
 					Calendar::StartNYE();
 				}
 			}
 
 			/*
 			 * Notes:
 			 * 
 			 * Dopey (8.?? to 8.??) mining stones
 			 * 
 			 * Rune events:
 			 * Sleepy (8.40) hit the rune and it moves
 			 * Leaky  (8.40) rotate 3 beams onto the rune
 			 * Sneezy (8.50) dance for progress
 			*/
-			if (Fortnite_Version == 8.40)
-			{
-				static UObject* SAR = FindObject("/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations:PersistentLevel.BP_SnowAlwaysRelevant_2");
-				if (SAR)
-				{
+                        if (Fortnite_Version == 8.40)
+                        {
+                                static UObject* SAR = FindObject("/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations:PersistentLevel.BP_SnowAlwaysRelevant_2");
+                                if (SAR)
+                                {
 					static bool LoadedSleepy = false;
 					if (!LoadedSleepy && ImGui::Button("Load Sleepy"))
 					{
 						SAR->ProcessEvent(SAR->FindFunction("LoadSleepy"));
 
 						LoadedSleepy = true;
 
 						UObject* SleepyProp = FindObject("/Game/Athena/Maps/Test/S8/SleepyMap.SleepyMap.PersistentLevel.BP_Sleepy_Prop_0");
 						UObject* SleepyM = FindObject("/Game/Athena/Maps/Test/S8/SleepyMap.SleepyMap.PersistentLevel.BP_Sleepy_M_2");
 
 						while (!SleepyProp && !SleepyM)
 						{
 							SleepyProp = FindObject("/Game/Athena/Maps/Test/S8/SleepyMap.SleepyMap.PersistentLevel.BP_Sleepy_Prop_0");
 							SleepyM = FindObject("/Game/Athena/Maps/Test/S8/SleepyMap.SleepyMap.PersistentLevel.BP_Sleepy_M_2");
 						}
 
 						Hooking::MinHook::Hook(SleepyProp, SleepyProp->FindFunction("OnDamageServer"), Calendar::OnDamageServerSleepyHook, nullptr, false, true);
 						int FiveHundred = 500;
 						*SleepyM->GetPtr<int>("MaxHealth") = 500;
 						SleepyM->ProcessEvent(SleepyM->FindFunction("RootSetProgress"), &FiveHundred);
 
 						LOG_INFO(LogDev, "Sleepy loaded!");
 					}
 
 					if (LoadedSleepy)
 					{
 						static int SleepyProgress = 0;
 						ImGui::SliderInt("Sleepy Progress", &SleepyProgress, 0, 1000);
 						if (ImGui::Button("Move Sleepy"))
 						{
 							static UObject* SleepyM = FindObject("/Game/Athena/Maps/Test/S8/SleepyMap.SleepyMap.PersistentLevel.BP_Sleepy_M_2");
 							static auto ProgressOffset = SleepyM->GetOffset("Progress");
 							*SleepyM->GetPtr<float>(ProgressOffset) = (float)SleepyProgress * (1.0f / 1000.0f);
 							static int EntryPoint = 929;
 							static auto ExecUbergraph = SleepyM->FindFunction("ExecuteUbergraph_BP_Sleepy_M");
 							SleepyM->ProcessEvent(ExecUbergraph, &EntryPoint);
-						}
-					}
-				}
+                                }
+                        }
+
+                        EndCard();
+                }
 				else
 				{
 					ImGui::Text("Failed to find BP_SnowAlwaysRelevant_C");
 				}
 			}
 
 			if (std::floor(Fortnite_Version) == 13)
 			{
 				static UObject* WL = FindObject("/Game/Athena/Apollo/Maps/Apollo_POI_Foundations.Apollo_POI_Foundations.PersistentLevel.Apollo_WaterSetup_2");
 
 				if (WL)
 				{
 					static auto MaxWaterLevelOffset = WL->GetOffset("MaxWaterLevel");
 
 					static int MaxWaterLevel = WL->Get<int>(MaxWaterLevelOffset);
 					static int WaterLevel = 0;
 
 					ImGui::SliderInt("WaterLevel", &WaterLevel, 0, MaxWaterLevel);
 
 					if (ImGui::Button("Set Water Level"))
 					{
 						Calendar::SetWaterLevel(WaterLevel);
 					}
 				}
 			}
@@ -1049,55 +1219,58 @@ static inline void MainUI()
 				UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), L"pausesafezone", nullptr);
 			}
 
 			if (ImGui::Button("Skip Zone"))
 			{
 				UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), L"skipsafezone", nullptr);
 			}
 
 			if (ImGui::Button("Start Shrink Safe Zone"))
 			{
 				UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), L"startshrinksafezone", nullptr);
 			}
 
 			if (ImGui::Button("Skip Shrink Safe Zone"))
 			{
 				auto GameMode = Cast<AFortGameModeAthena>(GetWorld()->GetGameMode());
 				auto SafeZoneIndicator = GameMode->GetSafeZoneIndicator();
 
 				if (SafeZoneIndicator)
 				{
 					SafeZoneIndicator->SkipShrinkSafeZone();
 				}
 			}
 		}
 
-		else if (Tab == DUMP_TAB)
-		{
-			ImGui::Text("These will all be in your Win64 folder!"); // TODO: Make a button to open this directory
+                else if (Tab == DUMP_TAB)
+                {
+                        SectionTitle("Data Dumps", "Write assets to disk");
+                        BeginCard("Dump##Card");
+
+                        ImGui::Text("These will all be in your Win64 folder!"); // TODO: Make a button to open this directory
 
-			static std::string FortniteVersionStr = std::format("Fortnite Version {}\n\n", std::to_string(Fortnite_Version));
+                        static std::string FortniteVersionStr = std::format("Fortnite Version {}\n\n", std::to_string(Fortnite_Version));
 
 			if (ImGui::Button("Dump Objects (ObjectsDump.txt)"))
 			{
 				auto ObjectNum = ChunkedObjects ? ChunkedObjects->Num() : UnchunkedObjects ? UnchunkedObjects->Num() : 0;
 
 				std::ofstream obj("ObjectsDump.txt");
 
 				obj << FortniteVersionStr;
 
 				for (int i = 0; i < ObjectNum; ++i)
 				{
 					auto CurrentObject = GetObjectByIndex(i);
 
 					if (!CurrentObject)
 						continue;
 
 					obj << CurrentObject->GetFullName() << '\n';
 				}
 			}
 
 			if (ImGui::Button("Dump Skins (Skins.txt)"))
 			{
 				std::ofstream SkinsFile("Skins.txt");
 
 				if (SkinsFile.is_open())
@@ -1141,87 +1314,92 @@ static inline void MainUI()
 						auto Object = AllObjects.at(i);
 
 						static auto UIDisplayNameOffset = Object->GetOffset("UIDisplayName");
 						FString PlaylistNameFStr = UKismetTextLibrary::Conv_TextToString(Object->Get<FText>(UIDisplayNameOffset));
 
 						if (!PlaylistNameFStr.Data.Data)
 							continue;
 
 						std::string PlaylistName = PlaylistNameFStr.ToString();
 
 						PlaylistsFile << std::format("[{}] {}\n", PlaylistName, Object->GetPathName());
 					}
 				}
 				else
 					std::cout << "Failed to open playlist file!\n";
 			}
 
 			if (ImGui::Button("Dump Weapons (Weapons.txt)"))
 			{
 				std::ofstream WeaponsFile("Weapons.txt");
 
 				if (WeaponsFile.is_open())
 				{
 					WeaponsFile << FortniteVersionStr;
 
-					auto DumpItemDefinitionClass = [&WeaponsFile](UClass* Class) {
-						auto AllObjects = GetAllObjectsOfClass(Class);
+                                auto DumpItemDefinitionClass = [&WeaponsFile](UClass* Class) {
+                                        auto AllObjects = GetAllObjectsOfClass(Class);
 
-						for (int i = 0; i < AllObjects.size(); i++)
-						{
+                                        for (int i = 0; i < AllObjects.size(); i++)
+                                        {
 							auto Object = AllObjects.at(i);
 
 							static auto DisplayNameOffset = Object->GetOffset("DisplayName");
 							FString ItemDefinitionFStr = UKismetTextLibrary::Conv_TextToString(Object->Get<FText>(DisplayNameOffset));
 
 							if (!ItemDefinitionFStr.Data.Data)
 								continue;
 
 							std::string ItemDefinitionName = ItemDefinitionFStr.ToString();
 
 							// check if it contains gallery or playset and just ignore?
 
 							WeaponsFile << std::format("[{}] {}\n", ItemDefinitionName, Object->GetPathName());
 						}
 					};
 
-					DumpItemDefinitionClass(UFortWeaponItemDefinition::StaticClass());
-					DumpItemDefinitionClass(UFortGadgetItemDefinition::StaticClass());
-					DumpItemDefinitionClass(FindObject<UClass>("/Script/FortniteGame.FortAmmoItemDefinition"));
-				}
-				else
-					std::cout << "Failed to open playlist file!\n";
-			}
-		}
-		else if (Tab == UNBAN_TAB)
-		{
+                                        DumpItemDefinitionClass(UFortWeaponItemDefinition::StaticClass());
+                                        DumpItemDefinitionClass(UFortGadgetItemDefinition::StaticClass());
+                                        DumpItemDefinitionClass(FindObject<UClass>("/Script/FortniteGame.FortAmmoItemDefinition"));
+                                }
+                                else
+                                        std::cout << "Failed to open playlist file!\n";
+                        }
+
+                        EndCard();
+                }
+                else if (Tab == UNBAN_TAB)
+                {
 
 		}
-		else if (Tab == FUN_TAB)
-		{
-			static std::string ItemToGrantEveryone;
-			static int AmountToGrantEveryone = 1;
+                else if (Tab == FUN_TAB)
+                {
+                        SectionTitle("Fun", "Quick experiments");
+                        BeginCard("Fun##Card");
+
+                        static std::string ItemToGrantEveryone;
+                        static int AmountToGrantEveryone = 1;
 
 			ImGui::InputFloat("Starting Shield", &StartingShield);
 			ImGui::InputText("Item to Give", &ItemToGrantEveryone);
 			ImGui::InputInt("Amount to Give", &AmountToGrantEveryone);
 
 			if (ImGui::Button("Destroy all player builds"))
 			{
 				bShouldDestroyAllPlayerBuilds = true;
 			}
 
 			if (ImGui::Button("Give Item to Everyone"))
 			{
 				auto ItemDefinition = FindObject<UFortItemDefinition>(ItemToGrantEveryone, nullptr, ANY_PACKAGE);
 				
 				if (ItemDefinition)
 				{
 					static auto World_NetDriverOffset = GetWorld()->GetOffset("NetDriver");
 					auto WorldNetDriver = GetWorld()->Get<UNetDriver*>(World_NetDriverOffset);
 					auto& ClientConnections = WorldNetDriver->GetClientConnections();
 
 					for (int i = 0; i < ClientConnections.Num(); i++)
 					{
 						auto PlayerController = Cast<AFortPlayerController>(ClientConnections.at(i)->GetPlayerController());
 
 						if (!PlayerController->IsValidLowLevel())
@@ -1251,79 +1429,89 @@ static inline void MainUI()
 			if (GameState)
 			{
 				static auto DefaultGliderRedeployCanRedeployOffset = FindOffsetStruct("/Script/FortniteGame.FortGameStateAthena", "DefaultGliderRedeployCanRedeploy", false);
 				static auto DefaultParachuteDeployTraceForGroundDistanceOffset = GameState->GetOffset("DefaultParachuteDeployTraceForGroundDistance", false);
 
 				if (Globals::bStartedListening) // it resets accordingly to ProHenis b4 this
 				{
 					if (DefaultParachuteDeployTraceForGroundDistanceOffset != -1)
 					{
 						ImGui::InputFloat("Automatic Parachute Pullout Distance", GameState->GetPtr<float>(DefaultParachuteDeployTraceForGroundDistanceOffset));
 					}
 				}
 
 				if (DefaultGliderRedeployCanRedeployOffset != -1)
 				{
 					bool EnableGliderRedeploy = (bool)GameState->Get<float>(DefaultGliderRedeployCanRedeployOffset);
 
 					if (ImGui::Checkbox("Enable Glider Redeploy", &EnableGliderRedeploy))
 					{
 						GameState->Get<float>(DefaultGliderRedeployCanRedeployOffset) = EnableGliderRedeploy;
 					}
 				}
 
 				GET_PLAYLIST(GameState);
 
-				if (CurrentPlaylist)
-				{
-					bool bRespawning = CurrentPlaylist->GetRespawnType() == EAthenaRespawnType::InfiniteRespawn || CurrentPlaylist->GetRespawnType() == EAthenaRespawnType::InfiniteRespawnExceptStorm;
+                                        if (CurrentPlaylist)
+                                        {
+                                                bool bRespawning = CurrentPlaylist->GetRespawnType() == EAthenaRespawnType::InfiniteRespawn || CurrentPlaylist->GetRespawnType() == EAthenaRespawnType::InfiniteRespawnExceptStorm;
 
 					if (ImGui::Checkbox("Respawning", &bRespawning))
 					{
-						CurrentPlaylist->GetRespawnType() = (EAthenaRespawnType)bRespawning;
-					}
-				}
-			}
-		}
-		else if (Tab == LATEGAME_TAB)
-		{
-			if (bEnableReverseZone)
-				ImGui::Text(std::format("Currently {}eversing zone", bZoneReversing ? "r" : "not r").c_str());
+                                                CurrentPlaylist->GetRespawnType() = (EAthenaRespawnType)bRespawning;
+                                        }
+                                }
+                        }
+
+                        EndCard();
+                }
+                else if (Tab == LATEGAME_TAB)
+                {
+                        SectionTitle("Lategame", "Storm pacing");
+                        BeginCard("Lategame##Card");
+
+                        if (bEnableReverseZone)
+                                ImGui::Text(std::format("Currently {}eversing zone", bZoneReversing ? "r" : "not r").c_str());
 
 			ImGui::Checkbox("Enable Reverse Zone (EXPERIMENTAL)", &bEnableReverseZone);
 
-			if (bEnableReverseZone)
-			{
-				ImGui::InputInt("Start Reversing Phase", &StartReverseZonePhase);
-				ImGui::InputInt("End Reversing Phase", &EndReverseZonePhase);
-			}
-		}
-		else if (Tab == DEVELOPER_TAB)
-		{
-			static std::string ClassNameToDump;
-			static std::string FunctionNameToDump;
-			static std::string ObjectToDump;
+                        if (bEnableReverseZone)
+                        {
+                                ImGui::InputInt("Start Reversing Phase", &StartReverseZonePhase);
+                                ImGui::InputInt("End Reversing Phase", &EndReverseZonePhase);
+                        }
+
+                        EndCard();
+                }
+                else if (Tab == DEVELOPER_TAB)
+                {
+                        SectionTitle("Developer", "Unsafe tools");
+                        BeginCard("Developer##Card");
+
+                        static std::string ClassNameToDump;
+                        static std::string FunctionNameToDump;
+                        static std::string ObjectToDump;
 			static std::string FileNameToSaveTo;
 			static bool bExcludeUnhandled = true;
 
 			ImGui::Checkbox("Handle Death", &bHandleDeath);
 			ImGui::Checkbox("Fill Vending Machines", &Globals::bFillVendingMachines);
 			ImGui::Checkbox("Enable Bot Tick", &bEnableBotTick);
 			ImGui::Checkbox("Enable Rebooting", &bEnableRebooting);
 			ImGui::Checkbox("Enable Combine Pickup", &bEnableCombinePickup);
 			ImGui::Checkbox("Exclude unhandled", &bExcludeUnhandled);
 			ImGui::InputInt("Amount To Subtract Index", &AmountToSubtractIndex);
 			ImGui::InputText("Class Name to mess with", &ClassNameToDump);
 			ImGui::InputText("Object to dump", &ObjectToDump);
 			ImGui::InputText("File to save to", &FileNameToSaveTo);
 
 			ImGui::InputText("Function Name to mess with", &FunctionNameToDump);
 
 			if (ImGui::Button("Print Gamephase Step"))
 			{
 				auto GameState = Cast<AFortGameStateAthena>(GetWorld()->GetGameState());
 
 				if (GameState)
 				{
 					LOG_INFO(LogDev, "GamePhaseStep: {}", (int)GameState->GetGamePhaseStep());
 				}
 			}
@@ -1456,166 +1644,184 @@ static inline void MainUI()
 			ImGui::Text(std::format("Amount of hooks {}", AllFunctionHooks.size()).c_str());
 
 			for (auto& FunctionHook : AllFunctionHooks)
 			{
 				if (ImGui::Button(std::format("{} {} (0x{:x})", (FunctionHook.IsHooked ? "Unhook" : "Hook"), FunctionHook.Name, (__int64(FunctionHook.Original) - __int64(GetModuleHandleW(0)))).c_str()))
 				{
 					if (FunctionHook.IsHooked)
 					{
 						if (!FunctionHook.VFT || FunctionHook.Index == -1)
 						{
 							Hooking::MinHook::Unhook(FunctionHook.Original);
 						}
 						else
 						{
 							VirtualSwap(FunctionHook.VFT, FunctionHook.Index, FunctionHook.Original);
 						}
 					}
 					else
 					{
 						Hooking::MinHook::Hook(FunctionHook.Original, FunctionHook.Detour, nullptr, FunctionHook.Name);
 					}
 
 					FunctionHook.IsHooked = !FunctionHook.IsHooked;
 				}
 			} 
-			*/
-		}
+                        */
+
+                        EndCard();
+                }
                 else if (Tab == DEBUGLOG_TAB)
                 {
+                        SectionTitle("Debug Logs", "Enable verbose logging");
+                        BeginCard("Debug##Card");
+
                         ImGui::Checkbox("Floor Loot Debug Log", &bDebugPrintFloorLoot);
                         ImGui::Checkbox("Looting Debug Log", &bDebugPrintLooting);
                         ImGui::Checkbox("Swapping Debug Log", &bDebugPrintSwapping);
                         ImGui::Checkbox("Engine Debug Log", &bEngineDebugLogs);
+
+                        EndCard();
                 }
                 else if (Tab == CREDITS_TAB)
                 {
+                        SectionTitle("Credits", "Project contributors");
+                        BeginCard("Credits##Card");
                         ImGui::Text("Credits");
                         ImGui::Separator();
                         ImGui::BulletText("Uncrustables");
+
+                        EndCard();
                 }
                 else if (Tab == SETTINGS_TAB)
                 {
                         // ImGui::Checkbox("Use custom lootpool (from Win64/lootpool.txt)", &Defines::bCustomLootpool);
                 }
-	}
+
+                ImGui::EndChild();
+        }
 }
 
 static inline void PregameUI()
 {
-	StaticUI();
+        SectionTitle("Pregame Setup", "Configure the next session");
+        BeginCard("Pregame##Card");
+
+        StaticUI();
 
 	if (Engine_Version >= 422 && Engine_Version < 424)
 	{
 		ImGui::Checkbox("Creative", &Globals::bCreative);
 	}
 
 	if (Addresses::SetZoneToIndex)
 	{
 		bool bWillBeLategame = Globals::bLateGame.load();
 		ImGui::Checkbox("Lategame", &bWillBeLategame);
 		SetIsLategame(bWillBeLategame);
 	}
 
 	if (HasEvent())
 	{
 		ImGui::Checkbox("Play Event", &Globals::bGoingToPlayEvent);
 	}
 
 	if (!bSwitchedInitialLevel)
 	{
 		// ImGui::Checkbox("Use Custom Map", &bUseCustomMap);
 
 		if (bUseCustomMap)
 		{
 			// ImGui::InputText("Custom Map", &CustomMapName);
 		}
 
 		ImGui::SliderInt("Seconds until load into map", &SecondsUntilTravel, 1, 100);
 	}
 
 	ImGui::SliderInt("Players required to start the match", &WarmupRequiredPlayerCount, 1, 100);
 		
-	if (!Globals::bCreative)
-		ImGui::InputText("Playlist", &PlaylistName);
+        if (!Globals::bCreative)
+                ImGui::InputText("Playlist", &PlaylistName);
+
+        EndCard();
 }
 
 static inline HICON LoadIconFromMemory(const char* bytes, int bytes_size, const wchar_t* IconName) {
 	HANDLE hMemory = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, bytes_size, IconName);
 	if (hMemory == NULL) {
 		return NULL;
 	}
 
 	LPVOID lpBuffer = MapViewOfFile(hMemory, FILE_MAP_READ, 0, 0, bytes_size);
 
 	if (lpBuffer == NULL) {
 		CloseHandle(hMemory);
 		return NULL;
 	}
 
 	ICONINFO icon_info;
 
 	if (!GetIconInfo((HICON)lpBuffer, &icon_info)) {
 		UnmapViewOfFile(lpBuffer);
 		CloseHandle(hMemory);
 		return NULL;
 	}
 
 	HICON hIcon = CreateIconIndirect(&icon_info);
 	UnmapViewOfFile(lpBuffer);
 	CloseHandle(hMemory);
 	return hIcon;
 }
 
 static inline DWORD WINAPI GuiThread(LPVOID)
 {
 	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"RebootClass", NULL };
 	::RegisterClassEx(&wc);
 
-	HWND hwnd = ::CreateWindowExW(0L,wc.lpszClassName,(L"Project Reboot " + ([](double v) { std::wstringstream ss; ss << std::fixed << std::setprecision(2) << v; return ss.str(); })(Fortnite_Version)).c_str(),(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX), 100, 100, Width, Height, NULL, NULL, wc.hInstance, NULL);
+        HWND hwnd = ::CreateWindowExW(0L,wc.lpszClassName,(L"Project AI's " + ([](double v) { std::wstringstream ss; ss << std::fixed << std::setprecision(2) << v; return ss.str(); })(Fortnite_Version)).c_str(),(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX), 100, 100, Width, Height, NULL, NULL, wc.hInstance, NULL);
 
 
 	if (hwnd == NULL)
 	{
-		MessageBoxA(0, ("Failed to create GUI window " + std::to_string(GetLastError()) + "!").c_str(), "Reboot 3.0", MB_ICONERROR);
+                MessageBoxA(0, ("Failed to create GUI window " + std::to_string(GetLastError()) + "!").c_str(), "Project AI's", MB_ICONERROR);
 		::UnregisterClass(wc.lpszClassName, wc.hInstance);
 		return 1;
 	}
 
 	if (false) // idk why this dont work
 	{
 		auto hIcon = LoadIconFromMemory((const char*)reboot_icon_data, strlen((const char*)reboot_icon_data), L"RebootIco");
 		SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
 		SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
 	}
 
 	// SetWindowLongPtrW(hwnd, GWL_STYLE, WS_POPUP); // Disables windows title bar at the cost of dragging and some quality
 
 	// Initialize Direct3D
 	if (!CreateDeviceD3D(hwnd))
 	{
-		// MessageBoxA(0, "Failed to create D3D Device!", "Reboot 3.0", MB_ICONERROR); // Error Boxes are within the helper function.
+                // MessageBoxA(0, "Failed to create D3D Device!", "Project AI's", MB_ICONERROR); // Error Boxes are within the helper function.
 		LOG_ERROR(LogDev, "Failed to create D3D Device!");
 		CleanupDeviceD3D();
 		::UnregisterClass(wc.lpszClassName, wc.hInstance);
 		return 1;
 	}
 
 	// Show the window
 	::ShowWindow(hwnd, SW_SHOWDEFAULT);
 	::UpdateWindow(hwnd);
 
 	// Setup Dear ImGui context
 	IMGUI_CHECKVERSION();
 	ImGui::CreateContext();
 	ImGuiIO& io = ImGui::GetIO(); (void)io;
 
 	io.IniFilename = NULL; // Disable imgui.ini generation.
 	io.DisplaySize = ImGui::GetMainViewport()->Size;
 	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
 	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
 
 	// Setup Dear ImGui style
 	InitFont();
 	InitStyle();
 
 	// Setup Platform/Renderer backends
@@ -1646,126 +1852,126 @@ static inline DWORD WINAPI GuiThread(LPVOID)
 			{
 				// done = true;
 				break;
 			}
 		}
 
 		ImGui_ImplDX9_NewFrame();
 		ImGui_ImplWin32_NewFrame();
 		ImGui::NewFrame();
 
 		auto WindowSize = ImGui::GetMainViewport()->Size;
 		// ImGui::SetNextWindowPos(ImVec2(WindowSize.x * 0.5f, WindowSize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f)); // Center
 		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
 
 		tagRECT rect;
 
 		if (GetWindowRect(hwnd, &rect))
 		{
 			int width = rect.right - rect.left;
 			int height = rect.bottom - rect.top;
 			ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
 		}
 
 		if (!ImGui::IsWindowCollapsed())
 		{
-			ImGui::Begin("Project Reboot 3.0", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
+                        ImGui::Begin("Project AI's", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
 
 			Globals::bInitializedPlaylist ? MainUI() : PregameUI();
 
 			ImGui::End();
 		}
 
 		// Rendering
 		ImGui::EndFrame();
 		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
 		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
 		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
 		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
 		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
 
 		if (g_pd3dDevice->BeginScene() >= 0)
 		{
 			ImGui::Render();
 			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
 			g_pd3dDevice->EndScene();
 		}
 
 		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
 
 		// Handle loss of D3D9 device
 		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
 			ResetDevice();
 	}
 
 	LOG_INFO(LogDev, "ImGUI has quit!");
 
 	ImGui_ImplDX9_Shutdown();
 	ImGui_ImplWin32_Shutdown();
 	ImGui::DestroyContext();
 
 	CleanupDeviceD3D();
 	::DestroyWindow(hwnd);
 	::UnregisterClass(wc.lpszClassName, wc.hInstance);
 
 	return 0;
 }
 
 // Helper functions
 
 static inline bool CreateDeviceD3D(HWND hWnd)
 {
 	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
 	if (g_pD3D == NULL)
 	{
-		MessageBoxA(0, "Failed call to Direct3DCreate9!", "Reboot 3.0", MB_ICONERROR);
+                MessageBoxA(0, "Failed call to Direct3DCreate9!", "Project AI's", MB_ICONERROR);
 		return false;
 	}
 
 	// Create the D3DDevice
 	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
 	g_d3dpp.Windowed = TRUE;
 	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
 	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
 	g_d3dpp.EnableAutoDepthStencil = TRUE;
 	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
 	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
 	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
 
 	auto CreateDeviceResult = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice);
 
 	if (CreateDeviceResult == -2005530520)
 	{
 		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), L"r.setres 1280x720w", nullptr);
 
 		Sleep(50); // for good measure
 
 		return CreateDeviceD3D(hWnd);
 	}
 	else if (CreateDeviceResult < D3D_OK)
 	{
-		MessageBoxA(0, ("Failed call to CreateDevice " + std::to_string(CreateDeviceResult) + "!").c_str(), "Reboot 3.0", MB_ICONERROR);
+                MessageBoxA(0, ("Failed call to CreateDevice " + std::to_string(CreateDeviceResult) + "!").c_str(), "Project AI's", MB_ICONERROR);
 
 		return false;
 	}
 
 	return true;
 }
 
 static inline void CleanupDeviceD3D()
 {
 	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
 	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
 }
 
 static inline void ResetDevice()
 {
 	ImGui_ImplDX9_InvalidateDeviceObjects();
 	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
 	if (hr == D3DERR_INVALIDCALL)
 		IM_ASSERT(0);
 	ImGui_ImplDX9_CreateDeviceObjects();
 }
 
 extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
 
 static inline LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
