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
        //gonna need some more structs my dude

	struct cacheLine{
	  int tag;//the tag, the high-order bits of memory
	  int validBit;//0 or 1, whether or not the data is in the cache
	} cacheLine;//values needed to simulate cache

	int hit_count = 0;//number of hits, initialized to 0
	int miss_count = 0;//number of misses, initialized to 0
	int eviction_count = 0;//number of evictions, initialized to 0

	cacheLine* cache = setCache(s, E, b);

	//assume function that grabs 1 line of file and determines if it is usable
	//the output of that function is the address
	int output = cacheLookup(address, cache);
	

	printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

/**
 * Gets the index
 */
int getIndex(int address){
  int index = address & 0100;//bit manipulation to get index
  return index;
}

/**
 * Gets the tag
 */
int getTag(int address){
  int tag = address & 0110;//bit manipulation to get tag
  return tag;
}

/**
 * Sets the valid bit
 */
int setValidBit(cacheLine* base_index, cacheLine* tag1, int updatedVal){
  cacheLine* location = base_index + tag1 + sizeof(base_index.tag);//set the location to change as the base index plus the given tag plus however many bits are in the tag to get to valid bit
  location.validBit = updatedVal;//set the valid bit at that location to the updated value
  return 1;
}

/**
 * Looks up the given address and determines if it exists in cache
 */
int cacheLookup(int address, cacheLine* cache){
  int answer = 0;
  int tag = getTag(address);
  int index = getIndex(address);
  cacheLine* line = cache + (cacheLine*)index;
  int currentTag = getTag(line);//this is getting passed into function that requires int input -- issue
  if (tag == currentTag){
    answer = 1;
  }
  else{
    answer = eviction(index, tag, cache);
  }
  return answer;
}

/**
 * Creates the simulated cache
 */
int setCache(int numSets, int linesPerSet, int blockSize){

   cacheLine* cacheSize = malloc(sizeof(cacheLine)*numSets);//creates array, cacheSize is pointer to 1st element in array
   for (int i = 0; i < numSets; i++){
     cacheLine* tag1 = 0;//need some way to update tag, how is tag initialized? 
     setValidBit(cacheSize, tag1, 0);//initializes the valid bit of each line to 0
   }  
     
}

/**
 * determines if eviction is needed, performs eviction from cache
 */
int eviction(int index, int tag, cacheLine* cache){
  cacheLine* line = 
}
