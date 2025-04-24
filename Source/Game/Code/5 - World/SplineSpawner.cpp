#include "SplineSpawner.h"

#include "Engine/Level/Prefabs/PrefabManager.h"

SplineSpawner::SplineSpawner(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void SplineSpawner::OnStart()
{
    if (!spline || !actorToSpawn)
        return;

    for (int i = 0; i < amount; i++)
    {
        float t = (amount > 1) ? float(i) / float(amount - 1) : 0.0f;

        Vector3 localPos = spline->GetSplinePoint(t);
        Quaternion localRot = spline->GetSplineOrientation(t);

        PrefabManager::SpawnPrefab(actorToSpawn, localPos, localRot);
    }
		
	
}

void SplineSpawner::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void SplineSpawner::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void SplineSpawner::OnUpdate()
{
    // Here you can add code that needs to be called every frame
}
