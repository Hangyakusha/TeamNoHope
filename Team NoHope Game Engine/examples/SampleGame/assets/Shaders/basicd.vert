attribute vec3 position;
attribute vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

varying vec3 color;
varying vec2 finalTexCoords;

void main()
{
  gl_Position = projection * model * vec4(position, 1.0);
  color = position;
  finalTexCoords = texCoords;
}