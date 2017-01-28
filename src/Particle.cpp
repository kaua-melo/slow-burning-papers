


#include "Particle.h"

Particle::Particle(int x, int y, int _r, float f)
{
	pos.x = x;
	pos.y = y;

	r = _r;

	friction = f;

	acc.set(0,0);
	vel.set(0,0);

	// limit the velocity of the particle
	speedLimit = 50;

	c = ofColor(0);
}


void Particle::update()
{
	vel += acc;
	vel.limit(speedLimit); // Avoid particle going too fast
						   // In case you're using a chain of particles,
						   //  avoid them going crazy some times...

	pos += vel;

	// add friction
	vel*=friction;

	// do not accumulate the acc
	acc.set(0,0);
	
	// check if the particle is touching the borders
	//boundaries();
}


void Particle::update2()
{
    pos+= 0.03*(fxP-pos);
}


void Particle::draw()
{
	//ofSetColor(c);
	//ofDrawEllipse(pos.x, pos.y, 2*r, 2*r);
    
    
    ofSetColor(0, 255, 255, 2);
    ofDrawEllipse(pos.x, pos.y, 4*r, 4*r);
    
    
    //ofSetColor(0, 255, 255, 5);
    //ofDrawEllipse(pos.x, pos.y, 5, 5);
    
    //ofSetColor(0,255,255,25);
    //ofDrawEllipse(100, 100, 5, 5);
    
    ofSetColor(0,255,255,255);
    ofDrawEllipse(pos.x, pos.y, r, r);
}


void Particle::addForce(ofVec2f f)
{
	acc += f;
}

void Particle::setColor(ofColor color)
{
	c = color;
}


void Particle::boundaries()
{
	// touching the right side
	if(pos.x + r > ofGetWindowWidth())
	{
		pos.x  = ofGetWindowWidth() - r;
		vel.x *= -1*0.3;
	}
	// touching the left side
	else if(pos.x - r < 0)
	{
		pos.x  =  r;
		vel.x *= -1*0.3;
	}

	// touching the top
	if(pos.y - r < 0)
	{
		pos.y  = r;
		vel.y *= -1*0.3;
	}
	// touching the bottom
	else if(pos.y + r > ofGetWindowHeight())
	{
		pos.y  = ofGetWindowHeight() - r;
		vel.y *= -1*0.3; 
	}
}

void Particle::setFixedPoint(ofVec2f point)
{
	fxP = point;
}

























