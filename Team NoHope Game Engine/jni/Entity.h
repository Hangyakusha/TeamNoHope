#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <math/Vec3.h>
#include <math/Vec2.h>
#include <math/Mat4.h>

namespace gg
{
	class Entity
	{
	public:

		Entity();
		virtual ~Entity();

		virtual void update(float dt) = 0;
		virtual void draw() = 0;

		void setPosition(const Vec3& position);
		void setPosition(const Vec2& position);
		void setPosition(const float x, const float y, const float z);
		void setPosition(const float x, const float y);
		void setScale(const Vec3& scale);
		void setScale(const float scale);
		void setRotationX(float rotation);
		void setRotationY(float rotation);
		void setRotationZ(float rotation);
		void setProjectionMatrix(Mat4& matrix);

		float getRotation() const;
		Vec3& getScale();
		Vec3& getPosition();
		Mat4& getMatrix();

		void addChild(Entity& entity);
		Entity* getParent();
		
	protected:

		void calculateMatrix();

		Vec3 _position;
		float _rotation;
		Vec3 _scale;
		bool _recalculateMatrix;

		Mat4 _translationMatrix;
		Mat4 _rotationMatrix;
		Mat4 _scaleMatrix;
		Mat4 _combinedMatrix;
		Mat4 _projectionMatrix;
		
		Entity* _parent;
		std::vector<Entity*> _children;
	};
}

#endif