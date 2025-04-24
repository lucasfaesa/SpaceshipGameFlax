#pragma once

#include "Engine/Content/AssetReference.h"
#include "Engine/Level/Actors/Spline.h"
#include "Engine/Scripting/Script.h"

API_CLASS() class GAME_API SplineSpawner : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(SplineSpawner);

	API_FIELD() Spline* spline = nullptr;
    API_FIELD() int amount = 20;
    API_FIELD() AssetReference<Prefab> actorToSpawn;

    // [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
};
