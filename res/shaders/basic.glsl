
#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
// layout(location = 1) in vec2 texCoord;

// out vec2 v_TexCoord;

uniform float r;

mat4 projection = mat4(
    1.0,  0.0,  0.0,  0.0,
    0.0,  1.0,  0.0,  0.0,
    0.0,  0.0,  1.0,  0.0,
    0.0,  0.0,  1.0,  0.0
);

mat4 center = mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.5,
    0.0, 0.0, 0.0, 1.0
);

mat4 r_mat = mat4(
     cos(r), 0.0, sin(r), 0.0,
        0.0, 1.0,    0.0, 0.0,
    -sin(r), 0.0, cos(r), 0.0,
        0.0, 0.0,    0.0, 1.0
);

mat4 m_center = mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, -1.5,
    0.0, 0.0, 0.0, 1.0
);

void main()
{
    gl_Position = position * m_center * r_mat * center * projection;
    // v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

// in vec2 v_TexCoord;

// uniform sampler2D u_Tex;

void main()
{
//    vec4 texColor = texture(u_Tex, v_TexCoord);
   color = vec4(1.0, 1.0, 1.0, 1.0);
};
