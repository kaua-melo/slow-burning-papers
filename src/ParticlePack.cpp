
#include "ParticlePack.h"



ParticlePack::ParticlePack(int _np, int _r, float f, ofColor _c)
{
	// number of particles
	np = _np;

	// radius of the particles
	//r = _r;

	// friction
	friction = f;

	// color
	c = _c;


	// Creating particles ---------------------------------------------------------------------------
	// Creating particles
	for(int i =0; i<np; i++)
	{        
        ofVec2f pos;
        pos.set(ofRandom(0, ofGetWindowWidth()),      
                ofRandom(0,ofGetWindowHeight()) );

														//Particle(int x, int y, int _r, float f)
		shared_ptr<Particle> tempParticle = shared_ptr<Particle>(new Particle(pos.x, pos.y, ofRandom(1,5), friction));

		p.push_back(tempParticle);
        
        p[i]->setFixedPoint(pos);
        p[i]->setColor(c);
		fxP.push_back(pos);
	}
	// ----------------------------------------------------------------------------------------------
}





void ParticlePack::update()
{
	// Updating particle's physic
	for(int i=0; i<np; i++)
	{
		p[i]->update2();
	}
}
	



void ParticlePack::draw()
{
	for(int i=0; i<np; i++)
	{
		p[i]->draw();
	}
}




void ParticlePack::setFixedPointsRandomly(ofVec2f p1, ofVec2f p2)
{
    for(int i=0; i<p.size(); i++)
    {
        ofVec2f randomP;
        randomP.set(ofRandom(p1.x, p2.x), ofRandom(p1.y, p2.y));
        
        p[i]->setFixedPoint(randomP);
    }
}




void ParticlePack::setFixedPointsToPolygon(vector <ofVec2f> vertices)
{
	// calculating the perimeter of the polygon ----------------------
	float perimeter=0;

	for(unsigned int i=0; i<vertices.size()-1; i++)
	{
		perimeter+= (vertices[i+1]-vertices[i]).length();
	}
	perimeter+= (vertices[0]-vertices[vertices.size()-1]).length();
	// ---------------------------------------------------------------

	
	// number of particles in each side ---------------------------------------
		float density = perimeter/np; // density of particles along the polygon's edges
		vector <int> n; // number of particles in each edge of the polygon
	
		for(unsigned int i=0; i<vertices.size()-1; i++)
		{
			n.push_back( (vertices[i+1]-vertices[i]).length()/density );
		}
		// last edge
		n.push_back( (vertices[0]-vertices[vertices.size()-1]).length()/density );
	// ------------------------------------------------------------------------



	// IF THERE ARE MISSING PARTICLES ==========================================
	// -------------------------------------------------------------------------
		// Counting the number of particles that was already distributed ---
		int nPartSoFar = 0;
		for(unsigned int i=0; i<n.size(); i++)
		{
			nPartSoFar+=n[i];
		}
		// -----------------------------------------------------------------

		// in case there are some missing particles
		if(nPartSoFar < np)
		{
			// number of missing particles
			int missingPart = np-nPartSoFar;

			for(int i=0; i<missingPart; i++)
			{
				n[i]++;
			}
		}

	/*			
			for(int i=0; i<n.size(); i++)
			{
				std::cout<<"n["<<i<<"]:  "<<n[i]<<endl;
			}
	*/
	// =========================================================================



	// POSITIONING THE PARTICLES AROUND THE POLYGON'S SHAPE ====================
		int index =0;
		vector <ofVec2f> points;

		// go through each edge
		for(int i=0; i<vertices.size()-1; i++)
		{
			// get points between the vertices passed
			// n[i]+1 -> because there is one point at the beginning of 
			//  the line from the last edge that should be counted.
			points = divideLine(vertices[i], vertices[i+1], n[i]+1);

			for(int m=0; m<points.size(); m++)
			{
				fxP[index].set(points[m]);
				index++;
			}
		}


		// LAST EDGE --------------------------------------------------------------------------
		// get points between the the vertices passed
		// n[i]+1 -> because there is one point at the beginning of 
		//  the line from the last edge that should be counted.
		points = divideLine(vertices[vertices.size()-1], vertices[0], n[vertices.size()-1]+1);
		for(int m=0; m<points.size(); m++)
		{
			fxP[index].set(points[m]);
			index++;
		}

    
        // Setting the particle's fixed points
        for(int i=0; i<p.size(); i++)
        {
            p[i]->setFixedPoint(fxP[i]);
        }

		// CENTERING THE PARTICLES
		//for(int i=0; i<fxP.size(); i++)
		//{
		//	fxP[i]+=center;
		//}
	// =========================================================================
}





// Get a vector with the points between two points on the screen.
// n = number of points on the line
vector <ofVec2f> ParticlePack::divideLine(ofVec2f p1, ofVec2f p2, int n)
{
	// 'n' should be at least two!!!
	
	vector <ofVec2f> points;

	// round p1 and p2 to two decimal place
	p1.x = ((int)(100*p1.x))/100;
	p1.y = ((int)(100*p1.y))/100;
	p2.x = ((int)(100*p2.x))/100;
	p2.y = ((int)(100*p2.y))/100;


    // The line between the two points is a function!
	if(p1.x!=p2.x)
	{
		// y = a*x + b
		float a = (p2.y-p1.y)/(p2.x-p1.x);
		float b = p1.y - a*p1.x;

        // Steps from point1 to point2
        float dx = (p2.x-p1.x)/(n-1);

		// coordinates of the points
		float x,y;

        // Find out the coordinates of the points between point1 to point2
		// skip the first point since it's gonna be last point point of the last edge
        for(int i=1; i<n; i++)
        {
            x = p1.x + i*dx;
            y = a*x + b;
            
            points.push_back( ofVec2f(x,y) );
        }
	}
   // p1.x==p2.x  The line between the two points isn't a function!
    else 
    {
        // Steps from point1 to point2
        float dy = (p2.y-p1.y)/(n-1);
        
		// coordinates of the points
        float x,y;

        // Find out the coordinates of the points between point1 to point2
		// skip the first point since it's gonna be last point point of the last edge
        for(int i =1; i<n; i++)
        {
            y = p1.y + i*dy;

            points.push_back( ofVec2f(p1.x,y) );
        }   
    }
        
    return points;
}





