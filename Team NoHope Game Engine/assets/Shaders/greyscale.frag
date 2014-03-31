precision mediump float;

varying vec2 finalTexCoords;

uniform sampler2D vSampler;
uniform float time;

void main() {
	vec4 pixel = texture2D(vSampler, finalTexCoords);
	//float average = (pixel.x + pixel.y + pixel.z) / 3.0;
	float sine = sin(time); 
	gl_FragColor = vec4(sine + pixel.x*2.0, sine + pixel.y, sine + pixel.z*2.0, 1.0);
}