#version 100

precision mediump float;

varying vec2 finalTexCoords;

uniform sampler2D vSampler;
uniform float time;

void main()
{
	vec4 sum = vec4(0);
	//vec2 finalTexCoords = vec2(finalTexCoords[0]);
	int j;
	int i;

	for( i = -4 ; i < 4; i++)
	{
		for (j = -3; j < 3; j++)
		{
			sum += texture2D(vSampler, finalTexCoords + vec2(j, i)*0.004) * 0.25;
		}
	}

	//gl_FragColor = sum*sum*0.012 + texture2D(vSampler, finalTexCoords);

	
	if (texture2D(vSampler, finalTexCoords).r < 0.3)
	{
		gl_FragColor = sum*sum*0.012 + texture2D(vSampler, finalTexCoords);
	}
	else
	{
		if (texture2D(vSampler, finalTexCoords).r < 0.5)
		{
			gl_FragColor = sum*sum*0.009 + texture2D(vSampler, finalTexCoords);
		}
		else
		{
			gl_FragColor = sum*sum*0.0075 + texture2D(vSampler, finalTexCoords);
		}
	}
}