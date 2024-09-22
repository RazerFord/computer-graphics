#include "game/Game.hpp"
#include "physics/PhysicsEngine.hpp"
#include "render/Render.hpp"
#include "resources/ResourceManager.hpp"
#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_double2x2.hpp>
#include <glm/ext/matrix_double2x3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <memory>

static constexpr unsigned int SCALE = 3;
static constexpr unsigned int BLOCK_SIZE = 16;

std::shared_ptr<game::Game> gameApp;
glm::ivec2 glfwWindowSize(SCALE * 16 * BLOCK_SIZE, SCALE * 15 * BLOCK_SIZE);

void glfwWindowResizeCallback(GLFWwindow * window, int width, int height)
{
	glfwWindowSize.x = width;
	glfwWindowSize.y = height;

	gameApp->setWindowSize(glfwWindowSize);
}

void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	gameApp->setKey(key, action);
}

int main(int _, char ** argv)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "glfwInit failed" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow * window = glfwCreateWindow(glfwWindowSize.x, glfwWindowSize.y, "Battle city", nullptr, nullptr);
	if (!window)
	{
		std::cout << "glfwCreateWindow failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, glfwWindowResizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
	{
		std::cout << "Can't init" << std::endl;
		return -1;
	}

	std::cout << "Renderer " << render::Render::getRenderer() << std::endl;
	std::cout << "OpenGL version " << render::Render::getVersion() << std::endl;

	render::Render::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	render::Render::enable(GL_DEPTH_TEST);

	{
		auto manager = std::make_shared<resources::ResourceManager>(argv[0]);
		auto physicsEngine = std::make_shared<physics::PhysicsEngine>();
		gameApp = std::make_shared<game::Game>(manager, physicsEngine, glfwWindowSize);
		// glfwSetWindowSize(window, 3 * gameApp->getCurrentWidth(), 3 * gameApp->getCurrentHeight());

		auto lastTime = std::chrono::high_resolution_clock::now();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			render::Render::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			double duration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
			lastTime = currentTime;

			gameApp->update(duration);
			gameApp->render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		gameApp = nullptr;
	}
	glfwTerminate();
	return 0;
}