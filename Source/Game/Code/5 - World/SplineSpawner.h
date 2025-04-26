// SplineSpawner.h
#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Level/Prefabs/PrefabManager.h"
#include <vector>

#include "Engine/Content/AssetReference.h"
#include "Engine/Level/Actors/Spline.h"
#include "Game/Code/Util/SplineDistanceSampler.h"

API_CLASS() class GAME_API SplineSpawner : public Script
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE(SplineSpawner);

    API_FIELD(Attributes) Spline* spline = nullptr;
    API_FIELD(Attributes) AssetReference<Prefab> actorToSpawn = nullptr;
    API_FIELD(Attributes) int amount = 10;
    API_FIELD(Attributes) int sampleCount = 200;
    API_FIELD(Attributes) Vector3 maxRandomOffset;
    API_FIELD(Attributes) float maxRandomRotation;
    API_FIELD(Attributes) int maxRandomScale;

    // Distance sampling data
    float totalLength = 0.0f;
    std::vector<float> parameters;
    std::vector<float> cumulativeDist;
    SplineDistanceSampler spline_distance_sampler;

public:
    
    void OnStart() override;
};
