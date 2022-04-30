#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <io.h>

//Window params
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//We have to create the vertex array obj here because 
//it needs to be in the global scope for this function (main.cpp:159)
//to be able to acces it.
unsigned vao;

//Create the shader program for attaching shaders
unsigned int shader_program;


/// <summary>
/// Reads file contents line by line.
/// </summary>
/// <param name="File Path - path to the file you want to read"></param>
/// <returns>std::string</returns>
std::string readFromFile(const char* filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}
//Read the glsl shader files.
const std::string vertex_shader_string = readFromFile("vertex.glsl");
const std::string fragment_shader_string = readFromFile("frag.glsl");

//Convert the into chars because the glShaderSource function wants a char.
const char* vertex_shader_source = vertex_shader_string.c_str();
const char* fragment_shader_source = fragment_shader_string.c_str();

void setup_shader()
{
	//Create and compile both the vertex and the fragment shaders.
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	//Create a shader program to attach the shaders we just made.
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	//Link the shader program.
	glLinkProgram(shader_program);

	//Dispose of the shaders.
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//This was used when i was debugging the 
	// readFromFile function, its not needed 
	// anymore.
	/*std::cout << vertex_shader_source << std::endl << vertex_shader_source;
	std::cout << fragment_shader_source << std::endl << vertex_shader_source;*/
}

void setup_data()
{
	//Create the vertecies for the two triangles used to fill the screen.
	float vertices[] = {
		// For visualization: each row is a vertex.
		// Each vertex has position [x, y, z] and color [r, g, b]
		  1.0f,  1.0f, 0.0f, 1.0, 1.0, 1.0,   // red color for this vertex
		 -1.0f,  1.0f, 0.0f, 1.0, 1.0, 1.0,   // green color
		 -1.0f, -1.0f, 0.0f, 1.0, 1.0, 1.0,    // blue color for our top vertex

		 -1.0f, -1.0f, 0.0f, 1.0, 1.0, 1.0,   // red color for this vertex
		 1.0f, -1.0f, 0.0f, 1.0, 1.0, 1.0,   // green color
		 1.0f,  1.0f, 0.0f, 1.0, 1.0, 1.0    // blue color for our top vertex
	};

	//Generate and bind the vertex array object.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create and generate the vertex buffer object.
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Fill the buufer obj with buffer data.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

int main(void)
{
	//Create a window obj.
	GLFWwindow* window;

	//Check if glfw has initialized properly.
	if (!glfwInit())
	{
		//If not throw an error.
		return -1;
	}

	///Give the window some hints so that it knows the glfw version and the profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /*<--only works on newer versions of opengl.*/

	//Call the glfwCreateWindow function on the window object to make it a real glfw window
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, 0);

	//Check if the window was created properly.
	if (!window)
	{
		//If not terminate glfw and throw an error.
		glfwTerminate();
		return -1;
	}

	//Set our window obj as the current context
	glfwMakeContextCurrent(window);

	//Check if glad has initialized properly.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//If not terminate glfw and throw an error.
		glfwTerminate();
		return -1;
	}

	//Call our setupShader and setupData functions.
	setup_shader();
	setup_data();

	//Set the clear color.
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	//Create the main loop tha terminates if the window should close.
	while (!glfwWindowShouldClose(window))
	{
		//Set the memory address of the clear color buffer bit for glad.
		glClear(GL_COLOR_BUFFER_BIT);
		//Use the previously created shader program.
		glUseProgram(shader_program);
		//Bind the vertex array obj.
		glBindVertexArray(vao);

		//Draw the triangles by the array at (main.cpp:85)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Swap the buffers so that we dont just see half of the image.
		glfwSwapBuffers(window);
		//Take the poll events like input, if the window should close etc.
		glfwPollEvents();
	}

	//Termine glfw.
	glfwTerminate();

	//Return a 0 (the "succes code")
	return 0;
}