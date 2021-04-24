#version 450 core

in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D hdrBuffer;
uniform bool hdr;   
uniform float exposure;



void main()
{    
/*
    const float gamma = 1.0f;
    vec3 hdrColor = texture(hdrBuffer, vTexCoord).rgb;
    if(hdr)
    {
        // vec3 result = hdrColor / (hdrColor + vec3(1.0));
	   vec3 vHSV = vec3(0.0, 0.0,0.0);

    
        // Экспозиция
        vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
		
        // Заодно проведем гамма-коррекцию      
        result = pow(result, vec3(1.0 / gamma));

        vec4 textureColor = texture2D(hdrBuffer, vTexCoord);
        //FragColor = vec4(fragRGB+result, textureColor.w);

        FragColor = vec4(result, 1.0);
    }
    else
    {
        vec3 result = pow(hdrColor, vec3(1.0 / gamma));
        FragColor = vec4(result, 1.0);
    }
*/
    FragColor = texture(hdrBuffer, vTexCoord);
}