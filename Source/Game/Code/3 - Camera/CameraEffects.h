#pragma once

#include <future>

#include "Engine/Scripting/Script.h"
#include "Game/Code/1 - Player/ShipMovement.h"
#include "Engine/Level/Actors/Camera.h"
#include "Engine/Particles/ParticleEffect.h"
#include "Engine/Particles/ParticleEmitter.h"

API_CLASS() class GAME_API CameraEffects : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(CameraEffects);

	API_FIELD(Attributes = "EditorDisplay(\"JAs\")") JsonAssetReference<ShipStatsJA> ship_stats_JA_asset;

	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<ShipMovement> character_controller = nullptr;
    API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Camera> camera = nullptr;
    API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<ParticleEffect> speed_lines_particle = nullptr;

	// [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:

    float shipCurrentVelocity = 0;
    float shipMinVelocity = 0;
    float shipMaxVelocity = 0;
    float shipMinFov = 0;
    float shipMaxFov = 0;
    float current_camera_FOV = 60;

    float camera_shake_intensity;
    float camera_shake_ship_speed_threshold = 0.95f;
    float speed_lines_ship_speed_threshold = 0.75f; 

    float stop_speed_lines_timer = 0.f;
    float stop_speed_lines_delay;
    StringView  speed_lines_emitter = TEXT("SpeedLinesEmitter");
    StringView  speed_lines_spawn_rate_parameter = TEXT("SpawnRate");

    Vector3 cameraOriginalPos;

    ShipStatsJA* ship_stats_ = nullptr;

    float CalculateFov();
    void UpdateCameraFov();
    void ApplyCameraShake() const;
    void UpdateCameraShakeStrength();
    void UpdateSpeedLinesParticle();
};
