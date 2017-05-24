
varying vec2 Texcoord;
uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform float osg_SimulationTime;

void main(void)
{
	vec4 color = texture2D(sampler0, Texcoord);
	color.a = 0.5;
	Texcoord.x -= osg_SimulationTime * 0.5;
	vec4 color1 = texture2D(sampler1, Texcoord);
	gl_FragColor = mix(color, color1, 0.5);
}
