//precision mediump float;

varying vec3 color;
varying vec2 finalTexCoords;

uniform sampler2D vSampler;

void main() {
	gl_FragColor = texture2D(vSampler, finalTexCoords);
}