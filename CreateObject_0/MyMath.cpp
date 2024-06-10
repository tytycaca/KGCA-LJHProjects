#include "MyMath.h"

namespace MY_Math
{
	FVector2 FVector2::ZeroVector2(0.0f, 0.0f);

	FVector2 FVector2::operator +(const FVector2& v) const
	{
		return FVector2(X + v.X, Y + v.Y);
	}

	FVector2 FVector2::operator -(const FVector2& v) const
	{
		return FVector2(X - v.X, Y - v.Y);
	}

	FVector2 FVector2::operator *(const float s) const
	{
		return FVector2(X * s, Y * s);
	}

	FVector2 FVector2::operator /(const float s) const
	{
		return FVector2(X / s, Y / s);
	}

	FVector2 FVector2::operator +=(const FVector2& v)
	{
		X += v.X;
		Y += v.Y;
		return *this;
	}

	float FVector2::Length()
	{
		return sqrt(X * X + Y * Y);
	}

	FVector2 FVector2::Normalize()
	{
		float fLength = 0.0f;
		if (isZero()) return ZeroVector2;
		return FVector2(X / fLength, Y / fLength);
	}

	bool FVector2::isZero(float& fLength)
	{
		fLength = Length();
		if (fLength <= 0.00001f)
			return true;

		return false;
	}

	bool FVector2::isZero()
	{
		float fLength = Length();
		if (fLength <= 0.00001f)
			return true;
		
		return false;
	}
};