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

	int index;//middle bits of address, which set it'll be in
	setCache();

	for (int i = 0; i < linesInFile; i++){
	  grabLine(fileLine);
	  int tag = fileLine & 0110;
	  int validBit = fileLine & 0110;
	  isHit(validBit, tag, givenTag);
	}

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
 * performs eviction from cache
 */
int eviction(int itemsInList){
  int eviction_count = 0;
  //figure out which one is lru
  //kick it out of cache
  //populate it into cache
  if (numBlocks == 1){//if it is a direct map, evict what is in the spot and put new item in
    head_pointer* = item_pointer*;
    free(head_pointer);
    eviction_count++;
    isHit(validBitCache, givenTag, tag);
  }
  if (itemsInList == numBlocks){//if the number of items in list is equal to number of lines in cache block
    head_pointer* = second_pointer*;//set the pointer of the head equal to the second pointer
    free(head_pointer);//free the memory for the head, removing it from cache
    //add the new node somehow
    eviction_count++;//increment the eviction
    isHit(validBitCache, givenTag, tag);
  }
  else{
    //add the new node
  }
  return eviction_count;
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
	  eviction();
	  return miss_count;
	}
}

/*
 * Gets the line in the cache we are looking at
 */
int grabLine(int index){
  return 1;
}




