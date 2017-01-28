
#include "ofApp.h"
#include "Particle.h"
#include "ParticlePack.h"
#include "Bubble2D.h"
#include "Gradient.h"



//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);   

    shader.load("shadersGL3/shader");
    shaderBlack.load("shadersGL3/shaderBlack");
    
    grain.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);    
    
    // in which beat we are
    beatIndex =0;
    
    
    // 
    beatFrame = 
    {0,
    242,
    481,
    720,
    959,
    1197,
    1435,
    1675,
    1913,
    2152,
    2390,
    2629,
    2868,
    3106,
    3345,
    3584,
    3823,
    4061,
    4300,
    4539,
    4778,
    5016,
    5255,
    5493,
    5732,
    5971,
    6209,
    6448,
    6687,
    6925,
    7164,
    7403,
    7641,
    7880,
    8119,
    8357,
    8596,
    8834,
    9073,
    9312,
    9551,
    9789,
    10028,
    10266,
    10506,
    10744,
    10983,
    11222,
    11461,
    11701,
    11940,
    12178,
    12417,
    12655,
    12894,
    13133,
    13371,
    13610,
    13849,
    14087
    };
    
    
    // what's the current frame being saved
    frameCount = 0;
    
    // Save the position of the mouse when clicked.
    // used if you want save the exact order and position
    // of the pulls on the bubble.
    textFileX.open("forceX.txt", ofFile::WriteOnly);
    textFileY.open("forceY.txt", ofFile::WriteOnly);

        
    // Perlin Noise Flow Variables --------------
	gridCell = 180;	  // width and height of a grid cell
	pInc  	 = 0.1;  // perlin noise increment
	zTime    = 0;	  // Third dimension perlin noise time
	nColumns = 5;
    nLines   = 5;
	// -------------------------------------------


	isMousePressed  = false;  // mouse can pull the bubble
	save		 	= false;  // true -> save each frame 


    ofEnableAlphaBlending();    // in case you want use 
	ofSetBackgroundAuto(false); // translucid background
    
    
    //getDark =0.7;
    getDark =0;
    
    // Bubble2D(int x, int y, int _np, int _r, float _str, float f, float w, ofColor _c)    
    bubble = new Bubble2D(ofGetWindowWidth()/2, 400, 15, 350, 0.01, 0.98, 5, ofColor(255, 255, 0));
    // -------------------------------------------------------
    
    
    
    
    // GRAIN -----------------------------------------------------------
    //float f = ofMap(mouseY, 0, ofGetHeight(), 0, 1);
    float f = 0.3;
    for(int y=0; y<grain.getHeight(); y++)
    {
        for(int x=0; x<grain.getWidth(); x++)
        {
            if(ofRandom(1)<f)
            {
                grain.setColor(x,y, ofColor(0,0,0,25));
            }
            else
            {
                grain.setColor(x,y, ofColor(255,255,255,0));
            }
        }
    }
    
    grain.update();
    // ----------------------------------------------------------------- 
    
    //ofSetFullscreen(true);
}



//--------------------------------------------------------------
void ofApp::update()
{
    // Random wind ==============================================================
		// Array with the force's direction of every cell of the screen
		//forceDirection.clear();
    
    /*
        float f = 2*(ofNoise(fTime) -0.5); //returns value from 0 to 1
    
        
            
        ofVec2f temp(bubble->p[0]->pos - bubble->cParticle->pos);
        float angle1 = atan( temp.y/temp.x );
 
        ofVec2f f1( f*cos(angle1), f*sin(angle1)  );        
        
        bubble->p[0]->addForce(f1);
        
    
    
        fTime+=0.01;
    */
    

/*
		// 2D Perlin noise field ---------------------
		float yTime = 0;
		for(int y=0; y<nLines; y++)
		{
			float xTime = 0;
			for(int x=0; x<nColumns; x++)
			{
				//float noise = ofSignedNoise(xTime, yTime, zTime); // returns value from -1 to 1
				float noise = ofNoise(xTime, yTime, zTime); //returns value from 0 to 1
				float teta = noise*6.28;

				forceDirection.push_back(ofVec2f(cos(teta), sin(teta)));

				xTime+=pInc;
			}
			yTime+=pInc;
		}
		zTime+=0.01;
		// -------------------------------------------
*/
    

/*
		// Applying the flow's force
		for(unsigned int i=0; i<bubble->p.size(); i+=2)
		{	
            int x = int( (bubble->p[i]->pos.x - bubble->cParticle->pos.x + bubble->r)/gridCell);
			int y = int( (bubble->p[i]->pos.y - bubble->cParticle->pos.y + bubble->r)/gridCell);
            
			bubble->p[i]->addForce(forceDirection[x + y*nColumns]*0.3);
		}
*/
    
        //std::cout<<forceDirection[0].length()<<endl;
        //bubble->p[0]->addForce(forceDirection[0]);
		
    
	//===========================================================================
    
    
    
    
    
   
    //factor = ofMap(mouseY, 0, ofGetWindowHeight(), 0, 1);
    //getDark += 0.000069735;
    factor = getDark;
    //factor =0;
    
    
    if(factor>1) factor=1;
    
    
    // SUN    
    ofColor sunI(232, 194, 40);
    ofColor sunF(241,  38,  5);
    
    //bubble->c = ofColor(236+5*factor, 
    //                    204-166*factor, 
    //                    93-88*factor, 50);

    // factor for sun color
    //float fsc = 2*factor;
    //fsc = ofClamp(fsc, 0, 1.1);
    
    //bubble->c = ofColor((int)sunI.r + fsc*((int)sunF.r-sunI.r), 
    //                    (int)sunI.g + fsc*((int)sunF.g-sunI.g), 
    //                    (int)sunI.b + fsc*((int)sunF.b-sunI.b),
    //                    255);
     
    int initialPos = 0.4*ofGetHeight();
    int finalPos   = 1.3*ofGetHeight();
    
    
    //bubble->cParticle->pos.set(bubble->cParticle->pos.x,
    //                           bubble->r+250+factor*ofGetWindowHeight());
    
    bubble->cParticle->pos.set(bubble->cParticle->pos.x,
                               initialPos + factor*(finalPos-initialPos));    
    
    

    
    // Applying force to the bubble
    if(fNFrames <10) // 13 times
    {
        for(unsigned int i=0; i<bubble->p.size(); i++)
		{
			if(f.distance(bubble->p[i]->pos) < 250)
			{
				ofVec2f force = bubble->p[i]->pos - f;
				force *= -0.01;

				bubble->p[i]->addForce(force);
			}
		}
        fNFrames ++;
    }

     
    

	// INTERACTION WITH THE MOUSE ========================
	// ---------------------------------------------------
	if(isMousePressed)
	{
        textFileX<<mouseX -  ofGetWindowWidth()/2<<endl;
        textFileY<<mouseY - bubble->cParticle->pos.y<<endl;
        
        
		ofVec2f mouse;
		mouse.set(mouseX, mouseY);

		//bubble->applyForce(mouse);
	

		for(unsigned int i=0; i<bubble->p.size(); i++)
		{
			if(mouse.distance(bubble->p[i]->pos) < 200)
			{
				ofVec2f f = bubble->p[i]->pos - mouse;
				f *= -0.01;

				bubble->p[i]->addForce(f);
			}
		}
	}
	//----------------------------------------------------    
    

    if(save)
    {
        frameCount = ofGetFrameNum() - firstFrame;
        
        if(frameCount > 119) // wait 2 seconds before start applying forces
        {            
            if(beatIndex < beatFrame.size())
            {
                //std::cout<<beatIndex<<endl;

                if(frameCount-120 == beatFrame[beatIndex])
                //if(frameCount%239 == 0)
                {
                    fNFrames = 0;

                    float angle = ofRandom(0, 6.28);

                    f = ofVec2f(314*cos(angle), 314*sin(angle));
                    f += ofVec2f(ofGetWindowWidth()/2, bubble->cParticle->pos.y);

                    beatIndex++;
                }
            }
            
            //getDark += 0.0000701213;
            getDark += 0.000069735;
        }
    }
    
	bubble->update();

	if(save)
	{
        // firstFrame = ofGetFrameNum();
        
        //bubble->update();
		//ofSaveScreen("f/"+ofToString(ofGetFrameNum())+".png");
		ofSaveScreen("f/"+ofToString( frameCount )+".png");
	}
    
    


}

//--------------------------------------------------------------
void ofApp::draw()
{
    
/*
	// draw Flow
	for(int y=0; y<nLines; y++)
	{
		for(int x=0; x<nColumns; x++)
		{
			ofPushMatrix();       
				ofTranslate(x*gridCell, y*gridCell);
				//ofRotateX(teta); 
				ofSetColor(0,200,200);        
				ofDrawLine(0, 0, forceDirection[x+y*nColumns].x*gridCell, forceDirection[x+y*nColumns].y*gridCell);
    		ofPopMatrix(); 
		}
	}
*/

        
            
    float color1[4];
    float color2[4];
    float color3[4];
    float percentage[2];
    
    float pos[3];
    
    //float ptimeAB = 0.40;
    //float ptimeBC = 0.35;
    //float ptimeCD = 0.15;
    //float ptimeDE = 0.10;
    
    float ptimeAB = 0.40;
    float ptimeBC = 0.45;
    float ptimeCD = 0.15;
    float ptimeDE = 0.01; 
    
    // A to B
    if(factor <= ptimeAB)
    {
        float f = ofMap(factor, 0, ptimeAB, 0, 1);
        
        color1[0] = A11[0] + f*(B11[0]-A11[0]);
        color1[1] = A11[1] + f*(B11[1]-A11[1]);
        color1[2] = A11[2] + f*(B11[2]-A11[2]);
        color1[3] = 1;

        color2[0] = A12[0] + f*(B12[0]-A12[0]);
        color2[1] = A12[1] + f*(B12[1]-A12[1]);
        color2[2] = A12[2] + f*(B12[2]-A12[2]);
        color2[3] = 1;
    
        color3[0] = A13[0] + f*(B13[0]-A13[0]);
        color3[1] = A13[1] + f*(B13[1]-A13[1]);
        color3[2] = A13[2] + f*(B13[2]-A13[2]);
        color3[3] = 1;
        
        
        percentage[0] = Apercentage[0] + f*(Bpercentage[0] - Apercentage[0]);
        percentage[1] = Apercentage[1] + f*(Bpercentage[1] - Apercentage[1]);
        
        pos[0] = 0;
        pos[1] = cPA + f*(cPB-cPA);
        pos[2] = 1;
    }   
    // B to C
    else if(factor>ptimeAB && factor<=ptimeAB+ptimeBC)
    {
        float f = ofMap(factor, ptimeAB, ptimeAB+ptimeBC, 0, 1);
        
        color1[0] = B11[0] + f*(C11[0]-B11[0]);
        color1[1] = B11[1] + f*(C11[1]-B11[1]);
        color1[2] = B11[2] + f*(C11[2]-B11[2]);
        color1[3] = 1;   

        color2[0] = B12[0] + f*(C12[0]-B12[0]);
        color2[1] = B12[1] + f*(C12[1]-B12[1]);
        color2[2] = B12[2] + f*(C12[2]-B12[2]);
        color2[3] = 1;   
        
        color3[0] = B13[0] + f*(C13[0]-B13[0]);
        color3[1] = B13[1] + f*(C13[1]-B13[1]);
        color3[2] = B13[2] + f*(C13[2]-B13[2]);
        color3[3] = 1;   
        
        
        percentage[0] = Bpercentage[0] + f*(Cpercentage[0] - Bpercentage[0]);
        percentage[1] = Bpercentage[1] + f*(Cpercentage[1] - Bpercentage[1]);
        
        pos[0] = 0;
        pos[1] = cPB + f*(cPC-cPB);
        pos[2] = 1;
    }
    // C to D
    if(factor>ptimeAB+ptimeBC && factor<=ptimeAB+ptimeBC+ptimeCD)
    {
        float f = ofMap(factor, ptimeAB+ptimeBC, ptimeAB+ptimeBC+ptimeCD, 0, 1);
        
        color1[0] = C11[0] + f*(D11[0]-C11[0]);
        color1[1] = C11[1] + f*(D11[1]-C11[1]);
        color1[2] = C11[2] + f*(D11[2]-C11[2]);
        color1[3] = 1;   

        color2[0] = C12[0] + f*(D12[0]-C12[0]);
        color2[1] = C12[1] + f*(D12[1]-C12[1]);
        color2[2] = C12[2] + f*(D12[2]-C12[2]);
        color2[3] = 1;   
        
        color3[0] = C13[0] + f*(D13[0]-C13[0]);
        color3[1] = C13[1] + f*(D13[1]-C13[1]);
        color3[2] = C13[2] + f*(D13[2]-C13[2]);
        color3[3] = 1;   


        percentage[0] = Cpercentage[0] + f*(Dpercentage[0] - Cpercentage[0]);
        percentage[1] = Cpercentage[1] + f*(Dpercentage[1] - Cpercentage[1]);
        
        pos[0] = 0;
        pos[1] = cPC + f*(cPD-cPC);
        pos[3] = 1;
    }
    // D to E
    else if(factor>ptimeAB+ptimeBC+ptimeCD)
    {
        float f = ofMap(factor, ptimeAB+ptimeBC+ptimeCD, 1, 0, 1);
        
        color1[0] = D11[0] + f*(E11[0]-D11[0]);
        color1[1] = D11[1] + f*(E11[1]-D11[1]);
        color1[2] = D11[2] + f*(E11[2]-D11[2]);
        color1[3] = 1;   

        color2[0] = D12[0] + f*(E12[0]-D12[0]);
        color2[1] = D12[1] + f*(E12[1]-D12[1]);
        color2[2] = D12[2] + f*(E12[2]-D12[2]);
        color2[3] = 1;   
        
        color3[0] = D13[0] + f*(E13[0]-D13[0]);
        color3[1] = D13[1] + f*(E13[1]-D13[1]);
        color3[2] = D13[2] + f*(E13[2]-D13[2]);
        color3[3] = 1;   


        percentage[0] = Dpercentage[0] + f*(Epercentage[0] - Dpercentage[0]);
        percentage[1] = Dpercentage[1] + f*(Epercentage[1] - Dpercentage[1]);
        
        pos[0] = 0;
        pos[1] = cPD + f*(cPE-cPD);
        pos[3] = 1;
    }
    
  
    /*
        float f = ofMap(factor, 0, 0.25, 0, 1);
        
        color1[0] = C11[0];
        color1[1] = C11[1];
        color1[2] = C11[2];
        color1[3] = 1;

        color2[0] = C12[0];
        color2[1] = C12[1];
        color2[2] = C12[2];
        color2[3] = 1;
    
        color3[0] = C13[0];
        color3[1] = C13[1];
        color3[2] = C13[2];
        color3[3] = 1;
        
        
        percentage[0] = Cpercentage[0];
        percentage[1] = Cpercentage[1];
        
        pos[0] = 0;
        pos[1] = cPC;
        pos[2] = 1;
    */
    

    
//    if(factor>0.9866)
//    {
        //shaderBlack.begin();
        //    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        //shaderBlack.end();
//    }
//    else
//    {
        shader.begin();
            shader.setUniform3fv("pos", &pos[0]);
            shader.setUniform2fv("cPercentage", &percentage[0]);


            shader.setUniform4fv("c1", &color1[0]);
            shader.setUniform4fv("c2", &color2[0]);
            shader.setUniform4fv("c3", &color3[0]);

            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        shader.end();        
//    }
    

/*    
    if(factor>0.9866)
    {
        // GRAIN -----------------------------------------------------------
        //float f = ofMap(mouseY, 0, ofGetHeight(), 0, 1);
        float f = 0.3;
        for(int y=0; y<grain.getHeight(); y++)
        {
            for(int x=0; x<grain.getWidth(); x++)
            {
                //grain.setColor(x,y, ofColor(6,3,11,5));
                //grain.setColor(x,y, ofColor(0,0,0,2));
                
                
                if(ofRandom(1)<f)
                {
                    grain.setColor(x,y, ofColor(0,0,0,8));
                }
                else
                {
                    grain.setColor(x,y, ofColor(255,255,255,0));
                }
            }
        }

        grain.update();
        // -----------------------------------------------------------------    
    
        grain.draw(0,0);
        
        //shaderBlack.begin();
        //    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        //shaderBlack.end();
    }
*/
    
	//bubble->drawP();
	//bubble->drawL();
	bubble->drawS();
    
    

    //ofSetColor(0);
    //ofDrawLine(0,0.25*ofGetHeight(),ofGetWidth(),0.25*ofGetHeight());
    //ofDrawLine(0,0.5*ofGetHeight(),ofGetWidth(),0.5*ofGetHeight());
    //ofDrawLine(0,0.75*ofGetHeight(),ofGetWidth(),0.75*ofGetHeight());
    
    //grain.draw(0,0);
    
    //std::cout<<factor<<endl;
    
    
    //ofClear(0); 
    //ofDrawBitmapString("Hello World!", 100, 100);
    
    //ofSetColor(0);
    //ofDrawCircle(f.x,f.y,10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

	std::cout<<key<<endl;
	if(key == 115)
	{
        save = true;
        firstFrame = ofGetFrameNum();
	}
	else if(key == 112)
	{
		save = false;
	}
      
    
    // space - force
    else if(key == 32)
    {
        fNFrames = 0;
        
        float angle = ofRandom(0,6.28);
        
        f = ofVec2f(314*cos(angle), 314*sin(angle));
        f += ofVec2f(ofGetWindowWidth()/2, bubble->cParticle->pos.y);
        
        
        /*
        int p1 = (int)ofRandom(0, bubble->p.size()-1);
        int p2 = p1 +1;
        //int p3 = p2 +1;

        
        //while(p2==p1)
        //{
        //    p2 = (int)ofRandom(0, bubble->p.size());
        //}
        

        //float angle1 = (bubble->p[p1]->pos - bubble->cParticle->pos).angleRad(ofVec2f(1,0));

        
        ofVec2f temp(bubble->p[p1]->pos - bubble->cParticle->pos);
        float angle1 = atan( temp.y/temp.x );
        

    

        temp.set(bubble->p[p2]->pos - bubble->cParticle->pos);
        //float angle2 = (bubble->p[p2]->pos - bubble->cParticle->pos).angleRad(ofVec2f(1,0));
        float angle2 = atan( temp.y/temp.x );
        
        //temp.set(bubble->p[p3]->pos - bubble->cParticle->pos);
        //float angle3 = atan( temp.y/temp.x );

        
        //float mag1 = ofRandom(9, 10);
        float mag1 = 4;
        ofVec2f f1( mag1*cos(angle1), mag1*sin(angle1)  );
        
        float mag2 = 4;
        ofVec2f f2( mag2*cos(angle2), mag1*sin(angle2)  );
        
        //float mag3 = 10;
        //ofVec2f f3( mag3*cos(angle3), mag3*sin(angle3)  );
        
        
        bubble->p[p1]->addForce(f1);
        bubble->p[p2]->addForce(f2);
        //bubble->p[p3]->addForce(f3);

        */
		
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	isMousePressed = true;
}


// get distance between two points

float ofApp::getDistance(ofVec2f p1, ofVec2f p2)
{
	return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) );
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	isMousePressed = false;
}




//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
