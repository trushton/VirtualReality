#version 330

layout (points) in;
layout(triangle_strip) out;
layout(max_vertices = 4) out;

uniform mat4 gVP;
uniform vec3 gCameraPos;
uniform sampler2D gColorMap;


out vec3 Color;
out vec2 TexCoord;
out vec4 outPos;

void main() {
    vec3 Pos = gl_in[0].gl_Position.xyz;

    vec3 toCamera = normalize(gCameraPos - Pos);
    vec3 up = vec3(0.0,1.0,0.0);
    vec3 right = cross(toCamera, up);
    vec3 original = Pos;

    float green = abs(cos(original.y)) / 5.0;

    gl_Position = gVP * vec4(Pos, 1.0);
    TexCoord = vec2(0.0, 0.0);
    outPos = gl_Position;
    EmitVertex();

    green = abs(cos(original.y)) / 5.0;

    gl_Position = gVP * vec4(Pos, 1.0);
    TexCoord = vec2(0.0, 1.0);
    outPos = gl_Position;

    EmitVertex();

    gl_Position = gVP * vec4(Pos, 1.0);
    TexCoord = vec2(1.0, 0.0);
    outPos = gl_Position;

    EmitVertex();

    green = abs(cos(original.y))/5;

    gl_Position = gVP * vec4(Pos, 1.0);
    TexCoord = vec2(1.0, 1.0);
    outPos = gl_Position;

    EmitVertex();

    EndPrimitive();

}
