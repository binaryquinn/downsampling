#include <iostream>
#include <map>
#include <pthread.h>
#include <vector>
#include <boost/multi_array.hpp>
#include "mappedheap.h"

using namespace std;
using namespace boost;

typedef multi_array<int, 3> mArray;


mArray baseline(extents[128][128][128]);
mArray firstIteration(extents[64][64][64]);
mArray secondIteration(extents[32][32][32]);
mArray thirdIteration(extents[16][16][16]);
mArray fourthIteration(extents[8][8][8]);
mArray fifthIteration(extents[4][4][4]);
mArray sixthIteration(extents[2][2][2]);
int finalSample;
MappedHeap grandHeap;


MappedHeap breakDown(int ulRow, int ulColumn, int ulDepth, int width)
{
	MappedHeap localHeap;
	if(width>1)
	{
		localHeap += breakDown(ulRow,ulColumn,ulDepth, width/2);
		localHeap += breakDown(ulRow+width,ulColumn,ulDepth, width/2);
		localHeap += breakDown(ulRow,ulColumn+width,ulDepth, width/2);
		localHeap += breakDown(ulRow,ulColumn,ulDepth+width, width/2);
		localHeap += breakDown(ulRow+width,ulColumn+width,ulDepth, width/2);
		localHeap += breakDown(ulRow+width,ulColumn,ulDepth+width, width/2);
		localHeap += breakDown(ulRow,ulColumn+width,ulDepth+width, width/2);
		localHeap += breakDown(ulRow+width,ulColumn+width,ulDepth+width, width/2);
	}
	else
	{
		for(int rowLoop = ulRow;rowLoop < (ulRow+2); rowLoop++)
		{
			for(int columnLoop = ulColumn; columnLoop <(ulColumn+2); columnLoop++)
			{
				for(int depthLoop = ulDepth; depthLoop <(ulDepth+2); depthLoop++)
				{
					localHeap.addNode(baseline[rowLoop][columnLoop][depthLoop],1);
				}
			}
		}
	}

	int denom = width*2;
	switch(width)
	{
		case 1:firstIteration[ulRow/denom][ulColumn/denom][ulDepth/denom] = localHeap.HeapPeak();break;
		case 2:secondIteration[ulRow/denom][ulColumn/denom][ulDepth/denom] = localHeap.HeapPeak();break;
		case 4:thirdIteration[ulRow/denom][ulColumn/denom][ulDepth/denom] = localHeap.HeapPeak();break;
		case 8:fourthIteration[ulRow/denom][ulColumn/denom][ulDepth/denom] = localHeap.HeapPeak();break;
		case 16:fifthIteration[ulRow/denom][ulColumn/denom][ulDepth/denom] = localHeap.HeapPeak();break;
		case 32:sixthIteration[ulRow/denom][ulColumn/denom][ulDepth/denom] = localHeap.HeapPeak();break;
	};
	return localHeap;
}


void *threadControl(void *thread)
{
	int threadNum = (int)thread;
	int width = 64;
	int row = (threadNum%2)*width;
	threadNum/=2;
	int col = (threadNum%2)*width;
	threadNum/=2;
	int dep =(threadNum%2)*width;
	grandHeap+=breakDown(row,col,dep,width/2);


	pthread_exit(NULL);
}

int main()
{

	int count= 0;
	int threadCap =  8;
	vector <pthread_t> threadManager(threadCap);
	for(count = 0; count < threadCap; count++)
		pthread_create(&threadManager[count],NULL, threadControl,(void*)count);

	for(count = 0; count < threadCap; count++)
		pthread_join(threadManager[count],NULL);


	finalSample = grandHeap.HeapPeak();

	return finalSample;
}

