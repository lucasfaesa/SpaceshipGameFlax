#pragma once

#include <functional>
#include <vector>

#include "Engine/Particles/ParticleEffect.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"

API_CLASS() class GAME_API ShipTrailsController : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ShipTrailsController);

	API_FIELD(Attributes = "EditorDisplay(\"References\")") Array<ScriptingObjectReference<ParticleEffect>> shipTrails;

    // [Script]
    void OnStart() override;
    void OnDestroy() override;

private:
    std::function<void(const std::vector<void*>&)> resetWorldEventCallback_;

    void OnWorldReset(const std::vector<void*>& args);
};
