#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "window.h"






float vertices[] =
{
	//pos					//col			
	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 0.0f,

	-1.0f, -1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	1.0f, -1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,

	-1.0f,  1.0f,  1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 0.0f, 1.0f,

	1.0f,  1.0f,  1.0f,  	1.f, 1.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  	1.f, 1.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 	1.f, 1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,  	1.f, 1.0f, 0.0f,
	1.0f, -1.0f,  1.0f,  	1.f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  	1.f, 1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  	1.f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  	1.f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 1.0f,

	-1.0f,  1.0f, -1.0f,  	0.0f, 1.f, 1.0f,
	1.0f,  1.0f, -1.0f,  	0.0f, 1.f, 1.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.f, 1.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.f, 1.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 1.f, 1.0f,
	-1.0f,  1.0f, -1.0f, 	0.0f, 1.f, 1.0f,
};








void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)		glfwSetWindowShouldClose(window, true);
}



int main(int argc, char** argv)
{
	GLFWwindow* window = CreateWindow(800, 600, "Lab 6a");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	unsigned int shaderProgram = LoadShader("mvp.vert", "uniform.frag");


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



	/*unsigned int VAO[2];
	glGenVertexArrays(2, VAO);
	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgram);


	while (!glfwWindowShouldClose(window))
	{
		processKeyboard(window);

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		glm::mat4 view = glm::mat4(1.f);
		view = glm::translate(view, -glm::vec3(5.0f, 5.f, 5.0f));
		view = glm::rotate(view, glm::radians(-90.f), glm::vec3(1.0f, 0.f, 0.f));
		/*view = glm::rotate(view, glm::radians(-180.f), glm::vec3(0.0f, 1.f, 0.f));*/
		int vloc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(vloc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)800 / (float)600, 1.f, 10.f);
		int ploc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(projection));

		int cloc = glGetUniformLocation(shaderProgram, "uCol");
		glUniform3f(cloc, 1.f, 0.f, 0.f);

		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(7.f, 0.f, 5.f));
		int mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		cloc = glGetUniformLocation(shaderProgram, "uCol");
		glUniform3f(cloc, 0.f, 1.f, 0.f);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(5.f, 0.f, 7.f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
