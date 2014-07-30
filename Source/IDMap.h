#ifndef IDCONTAINER_H
#define IDCONTAINER_H

#include <map>
#include <deque>
#include <algorithm>
using namespace std;

typedef unsigned int ID;

template<ID MINID,ID MAXID>
class IDManager
{
public:
	IDManager()
	{
		Reset();
	}
	ID gen()
	{
		if (freeIDs.size()>0)
		{
			ID id = freeIDs.front();
			freeIDs.pop_front();
			usedIDs.push_back(id);
			return id;
		}
		else
			return 0;
	}
	void Free(ID id)
	{
		freeIDs.push_back(id);
		usedIDs.erase(remove(usedIDs.begin(),usedIDs.end(),id),usedIDs.end());
	}
	void Reset()
	{
		freeIDs.clear();
		usedIDs.clear();
		for (ID i=MINID; i<=MAXID; i++)
			freeIDs.push_back(i);
	}
private:
	deque<ID> freeIDs;
	deque<ID> usedIDs;
};

template<typename T>
class IDMap
{
public:
	ID insert(const T& o)
	{
		ID id = IDManager_.gen();
		if (!id) return 0;
		IDMap_[id] = new T(o);
		return id;
	}
	ID gen()
	{
		ID id = IDManager_.gen();
		if (!id) return 0;
		IDMap_[id] = new T();
		return id;
	}
	T* operator[](ID id) 
	{
		return IDMap_[id];
	}
	bool remove(ID id)
	{
		if (!IDMap_[id])
			return false;
		delete IDMap_[id];
		IDMap_[id] = NULL;
		IDManager_.Free(id);
		return true;
	}

private:
	map<ID,T*> IDMap_;
	IDManager<1,100> IDManager_;
};


#endif

