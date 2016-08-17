#pragma once

#include "Math.h"

template <typename T>
class _Vec2
{
public:
	inline			_Vec2() {}
	inline			_Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	inline			_Vec2(const _Vec2& vect)
		:
		_Vec2(vect.x, vect.y)
	{}
	template <typename T2>
	inline			operator _Vec2< T2 >() const
	{
		return{ (T2)x,(T2)y };
	}

public:
	T x;
	T y;
};

typedef _Vec2< int > Veci2;
typedef _Vec2< float > Vecf2;
typedef _Vec2< double > Vecd2;