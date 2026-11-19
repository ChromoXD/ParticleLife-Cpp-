#version 430 core

layout(local_size_x = 64) in;

layout(std430, binding = 3) buffer particlesA
{
    float Particle_Array[];
};

layout(std430, binding = 2) buffer particlesB
{
    float Particle_Array_two[];
};

uniform int NumberOfParticles;

float Force(float a, float r) {
    const float beta = 0.08;

    float nr = 3*r/100;

    if (nr < beta) {
        return nr / beta - 1;
    } else if (beta < nr && nr < 1.0) {
        return a * (1.0 - abs(2.0 * nr - 1.0 - beta) / (1.0 - beta));
    } else {
        return 0.0;
    }
}

void main(){
    uint i = gl_GlobalInvocationID.x;
    uint count = uint(NumberOfParticles) / 2u;   

    float forceX = 0.0;
    float forceY = 0.0;
    float Scaling_Factor = 500.0;

    

    for(uint o = 0u; o < count; o++){
        if(o == i) continue;
        
        float x = 0.0;
        float y = 0.0;
        float forces = 0.0;

        if(i < NumberOfParticles/2){
            x = (Particle_Array[o*2] - Particle_Array[i*2]) * Scaling_Factor;
            y = (Particle_Array[o*2 + 1] - Particle_Array[i*2 + 1]) * Scaling_Factor;
        }else{
            x = (Particle_Array_two[o*2 - NumberOfParticles/2] - Particle_Array_two[(i - NumberOfParticles/2)*2]) * Scaling_Factor;
            y = (Particle_Array_two[(o*2 - NumberOfParticles/2) + 1] - Particle_Array_two[(i - NumberOfParticles/2)*2 + 1]) * Scaling_Factor;
        }

        float r = sqrt(x*x + y*y);
        if (r < 1e-6) continue;

        if(i < NumberOfParticles/2){
            forces = Force(1.0, r)/Scaling_Factor;
        }else{
            forces = Force(-1.0, r)/Scaling_Factor;
        }

        forceX += forces * x / r;
        forceY += forces * y / r;
    }

    
    if(i < NumberOfParticles/2){
        Particle_Array[i * 2] += forceX;
        Particle_Array[i * 2 + 1] += forceY;
    }
    else{
        Particle_Array_two[(i - NumberOfParticles/2) * 2] += forceX;
        Particle_Array_two[(i - NumberOfParticles/2) * 2 + 1] += forceY;
    }
}