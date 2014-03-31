#include "Entity.h"
#include "Util.h"
#include "Graphics.h"

using namespace gg;

Entity::Entity():
	_position(Vec3::zero()),
	_rotation(0),
	_scale(Vec3(1, 1, 1)),
	_recalculateMatrix(true),
	_parent(0)
{
	//setPosition(_position);
	setScale(_scale);
	//setRotation(_rotation);*/
}

Entity::~Entity() {}

void Entity::setPosition(const Vec3& position)
{
	_position = position;
	_translationMatrix = Mat4::createTranslation(_position);
	_recalculateMatrix = true;
}

void Entity::setPosition(const float x, const float y, const float z)
{
	setPosition(Vec3(x, y, z));
}

void Entity::setPosition(const float x, const float y)
{
	setPosition(Vec3(x, y, _position.z));
}

void Entity::setPosition(const Vec2& position)
{
	setPosition(Vec3(position.x, position.y, _position.z));
}

void Entity::setScale(const Vec3& scale)
{
	_scale = scale;
	_scaleMatrix = gg::Mat4::createScale(scale.x);
	_recalculateMatrix = true;
}

void Entity::setScale(const float scale)
{
	setScale(Vec3(scale, scale, scale));
}

void Entity::setRotationX(float rotation)
{
	_rotation = rotation;
	_rotationMatrix = Mat4::createRotationX(rotation);
	_recalculateMatrix = true;
}

void Entity::setRotationY(float rotation)
{
	_rotation = rotation;
	_rotationMatrix = Mat4::createRotationY(rotation);
	_recalculateMatrix = true;
}

void Entity::setRotationZ(float rotation)
{
	_rotation = rotation;
	_rotationMatrix = Mat4::createRotationZ(rotation);
	_recalculateMatrix = true;
}

void Entity::setProjectionMatrix(Mat4& matrix)
{
	_projectionMatrix = matrix;
}

float Entity::getRotation() const
{
	return _rotation;
}

Vec3& Entity::getScale()
{
	return _scale;
}

Vec3& Entity::getPosition()
{
	return _position;
}

Mat4& Entity::getMatrix()
{
	if(_recalculateMatrix)
	{
		calculateMatrix();
		_recalculateMatrix = false;
	}

	return _combinedMatrix;
}

void Entity::calculateMatrix()
{
	_combinedMatrix = _parent->_combinedMatrix * _translationMatrix * _rotationMatrix * _scaleMatrix;
}

void Entity::addChild(Entity& entity)
{
	Entity* entityParent = entity.getParent();
	entityParent = this;
	
	_children.push_back(&entity);
}

Entity* Entity::getParent()
{
	return _parent;
}
