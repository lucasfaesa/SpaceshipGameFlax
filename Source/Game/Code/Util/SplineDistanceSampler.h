// SplineDistanceSampler.h
#pragma once

#include <vector>
#include "Engine/Level/Actor.h"
#include "Engine/Level/Actors/Spline.h"

class SplineDistanceSampler
{
public:
    // How many segments to subdivide the spline into for building the table
    int sampleCount = 200;

    // Populated by Initialize()
    float totalLength = 0;
    std::vector<float> parameters;      // t values from 0..1
    std::vector<float> cumulativeDist;  // world-unit distances along spline

    // Build the lookup table. Call once, e.g. in OnStart().
    void Initialize(Spline* spline)
    {
        parameters.clear();
        cumulativeDist.clear();

        if (!spline || sampleCount < 2)
            return;

        parameters.resize(sampleCount);
        cumulativeDist.resize(sampleCount);

        // fill parameter array
        for (int i = 0; i < sampleCount; i++)
            parameters[i] = float(i) / float(sampleCount - 1);

        // sample positions and compute distances
        Vector3 prev = spline->GetSplinePoint(parameters[0]);
        cumulativeDist[0] = 0.0f;

        for (int i = 1; i < sampleCount; i++)
        {
            Vector3 cur = spline->GetSplinePoint(parameters[i]);
            cumulativeDist[i] = cumulativeDist[i - 1] + Vector3::Distance(prev, cur);
            prev = cur;
        }

        totalLength = cumulativeDist.back();
    }

    // Given a target distance along the spline [0..totalLength],
    // return an interpolated t in [0..1].
    float GetTAtDistance(float distance) const
    {
        if (parameters.empty())
            return 0.0f;

        // clamp
        if (distance <= 0.0f)
            return parameters.front();
        if (distance >= totalLength)
            return parameters.back();

        // find the segment
        int lo = 0, hi = int(cumulativeDist.size()) - 1;
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            if (cumulativeDist[mid] < distance)
                lo = mid;
            else
                hi = mid;
        }

        // linearly interpolate between lo and hi
        float segmentLen = cumulativeDist[hi] - cumulativeDist[lo];
        float alpha = (segmentLen > 0.0f)
            ? (distance - cumulativeDist[lo]) / segmentLen
            : 0.0f;

        return Lerp(parameters[lo], parameters[hi], alpha);
    }

private:
    static float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }
};
