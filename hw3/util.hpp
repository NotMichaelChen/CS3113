#ifndef UTIL_HPP
#define UTIL_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"

//Utility functions that can be useful anywhere

GLuint LoadTexture(const char *filepath, GLint filtering);
void DrawText(ShaderProgram *program, int fontTexture, std::string text, float size, float spacing, float x, float y);

#endif