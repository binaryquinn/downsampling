#ifndef MAPPEDHEAP_H
#define MAPPEDHEAP_H

#include <map>
#include <vector>
using namespace std;

class MappedHeap
{
public:
	MappedHeap();
	~MappedHeap();
	int HeapPeak();
	void addNode(int value, int count);
	MappedHeap* operator += (const MappedHeap &right);


private:

	struct MappedNode
	{
		MappedNode();
		int value;
		int count;
	};

	void bubbleUp(int pos);

	vector<MappedNode> myHeap;
	map<int, int> myMap;
	unsigned int myLast;


};

#endif // MAPPEDHEAP_H
