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

void ShipMovement::OnDisable()
{
    
}


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
        ship_speed_ = ship_stats_->ship_base_speed;
    }
}

void ShipMovement::OnUpdate()
{
    input_reading();
    move(movement_vector_, ship_speed_);
}

void ShipMovement::input_reading()
{
    get_keys_input();
    get_axis_input();
    mouse_look();
}

void ShipMovement::get_axis_input()
{
    const float horizontal_value = Input::GetAxis(INPUT_HORIZONTAL);
    const float depth_value = Input::GetAxis(INPUT_VERTICAL);

    movement_vector_ = Vector3(horizontal_value, 0, depth_value);
}

void ShipMovement::get_keys_input()
{
    float altitude_value = 0.0f;

    if (Input::GetActionState(INPUT_INCREASE_ALTITUDE) == InputActionState::Pressing)
    {
        altitude_value += 1.0f;
    }
    if (Input::GetActionState(INPUT_DECREASE_ALTITUDE) == InputActionState::Pressing)
    {
        altitude_value -= 1.0f;
    }

    movement_vector_.Y = altitude_value;


    mouse_delta_ = Vector2(Input::GetAxis(TEXT("Mouse X")), Input::GetAxis(TEXT("Mouse Y")));


    if (Input::GetActionState(INPUT_BOOST) == InputActionState::Pressing)
    {
        ship_speed_ = ship_stats_->ship_base_speed * ship_stats_->boost_speed_multiplier;
    }
	else
    {
        ship_speed_ = ship_stats_->ship_base_speed;
    }
    DebugLog::Log(LogType::Info, String::Format(TEXT("Speed: {0}"), ship_speed_));

    //DebugLog::Log(LogType::Info, String::Format(TEXT("Mouse delta X:{0}, Y:{1}"), mouse_delta.X, mouse_delta.Y));
}

void ShipMovement::move(const Vector3& direction, const float& speed) const
{
    const Matrix ship_transform = ship_actor->GetTransform().GetWorld();

    Vector3 movement_direction;

    //this makes the character controller to follow the ships forward
    Vector3::TransformNormal(direction, ship_transform, movement_direction);

    if (!movement_vector_.IsZero())
        movement_direction.Normalize();

    character_controller->Move(movement_direction * speed * Time::GetDeltaTime());
}

void ShipMovement::mouse_look()
{
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



