/**
 * By Victoria Bowen and Hava Kantrowitz
 * vabowen and hskantrowitz
 */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <math.h>
#include "cachelab.h"


int main(int argc, char **argv)
{
	
	struct cache myCache;
	struct cacheInfo info;
	//bzero(&exampleParameter, sizeof(exampleParameter));  // read the report for this function's purpose
	long long numSets;
	long long blockSize;	
	FILE *fp;
	char instruction;
	memoryAddress address;
	int size;
	char *trace_file;
	char c;
	/* this part takes in argument. More on how do I do this-> read report file */
    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1)
	{
        switch(c)
		{
        case 's':
            info.index_bits = atoi(optarg);
            break;
        case 'E':
            info.associativity = atoi(optarg);
            break;
        case 'b':
            info.block_bits = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'h':
            exit(0);
        default:
            exit(1);
        }
    }
   /* end of take in arguments from command line */ 

 	numSets = pow(2.0, info.index_bits);   // get Number of set by 2^s
	blockSize = pow(2.0, info.block_bits);  //  get sizeOfBlock by 2^b
	info.num_hits = 0;
	info.num_misses = 0;
	info.num_evicts = 0;
	myCache = setCache(numSets, info.associativity, blockSize);

	/* this part read file. More on how do I do this-> read report file */
	fp  = fopen(trace_file, "r");
	if (fp != NULL) {
		while (fscanf(fp, " %c %llx,%d", &instruction, &address, &size) == 3) {
			switch(instruction) {
				case 'I':
					break;
				case 'L':
					info = cacheLookup(myCache, info, address);
					break;
				case 'S':
				        info = cacheLookup(myCache, info, address);
					break;
				case 'M':
				        info = cacheLookup(myCache, info, address);
					info = cacheLookup(myCache, info, address);
					break;
				default:
					break;
			}
		}
	}
	/* end of read file */
	
    printSummary(info.num_hits, info.num_misses, info.num_evicts);
	fclose(fp);
    return 0;
}

struct cache setCache(long long numSets, int numLines, long long blockSize){
  struct cache myCache;
  struct set cacheSet;
  struct lineInfo cacheLine;
  
  myCache.sets = (struct set*) malloc(sizeof(struct set) * numSets);
  for (int set_index = 0; set_index < numSets; set_index++){ 
	        // this loop loops through every line in every set and put the default value 0 inside every slot. (because we contain nothing in the cache)
		
		cacheSet.lines =  (struct lineInfo *) malloc(sizeof(struct lineInfo) * numLines);
		myCache.sets[set_index] = cacheSet;

		for (int line_index = 0; line_index < numLines; line_index++){ 
			cacheLine.lastUsed = 0;
			cacheLine.validBit = 0;
			cacheLine.tag = 0; 
			cacheSet.lines[line_index] = cacheLine;	
		}
		
	} 

	return myCache;

}

int emptyLine(struct set mySet, struct cacheInfo info) {
	// check is whether the line that is matched is empty or not
	
  int emptyLine = -1;//the location of the empty line, initialized to -1 for no lines available

	int numLines = info.associativity;
	struct lineInfo line;

	for (int i = 0; i < numLines; i++) {
		line = mySet.lines[i];
		if (line.validBit == 0) {    // one line is available
			emptyLine = i;
			return emptyLine;
		}
	}
	return emptyLine;     // no line is available
}

int leastRecentlyUsed(struct set mySet, struct cacheInfo info, int *linesUsed) {
	// this function detects the line that can be evicted ( the least recently used line)



	int numLines = info.associativity;
	int maxFreqUsage = mySet.lines[0].lastUsed;     //store usage frequency
	int minFreqUsage = mySet.lines[0].lastUsed;	 // store usage frequency
	int minFreqUsage_index = 0;


	//very basic loop, compare each line with max & min to decide
	for (int line_index = 1; line_index < numLines; line_index++) {
		if (minFreqUsage > mySet.lines[line_index].lastUsed) {
			minFreqUsage_index = line_index;	
			minFreqUsage = mySet.lines[line_index].lastUsed;
		}

		if (maxFreqUsage < mySet.lines[line_index].lastUsed) {
			maxFreqUsage = mySet.lines[line_index].lastUsed;
		}
	}

	linesUsed[0] = minFreqUsage;
	linesUsed[1] = maxFreqUsage;
	return minFreqUsage_index;
}

/* this is the most important operation*/
struct cacheInfo cacheLookup(struct cache myCache, struct cacheInfo info, memoryAddress address) {
		int fullCache = 1;     // assume the cache is full

		int numLines = info.associativity;
		int lastHit = info.num_hits;

		int tagSize = 64 - (info.index_bits + info.block_bits);    // take the valid tag out t = m-s-b
		memoryAddress inputTag = address >> (info.index_bits + info.block_bits);
		unsigned long long tempIndex = address << tagSize;
		unsigned long long setIndex = tempIndex >> (tagSize + info.block_bits);
		
  		struct set mySet = myCache.sets[setIndex];

		for (int lineIndex = 0; lineIndex < numLines; lineIndex++) 	{
				
			if (mySet.lines[lineIndex].validBit) {   // check the valid tag != 0
					
				if (mySet.lines[lineIndex].tag == inputTag) {
						//check for matching tag


					mySet.lines[lineIndex].lastUsed++;  // update for later use of eviction
					info.num_hits++;    // tag match -> raise hit
				}
				// If the valid tag is different from 0 and the input tag matches that line tag, then it is safe for us to raise the hit because we did cache hit


			} else if (!(mySet.lines[lineIndex].validBit) && (fullCache)) {
				// valid tag = 0, fullcache != 0
				
				fullCache = 0;	    // reset this to 0	because there is empty space left.
			}
			// 
		}	

		if (lastHit == info.num_hits) {   // if after the above loop nothing hit -> we miss
			info.num_misses++;    // raise miss
		} else {
			return info;
		}
		int *linesUsed = (int*) malloc(sizeof(int) * 2);
		int minFreqUsage_index = leastRecentlyUsed(mySet, info, linesUsed);	

		if (fullCache)     // if cache is full (checkFullCache!=0) do eviction
		{
			info.num_evicts++;
			mySet.lines[minFreqUsage_index].tag = inputTag;
			mySet.lines[minFreqUsage_index].lastUsed = linesUsed[1] + 1;
		
		}

		else        // else write to tge empty line
	        {
			int empty_index = emptyLine(mySet, info);
			mySet.lines[empty_index].tag = inputTag;
			mySet.lines[empty_index].validBit = 1;
			mySet.lines[empty_index].lastUsed = linesUsed[1] + 1;
		}						

		return info;
}


