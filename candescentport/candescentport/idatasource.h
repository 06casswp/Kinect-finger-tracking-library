#ifndef IDATSRC_H
#define IDATSRC_H


class IDataSource
{
public:
			//virtual void Start();
			//virtual void Stop();
			bool IsRunning;

};

template <typename TValue> class IDataSourceT : public IDataSource
{
public:
	TValue CurrentValue;

};

#endif 