#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Define.h"

class Audio {
	Mix_Music *gMusic;
	std::vector<Mix_Chunk> chunk_vector;

public:
	Audio();
	~Audio();

	void PlayMusic();
	void PlayExplosion();

};