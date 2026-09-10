#version 430 core

layout(local_size_x = 10) in;

layout(std430, binding = 2) buffer particles
{
    float Particle_Array[];
};

layout(std430, binding = 4) buffer particles
{
    float next_Particle_Array[];
};

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

void main(){

    uint i = gl_LocalInvocationID.x;

    next_Particle_Array[i * 2] = 0.5;

    next_Particle_Array[i * 2 + 1] = 0.5;

    //next_Particle_Array[i * 2] =
    //    Particle_Array[i * 2] - 0.001;
    //
    //next_Particle_Array[i * 2 + 1] =
    //    Particle_Array[i * 2 + 1] - 0.001;

    //for(int o = 0; o < 10; o++){
    //    if(o != i && o != 9){
    //        float r_dist = sqrt(dx*dx + dy*dy);
    //        float dx = Particle_Array[o*2] - Particle_Array[i*2];
    //        float dy = Particle_Array[o*2+1] - Particle_Array[i*2+1];
    //        
    //        float inv_tan = atan(dx, dy);
    //
    //        next_Particle_Array[i*2] += cos(inv_tan) * Force(1, r_dist);
    //        next_Particle_Array[i*2+1] += sin(inv_tan) * Force(1, r_dist);
    //    }
    //}
}