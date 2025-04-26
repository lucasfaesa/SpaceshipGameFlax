#pragma once

#include <functional>
#include <vector>

#include "Engine/Core/Math/Vector3.h"
#include "Engine/Scripting/Script.h"

API_CLASS() class GAME_API PlanetDistanceMaintainer : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlanetDistanceMaintainer);

	// The actor to follow
	API_FIELD() Actor* Target = nullptr;

	void OnEnable() override;
	void OnDisable() override;
	void OnUpdate() override;


private:
    std::function<void(const std::vector<void*>&)> resetWorldEventCallback_;

    // Tracks whether we've initialized the previous target position
    bool bInitialized = false;
    // The target's position in the previous frame
    Vector3 PreviousTargetPos;

    void OnWorldReset(const std::vector<void*>& args);

};
