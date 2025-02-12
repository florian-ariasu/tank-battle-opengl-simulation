#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
// variabile puse de mine
uniform vec3 light_color;
uniform vec3 light_position2;
uniform int light_type;

uniform vec3 object_color;



// Output
layout(location = 0) out vec4 out_color;


vec3 point_light_contribution(vec3 light_pos, vec3 light_color) {
	
    vec3 N = normalize(world_normal);
	vec3 L = normalize(light_pos - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));

    float ambient_light = 0.25f;
    float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);
    float specular_light = 0.f;

    if (diffuse_light > 0) {
        specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
    }

    float light = 0.f;

    if (light_type == 0) {
        float dist = distance(light_pos, world_position);
	    float att_factor = 1.f / max(dist * dist, 1.f);
	    light = ambient_light + att_factor * (diffuse_light + specular_light);
    } else {
        light = ambient_light;

        float cut_off = 0.5235;
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(cut_off);
        if (spot_light > cos(cut_off)) {
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = linear_att * linear_att;
            light += light_att_factor * (diffuse_light + specular_light);
        }
    }

	return light_color * light * object_color;
}


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    float diffuse_light = 0;
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    // TODO(student): Write pixel out color
  //out_color = vec4(1);
    out_color = vec4(point_light_contribution(light_position, vec3(1, 1, 1) - light_color) + point_light_contribution(light_position2, light_color), 1.f);
}
