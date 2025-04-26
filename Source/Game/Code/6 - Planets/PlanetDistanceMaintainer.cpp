#include "PlanetDistanceMaintainer.h"

#include "Engine/Level/Actor.h"
#include "Game/Code/5 - World/UniverseToCenter.h"
#include "Game/Code/Util/EventHub.h"

PlanetDistanceMaintainer::PlanetDistanceMaintainer(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void PlanetDistanceMaintainer::OnEnable()
{
    resetWorldEventCallback_ = [this](const std::vector<void*>& args) { OnWorldReset(args); };

    EventHub::Subscribe(UniverseToCenter::RESET_WORLD_TO_CENTER_EVENT, resetWorldEventCallback_);
}

void PlanetDistanceMaintainer::OnDisable()
{
    EventHub::Unsubscribe(UniverseToCenter::RESET_WORLD_TO_CENTER_EVENT, resetWorldEventCallback_);
}

void PlanetDistanceMaintainer::OnUpdate()
{
	if (!Target)
        return;

    // Get current target position
    Vector3 targetPos = Target->GetPosition();

    if (!bInitialized)
    {
        // Store the initial position on first update
        PreviousTargetPos = targetPos;
        bInitialized = true;
        return;
    }

    // Compute how far the target moved since last frame
    Vector3 delta = targetPos - PreviousTargetPos;
    // Update for the next frame
    PreviousTargetPos = targetPos;

    // Move this actor by the same delta to maintain the initial offset
    if (!delta.IsZero())
    {
        Actor* self = this->GetActor();
        Vector3 newPos = self->GetPosition() + delta;
        self->SetPosition(newPos);
    }
}

void PlanetDistanceMaintainer::OnWorldReset(const std::vector<void*>& args)
{
    if (Target)
        PreviousTargetPos = Target->GetPosition();
}
