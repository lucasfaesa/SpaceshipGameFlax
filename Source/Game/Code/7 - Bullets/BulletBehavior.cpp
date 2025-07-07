#include "BulletBehavior.h"

#include "Engine/Debug/DebugLog.h"
#include "Engine/Engine/Time.h"
#include "Engine/Physics/Colliders/BoxCollider.h"
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
    if (boxCollider)
    {
        // build the std::function once and store it
        triggerEnterCb_ = [this](PhysicsColliderActor* other)
            {
                this->OnTriggerEnter(other);
            };

        // bind the lambda
        boxCollider->TriggerEnter.Bind(triggerEnterCb_);
    }
}

void BulletBehavior::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
    isAvailable = true;
    if (boxCollider)
    {
        // unbind *that same* lambda
        boxCollider->TriggerEnter.Unbind(triggerEnterCb_);
    }
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

void BulletBehavior::OnTriggerEnter(PhysicsColliderActor* other)
{
    
    DebugLog::Log(other->GetParent()->GetName());

    Actor* parent = other->GetParent();
    if (parent)
    {
        DebugLog::Log(TEXT("Destroyed"));
        parent->DeleteObject();
    }
    
    DisableBullet();
}


void BulletBehavior::DisableBullet()
{
    this->GetActor()->SetIsActive(false);
    bulletTimer_ = 0.f;
}
