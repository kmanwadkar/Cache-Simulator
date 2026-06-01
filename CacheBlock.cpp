#include "CacheBlock.h"

CacheBlock::CacheBlock(){
    valid = false;
    tag = 0;
    lastUsed = 0;
}

bool CacheBlock::check_match(unsigned int otherTag){
    if ((tag == otherTag) && (valid == true)){
        return true;
    }
    else {
        return false;
    }
}

void CacheBlock::load_block(unsigned int newTag, unsigned int use_time){
    tag = newTag;
    lastUsed = use_time;
    valid = true;
}

void CacheBlock::accessed(unsigned int use_time){
    lastUsed = use_time;
}