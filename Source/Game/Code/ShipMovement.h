#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/Colliders/CharacterController.h"

constexpr auto INPUT_HORIZONTAL = TEXT("Horizontal");
constexpr auto INPUT_VERTICAL = TEXT("Vertical");
constexpr auto INPUT_INCREASE_ALTITUDE = TEXT("IncreaseAltitude");
constexpr auto INPUT_DECREASE_ALTITUDE = TEXT("DecreaseAltitude");


API_CLASS() class GAME_API ShipMovement : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ShipMovement);

	API_FIELD() ScriptingObjectReference<CharacterController> character_controller = nullptr;
    API_FIELD() float ship_speed = 10.f;

    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:
    void input_reading();
    void move(const Vector3& direction, const float& speed) const;

private:
    Vector3 movement_vector_ = Vector3::Zero;
};
