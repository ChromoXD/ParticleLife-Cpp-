#version 430 core


in vec2 fragTexCoord;

layout(std430, binding = 3) buffer particles
{
    float Particle_Array[];
};

out vec4 FragColor;

float radius = 0.01;

void main(){
    FragColor = vec4(0.059, 0.055, 0.071, 1.0);

    for(int i = 0; i < 10; i++){
        float x = fragTexCoord.x - Particle_Array[i*2];
        float y = fragTexCoord.y - Particle_Array[i*2+1];

        if(x*x + y*y < radius*radius){
            FragColor = vec4(0.369, 0.659, 0.902, 1.0);
            break;
        }
    }

}