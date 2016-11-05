#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Define.h"

class Audio {
	Mix_Music *gMusic;
	std::vector<Mix_Chunk> chunk_vector;

public:
	Audio() {
		//Initialize SDL
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			if (SDL_Init(SDL_INIT_VIDEO) != 0) {
				Error::LogSDL(std::cout, "SDL_Init_Audio");
			}
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			Error::LogSDL(std::cout, "SDL_mixer could not initialize! SDL_mixer Error");
		}

		//Load music
		gMusic = Mix_LoadMUS("Luftrausers_Soundtrack_-_The_Original.wav");
		if (gMusic == NULL) Error::LogSDL(std::cout, "SDL_mixer could not initialize! SDL_mixer Error");


		//Load sound effects
		 chunk_vector.push_back(*Mix_LoadWAV("Explosion+1.wav"));


	}
	~Audio() {
		Mix_FreeMusic(gMusic);
		gMusic = NULL;

		for (auto& chunk : chunk_vector) {
			Mix_FreeChunk(&chunk);
		}

		Mix_Quit();
	}

	void PlayMusic() {
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(gMusic, -1);
		}
	}

	void PlayExplosion() {
		Mix_VolumeChunk(&chunk_vector[0], 25);
		Mix_PlayChannel(-1, &chunk_vector[0], 0);
	}

};