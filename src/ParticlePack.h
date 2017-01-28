
#ifndef _PARTICLEPACK // if this class hasn't been defined, the program can define it
#define _PARTICLEPACK // by using this if statement you prevent the class to be called more than once which would confuse the compiler

#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
#include "Particle.h"


class ParticlePack
{
	public:
		// number of particles
		int np;

		// radius of the particles
		float r;

		// friction of the particles 
		float friction;

		// particles
		vector <shared_ptr<Particle>> p;

		// fixed points of the particles
		vector <ofVec2f> fxP;

		// color of the particles
		ofColor c;


		ParticlePack(int _np, int _r, float f, ofColor _c); 
		void update();
		void draw(); 
        void  setFixedPointsToPolygon(vector <ofVec2f> vertices);
        void  setFixedPointsRandomly(ofVec2f p1, ofVec2f p2);

		vector <ofVec2f> divideLine(ofVec2f p1, ofVec2f p2, int n);
    
	private:

	
};
#endif
