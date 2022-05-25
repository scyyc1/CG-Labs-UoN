#define _USE_MATH_DEFINES 
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "window.h"

#include <iostream>




int ONESET = 6;


void processInput(GLFWwindow* window)
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

#define DEG2RAD(n)	n*(M_PI/180)

float* CreateCircle(int num_segments, float radius, glm::vec3 col)
{
	int n_verts = num_segments * 3;
	int n_atts = n_verts * 3;
	float* verts = (float*)malloc(sizeof(float) * (n_atts) * 2);

	std::cout <<  sizeof(verts) << std::endl;
	std::cout << col.x << " " << col.y << col.z << std::endl;

	float angle_offset = glm::radians(360.f) / num_segments;
	float current_angle = 0.f;

	for (int sc = 0; sc < num_segments; sc++)
	{
		// First pos
		verts[sc * 3 * 6 + 0] = 0.f;
		verts[sc * 3 * 6 + 1] = 0.f;
		verts[sc * 3 * 6 + 2] = 0.f;
		// First col
		verts[sc * 3 * 6 + 3] = col.x;
		verts[sc * 3 * 6 + 4] = col.y;
		verts[sc * 3 * 6 + 5] = col.z;
		
		// Second vert
		verts[sc * 3 * 6 + 6] = sin(current_angle) * radius;
		verts[sc * 3 * 6 + 7] = cos(current_angle) * radius;
		verts[sc * 3 * 6 + 8] = 0.f;
		verts[sc * 3 * 6 + 9] = col.x;
		verts[sc * 3 * 6 + 10] = col.y;
		verts[sc * 3 * 6 + 11] = col.z;

		// Third vert
		verts[sc * 3 * 6 + 12] = sin(current_angle + angle_offset) * radius;
		verts[sc * 3 * 6 + 13] = cos(current_angle + angle_offset) * radius;
		verts[sc * 3 * 6 + 14] = 0.f;
		verts[sc * 3 * 6 + 15] = col.x;
		verts[sc * 3 * 6 + 16] = col.y;
		verts[sc * 3 * 6 + 17] = col.z;

		current_angle += angle_offset;
	}

	//std::cout << verts[0] << "----------------" << std::endl;
	for (int i = 0; i < (n_atts) * 2; i++) {
		std::cout << verts[i] << "\t";
		if (i % 3 == 2) {
			std::cout << "\t";
		}
		if (i % 6 == 5) {
			std::cout << std::endl;
		}
		if (i % 18 == 17) {
			std::cout << std::endl;
		}
	}

	return verts;
}


int main(int argc, char** argv)
{
	GLFWwindow* window = CreateWindow(800, 600, "2D Modelling");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int shaderProgram = LoadShader("copy.vert", "flat.frag");

	int num_segs = 32;
	float* vertices = CreateCircle(num_segs, .5f, glm::vec3(1.f, 0.f, 0.f));

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_segs * 3 * 6, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	free(vertices);

	glfwTerminate();

	return 0;
}
