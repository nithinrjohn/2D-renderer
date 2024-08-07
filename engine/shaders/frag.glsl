#version 330 core

uniform vec4 color;
uniform sampler2D tex;

in vec2 UV;

out vec4 frag_color;

void main()
{
    vec4 texColor = texture(tex, UV);
    if(texColor.a == 0.0)
        discard;
    frag_color = texColor * color;
}