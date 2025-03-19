#include "ShipTrailsController.h"

#include "Game/Code/5 - World/UniverseToCenter.h"
#include "Game/Code/Util/EventHub.h"

ShipTrailsController::ShipTrailsController(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void ShipTrailsController::OnStart()
{
    resetWorldEventCallback_ = [this](const std::vector<void*>& args) { OnWorldReset(args); };

    EventHub::Subscribe(UniverseToCenter::RESET_WORLD_TO_CENTER_EVENT, resetWorldEventCallback_);
}

void ShipTrailsController::OnDestroy()
{
    EventHub::Unsubscribe(UniverseToCenter::RESET_WORLD_TO_CENTER_EVENT, resetWorldEventCallback_);
}

void ShipTrailsController::OnWorldReset(const std::vector<void*>& args)
{
    for (const auto& trail : shipTrails)
    {
        if (!trail)
            return;

		trail->ResetSimulation();
    }
}


