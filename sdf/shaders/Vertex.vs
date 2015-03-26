#version 120
attribute vec3 inPosition;
attribute vec3 inColour;
varying vec3 vertColour;
 
void main()
{
 gl_Position = vec4(inPosition, 1.0);
 vertColour = inColour;
}