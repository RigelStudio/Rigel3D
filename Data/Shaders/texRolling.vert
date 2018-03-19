varying vec2 Texcoord;

void main(void)
{
//gl_Position = ftransform();
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	Texcoord = gl_MultiTexCoord0.xy;
}
