#include <vector>
#include "CacheSet.h"

class Cache{

private:
    int cache_size;
    int block_size;
    int associativity;
    int num_sets;
    int offset_bits;
    int index_bits;
    int tag_bits;

    int hits;
    int misses;
    
    int time;

    std::vector<CacheSet> cacheSets;

public:
    Cache(int blockSize, int assoc);

    void access_cache(unsigned int address);

    void print_summary_statistics();
    
    void save_results(int run_number, int pattern, int stride);


private:
    void calculate_cache_parameters();

    unsigned int get_index(unsigned int address);

    unsigned int get_tag(unsigned int address);

    unsigned int get_offset(unsigned int address);

};