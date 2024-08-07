#include "render/ShaderProgram.hpp"
#include "render/Sprite.hpp"
#include "render/Texture2D.hpp"
#include "resources/ResourceManager.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_double2x2.hpp>
#include <glm/ext/matrix_double2x3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <vector>

glm::ivec2 glfwWindowSize(640, 480);

void glfwWindowResizeCallback(GLFWwindow * window, int width, int height)
{
	glfwWindowSize.x = width;
	glfwWindowSize.y = height;
	glViewport(0, 0, glfwWindowSize.x, glfwWindowSize.y);
}

void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
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

	std::cout << "Renderer " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	{
		resources::ResourceManager manager(argv[0]);
		auto program = manager.loadShader("triangle", "shaders/vsprite.vs", "shaders/fsprite.fs");
		std::vector<std::string> names{"first", "second"};
		auto texture = manager.loadTexture("firsttexture", "textures/firsttexture.jpg");
		auto atlas = manager.loadAtlas("firsttexture", "textures/firsttexture.jpg",
									   names, 64, 64);
		auto sprite = manager.loadSprite("sprite", "triangle", "firsttexture", 100.0F, 100.0F, "first");

		glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(glfwWindowSize.x), 0.0F, static_cast<float>(glfwWindowSize.y), -100.0F, 100.F);

		program->use();
		program->setInt("tex", 0);
		program->setMat4("projectionMat", projection);

		glEnable(GL_DEPTH_TEST);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			program->use();


			sprite->setPosition(glm::vec2(100.0F, 0.0F));
			sprite->render();
			sprite->setPosition(glm::vec2(0.0F, 100.0F));
			sprite->render();
			sprite->setPosition(glm::vec2(0.0F, 0.0F));
			sprite->render();
			sprite->setPosition(glm::vec2(100.0F, 100.0F));
			sprite->render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}