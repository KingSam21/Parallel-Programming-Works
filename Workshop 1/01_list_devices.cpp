// ============================================================
// Task 1.1: Exploring OpenCL Devices
// ============================================================
// Complete this program to list all GPU devices on your system
// and display the platform and device information.

#define CL_HPP_TARGET_OPENCL_VERSION 300
#define CL_HPP_ENABLE_EXCEPTIONS
#include <CL/opencl.hpp>
#include <iostream>
#include <vector>

//=================================================================
// To Run the program, go to a git.bash terminal
// ENTER IN TERMINAL
// g++ "NameofFile".cpp -o "NewFileName".exe -I"C:\OpenCL-SDK\include" -lOpenCL
// THEN ENTER
// ./NewFileName.exe
//=================================================================


int main() {
    // ============================================================
    // TODO 1: Query all available OpenCL platforms, and
    // store your results in the "platforms" vector
    // Use: cl::Platform::get(&platforms)
    // ============================================================
    
    // A vector for storing all found platforms
    std::vector<cl::Platform> platforms;
    // Retrieves all available platforms 
    cl::Platform::get(&platforms);

    //=============================================================
    // TODO 2: Display message "No OpenCL platforms found!" 
    // when "platform" vector is empty and terminate you application
    //=============================================================
    
    // Checks if any OpenCl platforms exist in the retrieved list
    if (platforms.empty()) {
        std::cout << "No OpenCL platforms found\n";
        return 1;
    }

    // For loop iterating through all available platforms to print information about each one.
    // Loop through each available platform
    for (auto &platform : platforms) {
        // ============================================================
        // TODO 3: Print the name of each platform
        // Hint: Use platform.getInfo<CL_PLATFORM_NAME>()
        // ============================================================
        
        std::cout << "====================\n";
        std::cout << "Platform Name:        " << platform.getInfo<CL_PLATFORM_NAME>() << "\n";
        std::cout << "Platform Vendor:      " << platform.getInfo<CL_PLATFORM_VENDOR>() << "\n";
        std::cout << "Platform Version:     " << platform.getInfo<CL_PLATFORM_VERSION>() << "\n";
        std::cout << "Profile:              " << platform.getInfo<CL_PLATFORM_PROFILE>() << "\n";
        
        // ============================================================
        // TODO 4: Get all GPU devices for this platform and 
        // store in a vector called devices
        // Hint: Use platform.getDevices(CL_DEVICE_TYPE_GPU, &devices)
        // CL_DEVICE_TYPE_ALL, CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_GPU, etc.
        // ============================================================
        
        // Vector for storing all of the available OpenCL devices on the platform.
        std::vector<cl::Device> devices;

        // Retrieve all available devices for the platform.
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

        //=============================================================
        // TODO 5: Display message "No devices found for this platform." 
        // when "device" vector is empty and terminate you application
        //=============================================================
        
        // Check if there are no devices on the platform. If there are loop through the information of each one
        if (devices.empty()) {
            std::cout << "No devices found for this platform.\n";
        } else{
        

        // ============================================================
        // TODO 6: Loop through each GPU device and print its info
        // Required info:Device name, Max compute units, Max work-group size
        // and Max clock frequency
        // Hint: use device.getInfo<>() with:
        //   CL_DEVICE_NAME returns data type std::string
        //   CL_DEVICE_MAX_COMPUTE_UNITS returns a data type cl_uint
        //   CL_DEVICE_MAX_WORK_GROUP_SIZE  returns a data type size_t
        //   CL_DEVICE_MAX_CLOCK_FREQUENCY returns a data type cl_uint
        // ============================================================
            for (auto &device : devices) {
                std::cout << "====================\n";
                std::cout << "Device Name:          " << device.getInfo<CL_DEVICE_NAME>() << "\n";
                std::cout << "Device Vendor:        " << device.getInfo<CL_DEVICE_VENDOR>() << "\n";
                std::cout << "Max Compute Units:    " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "\n";
                std::cout << "Global Memory Size:   " << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() / (1024*1024) << "\n";
            }
        }
    }

    // ============================================================
    // TODO 7: For discussion with colleagues:
    // Compare the specs of different CPU and GPU devices.
    // Which device do you expect to perform better in parallel tasks?
    // ============================================================

     // The GPU should perform better in parallel tasks, as it has 46 compute units, in comparison to the CPUs 16.


    return 0;
}
