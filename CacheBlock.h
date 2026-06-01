class CacheBlock{

    public:
        bool valid;
        unsigned int tag;
        unsigned int lastUsed; 

        CacheBlock();

        bool check_match(unsigned int otherTag);

        void load_block(unsigned int newTag, unsigned int use_time);

        void accessed(unsigned int use_time);
};