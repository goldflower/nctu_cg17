#version 430
layout(binding = 0) uniform sampler2D samplerTexture;
in vec2 newTexture;
// the norm of the fragment we are looking
in vec3 normal;
in vec3 gourund;

// we look at this position
in vec4 _position;

// output color
out vec4 outColor;
// light position
uniform vec3 light;
// view matrix, not model view matrix
uniform mat4 view;

// ambient coefficient
uniform vec4 ambient_coe;
// diffuse coefficient
uniform vec4 diffuse_coe;
// specular coefficient
uniform vec4 specular_coe;
// power of specular
uniform float shininess;

// 0: phong, 1: flat, 2: gourund
uniform int shader_selector;

void main()
{
	vec3 _light = (view * vec4(light, 1)).xyz;
	float diffuseIntensity = max(dot(normalize(_light - _position.xyz), normalize(normal)), 0);
	vec3 diffuse = diffuseIntensity * diffuse_coe.xyz;
	vec4 texture_color = texture2D(samplerTexture, newTexture);
	vec3 diffuse_texture = texture_color.xyz * diffuse;

	vec3 reflect_dir = normalize(reflect(_position.xyz-_light, normal));
	float specularIntensity = pow(max(dot(-normalize(_position.xyz), reflect_dir), 0.0), shininess);
	vec4 specular = vec4(specularIntensity * specular_coe.xyz, 1);
	if (shader_selector == 0)
		outColor = vec4(diffuse_texture + outColor.xyz + vec3(specularIntensity) + 2*ambient_coe.xyz, 1);
	else if (shader_selector == 1)
		outColor = vec4(diffuse_texture + outColor.xyz + ambient_coe.xyz, 1);
	else if (shader_selector == 2)
		outColor = vec4(gourund + diffuse_texture, 1);
}