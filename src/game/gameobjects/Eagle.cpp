#include "Eagle.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
Eagle::Eagle(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: IGameObject(position, size, rotation)
	, _sprites{
		  manager.getSprite("eagle"),
		  manager.getSprite("eagle_dead"),
	  }
	, _currentState(EagleState::Alive)
{}

void Eagle::render() const
{
	_sprites[static_cast<size_t>(_currentState)]->render(_position, _size, _rotation);
}

void Eagle::update(const size_t delta)
{
	// TODO: implement me
}
}// namespace game