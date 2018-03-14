#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
} fs_in;

uniform vec3 light_direction;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;

uniform vec3 view_position;

uniform mat4 model;

void main() {
    vec3 normal = fs_in.Normal;
    vec3 view_direction = normalize(view_position - fs_in.FragPos);

    vec3 light_direction = normalize(-light_direction);
    float diffuse_factor = max(dot(normal, light_direction), 0.0f);

    vec3 color = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = color * light_ambient;
    vec3 diffuse = color * light_diffuse * diffuse_factor;

    vec3 result = ambient + diffuse;

    FragColor = vec4(result, 1.0f);
}