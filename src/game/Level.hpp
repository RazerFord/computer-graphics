#pragma once

#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace resources
{
class ResourceManager;
}

namespace game
{
const int BLOCK_SIZE = 16;

class IGameObject;

class Level
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

public:
	Level(const std::vector<std::string> & description, const resources::ResourceManager & manager);
	void render() const;
	void update(const double delta);

	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

	const glm::ivec2 getPlayerRespawn1() const;
	const glm::ivec2 getPlayerRespawn2() const;
	const glm::ivec2 getEnemyRespawn1() const;
	const glm::ivec2 getEnemyRespawn2() const;
	const glm::ivec2 getEnemyRespawn3() const;

	std::vector<std::shared_ptr<IGameObject>> objectsInArea(const glm::vec2 & bottomLeft, const glm::vec2 & topRight) const;
};
}// namespace game