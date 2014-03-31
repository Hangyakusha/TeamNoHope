precision mediump float;

varying vec2 finalTexCoords;

uniform sampler2D vSampler;
uniform float time;

const float blurSizeH = 1.0 / 1280.0;
const float blurSizeV = 1.0 / 720.0;

void main() {
	vec4 sum = vec4(0.0);

	for (int x = -4; x <= 4; x++)
		for (int y = -4; y <= 4; y++)
			sum += texture2D(vSampler, vec2(finalTexCoords.x + float(x) * blurSizeH, finalTexCoords.y + float(y) * blurSizeV)) / 81.0;

	gl_FragColor = sum;
}