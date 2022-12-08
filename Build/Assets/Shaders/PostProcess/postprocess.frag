#version 430 core
  
in vec2 texcoord; 
  
out vec4 fcolor; 
  
 uniform float offset;
 uniform sampler2D textureMap; 

const float thickness = 0; 
  
 const float screen_height = 600.0; 
void main() 
{ 
	vec3 color = texture(textureMap, texcoord).rgb;
    
    vec2 p = vec2(floor(gl_FragCoord.x), floor(gl_FragCoord.y));
    
    fcolor = vec4(color, 1);
} 
