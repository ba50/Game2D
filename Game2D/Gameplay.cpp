#include "Gameplay.h"

float Gameplay::deltaTime = 2e-2f;
unsigned Gameplay::timer = 0;

bool Gameplay::pausa = false;
bool Gameplay::slow_motion = false;
bool Gameplay::score = false;