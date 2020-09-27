#ifndef FOREST_H
#define FOREST_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<iterator>
#include<string>
#include"index.h"
#include"board.h"
using namespace std;
//In fact, for judging who has won, I have inspired from the method that has been methioned in part A, the "most span tree" method. Firstly, we select one coordinate in 
//the vector "mov" which stores all the coordinates that have been placed the same move on. And then, we find all its neighbors that have the same colors.We put this first node with
//these neighbors into the same tree. Secondly, we put the neighbors in the first step into a containor in which we want to find all the neighbors of the nodes,surely the neighbors have the same color as the node. And then we put the neighbors found into 
//the same tree.Iteratively, we repeat these steps until we can no more find more neighbors for coordinate in this tree apart from the coordinates in the same tree. Until then,
//we exclude all the coordiantes in he first tree from the vector "mov".And then we begin search for the next tree. We continue doing this until there is no coordinate left in the vector mov.
//We can find that if there is one tree which contains the coordinate in the first row and last row, then we can conclude that the player cooresponding has won. If this tree does not exist, 
//it hasn't won.

//For this reason, I have defined the class forest for realising this algorithm,the data contained in this class include the vector "mov",its duplicate "mov_temp" and the two-dimension vector cont,
//in which can store different trees. The method include "compare", that judge if two coordiante are in the same tree or not, the method "search", which determinate if the coordinate enterred is in
//one of these trees created, the method "collect", which collect all the coordinates that have been palced move concerned  in the vector "mov", the method "associate",in which we
//have realised the algorithm methioned above, in which all the trees are created, and the method "who_win",with the help of all the methods above, it can determinate easily 
//if the player has won.


class forest
{
public:
	forest() :set_tree(0), mov(0), mov_temp(0) {};//Constructor of the class.
	bool compare(index ind_a, index ind_b);//Method for comparing if the two coordinates are in the same tree.
	bool search(index &ind);//Method for searching if the coordinate is included in one of all these trees.
	void collect(index ind);//Method for collecting the coordinates that have the move concerned on into the vector "mov". 
	void associate(board b);//Method for realising the algorithm of creating the trees.
	bool judge_win(int &dim,string color,board &b);//Method for determining if the player concerned has won.

	forest& operator=(const forest& f)//Overload the operator "=" for the object "forest".
	{
		this->set_tree.clear();
		this->mov.clear();
		this->mov_temp.clear();
		this->mov.insert(this->mov.end(), f.mov.begin(), f.mov.end());
		return *this;
	};
private://Defintion of the datas specilized for this class.
	vector<vector<index>> set_tree;//Container for sotcking all the trees.
	vector<index> mov;//Containor for storing all the moves concerned.
	vector<index> mov_temp;//Duplicate of the containor "mov".

};
bool equal_index(index ind_a, index ind_b);//Function for determining if the two coordinates are the same. 
#endif










