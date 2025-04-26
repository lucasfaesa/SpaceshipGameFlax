// SplineSpawner.cpp
#include "SplineSpawner.h"

#include "Engine/Core/Random.h"
#include "Game/Code/3 - Camera/CameraEffects.h"
#include "Game/Code/Util/SplineDistanceSampler.h"

SplineSpawner::SplineSpawner(const SpawnParams& params)
    : Script(params)
{
    _tickUpdate = false; // only spawning in OnStart
}

void SplineSpawner::OnStart()
{
    if (!spline || !actorToSpawn || amount <= 0)
        return;

    constexpr int kSampleCount = 200;
    spline_distance_sampler.sampleCount = kSampleCount;
    spline_distance_sampler.Initialize(spline);

    const float totalLength = spline->GetSplineLength();
    const int count = Math::Max(1, amount);
    const float step = (count > 1) ? totalLength / (count - 1) : 0.0f;

    const Vector3 maxOffset = maxRandomOffset;
    const float maxRot = maxRandomRotation;
    const int maxScale = maxRandomScale;

    // Helper lambdas
    auto RandomOffset = [](const Vector3& maxPos) -> Vector3 {
        return Vector3{
            Random::RandRange(-maxPos.X, maxPos.X),
            Random::RandRange(-maxPos.Y, maxPos.Y),
            Random::RandRange(-maxPos.Z, maxPos.Z)
        };
    };

    auto RandomRotQuat = [](float maxAngle) -> Quaternion{
        // build a random Euler then convert once
        const float x = Random::RandRange(-maxAngle, maxAngle);
        const float y = Random::RandRange(-maxAngle, maxAngle);
        const float z = Random::RandRange(-maxAngle, maxAngle);
        return Quaternion::Euler(x, y, z);
    };


    // spawn actors evenly by distance
    for (int i = 0; i < amount; ++i)
    {
        const float dist = step * i;
        const float t = spline_distance_sampler.GetTAtDistance(dist);

        Vector3 worldPos = spline->GetSplinePoint(t) + RandomOffset(maxOffset);
        Quaternion worldRot = spline->GetSplineOrientation(t) * RandomRotQuat(maxRot);

        Actor* spawned = PrefabManager::SpawnPrefab(actorToSpawn, worldPos, worldRot);
        float uniformScale = Random::RandRange(1, maxScale);
        spawned->SetLocalScale(Vector3(uniformScale));
        spawned->SetParent(spline);
    }
}
