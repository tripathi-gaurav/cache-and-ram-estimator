#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
	size_t size;
	struct node *next;
	struct node *prev;
	int isAllocated;
	int *blockMaxAddr;
	int *blockMinAddr;
	int arenaNumber;
	int dummy;
} MallocNode;

long long checkPhysicalMemoryHelper(long long lo, long long hi){
  long long mid = lo + (hi - lo) / 2;
  void *allocatedMemory;
  long long currentEstimatedRam = lo;

	while(currentEstimatedRam < hi){
		//printf("lo: %llu and hi: %llu\n", lo, hi);
		mid = currentEstimatedRam + (hi - currentEstimatedRam) / 2;
		allocatedMemory = malloc(mid);
		if( allocatedMemory ){
			memset(allocatedMemory, 0, mid);
		}
		if(allocatedMemory == NULL){
		  hi = mid;
		  //printf("hi %llu\n", hi);
		}else{
		  currentEstimatedRam = mid;


		  //printf("lo %llu\n", lo);
		}
	}
	 return currentEstimatedRam;
}


long long askDoubleMemoryUntilFail(){
	long long sizeToRequest = 4096;
	void *allocatedMemory;
	int isFirstTime = 1; //just a flag to not call free()

	do{
		if(isFirstTime){
		  isFirstTime = 0;
		}else{
		  free(allocatedMemory);
		  sizeToRequest = sizeToRequest*2;
		}
		//printf("requesting: %llu\n" , sizeToRequest);
		allocatedMemory = malloc(sizeToRequest);
    if( allocatedMemory ){
      //MallocNode* temp = (MallocNode*)allocatedMemory;
      //temp->size = sizeToRequest;
      memset(allocatedMemory, 0, sizeToRequest - 1024);
    }
	}while(allocatedMemory != NULL);

	return sizeToRequest;
}


long long incrementMemoryUntilFail(long long incrementSize, long long currentEstimatedRam){

	long long sizeToRequest = currentEstimatedRam;
	void * allocatedMemory;

	sizeToRequest = sizeToRequest + incrementSize;
	printf("prevSize: %lld incrementSize:%lld and sizeToRequest: %lld\n", currentEstimatedRam, incrementSize, sizeToRequest );
	allocatedMemory = malloc(sizeToRequest);

  if( allocatedMemory ){
    //MallocNode* temp = (MallocNode*)allocatedMemory;
    //temp->size = sizeToRequest;
    memset(allocatedMemory, 0, sizeToRequest - 1024);
  }

	while(allocatedMemory != NULL){
		sizeToRequest =  sizeToRequest + incrementSize;
		allocatedMemory = malloc(sizeToRequest);
    if( allocatedMemory ){
      //MallocNode* temp = (MallocNode*)allocatedMemory;
      //temp->size = sizeToRequest;
      memset(allocatedMemory, 0, sizeToRequest - 1024);
    }
	}
  free(allocatedMemory);

	return sizeToRequest;
}



int setIncrementOrder(long long currentEstimatedRam){
	long long incrementOrder = 0;
	while(currentEstimatedRam){
		incrementOrder++;
		currentEstimatedRam = currentEstimatedRam/1024;

	}
	return incrementOrder-1;
}


void findMemorySize(){
	long long memorySizeUpperBound = askDoubleMemoryUntilFail();
	long long currentEstimatedRam = memorySizeUpperBound/2;

	long long incrementOrder = setIncrementOrder(currentEstimatedRam);
	printf("currentEstimatedRam> %lld\n", currentEstimatedRam);
	long long prevRamEstimation = currentEstimatedRam;

	memorySizeUpperBound = checkPhysicalMemoryHelper(currentEstimatedRam, memorySizeUpperBound);

	while(incrementOrder){

		currentEstimatedRam = incrementMemoryUntilFail(incrementOrder*1024*1024*1024, currentEstimatedRam);
		printf("CurrentMemory Estimation %lld\n", currentEstimatedRam);
		printf("MemorySizeUpperBound %lld\n", memorySizeUpperBound);


		if(currentEstimatedRam - prevRamEstimation < 512){
			currentEstimatedRam = incrementMemoryUntilFail(8, currentEstimatedRam);
			printf("CurrentMemory Estimation %lld\n", currentEstimatedRam);
			printf("MemorySizeUpperBound %lld\n", memorySizeUpperBound);
			incrementOrder = 0;
		}

    if(currentEstimatedRam - prevRamEstimation < 1024){
      currentEstimatedRam = incrementMemoryUntilFail(512, currentEstimatedRam);
      printf("CurrentMemory Estimation %lld\n", currentEstimatedRam);
      printf("MemorySizeUpperBound %lld\n", memorySizeUpperBound);
      incrementOrder = 1;
    }

    if(currentEstimatedRam - prevRamEstimation < 1024*1024){
      currentEstimatedRam = incrementMemoryUntilFail(incrementOrder*1024, currentEstimatedRam);
      printf("CurrentMemory Estimation %lld\n", currentEstimatedRam);
      printf("MemorySizeUpperBound %lld\n", memorySizeUpperBound);
      incrementOrder = 1;
    }

    if(currentEstimatedRam - prevRamEstimation < 1024*1024*1024){
      currentEstimatedRam = incrementMemoryUntilFail(incrementOrder*1024*1024, currentEstimatedRam);
      printf("CurrentMemory Estimation %lld\n", currentEstimatedRam);
      printf("MemorySizeUpperBound %lld\n", memorySizeUpperBound);
      incrementOrder = 2;
    }

		prevRamEstimation = currentEstimatedRam;

		if(currentEstimatedRam > memorySizeUpperBound){
			break;
		}

	}

  printf("RAM size: %llu Gibibyte", currentEstimatedRam / 1024 / 1024 / 1024);
}

int main(){
	findMemorySize();

	return 0;
}
