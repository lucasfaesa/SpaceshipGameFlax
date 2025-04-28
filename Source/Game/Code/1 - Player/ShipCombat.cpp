#include "ShipCombat.h"

#include "Engine/Debug/DebugDraw.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Actor.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Physics/Types.h"
#include "Engine/Physics/Actors/PhysicsColliderActor.h"

ShipCombat::ShipCombat(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
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
    DebugLog::Log(TEXT("Try Shoot"));

    if (!canShoot_)
        return;

    DebugLog::Log(TEXT("Shoot"));

    RayCastHit hit;
    if (Physics::RayCast(shootingReference->GetPosition(), shootingReference->GetDirection(), hit, MAX_float, layers_to_hit))
    {
        
        DEBUG_DRAW_SPHERE(BoundingSphere(hit.Point, 50), Color::Red, 0.0f, true);
        DEBUG_DRAW_LINE(shootingReference->GetPosition(), hit.Point, Color::Green, 0.0f, true);

        hit.Collider->GetParent()->SetIsActive(false);
    }
    

    canShoot_ = false;
}
