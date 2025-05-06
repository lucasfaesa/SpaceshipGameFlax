#pragma once

#include <vector>

#include "ShipCombatJA.h"
#include "Engine/Content/AssetReference.h"
#include "Engine/Content/JsonAssetReference.h"
#include "Engine/Core/Types/LayersMask.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"

constexpr auto INPUT_FIRE = TEXT("Fire");

API_CLASS() class GAME_API ShipCombat : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ShipCombat);

	API_FIELD(Attributes = "EditorDisplay(\"JAs\")") JsonAssetReference<ShipCombatJA> shipCombatJaAsset;

	API_FIELD(Attributes) Array<ScriptingObjectReference<Actor>> shootingReference;
    API_FIELD(Attributes) AssetReference<Prefab> bulletPrefab;
    API_FIELD(Attributes) LayersMask layers_to_hit;

    // [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:
    bool canShoot_ = true;
    byte nextShotIndex_ = 0;
    float lastShotTime_ = 0;
    ShipCombatJA* shipCombatJAInstance_ = nullptr;


private:
    void InputReading();
    void Shoot();
};
