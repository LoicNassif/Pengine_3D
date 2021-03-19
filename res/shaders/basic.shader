#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 aNormal;

out vec3 theColor;
out vec2 v_TexCoord;
out vec3 f_Normal;
out vec3 frag_pos;

uniform mat4 u_MVP;
uniform vec3 rColor;
uniform mat4 model;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    frag_pos = vec3(model * vec4(position, 1.0));
    theColor = rColor;
    v_TexCoord = texCoord;
    f_Normal = mat3(transpose(inverse(model))) * aNormal;
};


#shader fragment
#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform SpotLight spotLight;

uniform Material material;

uniform DirLight dirLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

layout(location = 0) out vec4 FragColor;
in vec3 theColor;
in vec2 v_TexCoord;
in vec3 f_Normal;
in vec3 frag_pos;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;

uniform bool flashlightFlag;
uniform bool pointLightFlag;
uniform bool directionalLightFlag;
uniform bool lightSource;

uniform vec3 f_viewPos;

void main() 
{
    vec3 mixedColor = vec3(1.0, 1.0, 1.0);
    if (!lightSource) {
        vec4 texColor = mix(texture(u_Texture, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.75);
        mixedColor = vec3(texColor.x + theColor.x, texColor.y + theColor.y, texColor.z + theColor.z);
    }

    // properties
    vec3 norm = normalize(f_Normal);
    vec3 viewDir = normalize(f_viewPos - frag_pos);
    vec3 result = vec3(0.0, 0.0, 0.0);

    // Directional Lighting
    if (directionalLightFlag)
        result += CalcDirLight(dirLight, norm, viewDir);

    // Point Lights
    if (pointLightFlag) {
        for (int i = 0; i < NR_POINT_LIGHTS; i++) {
            result += CalcPointLight(pointLights[i], norm, frag_pos, viewDir);
        }
    }

    // Spot Light
    if (flashlightFlag) 
        result += CalcSpotLight(spotLight, norm, frag_pos, viewDir);

    if (lightSource)
        result = vec3(1.0, 1.0, 1.0);

    FragColor = vec4(result * mixedColor, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) 
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, v_TexCoord));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic
        * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, v_TexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - frag_pos);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, v_TexCoord));

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;
    return (ambient + diffuse + specular);
}
