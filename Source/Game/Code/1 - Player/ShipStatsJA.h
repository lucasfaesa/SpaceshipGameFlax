#pragma once

#include "Engine/Core/ISerializable.h"
#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Content/Assets/Model.h"
#include "Engine/Scripting/ScriptingType.h"

/// <summary>
/// ShipStatsJA Json Asset. 
/// </summary>
API_CLASS() class GAME_API ShipStatsJA : public ISerializable
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(ShipStatsJA);
public:

    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float ship_base_speed = 10.f;
    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float boost_speed_multiplier = 2.f;
    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float mouse_sensitivity = 5.f;
    API_FIELD(Attributes = "EditorDisplay(\"Data\")") Vector2 max_pitch;
    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float camera_smoothing = 10.f;
    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float ship_turn_smoothing = 10.f;
    API_FIELD(Attributes = "EditorDisplay(\"Data\")") float ship_strafe_smoothing = 10.f;

};
