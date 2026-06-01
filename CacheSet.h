#include <vector>
#include "CacheBlock.h"

class CacheSet{
    private:
        std::vector<CacheBlock> blocks_in_set;

    public:
        CacheSet(unsigned int associativity);
        
        int map_block(unsigned int tag, unsigned int time);

    private:
        int find_block(unsigned int tag);

        int empty_block_available();

        int find_lru();
};