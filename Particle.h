//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class Particle : Align16
{
public:
	friend class ParticleEmitter;

	Particle(const Vect4D& startP, const Vect4D& startV, const Vect4D& startSc);

	//Particle();
	~Particle();
	void Update(const float& time_elapsed);
	void reset(const Vect4D& startP, const Vect4D& startV, const Vect4D& startSc);
	void setParticle();
	//void CopyDataOnly(Particle *p);
	//void Spawn(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	//void init();
//	void setNext(Particle* x);
private:
	//Particle *next;
	//Particle *prev;

	//Vect4D	prev_Row0;
	//Vect4D	prev_Row1;
	//Vect4D  prev_Row2;
	//Vect4D  prev_Row3;
	
	Vect4D	position;
	//float	life;
	Vect4D	velocity;
	//Particle* next;
	Vect4D	scale;
	Particle* next;
	Particle* prev;
	float	life;
	float	rotation;
	//Vect4D  diff_Row0;
	//Vect4D  diff_Row1;
	//Vect4D  diff_Row2;
	//Vect4D  diff_Row3;
	float	rotation_velocity;


	//Vect4D	curr_Row0;
	//Vect4D	curr_Row1;
	//Vect4D  curr_Row2;
	//Vect4D  curr_Row3;
};


#endif 
