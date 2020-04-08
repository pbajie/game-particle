//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H
#include <xmmintrin.h>
#include <smmintrin.h>
// includes
#include "Enum.h"
#include "Vect4D.h"
// forward declare
//class Vect4D;

// class
class Matrix
{
public:

	// local enumerations
	enum MatrixRowEnum
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix();
	Matrix(Matrix& t);
	~Matrix();
	//Matrix() = default;
	//Matrix(const Matrix& tmp) = default;
	//Matrix& operator=(const Matrix& tmp) = default;
	//~Matrix() = default;

	Matrix(const Vect4D& tV0,
		const Vect4D& tV1,
		const Vect4D& tV2,
		const Vect4D& tV3);

	Matrix operator * (const Matrix& m) const;


	//void set(MatrixRowEnum row, Vect4D *t);
	void get(MatrixRowEnum row, Vect4D* vOut);

	Matrix operator*(Matrix& rhs);

	void setIdentMatrix();
	void setTransMatrix(Vect4D* t);
	void setScaleMatrix(Vect4D* s);
	void setRotZMatrix(float Z_Radians);

	float& operator[](INDEX_ENUM e);

	//Matrix operator*(Matrix &t);

	float Determinant();

	Matrix GetAdjugate();
	Matrix& Matrix::operator/=(float t);

	void Matrix::Inverse(Matrix& out);

private:
	union
	{
		//__m128	_m;
		struct {
			Vect4D   v0;
			Vect4D   v1;
			Vect4D   v2;
			Vect4D   v3;

		};
		// anonymous struct
		struct {
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;

			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;

			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;

			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};

#endif 

// End of File


