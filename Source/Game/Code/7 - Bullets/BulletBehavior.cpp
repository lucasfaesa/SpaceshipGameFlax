#include "BulletBehavior.h"

BulletBehavior::BulletBehavior(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void BulletBehavior::OnStart()
{
}

void BulletBehavior::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void BulletBehavior::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void BulletBehavior::OnUpdate()
{
    
}

void BulletBehavior::Setup(const Vector3& direction) const
{
    MoveBullet(direction);
}

void BulletBehavior::MoveBullet(const Vector3& direction) const
{
    rigidbody->AddForce(direction * bulletSpeed, ForceMode::VelocityChange);
}
