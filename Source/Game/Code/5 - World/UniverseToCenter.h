#pragma once

#include <string>

#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"


class ParticleEffect;
API_CLASS() class GAME_API UniverseToCenter : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(UniverseToCenter);


	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Actor> universeActor;
	API_FIELD(Attributes = "EditorDisplay(\"References\")") ScriptingObjectReference<Actor> shipActor;

    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float distanceThreshold = 25000.f;

    // [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

    static const std::string WILL_RESET_WORLD_TO_CENTER_EVENT;
    static const std::string RESET_WORLD_TO_CENTER_EVENT;

};
