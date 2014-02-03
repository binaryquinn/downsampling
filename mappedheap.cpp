#include "mappedheap.h"

MappedHeap::MappedHeap()
{
	myLast = 1;
	myHeap.resize(128);
}

MappedHeap::~MappedHeap()
{
}

int MappedHeap::HeapPeak()
{
	return myHeap[1].value;
}

MappedHeap* MappedHeap::operator +=(const MappedHeap &right)
{
	for(map<int, int>::const_iterator keys = right.myMap.begin();keys!=right.myMap.end();++keys)
	{
		addNode(keys->first,right.myHeap[keys->second].count);
	}
	return this;
}


void MappedHeap::addNode(int paraValue, int paraCount)
{
	if(myMap.find(paraValue)==myMap.end())
	{
		myHeap[myLast].value = paraValue;
		myHeap[myLast].count = paraCount;
		bubbleUp(myLast);
		myLast++;
		if(myLast >= myHeap.size())
				myHeap.resize(myLast+128);
	}
	else
	{
		int pos = myMap[paraValue];
		myHeap[pos].count += paraCount;
		bubbleUp(pos);
	}
}

void MappedHeap::bubbleUp(int pos)
{
	MappedNode old;
	while( pos > 1 && myHeap[pos].count > myHeap[pos/2].count)
	{
		old = myHeap[pos/2];
		myHeap[pos/2] = myHeap[pos];
		myHeap[pos] = old;
		myMap[old.value] = pos;
		pos /= 2;
	}
		myMap[myHeap[pos].value] = pos;
}


MappedHeap::MappedNode::MappedNode()
{
	value = 0;
	count = 0;
}


