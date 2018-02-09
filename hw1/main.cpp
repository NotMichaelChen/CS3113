#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;

GLuint LoadTexture(const char *filepath, GLint filtering);

int main(int argc, char *argv[])
{
	//Initialize the window
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	glewInit();

	glViewport(0, 0, 1280, 720);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Set the color the program clears the screen into
	glClearColor(0.4, 0.67, 0.31, 1);

	//Load the shader program and set untextured color
	ShaderProgram program, program_tex;
	program.Load("vertex.glsl", "fragment.glsl");
	program_tex.Load("vertex_textured.glsl", "fragment_textured.glsl");
	program.SetColor(0.831, 0.401, 0.58, 1);
	program_tex.SetColor(0.831, 0.401, 0.58, 1);

	//Load Textures
	GLuint squareStone = LoadTexture("./assets/elementStone011.png", GL_NEAREST);
	GLuint circleStone = LoadTexture("./assets/elementStone010.png", GL_NEAREST);
	GLuint debrisGlass = LoadTexture("./assets/debrisGlass_3.png", GL_NEAREST);

	//Declare matrices
	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	//Set orthographic projection
	projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);

	float lastFrameTicks = 0.0f;
	SDL_Event event;
	bool done = false;
	while (!done) {
		//Clear event queue
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		float ticks = (float)SDL_GetTicks()/1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		//Clear screen
		glClear(GL_COLOR_BUFFER_BIT);

		//Set program matrices
		program.SetModelMatrix(modelMatrix);
		program.SetProjectionMatrix(projectionMatrix);
		program.SetViewMatrix(viewMatrix);

		program_tex.SetModelMatrix(modelMatrix);
		program_tex.SetProjectionMatrix(projectionMatrix);
		program_tex.SetViewMatrix(viewMatrix);

		glUseProgram(program.programID);

		//Draw square
		float vertices[] = {-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5};
		modelMatrix.Translate(0, 1.0, 0);
		program.SetModelMatrix(modelMatrix);
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program.positionAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		modelMatrix.Identity();

		//Use textured shader program
		glUseProgram(program_tex.programID);

		//Draw square stone
		glBindTexture(GL_TEXTURE_2D, squareStone);

		modelMatrix.Translate(0, -1.5, 0);
		program_tex.SetModelMatrix(modelMatrix);
		modelMatrix.Identity();

		glVertexAttribPointer(program_tex.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program_tex.positionAttribute);

		float texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
		glVertexAttribPointer(program_tex.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program_tex.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program_tex.positionAttribute);
		glDisableVertexAttribArray(program_tex.texCoordAttribute);
		

		//Draw circle stone
		glBindTexture(GL_TEXTURE_2D, circleStone);

		modelMatrix.Translate(2, 0, 0);
		program_tex.SetModelMatrix(modelMatrix);
		modelMatrix.Identity();

		glVertexAttribPointer(program_tex.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program_tex.positionAttribute);

		glVertexAttribPointer(program_tex.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program_tex.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program_tex.positionAttribute);
		glDisableVertexAttribArray(program_tex.texCoordAttribute);
		
		//Draw debris
		glBindTexture(GL_TEXTURE_2D, debrisGlass);

		modelMatrix.Rotate(ticks);
		program_tex.SetModelMatrix(modelMatrix);
		modelMatrix.Identity();

		glVertexAttribPointer(program_tex.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program_tex.positionAttribute);

		glVertexAttribPointer(program_tex.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program_tex.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program_tex.positionAttribute);
		glDisableVertexAttribArray(program_tex.texCoordAttribute);

		//Swap window buffers
		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}

GLuint LoadTexture(const char *filepath, GLint filtering) {
	int w,h,comp;
	unsigned char* image = stbi_load(filepath, &w, &h, &comp, STBI_rgb_alpha);
	if(image == NULL) {
		std::cout << "Unable to load image. Make sure the path is correct\n";
		assert(false);
	}
	GLuint retTexture;
	glGenTextures(1, &retTexture);
	glBindTexture(GL_TEXTURE_2D, retTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

	stbi_image_free(image);
	return retTexture;
}