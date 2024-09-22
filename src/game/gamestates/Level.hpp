#pragma once

#include "IGameState.hpp"
#include <array>
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace resources
{
class ResourceManager;
}

namespace physics
{
class PhysicsEngine;
}

namespace game
{
const int BLOCK_SIZE = 16;

class IGameObject;
class Tank;

class Level : public IGameState
{
private:
	int _width;
	int _height;
	glm::ivec2 _playerRespawn1;
	glm::ivec2 _playerRespawn2;
	glm::ivec2 _enemyRespawn1;
	glm::ivec2 _enemyRespawn2;
	glm::ivec2 _enemyRespawn3;
	std::vector<std::shared_ptr<IGameObject>> _gameObjects;
	std::shared_ptr<Tank> _tank;

	std::shared_ptr<resources::ResourceManager> _manager;
	std::shared_ptr<physics::PhysicsEngine> _physicsEngine;

public:
	Level(
		const std::vector<std::string> & description,
		const std::shared_ptr<resources::ResourceManager> & manager,
		const std::shared_ptr<physics::PhysicsEngine> & physicsEngine);
	virtual void render() const override;
	virtual void update(const double delta) override;

	virtual int getStateWidth() const override;
	virtual int getStateHeight() const override;

	virtual void processInput(const std::array<bool, 350> & keys) override;

	const glm::ivec2 getPlayerRespawn1() const;
	const glm::ivec2 getPlayerRespawn2() const;
	const glm::ivec2 getEnemyRespawn1() const;
	const glm::ivec2 getEnemyRespawn2() const;
	const glm::ivec2 getEnemyRespawn3() const;

	void initPhysics();

	std::vector<std::shared_ptr<IGameObject>> objectsInArea(const glm::vec2 & bottomLeft, const glm::vec2 & topRight) const;
};
}// namespace game