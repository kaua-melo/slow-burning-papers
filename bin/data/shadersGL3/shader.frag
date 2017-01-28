#version 150

out vec4 outputColor;

// the factor passed by the OF app.


// where each color is located on the screen
uniform vec3 pos;

// colors of the gradient
uniform vec4 c1;
uniform vec4 c2;
uniform vec4 c3;

// the percentage of the first color
uniform vec2 cPercentage;

layout(origin_upper_left) in vec4 gl_FragCoord;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

    //float windowWidth  = 1280.0;
    //float windowHeight = 720.0;  
    float windowWidth  = 1920.0;
    float windowHeight = 1080.0;  

	float f = gl_FragCoord.y / windowHeight;

	float r,g,b;
	



	float percentage;
    float newPercentage;
    
    
	// First section
	if(f<=pos.y)
	{
		// section limits
		float yi = pos.x;
		float yf = pos.y;

		percentage = (f - yi)/(yf-yi); // goes from 0 to 1
        
        if(percentage <= cPercentage.x)
        {
            newPercentage = percentage/(2*cPercentage.x);
        }
        else
        {
            newPercentage = 0.5 + (percentage-cPercentage.x)/(2*(1-cPercentage.x));
        }
        
		r = c1.x + newPercentage*(c2.x - c1.x);
		g = c1.y + newPercentage*(c2.y - c1.y);
		b = c1.z + newPercentage*(c2.z - c1.z);
	}
    
	// Second section
	else if(f>pos.y && f<=pos.z)
	{
		// section limits
		float yi = pos.y;
		float yf = pos.z;

		percentage = (f - yi)/(yf-yi);

        if(percentage <= cPercentage.y)
        {
            newPercentage = percentage/(2*cPercentage.y);
        }
        else
        {
            newPercentage = 0.5 + (percentage-cPercentage.y)/(2*(1-cPercentage.y));
        }
        
		r = c2.x + newPercentage*(c3.x - c2.x);
		g = c2.y + newPercentage*(c3.y - c2.y);
		b = c2.z + newPercentage*(c3.z - c2.z);
	}
    
	

	float a = 1.0;
    
	outputColor = vec4(r, g, b, a);

    
    /*Anything marked "out" goes the next stage in the shading pipeline. For the fragment shader that next stage is to put a pixel into the framebuffer, so you need to one and only one "out" from a fragment shader. A vertex shader can have multiple "out" variables that are just passed to the fragment shader, while a fragment shader is just figuring out what color should be sent on for each pixel based on all the values passed from the vertex shader.*/
}
