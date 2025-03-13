#include "ShipMovement.h"

#include <stdexcept>

#include "Engine/Core/Math/Matrix.h"
#include "Engine/Engine/Screen.h"


ShipMovement::ShipMovement(const SpawnParams& params)
    : Script(params)
{
    _tickUpdate = true;
}

void ShipMovement::OnEnable()
{
    Screen::SetCursorLock(CursorLockMode::Locked);
    Screen::SetCursorVisible(false);
}

void ShipMovement::OnDisable(){ }


void ShipMovement::OnStart()
{
    if (!character_controller || !camera_socket || !ship_actor || !ship_stats_JA_asset)
    {
        throw std::runtime_error("Missing refs");
	}
    else
    {
        _tickUpdate = true;
        ship_stats_ = ship_stats_JA_asset.GetInstance();
        last_movement_direction_ = ship_actor->GetTransform().GetWorld().GetForward(); // Initialize to forward
    }
}

void ShipMovement::OnUpdate()
{
    input_reading();

    move(movement_vector_, ship_speed_);
    //DebugLog::Log(LogType::Info, String::Format(TEXT("move: {0}"), movement_vector_));
}

void ShipMovement::input_reading()
{
    get_axis_input();
    get_keys_input();
    mouse_look();
}

void ShipMovement::get_axis_input()
{
    const float horizontal_value = Input::GetAxis(INPUT_HORIZONTAL);
    const float depth_value = Input::GetAxis(INPUT_VERTICAL);

    movement_vector_ = Vector3(horizontal_value, movement_vector_.Y,depth_value);
}

void ShipMovement::get_keys_input()
{
    altitude_delta();

    boost_delta();

    brake_delta();

    //DebugLog::Log(LogType::Info, String::Format(TEXT("Speed:{0}"), ship_speed_));
}

void ShipMovement::altitude_delta()
{
    float altitude_value = 0.0f;

    if (Input::GetActionState(INPUT_INCREASE_ALTITUDE) == InputActionState::Pressing)
    {
        altitude_value = 1.0f;
    }
    if (Input::GetActionState(INPUT_DECREASE_ALTITUDE) == InputActionState::Pressing)
    {
        altitude_value = -1.0f;
    }

    movement_vector_.Y = altitude_value;
}

void ShipMovement::boost_delta()
{
    // Update speed directly based on input
    if (!movement_vector_.IsZero())
    {
        if (Input::GetActionState(INPUT_BOOST) == InputActionState::Pressing)
        {
            ship_speed_ = ship_stats_->ship_base_speed * ship_stats_->boost_speed_multiplier;
        }
        else
        {
            ship_speed_ = ship_stats_->ship_base_speed;
        }
    }
    else
    {
        ship_speed_ = 0.0f; // No movement input, no speed
    }
}

void ShipMovement::brake_delta()
{
    if (Input::GetActionState(INPUT_BRAKE) == InputActionState::Pressing)
    {
        // Override movement input and speed when braking is active
        movement_vector_ = Vector3::Zero;
        ship_speed_ = 0.0f;


        float brakeFactor = ship_stats_->ship_brake_deceleration;
        current_velocity_ = Vector3::Lerp(current_velocity_, Vector3::Zero, brakeFactor * Time::GetDeltaTime());
    }
    
}

void ShipMovement::move(const Vector3& direction, const float& speed)
{
    const Matrix ship_transform = ship_actor->GetTransform().GetWorld();
    Vector3 target_velocity = Vector3::Zero;

    if (!direction.IsZero())
    {
        // Transform the direction into world space
        Vector3 transformed_direction;
        Vector3::TransformNormal(direction, ship_transform, transformed_direction);
        transformed_direction.Normalize();

        // Compute the target velocity
        target_velocity = transformed_direction * speed;
    }

    // Determine smoothing factor based on input presence
    const float smoothing_factor = direction.IsZero()
        ? ship_stats_->ship_deceleration_smoothing // No input, decelerating
        : ship_stats_->ship_acceleration_smoothing; // Input present, accelerating

    // Smoothly interpolate current velocity towards the target velocity
    current_velocity_ = Vector3::Lerp(current_velocity_, target_velocity, smoothing_factor * Time::GetDeltaTime());


    if ((current_velocity_ - target_velocity).Length() < stop_lerp_threshold)
    {
        current_velocity_ = target_velocity;
    }

    // Apply movement
    character_controller->Move(current_velocity_ * Time::GetDeltaTime());

    // Update the last movement direction
    if (!current_velocity_.IsZero())
    {
        last_movement_direction_ = current_velocity_.GetNormalized();
    }

}

void ShipMovement::mouse_look()
{
    mouse_delta_ = Vector2(Input::GetAxis(TEXT("Mouse X")), Input::GetAxis(TEXT("Mouse Y")));

    yaw_ += mouse_delta_.X * ship_stats_->mouse_sensitivity * Time::GetDeltaTime();
    pitch_ += mouse_delta_.Y * ship_stats_->mouse_sensitivity * Time::GetDeltaTime();
    pitch_ = Math::Clamp(pitch_, ship_stats_->max_pitch.X, ship_stats_->max_pitch.Y);

    Quaternion const target_orientation = Quaternion::Euler(pitch_, yaw_, 0);
    float const camera_lerp_amount = ship_stats_->camera_smoothing * Time::GetDeltaTime();
    float const ship_lerp_amount = ship_stats_->ship_turn_smoothing * Time::GetDeltaTime();
    Quaternion new_camera_orientation;
    Quaternion new_ship_orientation;

    Quaternion::Slerp(camera_socket->GetOrientation(), target_orientation, camera_lerp_amount, new_camera_orientation);
    Quaternion::Slerp(ship_actor->GetOrientation(), target_orientation, ship_lerp_amount, new_ship_orientation);

    camera_socket->SetOrientation(new_camera_orientation);
    ship_actor->SetOrientation(new_ship_orientation);
}



