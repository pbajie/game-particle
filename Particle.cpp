//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
/*
#include "Particle.h"
#include "Matrix.h"


Particle::~Particle()
{
	// nothing to do
}
void Particle::setNext(Particle* x) {
	//this->next= x;
}
void Particle::CopyDataOnly(Particle *p)
{
	// copy the data only
	// this way of copying data is more efficient that element by element
	this->position = p->position;
	this->velocity = p->velocity;
	this->scale = p->scale;
	this->rotation = p->rotation;
	this->rotation_velocity = p->rotation_velocity;
	this->life = p->life;
}

void Particle::Spawn(Vect4D& pos, Vect4D& vel, Vect4D& sc) {
	
	Particle* newParticle = new Particle();
	newParticle->life = 0.0f;
	newParticle->position = pos;
	newParticle->velocity = vel;
	newParticle->scale = sc;
	

}
void Particle::init() {
	this->life = 0.0f;
	this->position.set(0.0f, 0.0f, 0.0f);
	this->velocity.set(0.0f, 0.0f, 0.0f);
	this->scale.set(1.0f, 1.0f, 1.0f);
	this->rotation = 0.0f;
	this->rotation_velocity = 0.25f;
	this->next = 0;
	this->prev = 0;
}
void Particle::Update(const float& time_elapsed)
{
	
	// Rotate the matrices
	Vect4D tmp_Row0;
	tmp_Row0 = curr_Row0;
	prev_Row0 = tmp_Row0;

	Vect4D tmp_Row1;
	tmp_Row1 = curr_Row1;
	prev_Row1 = tmp_Row1;

	Vect4D tmp_Row2;
	tmp_Row2 = curr_Row2;
	prev_Row2 = tmp_Row2;

	Vect4D tmp_Row3;
	tmp_Row3 = curr_Row3;
	prev_Row3 = tmp_Row3;

	diff_Row0 = curr_Row0 - prev_Row0;
	diff_Row1 = curr_Row1 - prev_Row1;
	diff_Row2 = curr_Row2 - prev_Row2;
	diff_Row3 = curr_Row3 - prev_Row3;

	//diff_Row0 = Vect4D(0, 0, 0, 0);
	//diff_Row1 = Vect4D(0, 0, 0, 0);
	//diff_Row2 = Vect4D(0, 0, 0, 0);
	//diff_Row3 = Vect4D(0, 0, 0, 0);

	Matrix tmp;

	tmp.set(Matrix::MATRIX_ROW_0, &this->diff_Row0);
	tmp.set(Matrix::MATRIX_ROW_1, &this->diff_Row1);
	tmp.set(Matrix::MATRIX_ROW_2, &this->diff_Row2);
	tmp.set(Matrix::MATRIX_ROW_3, &this->diff_Row3);

	float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * (time_elapsed));

	Vect4D axis(1, 0, 0);
	Vect4D v(0, 50, 0);
	position.Cross(axis, v);
	v.norm(v);
	position = position + v * 0.07 * life;

	if (MatrixScale > 1.0)
	{
		MatrixScale = 1.0 / MatrixScale;
	};

	
	rotation = rotation + (MatrixScale + rotation_velocity) * time_elapsed * 4.0;
	
	
}
*/
//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Particle.h"
#include "Matrix.h"


//article::Particle()
//
//	// construtor
//	this->life = 0.0f;
//	this->position.set(0.0f, 0.0f, 0.0f);
//	this->velocity.set(0.0f, 0.0f, 0.0f);
//	this->scale.set(1.0f, 1.0f, 1.0f);
//	this->rotation = 0.0f;
//	this->rotation_velocity = 0.25f;
//	this->next = 0;
//	this->prev = 0;
//*/

Particle::Particle(const Vect4D& startP, const Vect4D& startV, const Vect4D& startSc)
{
	this->life = 0.0f;
	this->position = startP;
	this->velocity = startV;
	this->scale = startSc;
	this->rotation = 0.0f;
	this->rotation_velocity = 0.25f;
	this->next = 0;
	this->prev = 0;
}

Particle::~Particle()
{
	// nothing to do
}
//void Particle::CopyDataOnly(Particle* p){
//
//	// copy the data only
//	// this way of copying data is more efficient that element by element
//	this->position = p->position;
//	this->velocity = p->velocity;
//	this->scale = p->scale;
//	this->rotation = p->rotation;
//	this->rotation_velocity = p->rotation_velocity;
//	this->life = p->life;
//}

void Particle::Update(const float& time_elapsed)
{
	//////////this->prev_Row0 = this->curr_Row0;
	//////////this->prev_Row1 = this->curr_Row1;
	//////////this->prev_Row2 = this->curr_Row2;
	//////////this->prev_Row3 = this->curr_Row3;
	//////////
	//////////diff_Row0 = this->curr_Row0 - this->prev_Row0;
	//////////diff_Row1 = this->curr_Row1 - this->prev_Row1;
	//////////diff_Row2 = this->curr_Row2 - this->prev_Row2;
	//////////diff_Row3 = this->curr_Row3 - this->prev_Row3;


	//Matrix tmp;

	///////tmp.set(Matrix::MATRIX_ROW_0, &this->diff_Row0);
	///////tmp.set(Matrix::MATRIX_ROW_1, &this->diff_Row1);
	///////tmp.set(Matrix::MATRIX_ROW_2, &this->diff_Row2);
	///////tmp.set(Matrix::MATRIX_ROW_3, &this->diff_Row3);

	//float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position += (velocity * (time_elapsed));

	Vect4D axis(1.0f, 0.0f, 0.0f);
	Vect4D v(0.0f, 50.0f, 0.0f);
	position.Cross(axis, v);
	v.norm(v);
	position += v * 0.07f * life;

//if (MatrixScale > 1.0f)
//{
//	MatrixScale = 1.0f / MatrixScale;
//};

	//rotation += (MatrixScale + rotation_velocity) * time_elapsed * 4.0f;
	rotation += ( rotation_velocity) * time_elapsed * 4.0f;
}

void Particle::reset(const Vect4D& startP, const Vect4D& startV, const Vect4D& startSc)
{
	this->position = startP;
	this->velocity = startV;
	this->scale = startSc;
}

void Particle::setParticle()
{
	this->life = 0.0f;
	this->position.set(0.0f, 0.0f, 0.0f);
	this->velocity.set(0.0f, 0.0f, 0.0f);
	this->scale.set(1.0f, 1.0f, 1.0f);
	this->rotation = 0.0f;
	this->rotation_velocity = 0.25f;
	this->next = 0;
	this->prev = 0;
}


