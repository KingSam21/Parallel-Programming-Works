// ============================================================
// This kernel should perform the operation:
//
//     C = A + B
//
// ============================================================
kernel void vector_add(global const float* A, global const float* B, global float* C) {
    
    int id = get_global_id(0);

    // TODO #1: Print global ID using printf
    // ---------------------------------------------------------
    // get_global_id(0) returns the index of this work item in
    // the global NDRange along the X dimension.
    //
    // printf() is supported in OpenCL 1.2+ on many GPUs/CPUs
    // (but not all - some embedded/OpenCL-1.1 devices may not
    // provide printf support).
    //
    // This will print once per work item and is useful for
    // debugging execution order or ensuring correct dispatch.
    // ---------------------------------------------------------

    printf("work item id = %d\n", id);                  // returns a unique id for each item.
    
    


    // ---------------------------------------------------------
    // TODO #2:
    // Print work-group info.
    // `get_local_size(0)` returns number of work-items
    // per group in dimension 0.
    //
    // Only print once using id == 0 to avoid huge output.
    // ---------------------------------------------------------
    
    if (id == 0) {                  // perform this part only once. i.e. for work item 0
        printf("work group size %d\n", get_local_size(0));
    }

    int loc_id = get_local_id(0);

    // print mapping between global and local IDs.
    printf("global id = %d, local id = %d\n", id, loc_id);


    // ---------------------------------------------------------
    // TODO #3:
    // Print total work-items (once) +
    // Print work-group ID for each work-item
    // ---------------------------------------------------------

    if (id == 0) {
        printf("\n total work-items = %d\n\n", global_size);
    }

    printf("global id = %d, group id = %d\n", id, group_id);
    
    


    // Perform vector addition
    C[id] = A[id] + B[id];
}
