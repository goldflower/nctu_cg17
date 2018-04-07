#version 430
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 vertNormal;
layout(location = 3) in vec3 faceNormal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec2 newTexture;
out vec3 normal;
out vec4 _position;
out vec3 gourund;
// light position
uniform vec3 light;

// ambient coefficient
uniform vec4 ambient_coe;
// specular coefficient
uniform vec4 specular_coe;
// power of specular
uniform float shininess;

// 0: phong, 1: flat, 2: gourund
uniform int shader_selector;
void main()
{
	if (shader_selector == 0 || shader_selector == 1)
	{
		// phong shading
		if (shader_selector == 0)
			normal = (transpose(inverse(view*model)) * vec4(vertNormal, 1)).xyz;
		// flat shading
		else if (shader_selector == 1)
			normal = (transpose(inverse(view*model)) * vec4(faceNormal, 1)).xyz;
		gl_Position = projection * view * model * vec4(position, 1.0f);
		_position = view * model * vec4(position, 1.0f);
		newTexture = textureCoords;
	}
	else if (shader_selector == 2)
	{
		normal = (transpose(inverse(view*model)) * vec4(vertNormal, 1)).xyz;
		gl_Position = projection * view * model * vec4(position, 1.0f);
		_position = view * model * vec4(position, 1.0f);
		newTexture = textureCoords;
		vec3 _light = (view * vec4(light, 1)).xyz;
		vec3 reflect_dir = normalize(reflect(_position.xyz-_light, normal));
		float specularIntensity = pow(max(dot(-normalize(_position.xyz), reflect_dir), 0.0), shininess);
		vec4 specular = vec4(specularIntensity * specular_coe.xyz, 1);
		gourund = specular.xyz + ambient_coe.xyz;
	}
}