#include "CameraEffects.h"

#include <stdexcept>

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
    }
}

void CameraEffects::OnEnable()
{
    current_camera_FOV = camera->GetFieldOfView();
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void CameraEffects::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void CameraEffects::OnUpdate()
{
    UpdateCameraFov();
    // Here you can add code that needs to be called every frame
}

float CameraEffects::CalculateFov()
{
    float shipCurrentVelocity = character_controller->GetShipCurrentVelocity().Length();

    
    return shipMinFov + ((shipCurrentVelocity - shipMinVelocity) / (shipMaxVelocity - shipMinVelocity)) * (shipMaxFov - shipMinFov);
}

void CameraEffects::UpdateCameraFov()
{
    camera->SetFieldOfView(CalculateFov());
}
