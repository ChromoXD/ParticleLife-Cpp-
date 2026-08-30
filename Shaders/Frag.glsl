#version 430 core

in vec4 FragCord;

out vec4 FragColor;

uniform float time;

float radius = 4;

void main(){
    vec4 Pixel_color;
    vec2 grid = mod(gl_FragCoord.xy, 25.0);

        Pixel_color = vec4(0.133, 0.157, 0.192, 1.0);
    


    FragColor = Pixel_color;
}