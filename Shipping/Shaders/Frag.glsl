#version 430 core

// FF8894

in vec2 fragTexCoord;

layout(std430, binding = 3) buffer particlesA
{
    float Particle_Array[];
};

uniform int NumberOfParticles;

out vec4 FragColor;

float radius = 0.001;

void main(){
    FragColor = vec4(0.059, 0.055, 0.071, 1.0);

    for(int i = 0; i < NumberOfParticles; i++){
        float x = 0;
        float y = 0;

        x = fragTexCoord.x - Particle_Array[i*2];
        y = fragTexCoord.y - Particle_Array[i*2+1];

        if((x*x + y*y < radius*radius) && i < NumberOfParticles/2){
            FragColor = vec4(0.369, 0.659, 0.902, 1.0);
            break;
        }
        if((x*x + y*y < radius*radius) && i > NumberOfParticles/2){
            FragColor = vec4(1.0, 0.53, 0.58, 1.0);
            break;
        }
    }

}