// speed.cl

/*------------------------------------------------------------------------
TODO # 1: compute_speed kernel
Goal: Compute speed = sqrt(vx^2 + vy^2 + vz^2) for each particle.
Input:
    - vel: float3 velocity vector per particle
    - numParticles: particle count
Output:
    - speed: float scalar per particle
Use bounds check id < numParticles to support padded NDRange.
------------------------------------------------------------------------*/

__kernel void compute_speed(__global float3* vel, __global float* speed, int numParticles)
{
    int id = get_global_id(0);
    if(id >= numParticles) return;

    float3 v = vel[id];
    float new_s = (float)(sqrt(v.x*v.x + v.y*v.y + v.z*v.z));
    speed[id] = new_s; 
}



