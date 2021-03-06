
#ifndef _PARTICLE // if this class hasn't been defined, the program can define it
#define _PARTICLE // by using this if statement you prevent the class to be called more than once which would confuse the compiler

#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework

class Particle
{
	public:
		// particle's position
		ofVec2f pos;
	
        // fixed point
        ofVec2f fxP;
    
		// radius
		int r;

		// friction
		float friction;

		// color
		ofColor c;

		// acc-vel
		ofVec2f acc;
		ofVec2f vel;
		float speedLimit;

		Particle(int x, int y, int r, float f); // constructor
		void update();  // through acc-vel-pos
    	void update2(); // % of the distance
		void draw();
		void addForce(ofVec2f f);
		void setColor(ofColor color);
        void setFixedPoint(ofVec2f point);
		void boundaries();
	private:

	
};
#endif
