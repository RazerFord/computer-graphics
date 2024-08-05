#include "render/ShaderProgram.hpp"
#include "render/Texture2D.hpp"
#include "resources/ResourceManager.hpp"
#include <GLFW/glfw3.h>
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

float vertices[] = {
	-0.5F, -0.5F, 0.5F,
	0.0F, 0.5F, 0.0F,
	0.5F, -0.5F, 0.5F,

	-0.5F, -0.5F, -0.5F,
	0.0F, 0.5F, 0.0F,
	-0.5F, -0.5F, 0.5F,

	0.5F, -0.5F, -0.5F,
	0.0F, 0.5F, 0.0F,
	-0.5F, -0.5F, -0.5F,

	0.5F, -0.5F, -0.5F,
	0.0F, 0.5F, 0.0F,
	0.5F, -0.5F, 0.5F,

	-0.5F, -0.5F, 0.5F,
	0.5F, -0.5F, 0.5F,
	0.5F, -0.5F, -0.5F,

	0.5F, -0.5F, -0.5F,
	-0.5F, -0.5F, -0.5F,
	-0.5F, -0.5F, 0.5F};

float texCoord[] = {
	0.0, 0.0,
	0.5, 1.0,
	1.0, 0.0,

	0.0, 0.0,
	0.5, 1.0,
	1.0, 0.0,

	0.0, 0.0,
	0.5, 1.0,
	1.0, 0.0,

	0.0, 0.0,
	0.5, 1.0,
	1.0, 0.0,

	0.0, 0.0,
	0.5, 1.0,
	1.0, 0.0,

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
		auto program = manager.loadShader("triangle", "shaders/vertex.vs", "shaders/fragment.fs");
		auto texture = manager.loadTexture("firsttexture", "textures/firsttexture.jpg");

		GLuint tex_colors_vbo, points_vbo, points_vao;

		glCreateBuffers(1, &tex_colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, tex_colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

		glCreateBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &points_vao);
		glBindVertexArray(points_vao);

		glBindBuffer(GL_ARRAY_BUFFER, tex_colors_vbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		program->use();
		program->setInt("tex", 0);

		glEnable(GL_DEPTH_TEST);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			program->use();

			int i = 0;
			for (const auto [dx, dy]: std::vector<std::pair<float, float>>{
					 {1.5, 0.0},
					 {-1.5, 0.0},
					 {0.0, 0.0},
				 })
			{
				glm::mat4 model(1.0f);
				model = glm::translate(model, glm::vec3(dx, dy, 0.0));
				model = glm::rotate(model, glm::radians(100 * (float)sin((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));

				glm::mat4 view(1.0f);

				view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.5));
				glm::mat4 projection;
				projection = glm::perspective(glm::radians(130.0f), static_cast<float>(glfwWindowSize.y) / glfwWindowSize.x, 0.1f, 100.0f);

				program->setMat4("model", model);
				program->setMat4("view", view);
				program->setMat4("projection", projection);

				glActiveTexture(GL_TEXTURE0);
				texture->bind();
				glBindVertexArray(points_vao);
				glDrawArrays(GL_TRIANGLES, 0, 18);
			}

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		glDeleteBuffers(1, &tex_colors_vbo);
		glDeleteVertexArrays(1, &points_vao);
		glDeleteBuffers(1, &points_vbo);
	}
	glfwTerminate();
	return 0;
}