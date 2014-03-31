precision mediump float;

varying vec2 finalTexCoords;

uniform sampler2D vSampler;
uniform float time;

void main() {
	vec2 displace = vec2(finalTexCoords.x, finalTexCoords.y + sin(time * 2.0 + (gl_FragCoord.x / 100.0)) / 8.0);
	gl_FragColor = texture2D(vSampler, displace);
}