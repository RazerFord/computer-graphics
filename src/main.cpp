#include "render/ShaderProgram.hpp"
#include "resources/ResourceManager.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

int glfwWindowSizeX = 640;
int glfwWindowSizeY = 480;

void glfwWindowResizeCallback(GLFWwindow * window, int width, int height)
{
	glfwWindowSizeX = width;
	glfwWindowSizeY = height;
	glViewport(0, 0, glfwWindowSizeX, glfwWindowSizeY);
}

void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

float vertices[] = {
	-0.5F, -0.5F, 0.0F,
	0.0F, 0.5F, 0.0F,
	0.5F, -0.5F, 0.0F};

float colors[] = {
	0.0, 0.0,
	0.5, 1.0,
	1.0, 0.0};

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
	GLFWwindow * window = glfwCreateWindow(640, 480, "Battle city", nullptr, nullptr);
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

	glClearColor(0.4f, 0.3f, 0.8f, 1.0f);

	{
		resources::ResourceManager manager(argv[0]);
		auto program = manager.loadShader("triangle", "shaders/vertex.vs", "shaders/fragment.fs");

		GLuint VBO, VAO;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glCreateBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			program->use();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	glfwTerminate();
	return 0;
}