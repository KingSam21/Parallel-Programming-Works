// 05_compute_speed.cpp
#include "common.hpp"

int main()
{
    // Load velocity data from binary file
    std::string filename = "dataset/small_data.bin";

    std::vector<float> velocities;
    if (!loadSimulationData(filename, velocities)) {
        return -1;
    }

    // Each particle has 3 velocity components (vx, vy, vz)
    // So the number of particles is total floats divided by 3
    int numParticles = static_cast<int>(velocities.size() / 3);
    std::cout << "Loaded " << numParticles << " particles from " << filename << "\n";


    // Setup OpenCL context, device, and command queue with profiling enabled
     cl::Context context;
    cl::Device device;
    cl::CommandQueue queue;
    if (!setupOpenCL(context, device, queue, CL_DEVICE_TYPE_GPU)) {
        return -1;
    }

    // Create buffers for velocity input and speed output
    cl::Buffer d_vel(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * velocities.size(), velocities.data());
    cl::Buffer d_speed(context, CL_MEM_WRITE_ONLY, sizeof(cl_float3) * velocities.size());
    

    // Load and build the OpenCL kernel
    std::string kernelSource = loadKernelSource("kernels/speed.cl");
    if (kernelSource.empty()) return -1;

    cl::Program program(context, kernelSource);
    cl_int buildErr = program.build({device});
    if (buildErr != CL_SUCCESS) {
        std::cerr << "Build error: " << buildErr << "\n";
        std::cerr << "Build log:\n" << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << "\n";
        return -1;
    }

    // Set kernel arguments and execute.
    cl::Kernel kernel(program, "compute_speed");
    kernel.setArg(0, d_vel);
    kernel.setArg(1, d_speed);
    kernel.setArg(2, numParticles);


    // Test different local work sizes and profile execution time
    // Note: The "AUTO" case lets OpenCL decide the local size, which may not always be optimal.
    // Try sizes: 0 (AUTO), 32, 64, 128
    std::vector<size_t> localSizes = {
        0,   // 0 => AUTO
        32,
        64,
        128
    };

    for (size_t ls : localSizes) {
        std::string label;
        cl::NDRange global;
        cl::NDRange local;
        cl::Event event;

        if (ls == 0) {
            // AUTO: let OpenCL decide local size
            label = "AUTO";
            global = cl::NDRange(numParticles);
            local  = cl::NullRange;
        } else {
            label = "localSize=" + std::to_string(ls);
            size_t padded = roundUpToMultiple(numParticles, ls);
            global = cl::NDRange(padded);
            local  = cl::NDRange(ls);
        }

        queue.enqueueNDRangeKernel(kernel,
                                   cl::NullRange,
                                   global,
                                   local,
                                   nullptr,
                                   &event);
        queue.finish();

        cl_ulong start = event.getProfilingInfo<CL_PROFILING_COMMAND_START>();
        cl_ulong end   = event.getProfilingInfo<CL_PROFILING_COMMAND_END>();
        double elapsedMs = (end - start) * 1.0e-6;

        std::cout << "[Profiling] " << label
                  << " : " << elapsedMs << " ms\n";
    }
    


    // For each local size, enqueue the kernel and measure execution time using OpenCL events.
        // - If local size is 0, use AUTO (let OpenCL decide). Otherwise, set the specified local size and calculate the global size accordingly.
        // - Enqueue the kernel and wait for it to finish, then read profiling info from the event.
        // - Get profiling info (start and end time) from the event to calculate elapsed time in milliseconds.
        // - Print the profiling results for this local size configuration.
        

    // Read back the computed speeds to verify correctness (optional).
    
    

    // Print the first few computed speeds to verify correctness.
    std::vector<cl_float3> speed(numParticles);
    queue.enqueueReadBuffer(d_speed, CL_TRUE, 0, sizeof(cl_float3) * numParticles, speed.data());


    std::cout << "Sample speeds (first 5):\n";
    for (int i = 0; i < std::min(numParticles, 5); ++i) {
        std::cout << "  a[" << i << "] = (" << speed[i].x << ", " << speed[i].y << ", " << speed[i].z << ")\n";
    }
    
    

    return 0;
}
