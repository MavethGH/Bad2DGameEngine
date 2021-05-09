#include "FPSCounter.h"

FPSCounter::FPSCounter() :
    frameCount(0),
    lastTime(0.0f)
{
}

float FPSCounter::getFPS(float newTime) {
    // Use frameCount instead of NUM_FRAMES for the first few frames so that averaging works
    int count = frameCount < NUM_FRAMES ? frameCount : NUM_FRAMES;

    // Store frame time sample
    frameTimes[frameCount % NUM_FRAMES] = newTime - lastTime;

    // Calculate FPS
    float averageFrameTime = 0;
    for (int i = 0; i < count; ++i) {
        averageFrameTime += frameTimes[i];
    }
    float fps;
    if (averageFrameTime) {     // Avoid div-by-zero
        averageFrameTime /= count;
        fps = 1.0f / averageFrameTime;
    } else {
        fps = 0.0f;
    }

    // Increment for next frame
    frameCount++;
    lastTime = newTime;

    return fps;
}