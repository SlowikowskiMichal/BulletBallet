#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class GameObject : public Drawable
{
public:
	virtual const Vector2i getPosition(RenderWindow &);

protected:

	Sprite sprite;
	Texture texture;
	size_t frame;

	virtual void draw(RenderTarget &target, RenderStates states) const;
};