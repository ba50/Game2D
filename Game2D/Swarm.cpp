#include "Swarm.h"

#include "Character.h"


Swarm::Swarm(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren)
{
	position.x = x;
	position.y = y;
	for (int i = 0; i < 50; ++i) {
		swarm.push_back(std::make_shared<Enemy>(x, y, file, ren));
	}
}


Swarm::~Swarm()
{
}

void Swarm::Update(const float deltaTime)
{
	Vecf2 r, sum{ 0.f,0.f };
	for (auto& enemy : swarm) {
		r.x = enemy->position.x - position.x;
		r.y = enemy->position.y - position.y;
		sum.x += enemy->position.x;
		sum.y += enemy->position.y;
		if (sqrt(r.x*r.x + r.y * r.y) > 50.f) {
			enemy->velocity.x = -r.x / 2.f;
			enemy->velocity.y = -r.y / 2.f;
		}
		enemy->Update(deltaTime);
	}
	position.x = sum.x / swarm.size();
	position.y = sum.y / swarm.size();


	for (auto it = swarm.begin(); it != swarm.end(); ++it)
	{
		if (!it->get()->life) {
			toDelete.push_back(it);
		}
	}

	for (auto& it : toDelete)
	{
		swarm.erase(it);
	}

	if (!toDelete.empty()) {
		toDelete.clear();
	}
}

void Swarm::Detect(std::shared_ptr<Character> cha)
{
	for (auto& enemy : swarm) {
		enemy->Detect(cha);
	}
}