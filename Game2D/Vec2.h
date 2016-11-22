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
////////////////////////////////////////////////////////////////////////
	template <typename T2>
	inline			operator _Vec2< T2 >() const
	{
		return{ static_cast<T2>(x),static_cast<T2>(y) };
	}
	inline T		LenSq() const
	{
		return *this * *this;
	}
	inline T		Len() const
	{
		return sqrt(LenSq());
	}
	inline _Vec2&		Norm() 
	{
		T len = this->Len();
		this->x /= len;
		this->y /= len;
		return *this;
	}
	inline _Vec2&	Swap(_Vec2& vect)
	{
		const _Vec2 temp = vect;
		vect = *this;
		*this = temp;
		return *this;
	}
	inline _Vec2	operator-() const
	{
		return _Vec2(-x, -y);
	}
	inline _Vec2&	operator+=(const _Vec2 &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	inline _Vec2&	operator-=(const _Vec2 &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	inline _Vec2&	operator*=(const T &rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}
	inline _Vec2	operator+(const _Vec2 &rhs) const
	{
		return _Vec2(*this) += rhs;
	}
	inline _Vec2	operator-(const _Vec2 &rhs) const
	{
		return _Vec2(*this) -= rhs;
	}
	inline T		operator*(const _Vec2 &rhs) const
	{
		return this->x * rhs.x + this->y * rhs.y;
	}
	inline _Vec2	operator*(const T &rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}
public:
	T x;
	T y;
};

typedef _Vec2< float > Vecf2;