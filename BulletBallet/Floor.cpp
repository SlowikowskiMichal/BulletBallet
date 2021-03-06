#include "Floor.h"

Floor::Floor()
{

}

Floor::Floor(float windowWidth,float windowHeight)
{
	try
	{
		if (!texture.loadFromFile("files/textures/floor.png"))
			throw Error(Error::texture);
	}
	catch (Error &error)
	{
		error.err();
	}

	width = 25;
	height = 19;
	tileSize = ceil(windowWidth / width);
	int textureSize = 32;

	collisions =
	{
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	};

	quads.setPrimitiveType(Quads);
	quads.resize(width * height * 4);
	Vector2f pos[4];
	size_t tileNumber = 0;

	Color color;
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{

				quads[0 + tileNumber] = Vector2f(j * tileSize, i * tileSize);
				quads[1 + tileNumber] = Vector2f((j + 1) * tileSize, i * tileSize);
				quads[2 + tileNumber] = Vector2f((j + 1) * tileSize, (i + 1) * tileSize);
				quads[3 + tileNumber] = Vector2f(j * tileSize, (i + 1) * tileSize);

			
				quads[0 + tileNumber].texCoords = Vector2f(textureSize * collisions[tileNumber / 4], 0);
				quads[1 + tileNumber].texCoords = Vector2f(textureSize * collisions[tileNumber / 4] + textureSize, 0);
				quads[2 + tileNumber].texCoords = Vector2f(textureSize * collisions[tileNumber / 4] + textureSize, textureSize);
				quads[3 + tileNumber].texCoords = Vector2f(textureSize * collisions[tileNumber / 4], textureSize);
				tileNumber += 4;
		}
	}

}

Floor::~Floor()
{

}

bool Floor::isColliding(Vector2f pos)
{
	
	int number = static_cast<int>(pos.x / tileSize) + static_cast<int>(pos.y / tileSize) * width;
	if (number > quads.getVertexCount() / 4)
		return true;
	return collisions[number];
}

void Floor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		states.texture = &texture;
		target.draw(quads, states);
}