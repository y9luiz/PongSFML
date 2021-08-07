#pragma once
template <class T>
class SolidObject
{
	protected:
		T geometric_shape_;
		virtual bool checkCollision(T & geometric_shape) = 0;
		virtual bool checkCollision(float x, float y) = 0;
};