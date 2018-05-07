#ifndef UTIL_HPP
#define UTIL_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>

#include "ShaderProgram.h"
#include "vec.hpp"

//Utility functions that can be useful anywhere

GLuint LoadTexture(const char *filepath, GLint filtering);
void DrawText(ShaderProgram *program, int fontTexture, std::string text, float size, float spacing, float x, float y);
//Inclusive Clamping (test may be lo or hi)
void clamp(int& test, int lo, int hi);
float dist(Vec a, Vec b);
float randFloat(float lo, float hi);
int randInt(int lo, int hi);

#endif