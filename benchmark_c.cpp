#include <algorithm>
#include <cstdlib>

//Modified version of http://stackoverflow.com/questions/4708105/performance-of-qsort-vs-stdsort

const size_t LARGE_SIZE = 100000;

struct rnd {
    int operator()() {
        return rand() % LARGE_SIZE;
    }
};

int comp( const void* a, const void* b ) {
    return *( int* )a < *( int* )b ? -1 : *( int* )a > *(int *) b;
}

int main() {
    int ary[LARGE_SIZE];
    // generate random data
    std::generate( ary, ary + LARGE_SIZE, rnd() );
    std::qsort( ary, LARGE_SIZE, sizeof( int ), comp );
}
