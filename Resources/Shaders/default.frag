#version 330 core
out vec4 FragColor;

in vec3 color;
in vec4 fragPos;
in vec2 TexCoord;
uniform vec3 timedRGB;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform bool flip;

void main()
{
   if(!flip)
   {
      FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4) * vec4(fragPos.xyz + 0.1 + timedRGB + (color * 0.5) + 1.0, 1.0f);
   }
   if(flip)
   {
      FragColor = mix(texture(texture1, TexCoord), texture(texture3, TexCoord), 0.4) * vec4(fragPos.xyz + 0.1 + timedRGB + (color * 0.5) + 1.0, 1.0f);
   }
}
