#include <iostream>
#include <fstream>
#include "Cache.h"
#include <cstdlib>

int main() {

    unsigned int block_size_number;
    unsigned int block_size;
    unsigned int assoc_number;
    unsigned int associativity;
    unsigned int access_pattern;
    int continue_run;

    std::ofstream out_file("cache_results.csv");
    out_file << "Run,Block Size,Associativity,Access Pattern,Stride,Hits,Misses,Hit Rate" << std::endl;

    std::cout << std::endl;
    std::cout << "Cache Simulator" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "You have up to 3 runs in this session to test different cache configurations and access patterns." << std::endl;
    std::cout << "After each run, you will be presented with a summary of the results." << std::endl;
    std::cout << "At the end of the session, you will also be presented with a graph of the results from all runs." << std::endl;
for (int run = 1; run < 4; run++){   
    std::cout << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Run " << run << std::endl;
    std::cout << std::endl;
    std::cout << "Choose block size: " << std::endl;
    std::cout << "[1] 16B " << std::endl;
    std::cout << "[2] 32B " << std::endl;
    std::cout << "[3] 64B " << std::endl;
    std::cout << "[4] 128B " << std::endl;

    std::cout << "Enter block size option number: ";
    std::cin >> block_size_number;
    if (block_size_number != 1 && block_size_number != 2 && block_size_number != 3 && block_size_number != 4) {
        std::cout << "Invalid block size option. Exiting." << std::endl;
        return 1;
    }
    else{
        std::cout << std::endl;
        if (block_size_number == 1){
            block_size = 16;
        }
        else if (block_size_number == 2){
            block_size = 32;
        }
        else if (block_size_number == 3){
            block_size = 64;
        }
        else if (block_size_number == 4){
            block_size = 128;
        }
    }

    std::cout << "Choose associativity: " << std::endl;
    std::cout << "[1] Direct-mapped" << std::endl;
    std::cout << "[2] 2-way set associative" << std::endl;
    std::cout << "[3] 4-way set associative" << std::endl;
    std::cout << "[4] 8-way set associative" << std::endl;
    std::cout << "[5] Fully associative" << std::endl;
    std::cout << "Enter associativity option number: ";
    std::cin >> assoc_number;
    std::cout << std::endl;

    if (assoc_number == 1){
        associativity = 1;
    }
    else if (assoc_number == 2){
        associativity = 2;
    }
    else if (assoc_number == 3){
        associativity = 4;
    }
    else if (assoc_number == 4){
        associativity = 8;
    }
    else if (assoc_number == 5){
        associativity = (32*1024) / block_size; 
    }
    else {
        std::cout << "Invalid associativity option. Exiting." << std::endl;
        return 1;
    }

    std::cout << "Choose memory access pattern: " << std::endl;
    std::cout << "[1] Sequential access" << std::endl;
    std::cout << "[2] Strided access" << std::endl;
    std::cout << "[3] Random access" << std::endl;
    std::cout << "Enter access pattern option number: ";
    std::cin >> access_pattern;

    if (access_pattern != 1 && access_pattern != 2 && access_pattern != 3) {
        std::cout << "Invalid access pattern option. Exiting." << std::endl;
        return 1;
    }
    else{
        std::cout << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    Cache cache(block_size, associativity);

    //print cache configuration
    std::cout << "Cache configuration: " << std::endl;
    std::cout << "Address length: 32 bits --> 4GB main memory" << std::endl;
    std::cout << "Cache size: 32 KB" << std::endl;

    std::cout << "Block size: " << block_size << " bytes" << std::endl;

    if (associativity == 1)
        std::cout << "Associativity: Direct-mapped" << std::endl;
    else if (associativity == 2)
        std::cout << "Associativity: 2-way set associative" << std::endl;
    else if (associativity == 4)
        std::cout << "Associativity: 4-way set associative" << std::endl;
    else if (associativity == 8)
        std::cout << "Associativity: 8-way set associative" << std::endl;
    else
        std::cout << "Associativity: Fully associative " << std::endl;
    
    if (access_pattern == 1)
        std::cout << "Access pattern: Sequential access" << std::endl;
    else if (access_pattern == 2)
        std::cout << "Access pattern: Strided access" << std::endl;
    else
        std::cout << "Access pattern: Random access" << std::endl;

    std::cout << "LRU replacement policy" << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << std::endl;

    //simulate memory accesses based on accesss pattern 
    unsigned int address = 0;
    unsigned int stride = 0;


    if (access_pattern == 1) {
        for (unsigned int i = 0; i < 10000; i++){
            cache.access_cache(address);
            address += 1;
        }
    }
    else if (access_pattern == 2){
        std::cout << "Enter stride value (bytes) from 2 to 1024: ";
        std::cin >> stride;
        if (stride < 2 || stride > 1024){
            std::cout << "Invalid stride value. Exiting." << std::endl;
            return 1;
        }
        else{
            std::cout << std::endl;
        }

        for (int i = 0; i < 10000; i++){
            cache.access_cache(address);
            address += stride;
        }
    }
    else if (access_pattern == 3){
        for (int i = 0; i < 10000; i++){
            address = rand() % (32 * 1024);
            cache.access_cache(address);
        }
    }

    //print summary statistics
    cache.print_summary_statistics();

    if (access_pattern == 2){
        cache.save_results(run, access_pattern, stride);
    }
    else{
        cache.save_results(run, access_pattern, 0);
    }

    if (run < 3){
        std::cout << std::endl;
        std::cout << "Enter 1 to continue to the next run. Enter 0 to end this session. ";
        std::cin >> continue_run;
        std::cout << std::endl;
        if (continue_run != 1 && continue_run != 0){
            std::cout << "Invalid option. Ending session." << std::endl;
            break;
        }
        else if (continue_run == 0){
            break;
        }
    }
}
std::cout << "End of session. Thank you for using the cache simulator!" << std::endl;
system("python make_chart.py");
std::cout << "Graph of results from this session has been generated and saved as Results.xlsx" << std::endl;

    return 0;
}