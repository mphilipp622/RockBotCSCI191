uniform float Scale;

void main(void)
{
vec4 a = gl_Vertex;


a.x = a.x * Scale; // Scale x
a.y = a.y * Scale; // Scale y


gl_Position = gl_ModelViewProjectionMatrix * a; // same as 
}


