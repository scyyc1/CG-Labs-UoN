﻿#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include "window.h"
#include "shader.h" 

#include <glm/glm/glm.hpp> 
#include <glm/glm/gtc/matrix_transform.hpp> 
#include <glm/glm/gtc/type_ptr.hpp> 

float vertices[] =
{
	//pos					// color
	0.5f, 0.5f, 0.f,		1.f,0.f,0.f,
	-0.5f, 0.5f, 0.f,		0.f,1.f,0.f,
	-0.f,  -0.5f, 0.f,		0.f,0.f,1.f
};

int WINDOW_HEIGH = 600;
int WINDOW_WIDTH = 800;

glm::vec3 move = glm::vec3(0.f, 0.f, 0.f);


void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window)
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)			move.y += 0.001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)		move.y -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)		move.x -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)		move.x += 0.001;
}

unsigned int loadShaderSource()
{

	return 0;
}

int main(int argc, char** argv)
{
	// Create Opengl window
	GLFWwindow* window = CreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, "Lab2");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load shaders
	unsigned int shaderProgram = LoadShader("triangle.vert", "flat.frag");



	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//




	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderProgram);

		// grey level
		//float col_com = 0.5f;
		int ms = (int)(glfwGetTime() * 1000.f);
		float col_com = (float)(ms % 1000) / 1000.f;
		int loc1 = glGetUniformLocation(shaderProgram, "grey_level");
		glUniform1f(loc1, col_com);

		// Key control move
		int loc2 = glGetUniformLocation(shaderProgram, "move");
		glUniform3f(loc2, move.x, move.y, move.z);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
