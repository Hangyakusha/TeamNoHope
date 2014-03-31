attribute vec2 position;
attribute vec4 color;
attribute vec2 texCoords;

varying vec4 finalColor;
varying vec2 finalTexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  gl_Position = projection * model * vec4(position, 0, 1.0);
  finalColor = color;
  finalTexCoords = texCoords;
}