#include "Texture.h"

#include <iostream>

#include "SDL_image.h"

#include "Renderer.h"
#include "Define.h"

#include "cleanup.h"

Texture::Texture(const std::string & file, std::shared_ptr<Renderer> ren)
{
	texture = IMG_LoadTexture(ren->ren, file.c_str());
	if (texture == nullptr) {
		Error::logSDL(std::cout, "LoadTexture");
	}
}

Texture::~Texture()
{
	cleanup(texture);
}
