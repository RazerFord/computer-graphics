#pragma once

#include <memory>
#include <string>
#include <vector>

namespace resources
{
class ResourceManager;
}

namespace game
{
class IGameObject;

class Level
{
private:
	int _width;
	int _height;
	std::vector<std::shared_ptr<IGameObject>> _gameObjects;

public:
	Level(const std::vector<std::string> & description, resources::ResourceManager * manager);
	void render() const;
	void update(const size_t delta);
};
}// namespace game