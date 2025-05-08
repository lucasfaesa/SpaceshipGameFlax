#pragma once

#include "Engine/Content/JsonAssetReference.h"
#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"

class ShipCombatJA;
API_CLASS() class GAME_API BulletBehavior : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(BulletBehavior);

	API_FIELD(Attributes) JsonAssetReference<ShipCombatJA> shipCombatJA = nullptr;
	API_FIELD(Attributes) ScriptingObjectReference<RigidBody> rigidbody = nullptr;
    API_FIELD(Attributes) float bulletSpeed;

    // [Script]
    void OnStart() override;
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

public:
    void Setup(const Vector3& direction) const;
    void Reset(const Vector3& direction, const Quaternion& rotation);
private:
    void MoveBullet(const Vector3& direction) const;
private:
    ShipCombatJA* shipCombatJAInstance;
    float bulletTimer_{0};
public:
    bool isAvailable = false;
};
