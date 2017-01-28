
#ifndef _BUBBLE2D // if this class hasn't been defined, the program can define it
#define _BUBBLE2D // by using this if statement you prevent the class to be called more than once which would confuse the compiler

#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
#include "Particle.h"


class Bubble2D
{
	public:
		// center of the bubble
		ofVec2f center;

		// number of particles
		int np;

		// circunference of the bubble
		int circunference;

		// radius of the bubble
		float r;

		// strength between the particles
		float str;

		// strength of the connection between 
		//  the particles and the central particle
		float cStr;


		// friction
		float friction;

		// weigth of the line when drawing the chain
		int weight;

		// surface's particles
		vector <shared_ptr<Particle>> p;

		// fixed points of the particles
		vector <ofVec2f> fxP;
		
		// center particle
		Particle* cParticle;

		// color
		ofColor c;
    
        // Colors --------------------------
        // ---------------------------------
        //float c2[4] = { 210.0/255.0,   68.0/255.0,   39.0/255.0, 1};
        //float c1[4] = {  232.0/255.0,  169.0/255.0,   34.0/255.0, 1};
        float c1[4] = { 255.0/255.0,  216.0/255.0,   13.0/255.0, 1};
        float c2[4] = { 255.0/255.0,  12.0/255.0,   0.0/255.0, 1};
  

        // The changing positions on the gradient
        // --------------------------------------
        float cP = 0.5;


        // contour of the blob
        ofPolyline contour;


		Bubble2D(int x, int y, int _np, int _r, float _str, float f, float w, ofColor _c); 
		void update();
		void drawP(); // draw particles
		void drawL(); // draw line
		void drawS(); // draw shape
		void applyForce(ofVec2f f); // apply force to the bubble (move it as a rigid body)
		vector <ofVec2f> pointsInside(int y); // get the points inside the shape
    
        ofShader bShader;

	private:

	
};
#endif
