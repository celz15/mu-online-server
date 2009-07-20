#pragma once
#include <stdio.h>
#include <utility>
#include "MuObiects/MuObjectsPool.h"
using std::pair;

typedef pair<MuViewPort *, MuViewPort *> MuViewPortPair;

class MuViewPort
{
public:
	enum
	{
		S_Empty = 0x00, S_ToForget = 0x01, S_New = 0x02, S_Known = 0x03
	};

	unsigned char c_State;
	short c_Number;
	unsigned char o_Type;
	unsigned short o_Index;
	int o_dist;

	~MuViewPort()
	{
	}

	MuViewPort()
	{
		c_State = S_Empty;
		c_Number = 0x00;
		o_Index = 0x00;
		o_Type = 0x00;
		o_dist = 0;
	}

	//------------------------------------dumps staff -----------------------------
	void PrintMe()
	{
		printf("Obj[Index:%d,Type:%d$] in distance [dist:%d,State:%d]\n",
				o_Index, o_Type, o_dist, c_State);
	}

};

class MuViewPortSet
{
	MuViewPort _vPort[75]; //array of data od viewport
	int _vSize; //count of used cell in array
	unsigned char _vRad; //radius on seeing of owner class
	unsigned short _vIndex; //id of ownew
public:
	MuViewPortSet(unsigned short id, unsigned char rad)
	{
		_vIndex = id;
		_vSize = 0;
		_vRad = rad;
	}
	unsigned char getViewRad()
	{
		return _vRad;
	}

	int getViewSize()
	{
		return _vSize;
	}

	MuViewPort & operator [](int i)
	{
		if (i > getViewSize())
			printf(
					"Error try to acces to offindex of array in [FIle:%s,Line:%d]\n",
					__FILE__, __LINE__);
		return _vPort[i];
	}

	MuViewPort * getViewPort(int pos)
	{
		return &_vPort[pos];
	}
	void checkViewPort()
	{
		for (int i = 0; i < getViewSize(); i++)
		{
			if (_vPort[i].c_State != MuViewPort::S_Empty)
			{
				MuViewPortPair t = ObiectPool::getInstance()->getDistance(
						_vIndex, _vPort[i].o_Index, getViewRad());
				memmove(&_vPort[i], t.second, sizeof(MuViewPort));
				if (_vPort[i].o_dist > _vRad)
					_vPort[i].c_State = MuViewPort::S_ToForget;
			};
		};
	}


	unsigned char searchId(unsigned short id)
	{
		for (int i = 0; i < getViewSize(); i++)
		{
			if (_vPort[i].o_Index == id)
				return i;
		};
		return 0xff;
	}

	unsigned short getIndex()
	{
		return _vIndex;
	}


	void printMe()
	{
		printf("\nPointView[Size:%d] for [Index:%d]in [Rad:%d]\n", _vSize,
				_vIndex, _vRad);
		for (int i = 0; i < getViewSize(); i++)
		{
			if (_vPort[i].c_State != MuViewPort::S_Empty)
				_vPort[i].PrintMe();
		};
		printf("End dump PoerView [Index:%d]\n", _vIndex);
	}


	void optymalize()
	{
		if (getViewSize() < 60)
			return;
		MuViewPort t[75];
		int size = 0;
		for (int i = 0; i < getViewSize(); i++)
		{
			if (_vPort[i].c_State != MuViewPort::S_Empty)
			{
				t[size] = _vPort[i];
				size++;
			}
		}
		for (int i = 0; i <= size; i++)
			_vPort[i] = t[i];
		_vSize = size;
	}


	void addViewPort(MuViewPort *p)
	{
		MuViewPort *temp = p;
		//if obiect is'nt in see area ther is to forget whotever its known or not
		unsigned char pos = searchId(p->o_Index);
		if (pos == 0xff) //we do not known it;
		{
			if (temp->c_State == MuViewPort::S_New)
			{
				_vSize++;
				memmove(&_vPort[_vSize - 1], p, sizeof(MuViewPort));
			};
		}
		else // we known it :)
		{
			if ((temp->c_State == MuViewPort::S_New) && (_vPort[pos].c_State
					== MuViewPort::S_Known))
				_vPort[pos].o_dist = temp->o_dist;
			else
				memmove(&(_vPort[pos]), temp, sizeof(MuViewPort)); //update dest and forget flag
		};
		//  printMe();
		delete temp;
	}


};
