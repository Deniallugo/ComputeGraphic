#version 120
 
varying vec3 vertColour;
 
void main()
{
  gl_FragColor = vec4(vertColour,1.0);
}
