#include "IdGenerator.h"
//make the vector contain the current used numbers
//to find an unused, start at zero and each increment, check if used.
int IdGenerator::GetNextId(){
	int nextId = 0;
	std::vector<int>::iterator iter;
	bool empty = false;
	while (!empty)
	{
		nextId++;
		for (iter=usedIds->begin();iter<usedIds->end();usedIds++) {
			if (!(int)*iter==nextId) {
				empty = true;
				break;
			}
		}

	}
	usedIds->push_back(nextId);

	return nextId;
}

void IdGenerator::Return(int id)        {
	std::vector<int>::iterator iter;
	for (iter=usedIds->begin();iter<usedIds->end();usedIds++) {
		if ((int)*iter==id) {
			usedIds->erase(iter);
			return;
		}
	}
	//this.usedIds.Remove(id);
}

void IdGenerator::Clear()        {
	//this.usedIds.Clear();
	usedIds->clear();
}

void IdGenerator::SetUsed(int id)        {
	usedIds->push_back(id);
	//this.usedIds.Add(id);
}

IdGenerator::IdGenerator(){
	usedIds = new std::vector<int>;
}