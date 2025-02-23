#pragma once

#include "Engine/Scripting/Script.h"
#include "Game/Code/1 - Player/ShipMovement.h"
#include "Engine/Level/Actors/Camera.h"

API_CLASS() class GAME_API CameraEffects : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(CameraEffects);

	API_FIELD(Attributes = "EditorDisplay(\"JAs\")") JsonAssetReference<ShipStatsJA> ship_stats_JA_asset;

	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<ShipMovement> character_controller = nullptr;
    API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Camera> camera = nullptr;
	// [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:

    float shipMinVelocity = 0;
    float shipMaxVelocity = 0;
    float shipMinFov = 0;
    float shipMaxFov = 0;

    ShipStatsJA* ship_stats_ = nullptr;

    float CalculateFov();
    void UpdateCameraFov();

    float current_camera_FOV = 60;
};
