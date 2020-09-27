#ifndef INDEX_H
#define INDEX_H
#include<iostream>
using namespace std;
//Definition of the class index, in which the coordinate of each node is stored.
class index
{
public:
	//Default constructor and parameterized constructor
	index() :row(0), column(0) {};
	index(int i, int j) :row(i), column(j) {};
	int row;
	int column;
	index& operator=(const index& ind)
	{
		this->row = ind.row;
		this->column = ind.column;
		return *this;
	};

};
//Function that will return the type "index" that cooresponds to the input coordinate
index rt_ind(int i,int j);
#endif