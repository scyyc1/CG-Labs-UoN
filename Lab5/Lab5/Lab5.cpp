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
	//TL
	//pos					//col			
	-1.0f, 0.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	-1.0f, 0.0f, 1.0f,  	1.f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,  		1.f, 0.0f, 0.0f,

	//TB
	//pos					//col		
	1.0f, 0.0f, -1.0f,  	0.f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,  	0.f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,  		0.f, 1.0f, 0.0f,

	//TR
	//pos					//col		
	1.0f, 0.0f, -1.0f,  	0.f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,  		0.f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,  		0.f, 0.0f, 1.0f,

	//TF
	//pos					//col		
	1.0f, 0.0f, 1.0f,  		1.f, 1.f, 1.f,
	-1.0f, 0.0f, 1.0f,  	1.f, 1.f, 1.f,
	0.0f, 1.0f, 0.0f,  		1.f, 1.f, 1.f,



	//BL
	//pos					//col	
	-1.0f, 0.0f, -1.0f,  	1.f, 1.0f, 0.0f,
	-1.0f, 0.0f, 1.0f,  	1.f, 1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,  	1.f, 1.0f, 0.0f,

	//BB
	//pos					//col	
	1.0f, 0.0f, -1.0f,  	0.f, 1.0f, 1.0f,
	-1.0f, 0.0f, -1.0f,  	0.f, 1.0f, 1.0f,
	0.0f, -1.0f, 0.0f,  	0.f, 1.0f, 1.0f,

	//BR
	//pos					//col			
	1.0f, 0.0f, -1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,  		1.f, 0.0f, 1.0f,
	0.0f, -1.0f, 0.0f,  	1.f, 0.0f, 1.0f,

	//BF
	//pos					//col		
	1.0f, 0.0f, 1.0f,  		0.5f, 0.5f, 0.5f,
	-1.0f, 0.0f, 1.0f,  	0.5f, 0.5f, 0.5f,
	0.0f, -1.0f, 0.0f,  	0.5f, 0.5f, 0.5f,
};

float cube[] =
{
	// top-1				// col
	1.f, 1.f, 1.f,			1.f,0.f,0.f,
	-1.f, 1.f, 1.f,			1.f,0.f,0.f,
	1.f, 1.f, -1.f,			1.f,0.f,0.f,
	// top-2
	-1.f, 1.f, -1.f,		1.f,0.f,0.f,
	-1.f, 1.f, 1.f,			1.f,0.f,0.f,
	1.f, 1.f, -1.f,			1.f,0.f,0.f,

	// bottom-1
	1.f, -1.f, 1.f,			1.f,0.f,0.f,
	-1.f, -1.f, 1.f,		1.f,0.f,0.f,
	1.f, -1.f, -1.f,		1.f,0.f,0.f,
	// bottom-2
	-1.f, -1.f, -1.f,		1.f,0.f,0.f,
	-1.f, -1.f, 1.f,		1.f,0.f,0.f,
	1.f, -1.f, -1.f,		1.f,0.f,0.f,

	// front-1
	-1.f, 1.f, 1.f,			0.f,0.f,1.f,
	1.f, -1.f, 1.f,			0.f,0.f,1.f,
	1.f, 1.f, 1.f,			0.f,0.f,1.f,
	// front-2
	-1.f, 1.f, 1.f,			0.f,0.f,1.f,
	1.f, -1.f, 1.f,			0.f,0.f,1.f,
	-1.f, -1.f, 1.f,		0.f,0.f,1.f,

	// back-1
	-1.f, 1.f, -1.f,		0.f,0.f,1.f,
	1.f, -1.f, -1.f,		0.f,0.f,1.f,
	1.f, 1.f, -1.f,			0.f,0.f,1.f,
	// back-2
	-1.f, 1.f, -1.f,		0.f,0.f,1.f,
	1.f, -1.f, -1.f,		0.f,0.f,1.f,
	-1.f, -1.f, -1.f,		0.f,0.f,1.f,

	// left-1
	1.f, 1.f, 1.f,			0.f,1.f,0.f,
	1.f, 1.f, -1.f,			0.f,1.f,0.f,
	1.f, -1.f, -1.f,		0.f,1.f,0.f,
	// left-2					
	1.f, 1.f, 1.f,			0.f,1.f,0.f,
	1.f, -1.f, 1.f,			0.f,1.f,0.f,
	1.f, -1.f, -1.f,		0.f,1.f,0.f,

	// right-1
	-1.f, 1.f, 1.f,			0.f,1.f,0.f,
	-1.f, 1.f, -1.f,		0.f,1.f,0.f,
	-1.f, -1.f, -1.f,		0.f,1.f,0.f,
	// right-2					
	-1.f, 1.f, 1.f,			0.f,1.f,0.f,
	-1.f, -1.f, 1.f,		0.f,1.f,0.f,
	-1.f, -1.f, -1.f,		0.f,1.f,0.f,
};






void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)		glfwSetWindowShouldClose(window, true);
}

//DECLARE POSITION VARIABLES HERE
glm::vec3 cube_pos = glm::vec3(0.f, 2.f, -6.0f);
glm::vec3 oct_pos = glm::vec3(0.f, 0.f, -6.0f);
glm::vec3 cam_pos = glm::vec3(0.f, 0.5f, 0.f);


int main(int argc, char** argv)
{
	GLFWwindow* window = CreateWindow(800, 600, "3D Modelling");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int shaderProgram = LoadShader("mvp.vert", "col.frag");

	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);
	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	// cube
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// oct
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//

	//ENABLE DEPTH TEST HERE
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgram);


	while (!glfwWindowShouldClose(window))
	{
		processKeyboard(window);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		//CLEAR DEPTH BUFFER HERE
		//	|
		//	V
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/**********************正方体**********************/
		//SET UP AND COPY MODEL MATRIX HERE
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, cube_pos);
		model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(0.f, 1.f, 0.f));
		int mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));

		//SET UP AND COPY VIEW MATRIX HERE
		glm::mat4 view = glm::mat4(1.f);
		view = glm::translate(view, -cam_pos);
		int vloc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(vloc, 1, GL_FALSE, glm::value_ptr(view));

		//SET UP AND COPY PROJECTION MATRIX HERE
		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(90.f), (float)800 / (float)600, 4.f, 10.f);
		int ploc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/**********************八边形*****************************/
		//SET UP AND COPY MODEL MATRIX HERE
		model = glm::mat4(1.f);
		model = glm::translate(model, oct_pos);
		model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(0.f, 1.f, 0.f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));

		//SET UP AND COPY VIEW MATRIX HERE
		view = glm::mat4(1.f);
		view = glm::translate(view, -cam_pos);
		vloc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(vloc, 1, GL_FALSE, glm::value_ptr(view));

		//SET UP AND COPY PROJECTION MATRIX HERE
		projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(90.f), (float)800 / (float)600, 4.f, 10.f);
		ploc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 24);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
