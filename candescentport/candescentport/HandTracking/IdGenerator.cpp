#include "IdGenerator.h"
//make the vector contain the current used numbers
//to find an unused, start at zero and each increment, check if used.
int IdGenerator::GetNextId(){
	int nextId = 0;
	std::vector<int>::iterator iter;

	if (usedIds->empty()) {
		usedIds->push_back(0);
		return 0;
	}

	bool currentused = true;
	while (currentused)
	{
		nextId++;
		for (iter=usedIds->begin();iter<usedIds->end();iter++) {
			if ((int)*iter==nextId) {
				break;
			}
			currentused = false;
		}

	}
	usedIds->push_back(nextId);

	return nextId;
}

void IdGenerator::Return(int id)        {
	std::vector<int>::iterator iter;
	for (iter=usedIds->begin();iter<usedIds->end();iter++) {
		if ((int)*iter==id) {
			usedIds->erase(iter);
			return;
		}
	}
	//this.usedIds->Remove(id);
}

void IdGenerator::Clear()        {
	//this.usedIds->Clear();
	usedIds->clear();
}

void IdGenerator::SetUsed(int id)        {
	usedIds->push_back(id);
	//this.usedIds->Add(id);
}
