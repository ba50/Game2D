#include "Swarm.h"

#include "Character.h"


Swarm::Swarm(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren)
{
	swarm.push_back(std::make_shared<Enemy>(x, y, file, ren));
	swarm.push_back(std::make_shared<Enemy>(x+80, y, file, ren));
	swarm.push_back(std::make_shared<Enemy>(x+160, y, file, ren));
}


Swarm::~Swarm()
{
}

void Swarm::Update(const float deltaTime)
{

}
