#pragma once
#include <math.h>

namespace MY_Math
{
	class FVector2
	{
	public:
		float X;
		float Y;
		static FVector2 ZeroVector2;

	public:
		FVector2 operator +(const FVector2& v) const;
		FVector2 operator -(const FVector2& v) const;
		FVector2 operator *(const float s) const;
		FVector2 operator /(const float s) const;
		float	 Length();
		FVector2 Normalize();
		bool	 isZero(float& fLength);
		bool	 isZero();

	public:
		FVector2()
		{
			X = Y = 0.0f;
		}
		FVector2(float x, float y)
		{
			X = x;
			Y = y;
		}
		FVector2(const FVector2& v)
		{
			X = v.X;
			Y = v.Y;
		}
	};

	class FVector4
	{
	public:
		float X;
		float Y;
		float Z;
		float W;

	public:
		FVector4()
		{
			X = Y = Z = W = 1.0f;
		}
		FVector4(float x, float y, float z, float w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}
		FVector4(const FVector4& v)
		{
			X = v.X;
			Y = v.Y;
			Z = v.Z;
			W = v.W;
		}
	};
}

