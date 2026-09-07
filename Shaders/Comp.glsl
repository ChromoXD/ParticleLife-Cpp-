#version 430 core

layout(local_size_x = 10) in;

layout(std430, binding = 3) buffer particles
{
    float Particle_Array[];
};

void main(){

    uint i = gl_LocalInvocationID.x;

    float x = Particle_Array[i*2];
    float y = Particle_Array[i*2+1];

    for(int o = 0; o < 10; o++){
        float dx = Particle_Array[(i+1)*2]-x;
        float dy = Particle_Array[(i+1)*2+1]-y;

        float r_dist = dx*dx + dy*dy;

        if(0 != i){
            Particle_Array[i*2] += Force(1.0, )
        }
    }

}

float Force(float a, float r) {
    const float beta = 0.3;

    float nr = r / 100.0;

    if (nr < beta) {
        return nr / beta - 1.0;
    } else if (beta < nr && nr < 1.0) {
        return a * (1.0 - abs(2.0 * nr - 1.0 - beta) / (1.0 - beta));
    } else {
        return 0.0;
    }
}