#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticlePack.h"
#include "Bubble2D.h"
#include "Gradient.h"



class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		float getDistance(ofVec2f p1, ofVec2f p2);
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
	    
    
	private:
        Bubble2D* bubble;

		bool isMousePressed; // mouse can pull the bubble
    
        // Save frames ---------------------
		bool save; // Will be used as a trigger sign to save the frames
        int frameCount; // what's the current frame being saved
        int firstFrame; // used to force the first frame saved to be 0
        // ---------------------------------
    
    
    
        /*
        
        c1 -----c12----------------c2-----c23----c3
        A11      /                 A12     /     A13
                /                 /       /
        Apercentage[0]           /  Apercentage[1]
                                /
                             cPA
        */
        
        // Colors --------------------------
        // ---------------------------------
        float A13[4] = { 255.0/255.0,   0.0/255.0,     0.0/255.0, 1};
        float A12[4] = { 245.0/255.0,  127.0/255.0,   32.0/255.0, 1};
        float A11[4] = { 122.0/255.0,   70.0/255.0,  155.0/255.0, 1};
        float Apercentage[2] = {0.3947, 0.7468};
    
        float B13[4] = { 237.0/255.0,   31.0/255.0,  36.0/255.0, 1};
        float B12[4] = { 245.0/255.0,  127.0/255.0,  32.0/255.0, 1};
        float B11[4] = {  58.0/255.0,   27.0/255.0,  84.0/255.0, 1};
        float Bpercentage[2] = {0.3258, 0.5322};

        float C11[4] = { 27.0/255.0,   14.0/255.0,   44.0/255.0, 1};
        float C12[4] = { 238.0/255.0,  41.0/255.0,   36.0/255.0, 1};    
        float C13[4] = { 238.0/255.0,  41.0/255.0,   36.0/255.0, 1};
        float Cpercentage[2] = {0.8, 0.0};

        float D11[4] = {  27.0/255.0,  14.0/255.0,   44.0/255.0, 1};
        float D12[4] = { 238.0/255.0,  41.0/255.0,   36.0/255.0, 1};    
        float D13[4] = { 238.0/255.0,  41.0/255.0,   36.0/255.0, 1};
        float Dpercentage[2] = {1, 0.0};
    
        float E13[4] = { 0.0/255.0,  0.0/255.0,  0.0/255.0, 1};
        float E12[4] = { 0.0/255.0,  0.0/255.0,  0.0/255.0, 1};
        float E11[4] = { 0.0/255.0,  0.0/255.0,  0.0/255.0, 1};
        float Epercentage[2] = {1, 0.0};
    
        // ---------------------------------
   

        // The changing positions on the gradient
        // --------------------------------------
        float cPA = 1-0.4183;
        float cPB = 1-0.2703;
        float cPC = 1;
        float cPD = 1;
        float cPE = 1;
    

    
    
        float getDark;    
        // Goes from 0 to 1.
        // 0 = day  1 = night
        float factor;
    

		// Perlin Noise Flow Variables -----------------------------------
		int gridCell;  // width and height of a grid cell
		int nColumns;  // grid's number of columns
		int nLines;  // grid's number of columns
		float pInc;    // perlin noise increment
		float zTime;   // Third dimension perlin noise time
        float fTime;

		// Array with the force's direction of every cell of the screen
		vector<ofVec2f>  forceDirection;
		//-----------------------------------------------------------------

    
    
        // Save the position of the mouse when clicked.
        // used if you want save the exact order and position
        // of the pulls on the bubble.
        ofFile textFileX;
        ofFile textFileY;
        
    
        int fNFrames; // number of frames the force will actuate
        ofVec2f f;
    
    
        // the frames a force will pull the bubble
        vector <int> beatFrame;
        // in which beat we are
        int beatIndex;
    
        ofShader shader;
        ofShader shaderBlack;

    
        // to add grain on the image
        ofImage grain;
};
