#include "ConcreteWall.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
ConcreteWall::ConcreteWall(const ConcreteWallType & type, const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: IGameObject(position, size, rotation)
	, _sprite{manager.getSprite("betonWall")}
	, _states{
		  ConcreteState::Destroyed,
		  ConcreteState::Destroyed,
		  ConcreteState::Destroyed,
		  ConcreteState::Destroyed,
	  }
	, _offsets{
		  glm::vec2(0.0F, _size.y / 2.0F),
		  glm::vec2(_size.x / 2.0F, _size.y / 2.0F),
		  glm::vec2(0.0F, 0.0F),
		  glm::vec2(_size.x / 2.0F, 0.0F),
	  }
{

	switch (type)
	{
		case ConcreteWallType::All: {
			_states[static_cast<size_t>(BlockLocation::TopLeft)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::TopRight)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::BottomLeft)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::BottomRight)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::Top: {
			_states[static_cast<size_t>(BlockLocation::TopLeft)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::TopRight)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::Left: {
			_states[static_cast<size_t>(BlockLocation::TopLeft)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::BottomLeft)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::Right: {
			_states[static_cast<size_t>(BlockLocation::TopRight)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::BottomRight)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::Bottom: {
			_states[static_cast<size_t>(BlockLocation::BottomLeft)] = ConcreteState::Built;
			_states[static_cast<size_t>(BlockLocation::BottomRight)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::TopLeft: {
			_states[static_cast<size_t>(BlockLocation::TopLeft)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::TopRight: {
			_states[static_cast<size_t>(BlockLocation::TopRight)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::BottomLeft: {
			_states[static_cast<size_t>(BlockLocation::BottomLeft)] = ConcreteState::Built;
			break;
		}
		case ConcreteWallType::BottomRight: {
			_states[static_cast<size_t>(BlockLocation::BottomRight)] = ConcreteState::Built;
			break;
		}
	}
}

void ConcreteWall::render() const
{
	for (const auto location: {
			 BlockLocation::TopLeft,
			 BlockLocation::TopRight,
			 BlockLocation::BottomLeft,
			 BlockLocation::BottomRight,
		 })
	{
		renderBlock(location);
	}
}

void ConcreteWall::update(const size_t delta)
{
	// ConcreteWall static object
}

void ConcreteWall::renderBlock(const BlockLocation & location) const
{
	const size_t index = static_cast<size_t>(location);
	const auto state = _states[index];
	if (state != ConcreteState::Destroyed)
	{
		_sprite->render(_position + _offsets[index], _size / 2.0F, _rotation);
	}
}

}// namespace game