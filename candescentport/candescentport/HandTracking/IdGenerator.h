#ifndef IDGEN_H
#define IDGEN_H
#include <vector>
class IdGenerator
{
public:
	IdGenerator();
	std::vector<int> usedIds;

	int GetNextId();

	void Return(int id);

	void Clear();

	void SetUsed(int id);
};

#endif 