#version 150

out vec4 outputColor;


uniform vec4 c1;
uniform vec4 c2;
uniform float p;
uniform float c; // center of the bubble



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
    float newF;
	float r,g,b;
    
    float topLimit    = (c-350)/windowHeight;
    float bottomLimit = (c+350)/windowHeight;
    float cP          = c/windowHeight;
    
    
    
    // above the top of the bubble
    if(f<=topLimit)
    {
        newF = 0;
    }
    // between the top and the center
    else if(f>topLimit && f<cP)
    {
        newF = (f-topLimit)/(2*(cP-topLimit));
    }
    // between the center and the bottom
    else if(f>cP && f<bottomLimit)
    {
        newF = 0.5 + (f-cP)/(2*(bottomLimit-cP));
    }
    // under the bottom
    else if(f>bottomLimit)
    {
        newF = 1;
    }

    r = c1.x + newF*(c2.x - c1.x);
	g = c1.y + newF*(c2.y - c1.y);
	b = c1.z + newF*(c2.z - c1.z);
	
    
    
/*    
    float a;
    if(c>=windowHeight-300.0)
    {
        a = (bottomLimit-f)/(bottomLimit-topLimit);
    }
    else
    {
	   a = 1.0;
    }
*/

    float a = 1.0;
	outputColor = vec4(r, g, b, a);

    
    /*Anything marked "out" goes the next stage in the shading pipeline. For the fragment shader that next stage is to put a pixel into the framebuffer, so you need to one and only one "out" from a fragment shader. A vertex shader can have multiple "out" variables that are just passed to the fragment shader, while a fragment shader is just figuring out what color should be sent on for each pixel based on all the values passed from the vertex shader.*/
}
