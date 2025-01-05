#pragma once

#include "ShipStatsJA.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/Colliders/CharacterController.h"
#include "Engine/Engine/Time.h"

constexpr auto INPUT_HORIZONTAL = TEXT("Horizontal");
constexpr auto INPUT_VERTICAL = TEXT("Vertical");
constexpr auto INPUT_INCREASE_ALTITUDE = TEXT("IncreaseAltitude");
constexpr auto INPUT_DECREASE_ALTITUDE = TEXT("DecreaseAltitude");
constexpr auto INPUT_BOOST = TEXT("Boost");


API_CLASS() class GAME_API ShipMovement : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ShipMovement);

	API_FIELD(Attributes = "EditorDisplay(\"JAs\")") JsonAssetReference<ShipStatsJA> ship_stats_JA_asset;

	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<CharacterController> character_controller = nullptr;
	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Actor> camera_socket = nullptr;
    API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Actor> ship_actor = nullptr;
    
    void OnEnable() override;
    void OnDisable() override;
    void OnStart() override;
    void OnUpdate() override;

private:
    void input_reading();
    void get_keys_input();
    void get_axis_input();
    void move(const Vector3& direction, const float& speed) const;
    void mouse_look();


private:
    ShipStatsJA* ship_stats_ = nullptr;

    Vector3 movement_vector_ = Vector3::Zero;
    Vector2 mouse_delta_ = Vector2::Zero;
    float yaw_ = 0.f;
    float pitch_ = 0.f;

    float ship_speed_ = 0.f;
};
