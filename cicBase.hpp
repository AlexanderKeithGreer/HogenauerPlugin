#ifndef CICBASE_H_INCLUDED
#define CICBASE_H_INCLUDED

class CICBase {
    public:
        virtual void initCIC(uint64_t r, uint64_t d, uint64_t s);
        virtual void clearMemory();
        void i64InOutSet(int64_t* input, int64_t* output);
        virtual void runFilter(uint64_t steps) = 0;

    protected:
        uint64_t rCIC;
        uint64_t dCIC;
        uint64_t sCIC;

        // Pointers to various CIC heap references.
        int64_t* i64Memory;
        int64_t* i64Input;
        int64_t* i64Output;
};

#endif
