#include "BulletBehavior.h"

#include "Engine/Debug/DebugLog.h"
#include "Engine/Engine/Time.h"
#include "Game/Code/1 - Player/ShipCombatJA.h"

BulletBehavior::BulletBehavior(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void BulletBehavior::OnStart()
{
    if (shipCombatJA == nullptr)
    {
        _tickUpdate = false;
        return;
    }

    shipCombatJAInstance = shipCombatJA.GetInstance();
}

void BulletBehavior::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
    isAvailable = false;
}

void BulletBehavior::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
    isAvailable = true;
}

void BulletBehavior::OnUpdate()
{
    bulletTimer_ += Time::GetDeltaTime();

    if (bulletTimer_ >= shipCombatJAInstance->BulletLifetime)
        this->GetActor()->SetIsActive(false);
}

void BulletBehavior::Setup(const Vector3& direction) const
{
    MoveBullet(direction);
}

void BulletBehavior::Reset(const Vector3& direction, const Quaternion& rotation)
{
    GetActor()->SetPosition(direction);
    GetActor()->SetOrientation(rotation);
    GetActor()->SetIsActive(true);
    bulletTimer_ = 0.f;
}

void BulletBehavior::MoveBullet(const Vector3& direction) const
{
    rigidbody->AddForce(direction * (bulletSpeed * 10), ForceMode::VelocityChange);
}
