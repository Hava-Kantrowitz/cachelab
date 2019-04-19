#include "cachelab.h"

/**
 * Sets up variables and calls the simulation
 */
int main()
{
    //get file
	//parse file
	//make struct
	//tag, index, offset
	//create the cache
	//loop to look through the cache
	//for each level, determine if hit
	//if hit, increment hit count
	//if not hit, increment miss count
	//must keep track of LRU -- counter or method

	struct cacheLine{
		int validBit;//0 or 1, whether or not the data is in the cache
		int tag;//the tag, the high-order bits of memory
	};//values needed to simulate cache

	int hit_count = 0;//number of hits, initialized to 0
	int miss_count = 0;//number of misses, initialized to 0
	int eviction_count = 0;//number of evictions, initialized to 0

	//int index;//middle bits of address, which set it'll be in


	printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

/**
 * Creates the simulated cache
 */
int setCache(int cache){

	return 1;
}

/**
 * Determines if hit, increments needed counters
 */
int isHit(int validBitCache, int givenTag, int tag){
  int hit_count = 0;
  int miss_count = 0;
	if (validBitCache == 1 && tag == givenTag){
		hit_count++;
		return hit_count;
	}
	else{
	  miss_count++;
	  return miss_count;
	}
}

/**
 * performs eviction from cache
 */
int eviction(){
  return 1;
}

/**
 *
 */
int populateCache(){
  return 1;
}




