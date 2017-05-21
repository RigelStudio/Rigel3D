
varying vec2 Texcoord;
uniform sampler2D sampler0;
uniform float osg_SimulationTime;

void main(void)
{
	Texcoord.x -= osg_SimulationTime * 0.5;
	vec4 color = texture2D(sampler0, Texcoord);
	gl_FragColor = vec4(color.rgba);
}
