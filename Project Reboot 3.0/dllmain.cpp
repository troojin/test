diff --git a/Project Reboot 3.0/dllmain.cpp b/Project Reboot 3.0/dllmain.cpp
index 60ab3907d77fc9c44b66af59c6b42229cf36afd9..e85172e89c2a316edbe0bb0035728f77569fddf2 100644
--- a/Project Reboot 3.0/dllmain.cpp	
+++ b/Project Reboot 3.0/dllmain.cpp	
@@ -900,99 +900,99 @@ bool ReplicateActorHook(UActorChannel* Channel)
     LOG_INFO(LogDev, "[ReplicateActorHook] Replicating: {}", Channel->GetActor()->GetFullName());
     return ReplicateActorOriginal(Channel);
 }
 
 // #define CLIENT_ONLY // only console reboot
 
 DWORD WINAPI Main(LPVOID)
 {
 #ifndef CLIENT_ONLY
     InitLogger();
 
     std::cin.tie(0);
     std::cout.tie(0);
     std::ios_base::sync_with_stdio(false);
 
     auto MH_InitCode = MH_Initialize();
     
     if (MH_InitCode != MH_OK)
     {
         LOG_ERROR(LogInit, "Failed to initialize MinHook {}!", MH_StatusToString(MH_InitCode));
         return 1;
     }
 
     std::cout << std::format("Base Address: 0x{:x}\n", __int64(GetModuleHandleW(0)));
 
-    LOG_INFO(LogInit, "Initializing Project Reboot!");
+    LOG_INFO(LogInit, "Initializing Project AI's!");
     LOG_INFO(LogDev, "Built on {} {}", __DATE__, __TIME__);
 
 #endif 
 
     Addresses::SetupVersion();
 
     NumToSubtractFromSquadId = Engine_Version >= 424 ? 2 : Engine_Version >= 423 ? 3 : 0; // TODO: check this
     NumElementsPerChunk = std::floor(Fortnite_Version) >= 5 && Fortnite_Version <= 6 ? 0x10400 : 0x10000; // Idk what version tbh
 
     Offsets::FindAll(); // We have to do this before because FindCantBuild uses FortAIController.CreateBuildingActor
     Offsets::Print();
 
     Addresses::FindAll();
     Addresses::Init();
     Addresses::Print();
 
     bEnableRebooting = Addresses::RebootingDelegate && Addresses::FinishResurrection && Addresses::GetSquadIdForCurrentPlayer && false;
 
 #ifdef CLIENT_ONLY // CONSOLE ONLY (FOR CLIENT)
     SetConsoleTitleA("Console");
 
     // Spawn Console unreal engine Gameviewport
     static UObject* Engine = GetEngine();
     auto GameViewport = Engine->Get("GameViewport");
 
     if (!GameViewport) return 0;
 
     auto ViewportConsolePtr = GameViewport->GetPtr("ViewportConsole");
 	*ViewportConsolePtr = UGameplayStatics::SpawnObject(FindObject<UClass>(L"/Script/Engine.Console"), GameViewport);
 
     return 0;
 #endif
 
     LOG_INFO(LogDev, "Fortnite_CL: {}", Fortnite_CL);
     LOG_INFO(LogDev, "Fortnite_Version: {}", Fortnite_Version);
     LOG_INFO(LogDev, "Engine_Version: {}", Engine_Version);
 
 #ifdef ABOVE_S20
     if (Fortnite_Version < 20)
     {
-        MessageBoxA(0, "Please undefine ABOVE_S20", "Project Reboot 3.0", MB_ICONERROR);
+        MessageBoxA(0, "Please undefine ABOVE_S20", "Project AI's", MB_ICONERROR);
         LOG_ERROR(LogDev, "Aborting!");
         return 0;
     }
 #else
     if (Fortnite_Version > 20)
     {
-        MessageBoxA(0, "Please define ABOVE_S20 (compile it yourself and change inc.h)", "Project Reboot 3.0", MB_ICONERROR);
+        MessageBoxA(0, "Please define ABOVE_S20 (compile it yourself and change inc.h)", "Project AI's", MB_ICONERROR);
         LOG_ERROR(LogDev, "Aborting!");
         return 0;
     }
 #endif
 
     CreateThread(0, 0, GuiThread, 0, 0, 0);
 
     while (SecondsUntilTravel > 0)
     {
         SecondsUntilTravel -= 1;
 
         Sleep(1000);
     }
 
     bSwitchedInitialLevel = true;
 
     // Globals::bAutoRestart = IsRestartingSupported();
 
     bool isPlayspaceGamemode = PlaylistName == "/MoleGame/Playlists/Playlist_MoleGame.Playlist_MoleGame";
     static auto GameModeDefault = isPlayspaceGamemode ? FindObject<AFortGameModeAthena>(L"/Script/FortniteGame.Default__FortPlayspaceGameMode")
         : FindObject<AFortGameModeAthena>(L"/Script/FortniteGame.Default__FortGameModeBR")
         ? FindObject<AFortGameModeAthena>(L"/Script/FortniteGame.Default__FortGameModeBR") // 22.30 atleast
         : FindObject<AFortGameModeAthena>(L"/Script/FortniteGame.Default__FortGameModeAthena");
     static auto FortPlayerControllerZoneDefault = FindObject<AFortPlayerController>(L"/Script/FortniteGame.Default__FortPlayerControllerZone");
     static auto FortPlayerControllerDefault = FindObject<AFortPlayerController>(L"/Script/FortniteGame.Default__FortPlayerController");
