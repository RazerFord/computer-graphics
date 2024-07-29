#include <glad/glad.h>
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

const char * const vertexShaderSource = "#version 460 core\n"
										"layout (location = 0) in vec3 aPos;"
										"void main()\n"
										"{\n"
										"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
										"}\0";

const char * const fragmentShaderSource = "#version 460 core\n"
										  "out vec4 fragColor;"
										  "void main()\n"
										  "{\n"
										  "    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
										  "}\0";

int main(void)
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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
		return -1;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
		return -1;
	}

	GLuint shaderProgram = glCreateProgram();
	for (const auto & shader: {vertexShader, fragmentShader})
		glAttachShader(shaderProgram, shader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
		return -1;
	}

	for (const auto & shader: {vertexShader, fragmentShader})
		glDeleteShader(shader);

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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}