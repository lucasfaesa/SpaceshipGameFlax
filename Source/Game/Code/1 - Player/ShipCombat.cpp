#include "ShipCombat.h"

#include "Engine/Debug/DebugDraw.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Engine/Time.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Actor.h"
#include "Engine/Level/Prefabs/PrefabManager.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Physics/Types.h"
#include "Engine/Physics/Actors/PhysicsColliderActor.h"
#include "Game/Code/7 - Bullets/BulletBehavior.h"

ShipCombat::ShipCombat(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void ShipCombat::OnStart()
{
    if (shipCombatJaAsset == nullptr)
    {
        _tickUpdate = false;
        return;
    }
    shipCombatJAInstance_ = shipCombatJaAsset.GetInstance();
}

void ShipCombat::OnEnable()
{

}

void ShipCombat::OnDisable()
{

}

void ShipCombat::OnUpdate()
{
    

    InputReading();
}

void ShipCombat::InputReading()
{
    if (Input::GetActionState(INPUT_FIRE) == InputActionState::Pressing)
    {
        canShoot_ = true;
        Shoot();
    }
}

void ShipCombat::Shoot()
{
    if (!canShoot_ || Time::GetGameTime() - lastShotTime_ < shipCombatJAInstance_->DelayBetweenShots)
        return;

    Actor* bullet = PrefabManager::SpawnPrefab(bulletPrefab,
												shootingReference[nextShotIndex_]->GetPosition(),
											shootingReference[nextShotIndex_]->GetOrientation());

    BulletBehavior* bullet_behavior = bullet->FindScript<BulletBehavior>();
    bullet_behavior->Setup(shootingReference[nextShotIndex_]->GetTransform().GetForward().GetNormalized());

    // Now increment the index, wrapping around
    nextShotIndex_ = (nextShotIndex_ + 1) % shootingReference.Count();


    lastShotTime_ = Time::GetGameTime();
    /*RayCastHit hit;
    if (Physics::RayCast(shootingReference->GetPosition(), shootingReference->GetDirection(), hit, MAX_float, layers_to_hit))
    {
        
        DEBUG_DRAW_SPHERE(BoundingSphere(hit.Point, 50), Color::Red, 0.0f, true);
        DEBUG_DRAW_LINE(shootingReference->GetPosition(), hit.Point, Color::Green, 0.0f, true);

        hit.Collider->GetParent()->SetIsActive(false);
    }*/
    

    canShoot_ = false;
}
