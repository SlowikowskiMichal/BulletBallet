#include "GameObject.h"

const Vector2i GameObject::getPosition(RenderWindow &okno)
{
	return Vector2i(okno.getPosition().x + sprite.getPosition().x, okno.getPosition().y + sprite.getPosition().y);
}

void GameObject::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(sprite, states);
}