#version 430 core

layout(local_size_x = 64) in;

layout(std430, binding = 3) buffer particles
{
    float Particle_Array[];
};

uniform int NumberOfParticles;

float Force(float a, float r) {
    const float beta = 0.3;

    float nr = r/100;

    if (nr < beta) {
        return nr / beta - 1;
    } else if (beta < nr && nr < 1.0) {
        return a * (1.0 - abs(2.0 * nr - 1.0 - beta) / (1.0 - beta));
    } else {
        return 0.0;
    }
}

void main(){
    uint i = gl_LocalInvocationID.x;

    float forceX = 0;
    float forceY = 0;
    float Scaling_Factor = 500;

    for(int o = 0; o < NumberOfParticles; o++){
        if(o == i) continue;

        float x = (Particle_Array[o*2] - Particle_Array[i*2]) * Scaling_Factor;
        float y = (Particle_Array[o*2 + 1] - Particle_Array[i*2 + 1]) * Scaling_Factor;
        

        float r = sqrt(x*x + y*y);
        //float forces = Force(-1.0, r);
        float forces = 0.001;

        forceX += forces * x / r;
        forceY += forces * y / r;
    }

    Particle_Array[i * 2] += forceX;
    Particle_Array[i * 2 + 1] += forceY;

}