//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "DO_NOT_MODIFY\OpenGLInterface.h"
#include "Framework.h"

#include "ParticleEmitter.h"
#include "Settings.h"
#define UNUSED_VAR(x) (void *)x
extern PerformanceTimer GlobalTimer;

static const unsigned char squareColors[] =
{
	// ----------------------------
	//  point is actually a quad   
	//  set color on each vertex   
	// ----------------------------
	//    Vert A = Yellow 
	//    Vert B = Yellow
	//    Vert C = Yellow
	//    Vert D = Yellow
	// ----------------------------

	200,  200,  0,  255,
	200,  200,  0,  255,
	200,  200,  0,  255,
	200,  200,  0,  255,
};

static const float squareVertices[] =
{
	// --------------------
	//   Vert A = (x,y,z)
	//   Vert B = (x,y,z)
	//   Vert C = (x,y,z)
	//   Vert D = (x,y,z)
	// --------------------

	-0.015f,  -0.015f, 0.0f, // Size of Triangle
	 0.015f,  -0.015f, 0.0f, // Size of Triangle
	-0.015f,   0.015f, 0.0f, // Size of Triangle
	 0.015f,   0.015f, 0.0f, // Size of Triangle
};

ParticleEmitter::ParticleEmitter()
	: start_position(0.0f, 0.0f, 0.0f),
	start_velocity(0.0f, 1.0f, 0.0f),
	max_life(MAX_LIFE),
	max_particles(NUM_PARTICLES),
	spawn_frequency(0.0000001f),
	last_active_particle(-1),

	//particle_list(NUM_PARTICLES),//
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f),
	scale_variance(2.5f),
	headParticle(0)
{
	GlobalTimer.Toc();

	this->SpawnParticle();
	last_spawn = GlobalTimer.TimeInSeconds();
	last_loop = GlobalTimer.TimeInSeconds();
}


ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}

void ParticleEmitter::SpawnParticle()
{
	this->maddr = malloc(sizeof(Particle) * this->max_particles);
	//this->maddr = _aligned_malloc(sizeof(Particle) * this->max_particles, 16); //load in place 
	this->headParticle = (Particle*)maddr;
	//Particle* phead = (Particle*)maddr;
	Particle* phead = this->headParticle;
	for (int i = 0; i < this->max_particles; i++) {
			
		phead->setParticle();
		phead->reset(start_position, start_velocity, Vect4D(2.0f, 2.0f, 2.0f, 2.0f));
		//pCurr->life = 0.0f;
		/////////phead->position = start_position;
		/////////phead->velocity = start_velocity;
		/////////phead->scale = Vect4D(2.0, 2.0, 2.0, 2.0);
		this->Execute(phead->position, phead->velocity, phead->scale);
		//	phead->next = phead + 1;
			//add to the list 
		phead++;
	}
	//pLast->next = nullptr;
	this->lastParticle = phead--;


}

void ParticleEmitter::update()
{
	// get current time
	GlobalTimer.Toc();
	float current_time = GlobalTimer.TimeInSeconds();
	//float time_elapsed;
	// spawn particles
	float time_elapsed = current_time - last_spawn;
	
	// update
	//this->SpawnParticle();
	while (spawn_frequency < time_elapsed)
	{
		// spawn a particle
		//this->SpawnParticle();
		// adjust time
		time_elapsed -= spawn_frequency;
		// last time
		last_spawn = current_time;
	}
	
	// total elapsed
     time_elapsed = current_time - last_loop;



	Particle* p = this->headParticle;
	if ((p->life > max_life)) {
		this->SpawnParticle();
	}
	for (int i = 0; i < max_particles; i++)
	{
		p->Update(time_elapsed);
		p++;
	}
	last_loop = current_time;


	//move a copy to vector for faster iterations in draw
	//p = this->headParticle;
	//bufferCount = 0;

	// clear the buffer
	//drawBuffer.clear();

	// walk the pointers, add to list
	/*
	while (p != nullptr)
	{
		// add to buffer
		drawBuffer.push_back(*p);

		// advance ptr
		p = p->next;

		// track the current count
		bufferCount++;
	}
	*/
	// make sure the counts track (asserts go away in release - relax Christos)
	//assert(bufferCount == (last_active_particle + 1));
	
}

/////void ParticleEmitter::addParticleToList(Particle* p)
/////{
/////	assert(p);
/////	if (this->headParticle == nullptr)
/////	{ // first on list
/////		this->headParticle = p;
/////		p->next = nullptr;
/////		p->prev = nullptr;
/////	}
/////	else
/////	{ // add to front of list
/////		headParticle->prev = p;
/////		p->next = headParticle;
/////		p->prev = nullptr;
/////		headParticle = p;
/////
/////	}
/////
/////}

////void ParticleEmitter::removeParticleFromList(Particle* p)
////{
////	// make sure we are not screwed with a null pointer
////	assert(p);
////
////	if (p->prev == nullptr && p->next == nullptr)
////	{ // only one on the list
////		this->headParticle = nullptr;
////	}
////	else if (p->prev == nullptr && p->next != nullptr)
////	{ // first on the list
////		p->next->prev = nullptr;
////		this->headParticle = p->next;
////	}
////	else if (p->prev != nullptr && p->next == nullptr)
////	{ // last on the list 
////		p->prev->next = nullptr;
////	}
////	else//( p->next != nullptr  && p->prev !=nullpttr )
////	{ // middle of the list
////		p->prev->next = p->next;
////		p->next->prev = p->prev;
////	}
////
////	// bye bye
////	delete p;
////}

void ParticleEmitter::draw()
{
	// get the camera matrix from OpenGL
	// need to get the position
	Matrix cameraMatrix;

	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));
	
	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);
	// iterate throught the list of particles
	//list<Particle>::iterator it=
	//Particle* it = this->headParticle;
	//std::list<Particle>::iterator it;
	//for (it = drawBuffer.begin(); it != drawBuffer.end(); ++it)
	//while(it!=nullptr)
	//{
		//Temporary matrix
		//Matrix tmp;

		// get the position from this matrix
	
	Vect4D camPosVect;
	cameraMatrix.get(Matrix::MATRIX_ROW_3, &camPosVect);

	//	Matrix transCamera;
		//	transCamera.setTransMatrix(&camPosVect);
	//////////////////Matrix transParticle;
	//////////////////Matrix pivotParticle;
	////////////////////Matrix tmp;
	//////////////////Matrix rotParticle;
	//////////////////Matrix scaleMatrix;
	//////////////////Vect4D pivotVect;
	//////////////////Matrix transCamera;
	//////////////////transCamera.setTransMatrix(&camPosVect);
	Particle* it = this->headParticle;
	if (it == 0) return;
	for(int i=0;i<this->max_particles;i++)
	{
		Matrix tmp;
		// camera position
	//	Matrix transCamera;
		tmp.setRotZMatrix(it->rotation);
		Vect4D tmpV4 = (camPosVect + it->position * 0.35f);
		//	transCamera.setTransMatrix(&camPosVect);

			// particle position

		   // transParticle.setTransMatrix(&(it->position * 0.35f));
										//it->position = it->position * 0.35f;
									   // transParticle.setTransMatrix(&(it->position));
			// rotation matrix

										//  rotParticle.setRotZMatrix(it->rotation);

			// pivot Point

										  //    pivotVect.set(1.0f, 0.0f, 50.0f);
										  //    pivotVect = pivotVect * 20.0f * it->life;

										   //   pivotParticle.setTransMatrix(&pivotVect);

			// scale Matrix

										   //   scaleMatrix.setScaleMatrix(&it->scale);

		//direct caculate matrix not use * or proxy 
		float tmpX = tmpV4[VECT_ENUM::x];
		float tmpY = tmpV4[VECT_ENUM::y];
		tmpV4[VECT_ENUM::x] = (tmpX * tmp[m0] + tmpY * tmp[m4]) * it->scale[VECT_ENUM::x];
		tmpV4[VECT_ENUM::y] = (tmpX * tmp[m1] + tmpY * tmp[m5]) * it->scale[VECT_ENUM::y];
		tmpV4[VECT_ENUM::z] *= it->scale[VECT_ENUM::z];

		tmp[m0] *= it->scale[VECT_ENUM::x] * it->scale[VECT_ENUM::x];
		tmp[m1] *= it->scale[VECT_ENUM::x] * it->scale[VECT_ENUM::x];
		tmp[m4] *= it->scale[VECT_ENUM::y] * it->scale[VECT_ENUM::y];
		tmp[m5] *= it->scale[VECT_ENUM::y] * it->scale[VECT_ENUM::y];
		tmp[m10] *= it->scale[VECT_ENUM::z] * it->scale[VECT_ENUM::z];

		tmp[m12] = tmpV4[VECT_ENUM::x];
		tmp[m13] = tmpV4[VECT_ENUM::y];
		tmp[m14] = tmpV4[VECT_ENUM::z];
		tmp[m15] = 1.0f;

		//tmp = scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;
		// rotation matrix

	//	rotParticle.setRotZMatrix(it->rotation);

		// pivot Point
	//	Matrix pivotParticle;
	//	Vect4D pivotVect;

		//pivotVect.set(1.0, 0.0, 50.0);
	//	pivotVect = pivotVect * 20.0 * it->life;

		//pivotParticle.setTransMatrix(&pivotVect);

		// scale Matrix
		//Matrix scaleMatrix;
		//scaleMatrix.setScaleMatrix(&it->scale);

		// total transformation of particle
		//tmp = scaleMatrix * transCamera * transParticle *rotParticle * scaleMatrix;

		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));

		// squirrel away matrix for next update
		//////////////tmp.get(Matrix::MATRIX_ROW_0, &it->curr_Row0);
		//////////////tmp.get(Matrix::MATRIX_ROW_1, &it->curr_Row1);
		//////////////tmp.get(Matrix::MATRIX_ROW_2, &it->curr_Row2);
		//////////////tmp.get(Matrix::MATRIX_ROW_3, &it->curr_Row3);

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);



		// difference vector     
		/*it->diff_Row0 = it->curr_Row0 - it->prev_Row0;
		it->diff_Row1 = it->curr_Row1 - it->prev_Row1;
		it->diff_Row2 = it->curr_Row2 - it->prev_Row2;
		it->diff_Row3 = it->curr_Row3 - it->prev_Row3;*/

		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
				// do not delete these two lines
		GLenum glError = glGetError();
		UNUSED_VAR(glError);
		it++;
	}

	// delete the buffer

	/*
	for (size_t i = 0; i < drawBuffer.size(); i++)
	{
		drawBuffer.pop_back();
	}

	// done with buffer, clear it.
	drawBuffer.clear();
	*/
}

//*******************************************************************************
void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// --------------------------------------------------------------
	//   Ses it's ugly - I didn't write this so don't bitch at me   |
	//   Sometimes code like this is inside real commerical code    |
	//   ( so now you know how it feels )  |
	//---------------------------------------------------------------

	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.005f; // Var
	float sign = static_cast<float>(rand() % 2);  // Sign 
	float* t_pos = reinterpret_cast<float*>(&pos);
	float* t_var = &pos_variance[VECT_ENUM::x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	// x  - add velocity
	t_pos = &vel[VECT_ENUM::x];
	t_var = &vel_variance[VECT_ENUM::x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// correct the sign
	var = 1.5f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if (sign == 0)
	{
		var *= -1.0;
	}
	sc = sc * var;
}


void ParticleEmitter::GoodBye()
{
	/*
	Particle* pTmp = this->headParticle;
	Particle* pDeadMan = nullptr;
	while (pTmp)
	{
		pDeadMan = pTmp;
		pTmp = pTmp->next;
		delete pDeadMan;
	}
	*/
	delete maddr;
}

// End of file
