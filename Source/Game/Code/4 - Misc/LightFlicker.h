#pragma once

#include <vector>

#include "Engine/Content/AssetReference.h"
#include "Engine/Level/Actors/PointLight.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"


API_CLASS() class GAME_API LightFlicker : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(LightFlicker);

	API_FIELD(Attributes = "EditorDisplay(\"References\")") Array<ScriptingObjectReference<PointLight>> lights;

	API_FIELD(Attributes = "EditorDisplay(\"Data\")") float min_delay_between_flick;
	API_FIELD(Attributes = "EditorDisplay(\"Data\")") float max_delay_between_flick;
	API_FIELD(Attributes = "EditorDisplay(\"Data\")") float minimum_intensity;
	API_FIELD(Attributes = "EditorDisplay(\"Data\")") float maximum_intensity;


    // [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

private:
    float timer_;
    float delay_ = 0;
};
