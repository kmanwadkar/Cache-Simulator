#include "CacheSet.h"

CacheSet::CacheSet(unsigned int associativity){
    for (int i = 0; i < associativity; i++){
        blocks_in_set.push_back(CacheBlock());
    }
}

int CacheSet::map_block(unsigned int tag, unsigned int time){
    int index = find_block(tag);
    if (index > -1){
        blocks_in_set[index].accessed(time); 
        return 1;
    }
    else if (index == -1){
        index = empty_block_available();        
        if (index > -1){
            blocks_in_set[index].load_block(tag, time);
            return 0;

        }
        else if (index == -1){
            index = find_lru();
            blocks_in_set[index].load_block(tag, time);
            return 0;   
        }
    }

    return 0;
}

int CacheSet::find_block(unsigned int tag){
    for (int i = 0; i < blocks_in_set.size(); i++){
        if (blocks_in_set[i].check_match(tag)){
           return i;
        }
    }

    return -1;
}

int CacheSet::empty_block_available(){
    for (int i = 0; i < blocks_in_set.size(); i++){
        if (blocks_in_set[i].valid == 0){
            return i;
        }
    }

    return -1;
}

int CacheSet::find_lru(){
    int lru_index = 0;
    for (int i = 0; i < blocks_in_set.size(); i++){
        if (blocks_in_set[i].lastUsed < blocks_in_set[lru_index].lastUsed){
            lru_index = i;
        }
    }
    return lru_index;
}
