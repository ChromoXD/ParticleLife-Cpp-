#version 430 core

layout(local_size_x = 16, local_size_y = 16) in;

layout(set = 0, binding = 0) uniform Config{
    mat4 transform;
    int matrixCount;
} opData;

layout(set = 0, binding = 1) readonly buffer  InputBuffer{
    mat4 matrices[];
} sourceData;

layout(set = 0, binding = 2) buffer  OutputBuffer{
    mat4 matrices[];
} outputData;

void main(){
    ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);
    imageStore(img, pixel, vec4(1.0, 0.0, 0.0, 1.0));
}

float Force(float particle1, float particle2, float a, float r) {
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