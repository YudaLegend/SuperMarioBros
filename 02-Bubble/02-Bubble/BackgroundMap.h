#ifndef _BACKGROUND_MAP_INCLUDE
#define _BACKGROUND_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <vector>


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class BackgroundMap {

private:
	BackgroundMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

public:
	// Tile maps can only be created inside an OpenGL context
	static BackgroundMap* createBackgroundMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	~BackgroundMap();

	void render() const;
	void free();

private:
	bool loadBackground(const string& levelFile);
	void prepareArrays(ShaderProgram& program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;
	int* indices;
	vector<float> vertices;
	glm::vec2 minCoords;

};


#endif // _TILE_MAP_INCLUDE


