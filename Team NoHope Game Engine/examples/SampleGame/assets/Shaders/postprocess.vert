attribute vec2 position;
attribute vec2 texCoords;

varying vec2 finalTexCoords;

void main()
{
  gl_Position = vec4(position, 1.0, 1.0);
  finalTexCoords = texCoords;
}