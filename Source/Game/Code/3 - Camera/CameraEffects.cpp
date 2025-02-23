#include "CameraEffects.h"

#include <stdexcept>

#include "Engine/Core/Random.h"

CameraEffects::CameraEffects(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
}

void CameraEffects::OnStart()
{
    if (!character_controller || !camera || !ship_stats_JA_asset)
    {
        throw std::runtime_error("Missing refs");
    }
    else
    {
        _tickUpdate = true;
        ship_stats_ = ship_stats_JA_asset.GetInstance();

        shipMaxVelocity = ship_stats_->ship_base_speed * ship_stats_->boost_speed_multiplier;
        shipMinFov = ship_stats_->min_ship_fov;
        shipMaxFov = ship_stats_->max_ship_fov;
        camera_shake_intensity = 0;

        cameraOriginalPos = camera->GetPosition();
    }
}

void CameraEffects::OnEnable()
{
    current_camera_FOV = camera->GetFieldOfView();
}

void CameraEffects::OnDisable()
{

}

void CameraEffects::OnUpdate()
{
    UpdateCameraFov();

    UpdateCameraShakeStrength();
    ApplyCameraShake();

    //DebugLog::Log(LogType::Info, String::Format(TEXT("vel: {0} thrsh{1}"), shipCurrentVelocity, shipMaxVelocity * camera_shake_ship_speed_threshold));

}

float CameraEffects::CalculateFov()
{
    shipCurrentVelocity = character_controller->GetShipCurrentVelocity().Length();

    return shipMinFov + ((shipCurrentVelocity - shipMinVelocity) / (shipMaxVelocity - shipMinVelocity)) * (shipMaxFov - shipMinFov);
}

void CameraEffects::UpdateCameraFov()
{
    camera->SetFieldOfView(CalculateFov());
}

void CameraEffects::ApplyCameraShake() const
{
    if (camera_shake_intensity > 0.0f)
    {
        // Apply smooth random shake with intensity curve
        const float currentIntensity = camera_shake_intensity * ship_stats_->shake_intensity;

        const Vector3 shakeOffset = {
            Random::RandRange(-currentIntensity, currentIntensity),
            Random::RandRange(-currentIntensity, currentIntensity),
            Random::RandRange(-currentIntensity, currentIntensity) * 0.5f
        };
        camera->SetLocalPosition(cameraOriginalPos + shakeOffset);
    }
    else
    {
        // Smoothly return to original position
        camera->SetLocalPosition(cameraOriginalPos);
    }
}

void CameraEffects::UpdateCameraShakeStrength()
{
    const float threshold = shipMaxVelocity * camera_shake_ship_speed_threshold;
    const float delta = Time::GetDeltaTime();

    if (shipCurrentVelocity > threshold)
    {
        // Wind up effect
        camera_shake_intensity = Math::Min(camera_shake_intensity + delta / ship_stats_->shake_wind_up_time, 1.0f);
    }
    else
    {
        // Wind down effect
        camera_shake_intensity = Math::Max(camera_shake_intensity - delta / ship_stats_->shake_wind_down_time, 0.0f);
    }
}
