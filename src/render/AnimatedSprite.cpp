#include "AnimatedSprite.hpp"
#include "Sprite.hpp"
#include "Texture2D.hpp"
#include <iostream>
#include <vector>

namespace render
{
void AnimatedSprite::insertState(const std::string & state, const std::vector<details::State> & subTextureDuration)
{
	_statesMap[state] = subTextureDuration;
}

void AnimatedSprite::render() const
{
	if (_dirty)
	{
		const std::vector<details::State> & animations = _currentAnimationDurations->second;
		const render::Texture2D::SubTexture2D & st = this->_spTexture2D->getSubTexture(animations[_currentFrame].name());

		const GLfloat textureCoords[]{
			st.leftBottomUV.x, st.leftBottomUV.y,
			st.leftBottomUV.x, st.rightTopUV.y,
			st.rightTopUV.x, st.rightTopUV.y,

			st.rightTopUV.x, st.rightTopUV.y,
			st.rightTopUV.x, st.leftBottomUV.y,
			st.leftBottomUV.x, st.leftBottomUV.y};

		glBindBuffer(GL_ARRAY_BUFFER, _textureCoordsVbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), textureCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		_dirty = false;
	}

	Sprite::render();
}

void AnimatedSprite::setState(const std::string & state)
{
	auto it = _statesMap.find(state);
	if (it == _statesMap.end())
	{
		std::cerr << "can't find animation state " << state << std::endl;
		return;
	}

	_currentAnimationTime = 0;
	_currentFrame = 0;
	_currentAnimationDurations = it;
	_dirty = true;
}

void AnimatedSprite::update(const size_t delta)
{
	if (_currentAnimationDurations != _statesMap.end())
	{
		_currentAnimationTime += delta;
		const std::vector<details::State> & animations = _currentAnimationDurations->second;
		if (size_t duration = animations[_currentFrame].duration(); _currentAnimationTime > duration)
		{
			_currentAnimationTime %= duration;
			_currentFrame = (_currentFrame + 1) % animations.size();
			_dirty = true;
		}
	}
}
}// namespace render