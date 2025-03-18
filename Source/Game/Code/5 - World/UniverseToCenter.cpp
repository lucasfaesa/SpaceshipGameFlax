#include "UniverseToCenter.h"

#include "Engine/Debug/DebugLog.h"
#include "Engine/Level/Actor.h"
#include "Engine/Particles/ParticleEffect.h"

UniverseToCenter::UniverseToCenter(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = false;
}

void UniverseToCenter::OnStart()
{
    if (!shipActor && !universeActor)
    {
        DebugLog::Log(TEXT("Could not find ship actor"));
        _tickUpdate = false;
    }
	else
    {
        _tickUpdate = true;
    }
}

void UniverseToCenter::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void UniverseToCenter::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void UniverseToCenter::OnUpdate()
{
    DebugLog::Log(String::Format(TEXT("pos {}"), shipActor->GetPosition().Length()));

    Vector3 currentUniversePos = universeActor->GetPosition();
    Vector3 shipWorldPos = shipActor->GetPosition();

    if (shipWorldPos.Length() >= distanceThreshold)
    {
        DebugLog::Log(TEXT("Reset"));
        universeActor->SetPosition(currentUniversePos - shipWorldPos);

        for (auto& trail : shipTrails)
        {
			trail->ResetSimulation();
        }
    }
}
