#pragma once

class FPSCounter
{
public:
    FPSCounter();
    float getFPS(float newTime);

private:
    static const int NUM_FRAMES = 10;
    float frameTimes[NUM_FRAMES];
    float lastTime;
    int frameCount;
};