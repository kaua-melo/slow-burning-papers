
#include "Bubble2D.h"



Bubble2D::Bubble2D(int x, int y, int _np, int _r, float _str, float f, float w, ofColor _c)
{
    bShader.load("shadersGL3/shader2");

	// center of the bubble
	center.set(x,y);

	// number of particles
	np = _np;

	// radius of the bubble
	r = _r;

	// circunference of the bubble
	circunference = 6.28*r;

	// strength of the connection between the particles
	str = _str;

	// strength of the connection between 
	//  the particles and the central particle
	cStr = 0.5;

	// friction
	friction = f;

	// weigth of the line when drawing the chain
	weight = w;

	// color
	c = _c;

	// Creating center particle
	cParticle = new Particle(center.x, center.y, r*0.1, friction);



	// Creating surface's particles -----------------------------------------------------------------
	float angle = 6.28/np;

	// Creating particles
	for(int i =0; i<np; i++)
	{
		ofVec2f position = ofVec2f(center.x+r*cos(i*angle), center.y+r*sin(i*angle));

														//Particle(int x, int y, int _r, float f)
		shared_ptr<Particle> tempParticle = shared_ptr<Particle>(new Particle(position.x, position.y, weight, friction));

		p.push_back(tempParticle);

		fxP.push_back(position - center);
	}
	// ----------------------------------------------------------------------------------------------
}



void Bubble2D::applyForce(ofVec2f point)
{
	cParticle->addForce( (point - cParticle->pos)*str );	
	cParticle->update();
}



void Bubble2D::update()
{

	// CONNECTING SURFACE'S PARTICLE ==================================
	// ----------------------------------------------------------------
	// FIRST PARTICLE
		// Connecting with the second particle
		p[0]->addForce( (p[1]->pos - p[0]->pos)*str);

		// Connecting with the last particle
		p[0]->addForce( (p[np-1]->pos - p[0]->pos)*str);


	// MIDDLE PARTICLES
		for(int i=1; i< np-1; i++)
		{
			// Connecting with the right particle
			p[i]->addForce( (p[i+1]->pos - p[i]->pos)*str);

			// Connecting with the left particle
			p[i]->addForce( (p[i-1]->pos - p[i]->pos)*str);
		}


	// LAST PARTICLE
		// Connecting last particle with the second last
		p[np-1]->addForce( (p[np-2]->pos - p[np-1]->pos)*str);

		// Connecting last particle with the first
		p[np-1]->addForce( (p[0]->pos - p[np-1]->pos)*str);
	// ================================================================




	// CONNECTING PARTICLES WITH THEIR FIXED POINTS ===================
	// ----------------------------------------------------------------
	for(int i=0; i< np; i++)
	{
		//ofVec2f dToFxP = 0.01*(fxP[i] + cParticle->pos - p[i]->pos);

		ofVec2f dToFxP = 0.005*(fxP[i] + cParticle->pos - p[i]->pos);
		p[i]->addForce(dToFxP);
	}
	// ================================================================



/*
	// CONNECTING SURFACE'S PARTICLE WITH CENTRAL PARTICLE ============
	// ----------------------------------------------------------------
	// MIDDLE PARTICLES
	for(int i=0; i< np; i++)
	{
		ofVec2f distanceToCenter = p[i]->pos - cParticle->pos;

		// attract if particle is getting far from the center
		if( distanceToCenter.length() > r)
		{
			distanceToCenter.scale(distanceToCenter.length() - r );	
			distanceToCenter *= -cStr;

			p[i]->addForce(distanceToCenter);
		}

		// repels if particle is getting close to the center
		else if( distanceToCenter.length() < r)
		{
			distanceToCenter.scale( r - distanceToCenter.length() );	
			distanceToCenter *= cStr;

			p[i]->addForce(distanceToCenter);
		}
	}
*/
	// ================================================================



	// Updating particle's physic
	for(int i=0; i<np; i++)
	{
		p[i]->update();
	}
	
}
	



void Bubble2D::drawP()
{
	cParticle->draw();

	for(int i=0; i<np; i++)
	{
		p[i]->draw();

		ofSetColor(0,200,200);
		ofDrawCircle(fxP[i].x + cParticle->pos.x, fxP[i].y + cParticle->pos.y, 3);
	}
}

void Bubble2D::drawS()
{
    bShader.begin();
        bShader.setUniform1f("p", cP);
        bShader.setUniform1f("c", cParticle->pos.y);

        bShader.setUniform4fv("c1", &c1[0]);
        bShader.setUniform4fv("c2", &c2[0]);
    
        ofBeginShape();
            for(int i=0; i<np; i++)
            {
                ofCurveVertex(p[i]->pos.x, p[i]->pos.y);
            }
            ofCurveVertex(p[0]->pos.x, p[0]->pos.y);
            ofCurveVertex(p[1]->pos.x, p[1]->pos.y);
            ofCurveVertex(p[2]->pos.x, p[2]->pos.y);
        ofEndShape();
    bShader.end();    
}



void Bubble2D::drawL()
{
    contour.clear();

	for(int i=0; i<np; i++)
	{
		contour.curveTo(p[i]->pos);
	}
	contour.curveTo(p[0]->pos);
	contour.curveTo(p[1]->pos);
	contour.curveTo(p[2]->pos);

    contour.draw();

/*
	// There are two ways of setting the weight 
	// of a line in OF: ofSetLineWidth(2) and glLineWidth(20);
	// Both of the ways has a weight maximum limit.
	// Here's what I did to workaround it:
	ofVec2f v = line.getPointAtLength(0);

	ofSetColor(c);
	int index=0;
	while( index < line.getPerimeter() )
	{
		v = line.getPointAtLength(index);
		ofDrawEllipse(v.x, v.y, 2*weight, 2*weight);
		index+=1;
	}
*/
	//v = line.getPointAtLength(line.getPerimeter());
	//ofDrawEllipse(v.x, v.y, 2*weight, 2*weight);
}


vector <ofVec2f> Bubble2D::pointsInside(int y) // get the points inside the shape
{
    // detecting the boders
    vector <ofVec2f> border;
    vector <int> borderIndex;
        
	int index=0;
	while( index < contour.getPerimeter() )
	{
		if( (int)contour.getPointAtLength(index).y == y)
        {
            border.push_back( ofVec2f(contour.getPointAtLength(index).x,        
                    contour.getPointAtLength(index).y) );
            
            borderIndex.push_back(index);
        }
        index++;
	}
    
    //return border;
    
    
    
    vector <ofVec2f> inside;
    
    //inside.push_back(border[0]);
    
    // go through each
    for(int i=0; i<border.size()-1; i++)
    {
        ofVec2f rightPoint = contour.getPointAtLength(borderIndex[i]-1);
            
        // check if the right point is inside or outside the bubble
        
        // if we are at the bottom of the bubble
        if(rightPoint.y > cParticle->pos.y)
        {
            // if the right point is inside the bubble
            if( border[i].x+1 < rightPoint.y  ) 
            {
                for(int m=i; m<borderIndex[i+1]; m++)
                {
                    inside.push_back(border[m]);
                }
            }            
            // if next point is outside the bubble
        //    else
        //    {
        //        inside.push_back(border[i]);
        //    }
        }
    }
    
    
    return inside;
}










