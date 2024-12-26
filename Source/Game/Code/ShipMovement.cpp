#include "ShipMovement.h"



ShipMovement::ShipMovement(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}


void ShipMovement::OnEnable()
{
    if (character_controller)
    {
		DebugLog::LogWarning(TEXT("Character controller is not assigned."));
        _tickUpdate = false;
    }
        
}

void ShipMovement::OnDisable()
{
    
}

void ShipMovement::OnUpdate()
{
    input_reading();
    move(movement_vector_, ship_speed);
}

void ShipMovement::input_reading()
{
    const float horizontal_value = Input::GetAxis(INPUT_HORIZONTAL);
    const float depth_value = Input::GetAxis(INPUT_VERTICAL);
    float altitude_value = 0.0f;

    if (Input::GetActionState(INPUT_INCREASE_ALTITUDE) == InputActionState::Pressing)
    {
        altitude_value += 1.0f;
    }
    if (Input::GetActionState(INPUT_DECREASE_ALTITUDE) == InputActionState::Pressing)
    {
        altitude_value -= 1.0f;
    }

    movement_vector_ = Vector3(horizontal_value, altitude_value, depth_value);

    movement_vector_.Normalize();
    
}

void ShipMovement::move(const Vector3& direction, const float& speed) const
{
    character_controller->Move(direction * speed);
}



