#include "Cache.h"
#include <cmath>
#include <iostream>
#include <fstream>

Cache::Cache(int blockSize, int assoc){
    block_size = blockSize;
    associativity = assoc;
    cache_size = 32 * 1024; 
    hits = 0;
    misses = 0;
    time = 0;

    num_sets = cache_size / (block_size * associativity);

    for (int i = 0; i < num_sets; i++){
        cacheSets.push_back(CacheSet(associativity));
    }

    calculate_cache_parameters();
}

void Cache::access_cache(unsigned int address){
    time = time + 1;
    unsigned int index = get_index(address);
    unsigned int tag = get_tag(address);
    unsigned int offset = get_offset(address);

    if (cacheSets[index].map_block(tag, time) == 1){
        hits = hits + 1;
    }
    else{
        misses = misses + 1;
    }
}

void Cache::print_summary_statistics(){
    std::cout << "Summary Statistics:" << std::endl;
    std::cout << "Total Accesses: " << hits + misses << std::endl;
    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Misses: " << misses << std::endl;
    std::cout << "Hit Rate: " << (double)hits / (hits + misses) * 100 << "%" << std::endl;
}

void Cache::calculate_cache_parameters(){
    offset_bits = log2(block_size);
    index_bits = log2(num_sets);
    tag_bits = 32 - index_bits - offset_bits;
}

unsigned int Cache::get_index(unsigned int address){
    if (num_sets == 1){
        return 0;
    }
    return (address >> offset_bits) & ((1 << index_bits) - 1);
}

unsigned int Cache::get_tag(unsigned int address){
    return (address >> (offset_bits + index_bits));
}

unsigned int Cache::get_offset(unsigned int address){
    return (address & ((1 << offset_bits) - 1));
}

void Cache::save_results(int run_number, int pattern, int stride){
    std::ofstream out_file("cache_results.csv", std::ios::app);
    
    double hit_rate = (double)hits / (hits + misses) * 100;

    out_file << run_number << "," << block_size << "," << associativity << "," << pattern << "," << stride << "," << hits << "," << misses << "," << hit_rate << std::endl;
    out_file.close(); 
}