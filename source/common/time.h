#pragma once
#include "utility.h"

// timing
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

float FPS_DELTA = 0.5f;
float lastFPS = 0.0f;
float printedFPS = 0.0f;

void MeasureTime()
{
	// per-frame time logic
	// --------------------
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

}

void PrintFPS()
{
	if (lastFPS + FPS_DELTA < currentTime)
	{
		printedFPS = 1 / deltaTime;
		std::cout << printedFPS << " FPS    " << "\r";
		lastFPS = currentTime;
	}
}