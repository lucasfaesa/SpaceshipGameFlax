#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"

class ParticleEffect;
API_CLASS() class GAME_API UniverseToCenter : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(UniverseToCenter);


	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Actor> universeActor;
	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Actor> shipActor;
    API_FIELD(Attributes = "EditorDisplay(\"References\")") Array<ScriptingObjectReference<ParticleEffect>> shipTrails;

    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float distanceThreshold = 25000.f;

    // [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:
    StringView  trail_emitter = TEXT("Trail");
    StringView  trail_spawn_rate_parameter = TEXT("SpawnRate");
    StringView  trail_lifetime_parameter = TEXT("Lifetime");
};
