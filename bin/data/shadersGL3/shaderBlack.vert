#version 150

uniform mat4 modelViewProjectionMatrix;
/* A uniform is a value passed to each shader from your program that sets some additional values that you use in each stage of your shading. Uniform variables act as constants, at least for the duration of your OF applications draw() method. Your OF application feeds these variables to the graphics pipeline so that they're accessible in both stages of shading. Any shader can access any uniform variable as long as it declares the variable, like we do in both shaders in our example. Note though that these variables are read-only in the shaders. If you want to update the value of a uniform, you can do it in your OF application by calling:

shader.setUniform1f("myUniform", 1.f);

That's how you set a uniform like this:

uniform float myUniform;
*/

in vec4 position;
/*position - This is also a value passed in from OF but you'll notice that it has an "in" at the front of it, which means that the value passed in is different for each vertex because the each vertex has a slightly different position. These are called attributes and they're all set up when the ofMesh is created and each value is set when they're being drawn.*/


void main()
{
	gl_Position = modelViewProjectionMatrix * position;
    
    
    /*gl_Position - This is what comes out of the vertex shader. It's a variable with a fixed role: pass the position of the vertex to the triangle assembly. "Triangle assembly" is when the GPU connects vertices to form triangles. It does this by taking the vertices in the order specified by the element array and grouping them into sets of three that then either create triangle strips or triangle fans.*/
}
