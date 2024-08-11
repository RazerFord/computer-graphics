#version 460 core
in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, texCoords);
    if (fragColor.rgb == vec3(0.0, 0.0, 0.0))
    {
        discard;
    }
}
