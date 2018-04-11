#ifndef UTIL_HPP
#define UTIL_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>

#include "ShaderProgram.h"

//Utility functions that can be useful anywhere

GLuint LoadTexture(const char *filepath, GLint filtering);
void DrawText(ShaderProgram *program, int fontTexture, std::string text, float size, float spacing, float x, float y);
std::pair<int, int> worldToTileCoordinates(float worldX, float worldY, float tilesize);
bool inBoundsTilemap(size_t n1, size_t n2, std::vector<std::vector<int>>& vec);

#endif