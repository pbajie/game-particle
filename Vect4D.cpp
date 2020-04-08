//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include <assert.h>

#include "Vect4D.h"

Vect4D::Vect4D()
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->w = 1.0;
}

Vect4D::Vect4D(const float tx, const float ty, const float tz, const float tw)
{
	this->_m = _mm_set_ps(tw, tz, ty, tx);
	//this->x = tx;
	//this->y = ty;
	//this->z = tz;
	//this->w = tw;
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

void Vect4D::norm(Vect4D& out)
{
	///float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	///
	///if (0.0f < mag)
	///{
	///	out.x = this->x / mag;
	///	out.y = this->y / mag;
	///	out.z = this->z / mag;
	///	out.w = 1.0;
	///}
	__m128 mag = _mm_sqrt_ps(_mm_dp_ps(_m, _m, 0X77));

	if (0.0f < _mm_cvtss_f32(mag))
	{
		out._m = _mm_div_ps(_m, mag);
		out.w = 1.0f;
	}
}
Vect4D::Vect4D(const __m128 x)
{
	this->_m = x;
}
Vect4D Vect4D::operator + (Vect4D t)
{
	//Vect4D out;
	//
	//out.x = this->x + t.x;
	//out.y = this->y + t.y;
	//out.z = this->z + t.z;
	//
	//return out;
	return Vect4D(_mm_add_ps(this->_m, t._m));
}

Vect4D Vect4D::operator - (Vect4D t)
{
	//Vect4D out;
	//
	//out.x = this->x - t.x;
	//out.y = this->y - t.y;
	//out.z = this->z - t.z;
	//
	//return out;
	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z);
}

Vect4D Vect4D::operator *(const float scale)
{
	//Vect4D tmp;
	//
	//tmp.x = this->x * scale;
	//tmp.y = this->y * scale;
	//tmp.z = this->z * scale;
	//
	//return tmp;
	return Vect4D(this->x * scale, this->y * scale, this->z * scale);
}

float& Vect4D::operator[](VECT_ENUM e)
{
	switch (e)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		assert(0);
		return x;
	}
}

void Vect4D::Cross(Vect4D& vin, Vect4D& vout)
{
	//vout._m = _mm_sub_ps(_mm_set_ps1(y*vin.z) , _mm_set_ps1( z * vin.y));
	//vout._m = _mm_sub_ps(_mm_set_ps1(z*vin.x) , _mm_set_ps1(x * vin.z));
	//vout._m = _mm_sub_ps((_mm_set_ps1)(x*vin.y) , _mm_set_ps1( y * vin.x));
	//vout.w = 1.0f;
	vout.x = (y * vin.z - z * vin.y);
	vout.y = (z * vin.x - x * vin.z);
	vout.z = (x * vin.y - y * vin.x);
	vout.w = 1.0f;
}
void Vect4D::operator += (const Vect4D& t)
{
	this->_m = _mm_add_ps(this->_m, t._m);
}

void Vect4D::set(const float tx, const float ty, const float tz, const float tw)
{
	//this->x = tx;
	//this->y = ty;
	//this->z = tz;
	//this->w = tw;
	this->_m = _mm_set_ps(tx, ty, tz, tw);
}

// End of file



