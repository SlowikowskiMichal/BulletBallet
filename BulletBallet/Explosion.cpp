#include "Explosion.h"

Explosion::Explosion(Vector2f pos, float angle, Texture itexture, float windowWidth, float windowHeight, Color color)
{
	texture = itexture;
	sprite.setTexture(texture);
	sprite.setColor(Color(color.r, color.g, color.b, 175));
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	sprite.setOrigin(16, 32);
	sprite.setPosition(pos);
	sprite.setRotation(angle);
	sprite.setScale(windowWidth / 800, windowWidth / 800);

	frame = 0;
}

Explosion::~Explosion()
{

}

bool Explosion::animation()
{
	if (frame < 7)
	{
		frame++;
		sprite.setTextureRect(IntRect(frame * sprite.getTextureRect().width, 0, sprite.getTextureRect().width, sprite.getTextureRect().height));
		return true;
	}
	
	return false;
}
