//precision mediump float;

varying vec2 finalTexCoords;

uniform sampler2D vSampler;

void main() {
	gl_FragColor = texture2D(vSampler, finalTexCoords);
}