#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texCoord;

out vec3 theColor;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    theColor = aColor;
    v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;
in vec3 theColor;
in vec2 v_TexCoord;

uniform float offsetx;
uniform float offsety;
uniform float offsetz;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = mix(texture(u_Texture, v_TexCoord), texture(u_Texture, v_TexCoord), 0.75);
    FragColor = vec4(texColor.x + theColor.x + offsetx, texColor.y + theColor.y + offsety, 
                        texColor.z + theColor.z + offsetz, 1.0f);
};