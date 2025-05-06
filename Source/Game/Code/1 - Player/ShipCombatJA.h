#pragma once

#include "Engine/Core/ISerializable.h"
#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Content/Assets/Model.h"
#include "Engine/Scripting/ScriptingType.h"

/// <summary>
/// ShipCombatJA Json Asset. 
/// </summary>
API_CLASS() class GAME_API ShipCombatJA : public ISerializable
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(ShipCombatJA);
public:
    
    API_FIELD(Attributes) float DelayBetweenShots = 1.0f;
    API_FIELD(Attributes) float BulletLifetime = 5.0f;

        
};
