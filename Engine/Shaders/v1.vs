uniform float Scale;
varying vec2 vTexCoord;

void main(void)
{
	vec4 a = gl_Vertex;
	
	vTexCoord = vec2(gl_MultiTexCoord0);
	
	a.x = a.x * Scale;
	a.y = a.y * Scale;

	gl_Position = gl_ModelViewProjectionMatrix * a;
}