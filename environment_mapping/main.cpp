
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <vector>
#include <iostream>

#include <shaders.h>

int WIDTH = 1200;
int HEIGHT = 800;

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

GLuint shader, skybox_shader;

vec3 eye = vec3(0.0f, 0.0f, 1.5f);
vec3 up = vec3(0.f, 1.f, 0.f);
mat4 projection, view, normal_matrix;
GLuint projection_loc, view_loc, normal_matrix_loc, skybox_projection_loc, skybox_view_loc, eye_loc;

// Cube attributes
GLfloat cube_vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
};
GLfloat cube_normals[] = {
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	
	 0.0f,  0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f,
	
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f
};
GLfloat cube_texture_coord[] = {
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f,
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f,
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f,
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f,
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f,
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f,
};
GLuint cubeVAO;
mat4 cube_model;
GLuint cube_model_loc;

GLuint cubemap_texture, skyboxVAO;
GLfloat skybox_vertices[] = {       
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
};
std::vector<std::string> faces{
	"skybox/right.jpg",
	"skybox/left.jpg",
	"skybox/top.jpg",
	"skybox/bottom.jpg",
	"skybox/front.jpg",
	"skybox/back.jpg"
};

bool is_reflection = true;
GLfloat index = 0.67;
GLuint is_ref_loc, index_loc;

// Function prototypes
void init();
void change_viewport(int w, int h);
void keyboard(unsigned char key, int x, int y);
GLuint load_texture(const char* path);
void init_shaders();
void init_camera();
void init_skybox();
void init_cube();
void draw_camera();
void draw_skybox_camera();
void draw_skybox();
void draw_cube();
void render();

int main(int argc, char* argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Create window
	glutCreateWindow("Environment Map");

	glEnable(GL_DEPTH_TEST); // Enable depth test

	glutInitWindowSize(WIDTH, HEIGHT);
	glutReshapeWindow(WIDTH, HEIGHT);

	// Bind functions
	glutReshapeFunc(change_viewport);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);

	// Initialize Glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Unable to initalize Glew ! " << std::endl;
		return 1;
	}

	// Start program
	init();

	glutMainLoop();

	return 0;
}

void change_viewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

void init()
{
	std::cout << "W/A/S/D/R/F to move around." << std::endl;
	std::cout << "T to choose 'Refraction' or 'Reflection'." << std::endl;
	std::cout << "Q/E to adjust index of refraction index." << std::endl;
	init_shaders();
	init_camera();
	init_skybox();
	init_cube();
}

void init_shaders()
{
	// Shaders
	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/vertex_shader.glsl");
	GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/fragment_shader.glsl");
	shader = initprogram(vertex_shader, fragment_shader);

	// Skybox shaders
	vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/skybox_vs.glsl");
	fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/skybox_fs.glsl");
	skybox_shader = initprogram(vertex_shader, fragment_shader);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			view = glm::translate(view, vec3(0.0, 0.0, 0.1));
			break;
		case 's':
			view = glm::translate(view, vec3(0.0, 0.0, -0.1));
			break;
		case 'a':
			view = glm::translate(view, vec3(-0.1, 0.0, 0.0));
			break;
		case 'd':
			view = glm::translate(view, vec3(0.1, 0.0, 0.0));
			break;
		case 'r':
			view = glm::translate(view, vec3(0.0, 0.1, 0.0));
			break;
		case 'f':
			view = glm::translate(view, vec3(0.0, -0.1, 0.0));
			break;
		case 't':
			is_reflection = !is_reflection;
			break;
		case 'q':
			index += 0.05;
			break;
		case 'e':
			index += -0.05;
			break;
	}
	glutPostRedisplay();
}

GLuint load_texture(const char* path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	GLenum format;
	if (data)
	{
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void init_camera()
{
	// Initialize viewing values
	projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(eye, vec3(0.0f, 0.0f, 0.0f), up);

	eye_loc = glGetUniformLocation(shader, "camera_pos");

	projection_loc = glGetUniformLocation(shader, "projection");
	view_loc = glGetUniformLocation(shader, "view");

	// Skybox shaders
	skybox_projection_loc = glGetUniformLocation(skybox_shader, "projection");
	skybox_view_loc = glGetUniformLocation(skybox_shader, "view");
}

void init_skybox()
{
	// Skybox texture
	glGenTextures(1, &cubemap_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);

	int width, height, nrChannels;
	for (int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glUniform1i(glGetUniformLocation(skybox_shader, "skybox"), 0);

	// Skybox buffers
	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind for prevent further modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void init_cube()
{
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	// Vertex buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Normal buffer
	GLuint NBO;
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normals), &cube_normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind for prevent further modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Cube model matrix
	cube_model = glm::mat4(1.f);
	cube_model_loc = glGetUniformLocation(shader, "model");

	// Cube normal matrix
	normal_matrix = glm::transpose(glm::inverse(cube_model));
	normal_matrix_loc = glGetUniformLocation(shader, "normal_matrix");

	glUniform1i(glGetUniformLocation(shader, "skybox"), 0);

	index_loc = glGetUniformLocation(shader, "index");
	is_ref_loc = glGetUniformLocation(shader, "is_reflection");
}

void draw_camera()
{
	// Send camera uniforms
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &(view)[0][0]);
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &(projection)[0][0]);
	glUniformMatrix4fv(cube_model_loc, 1, GL_FALSE, &(glm::mat4(1.0))[0][0]);
	glUniformMatrix4fv(normal_matrix_loc, 1, GL_FALSE, &(normal_matrix)[0][0]);

	// This doesn't work if the camera rotates. I am also not sure if it is something correct to calculate eye coordinates
	vec3 cam_pos = vec3((glm::inverse(view))[3]); 
	glUniform3fv(eye_loc, 1, &cam_pos[0]);
}

void draw_cube()
{
	glUniform1f(index_loc, index);
	glUniform1i(is_ref_loc, (int)is_reflection);

	glUniformMatrix4fv(cube_model_loc, 1, GL_FALSE, &cube_model[0][0]);

	// Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);

	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

void draw_skybox_camera()
{
	// We dont need to translate the skybox, so the player can not reach skybox
	mat4 new_view = glm::mat4(glm::mat3(view));
	glUniformMatrix4fv(skybox_view_loc, 1, GL_FALSE, &(new_view)[0][0]);
	glUniformMatrix4fv(skybox_projection_loc, 1, GL_FALSE, &(projection)[0][0]);
}

void draw_skybox()
{
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glBindVertexArray(0);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.9f, 0.9f, 0.9f, 1.f);

	glUseProgram(shader);
	draw_camera();
	draw_cube();

	// Disable depth write to draw skybox always at background
	// Change depth function so depth test passes when values are equal to depth buffer's content
	glDepthFunc(GL_LEQUAL);

	glUseProgram(skybox_shader);
	draw_skybox_camera();
	draw_skybox();
	glDepthFunc(GL_LESS); // Set depth function back

	glutSwapBuffers();
}
