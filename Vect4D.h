//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <xmmintrin.h>
#include <smmintrin.h>
// Foward Declarations
class Matrix;

// class
class Vect4D
{
public:
	friend class Matrix;

	Vect4D();
	Vect4D(const float tx, const float ty, const float tz, const float tw = 1.0f);
	~Vect4D();

	void norm(Vect4D &out);
	Vect4D(const __m128 x);
	void set(const float tx, const float ty, const float tz, const float tw = 1.0f);

	Vect4D operator + (Vect4D t);
	Vect4D operator - (Vect4D t);
	Vect4D operator * (const float scale);
	void operator += (const Vect4D& t);
	void Cross(Vect4D &vin, Vect4D &vout);

	float&operator[](VECT_ENUM e);

private:
	union
	{
	     __m128	_m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};     

#endif  

// End of file



//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

