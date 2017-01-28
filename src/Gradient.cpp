
#include "Gradient.h"


Gradient::Gradient(int w, int h, vector <int> change, vector <ofColor> c, vector <float>   p, int a)
{
    // nD = number of dividions
    // I feel that dividing the area and calculating only that small piece of colors and repeat them might decrease the computational effort
    nD = 10;
    
    
	width  = w/nD;
    
    height = h;
    
    changingPoints = change;
    
    color = c;
    
    percentage = p;
    
    alpha = a;
    
    img.allocate(width, height, OF_IMAGE_COLOR);    
}


void Gradient::setChangingPoints(vector <int> change)
{
    changingPoints = change;
}


void Gradient::setColor(vector <ofColor> c)
{
    color = c;
}


void Gradient::update()
{
    
    // go through each division
    for(int i=0; i<changingPoints.size()-1; i++)
    {    
    
    /*
        float yi = changingPoints[i];
        float yf = changingPoints[i+1];       

        ofColor c1(color[i]);
        ofColor c2(color[i+1]);

        
        
        int nSubDivisions = 5-i;
        float ySubDiv = (yf-yi)/nSubDivisions;
            
        
        
        // go through each sub division
        for(int m=0; m<nSubDivisions; m++)
        {
            
            // go through the whole subdivision
            for(float y= yi+ m*ySubDiv; y < yi+(m+1)*ySubDiv; y++)
            {
                for(float x=0; x<img.getWidth(); x++)
                {
                    // y = x/a      a = maximum y value
                    float f = m*ySubDiv/(yf-yi);
                    
                    ofColor c((int)c1.r + f*((int)c2.r-(int)c1.r), 
                              (int)c1.g + f*((int)c2.g-(int)c1.g), 
                              (int)c1.b + f*((int)c2.b-(int)c1.b));      
                    
                    img.setColor(x,y,c); 
                    
                    //std::cout<<f<<endl;
                }
            }       
            
            
        }
        */
    
        
        
        
        
        // #############################################################################################
        // first part
        float yi = changingPoints[i];
        float yf = changingPoints[i] + (changingPoints[i+1]-changingPoints[i])*percentage[i];    
        
        ofColor c1(color[i]);
        ofColor _c2(color[i+1].r, color[i+1].g, color[i+1].b);
        ofColor c2((float)c1.r + 0.5*((float)_c2.r-c1.r), 
                        (float)c1.g + 0.5*((float)_c2.g-c1.g), 
                        (float)c1.b + 0.5*((float)_c2.b-c1.b)); 
        
        
        for(float y=yi; y<yf; y++)
        {
            for(float x=0; x<img.getWidth(); x++)
            {
                // y = x/a      a = maximum y value
                float f = (y-yi)/(yf-yi);
                                
                //float f = (float)pow((y-yi),4)/pow((yf-yi),4);

                ofColor c((float)c1.r + f*((float)c2.r-c1.r), 
                          (float)c1.g + f*((float)c2.g-c1.g), 
                          (float)c1.b + f*((float)c2.b-c1.b));       
                
                img.setColor(x,y,c);
            }
        }  
        
        
        
        
        // second part
        yi = changingPoints[i] + (changingPoints[i+1]-changingPoints[i])*percentage[i];
        yf = changingPoints[i+1];       
        
        c1 = c2;
        c2 =_c2;
        
        
        for(float y=yi; y<yf; y++)
        {
            for(float x=0; x<img.getWidth(); x++)
            {
                // y = x/a      a = maximum y value
                float f = (y-yi)/(yf-yi);
                
                //float f = (float)pow((y-yi),4)/pow((yf-yi),4);

                ofColor c((float)c1.r + f*((float)c2.r-c1.r), 
                          (float)c1.g + f*((float)c2.g-c1.g), 
                          (float)c1.b + f*((float)c2.b-c1.b));       
                                
                img.setColor(x,y,c);
            }
        }  
        // #############################################################################################

        
    }
    
        
        
    img.update();
}



void Gradient::draw(int x, int y)
{
    ofSetColor(255,255,255,alpha);
    for(int i=0; i<nD; i++)
    {
        
        img.draw(x + i*img.getWidth(),y);
    }
}

