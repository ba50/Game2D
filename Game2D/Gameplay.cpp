#include "Gameplay.h"

float Gameplay::deltaTime = 2e-2f;
unsigned Gameplay::timer = 0;
float Gameplay::sky_level;
float Gameplay::water_level;

bool Gameplay::pausa = true;
bool Gameplay::slow_motion = false;
bool Gameplay::score = false;
bool Gameplay::start = false;