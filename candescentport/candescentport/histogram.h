#ifndef HISTO_H
#define HISTO_H


class Histogram
{
public:
	int* data;
	int length;

	Histogram(int length1);

	void Reset();

	void Increase(int depthValue);

	void PostProcess(int points);

	int GetValue(unsigned short depthValue);

	int Length();

};

#endif