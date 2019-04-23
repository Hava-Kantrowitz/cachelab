/* 
 * cachelab.h - Prototypes for Cache Lab helper functions
 */

#ifndef CACHELAB_TOOLS_H
#define CACHELAB_TOOLS_H

#define MAX_TRANS_FUNCS 100
#define MISS 0
#define HIT 1
#define EVICT 2
#include <stdio.h>

typedef struct trans_func{
  void (*func_ptr)(int M,int N,int[N][M],int[M][N]);
  char* description;
  char correct;
  unsigned int num_hits;
  unsigned int num_misses;
  unsigned int num_evictions;
} trans_func_t;

typedef unsigned long long int memoryAddress;

struct cacheInfo{
  int index_bits;
  int block_bits;
  int associativity;
  int num_sets;
  int block_size;
  int num_hits;
  int num_misses;
  int num_evicts;
};

struct lineInfo{
  int lastUsed;
  int validBit;
  memoryAddress tag;
  char *block;
};

struct set{
  struct lineInfo *lines;
};

struct cache{
  struct set *sets;
};

/* 
 * printSummary - This function provides a standard way for your cache
 * simulator * to display its final hit and miss statistics
 */ 
void printSummary(int hits,  /* number of  hits */
				  int misses, /* number of misses */
				  int evictions); /* number of evictions */

/* Fill the matrix with data */
void initMatrix(int M, int N, int A[N][M], int B[M][N]);

/* The baseline trans function that produces correct results. */
void correctTrans(int M, int N, int A[N][M], int B[M][N]);

/* Add the given function to the function list */
void registerTransFunction(
    void (*trans)(int M,int N,int[N][M],int[M][N]), char* desc);

/*Set the cache up*/
struct cache setCache(long long numSets, int numLines, long long blockSize);

/*Determines if and where there is empty space*/
int emptyLine(struct set mySet, struct cacheInfo info);

/*Determines which line was most recently used*/
int leastRecentlyUsed(struct set mySet, struct cacheInfo info, int *linesUsed);

/*Performs the search in the cache*/
struct cacheInfo cacheLookup(struct cache myCache, struct cacheInfo info, memoryAddress address);



#endif /* CACHELAB_TOOLS_H */
