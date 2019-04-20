#include "cachelab.h"

/**
 * Sets up variables and calls the simulation
 */
int main()
{
    //Parsing done by Vicky

	struct cacheLine{
	  int tag;//the tag, the high-order bits of memory
	  int validBit;//0 or 1, whether or not the data is in the cache
	} cacheLine;//values needed to simulate cache

	int hit_count = 0;//number of hits, initialized to 0
	int miss_count = 0;//number of misses, initialized to 0
	int eviction_count = 0;//number of evictions, initialized to 0
	int output = 0;//output of the cache lookup

	cacheLine* cache = setCache(s, E, b);

	//assume function that grabs 1 line of file and determines if it is usable
	//the output of that function is the address

	for (int i = 0; i < linesInFile; i++){
	  
	   output = cacheLookup(address, cache);
	   if (output == 0){//it was a miss, no eviction needed
	     miss_count++;
	   }
	   else if (output == 1){//it was a hit
	     hit_count++;
	   }
	   else if (output == 2){//it was a miss with an eviction
	     eviction_count++;
	     miss_count++;
	   }
	}

	//print verbose code 

	printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

/**
 * Gets the index
 */
int getIndex(int address){
  int index = address & 0100;//bit manipulation to get index--NOT CORRECT YET
  return index;
}

/**
 * Gets the tag
 */
int getTag(int address){
  int tag = address & 0110;//bit manipulation to get tag--NOT CORRECT YET
  return tag;
}

/**
 * Sets the valid bit
 */
int setValidBit(cacheLine* base_index, cacheLine* index, int updatedVal){
  cacheLine* location = base_index + index + sizeof(base_index.tag);//set the location to change as the base index plus the given tag plus however many bits are in the tag to get to valid bit
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
  if (tag == currentTag && validBit == 1){
    answer = 1;
  }
  else{
    answer = eviction(line, currentTag, tag);
  }
  return answer;
}

/**
 * Creates the simulated cache
 */
int setCache(int numSets, int linesPerSet, int blockSize){

   cacheLine* cacheSize = malloc(sizeof(cacheLine)*numSets);//creates array, cacheSize is pointer to 1st element in array
   for (int i = 0; i < numSets; i++){
     cacheLine* index = (cacheLine*) (linesPerSet*i);//casts the line currently on to a cacheLine pointer
     setValidBit(cacheSize, index, 0);//initializes the valid bit of each line to 0
   }  
     
}

/**
 * determines if eviction is needed, performs eviction from cache
 */
int eviction(cacheLine* line, int currentTag, int tagNext){
  int eviction = 0;
  if (currentTag != 0){//really want to say, if there's something in the tag, increment eviction count
    eviction = 2;
    line.tag = tagNext;//set the current tag into the cache
    free(currentTag);//free the memory the old tag was using, deleting it
    line.validBit = 1;//set the valid bit to 1
  }
  //otherwise just populate the space
  line.tag = tagNext;
  line.validBit = 1;
  return eviction;
}
