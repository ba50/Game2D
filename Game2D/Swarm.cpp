#include "Swarm.h"

#include "Character.h"


Swarm::Swarm(Vecf2 position, const std::string & file, const std::shared_ptr<Renderer> ren) :
	Object(ren)
{
	Object::position = position;
	for (int i = 0; i < 20; ++i) {
		enemyList.push_back(std::make_shared<Enemy>(position, file, Object::ren));
	}
}

Swarm::~Swarm()
{
}

void Swarm::Update(const float deltaTime)
{
	Vecf2 r, sum{ 0.f,0.f };
	for (auto& enemy : enemyList) {
		r.x = enemy->position.x - position.x;
		r.y = enemy->position.y - position.y;
		sum.x += enemy->position.x;
		sum.y += enemy->position.y;
		if (sqrt(r.x*r.x + r.y * r.y) > 75.f) {
			enemy->velocity.x = -r.x;
			enemy->velocity.y = -r.y;
		}
		enemy->Update(deltaTime);
	}
	position.x = sum.x / enemyList.size();
	position.y = sum.y / enemyList.size();


	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		if (!it->get()->life) {
			toDelete.push_back(it);
		}
	}

	for (auto& it : toDelete)
	{
		enemyList.erase(it);
	}

	if (!toDelete.empty()) {
		toDelete.clear();
	}
}

void Swarm::Draw()
{
	for (auto& enemy : enemyList) {
		enemy->Draw();
	}
}

void Swarm::Detect(std::shared_ptr<Character> cha)
{
	for (auto& enemy : enemyList) {
		enemy->Detect(cha);
	}
}