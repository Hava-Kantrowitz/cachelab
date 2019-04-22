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

struct cacheLine {
  int tag;//the tag, the high-order bits of memory
  int validBit;//0 or 1, whether or not the data is in the cache
  int recentInst;//the most recent instruction using this item of the cache line
};//values needed to simulate cache

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

/*Get the index*/
int getIndex(int address, int index_bits, int offset_bits);

/*Get the tag*/
int getTag(int address, int tag_bits, int offset_bits, int index_bits);

/*Set the valid bit*/
int setValidBit(struct cacheLine* base_index, int index);

/*Perform cache lookup*/
int cacheLookup(int address, struct cacheLine* cache, int index_bits, int block_bits, int address_size, int numLines, int instrucNum);

/*Sets up the cache*/
struct cacheLine* setCache(int numSets, int linesPerSet, int blockSize);

/*Determines if eviction*/
int evictionOrMiss(struct cacheLine* line, int currentTag, int tagNext, int numLines, int instructNum);

/* this gets the number of lines in the file */
int numLinesFile(FILE* fp);

/* gets the char from a line of the file */
char getChar(char* line);

/* gets the address from a line of the file */
unsigned long getAddress(FILE* fp, int lineNumber);

/* gets the number of bits occupied by address */
int addressLength(unsigned long decAddr);

/* prints the help menu */
void printHelp(void);

/* this gets a specified line from the file */
char* readLine(FILE* fp, int lineNumber);

#endif /* CACHELAB_TOOLS_H */
