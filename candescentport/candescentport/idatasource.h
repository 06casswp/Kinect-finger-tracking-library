#ifndef IDATSRC_H
#define IDATSRC_H

class IDataSource
{

			bool IsRunning;

};

template <typename TValue> class IDataSourceT : public IDataSource
{
public:
	TValue CurrentValue;

};

#endif 