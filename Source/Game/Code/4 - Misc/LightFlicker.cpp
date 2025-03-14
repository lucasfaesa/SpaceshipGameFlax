#include "LightFlicker.h"

#include <stdexcept>

#include "Engine/Core/Random.h"
#include "Engine/Engine/Time.h"

LightFlicker::LightFlicker(const SpawnParams& params)
    : Script(params)
{
    _tickUpdate = false;
}

void LightFlicker::OnStart()
{
	for (const auto& light : lights)
	{
        if (!light)
        {
            throw std::runtime_error("Missing refs");
            return;
        }
	}
    _tickUpdate = true;
    
}

void LightFlicker::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void LightFlicker::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void LightFlicker::OnUpdate()
{
    timer_ += Time::GetDeltaTime();

    if (timer_ >= delay_)
    {
        timer_ = 0;
        delay_ = Random::RandRange(min_delay_between_flick, max_delay_between_flick);
        float value = Random::RandRange(minimum_intensity, maximum_intensity);

        for (const auto& light : lights)
        {
            light->Brightness = value;
        }
    }
}
