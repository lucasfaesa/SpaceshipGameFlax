#pragma once

#include "Engine/Core/Types/LayersMask.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"

constexpr auto INPUT_FIRE = TEXT("Fire");

API_CLASS() class GAME_API ShipCombat : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ShipCombat);

	API_FIELD(Attributes) ScriptingObjectReference<Actor> shootingReference = nullptr;
    API_FIELD() LayersMask layers_to_hit;

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:
    bool canShoot_ = true;
    void InputReading();
    void Shoot();
};
