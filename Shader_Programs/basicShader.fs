#version 120

// Varying variables are kinda like uniforms but only accessible in shaders
varying vec2 texCoord0;
varying vec3 normal0;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0)
				// Lambershia lighting
				//					V where lighting direction goes
				 * clamp(dot(-vec3(0.0,0.0,1.0), normal0), 0.0, 1.0);
}
