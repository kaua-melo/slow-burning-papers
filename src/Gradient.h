
#ifndef _GRADIENT // if this class hasn't been defined, the program can define it
#define _GRADIENT // by using this if statement you prevent the class to be called more than once which would confuse the compiler

#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework

// only vertical gradient 
class Gradient
{
	public:
    
        // image that is gonna contain the gradient
        ofImage img;
    
        int nD; // number of divisions
    
        int width;
        int height;
    
        vector <int> changingPoints;
        vector <ofColor> color;
        vector <float>   percentage; // percentage of the first color on the gradient

    
        int alpha;

		Gradient(int w, int h, vector <int> change, vector <ofColor> c, vector <float>   p, int a);
    
        void setColor(vector <ofColor> c);
        void setChangingPoints(vector <int> change);
		void update(); 
		void draw(int x, int y);

	private:
};
#endif
