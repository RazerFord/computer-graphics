#include "StartScreen.hpp"

#include <iostream>
#include "../../resources/ResourceManager.hpp"
#include "../../render/Sprite.hpp"

namespace {
    inline std::shared_ptr<render::Sprite> getSpriteForDescription(const char description, const resources::ResourceManager& manager)
    {
        switch (description)
        {
        case '0':
            return manager.getSprite("brickWall_All");
        case '1':
            return manager.getSprite("brickWall_TopLeft");
        case '2':
            return manager.getSprite("brickWall_TopRight");
        case '3':
            return manager.getSprite("brickWall_Top");
        case '4':
            return manager.getSprite("brickWall_BottomLeft");
        case '5':
            return manager.getSprite("brickWall_Left");
        case '6':
            return manager.getSprite("brickWall_TopRight_BottomLeft");
        case '7':
            return manager.getSprite("brickWall_Top_BottomLeft");
        case '8':
            return manager.getSprite("brickWall_BottomRight");
        case '9':
            return manager.getSprite("brickWall_TopLeft_BottomRight");
        case 'A':
            return manager.getSprite("brickWall_Right");
        case 'B':
            return manager.getSprite("brickWall_Top_BottomRight");
        case 'C':
            return manager.getSprite("brickWall_Bottom");
        case 'D':
            return manager.getSprite("brickWall_TopLeft_Bottom");
        case 'E':
            return manager.getSprite("brickWall_TopRight_Bottom");
        case 'F':
            return nullptr;
        default:
            std::cerr << "Unknown Start Level description: " << description << std::endl;
        }
        return nullptr;
    }
}

namespace game {
    StartScreen::StartScreen(const std::vector<std::string>& startScreenDescription, const resources::ResourceManager& manager) {
        if (startScreenDescription.empty()) {
            std::cerr << "Empty start screen description" << std::endl;
        }
        auto leftOffsetPixels = 2 * BLOCK_SIZE;
        auto bottomOffsetPixels = START_SCREEN_HEIGHT - 2 * BLOCK_SIZE;

        auto currentBottomOffset = bottomOffsetPixels;
        for (const std::string& currentRow : startScreenDescription) {
            int currentLeftOffset = leftOffsetPixels;
            for (const char currentElement : currentRow) {
                auto sprite = getSpriteForDescription(currentElement, manager);
                _sprites.emplace_back(std::make_pair(sprite, glm::vec2(currentLeftOffset, currentBottomOffset)));
                currentLeftOffset += BLOCK_SIZE;
            }
            currentBottomOffset -= BLOCK_SIZE;
        }
    }

	void StartScreen::render() const {
        for (const auto& current : _sprites) {
            if (current.first) {
                current.first->render(current.second, glm::vec2(BLOCK_SIZE), 0.F);
            }
        }
    }

	void StartScreen::update(const double delta) {}

	int StartScreen::getStateWidth() const {
        return START_SCREEN_WIDTH;
    }

	int StartScreen::getStateHeight() const {
        return START_SCREEN_HEIGHT;
    }
}