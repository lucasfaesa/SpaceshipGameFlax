#pragma once

#include <string>

#include "Engine/Core/ISerializable.h"
#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Content/Assets/Model.h"
#include "Engine/Scripting/ScriptingType.h"

/// <summary>
/// ok Json Asset. 
/// </summary>
API_CLASS() class GAME_API TodoJA : public ISerializable
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(ok);
public:
    // Custom float value.
    API_FIELD(Attributes = "MultilineText") String todos ;
};
