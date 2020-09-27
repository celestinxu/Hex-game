#ifndef BOARD_H
#define BOARD_H
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include"index.h"
using namespace std;
//Defintion of the class type board for enscapsulating the information about the dimension of the board,the move, the color, 
//the neigbor  of every node etc. A set of methods are defined for execuating the move, showing the board, judging if the neighbor of
//one node has the same color.
class  board
{
public:
	//Constructor of the class, initilizing the object of the class with the interger dim entering by the player.Initlizing the vector brd,neighbor and B_neighbor(R_neighbor) as null
	board(int dim) :num_column(2 * dim - 1), num_row(2 * dim - 1), dim_brd(dim),brd(0),neighbor(0),B_neighbor(0), R_neighbor(0) {

	};
	void init_brd();//Method for initializing the board
	void show_brd();//Method for displaying the board
	bool move(int& i, int& j, string ply);//Method for execuating the move on the board
	string rtn_val(int& i, int &j);//Method for returning the value of the corresponding coordinate
	void init_neigh();//Method for initializing the neighbor of every node
	void judge_neigh(string color);//Method for judging if the neighbor of the node having the color"color" has the same color as its own, and put the neighbors having the same color into the container corresponding.
	vector<index> rtn_neigh(int& i, int& j);//Method for return the vector that contain the neighbors which have the same color as one node
	void init_ply_neighbor();//Method for intializing the vector contain the neighbor that have the same color as one node.
	board& operator=(const board &b)//Overload the operator "=" for the object "board".
	{
		this->brd.clear();
		this->brd.insert(this->brd.end(),b.brd.begin(), b.brd.end());
		this->neighbor.clear();
		this->neighbor.insert(this->neighbor.end(), b.neighbor.begin(), b.neighbor.end());
		vector<vector<vector<index>>>().swap(this->B_neighbor);
		vector<vector<vector<index>>>().swap(this->R_neighbor);
		this->init_ply_neighbor();
		this->num_column = b.num_column;
		this->num_row = b.num_row;
		this->dim_brd = b.dim_brd;
		return *this;
	};
	
	

private:
	//Definition of the data for this class
	vector<vector<string>> brd;//Container that store the ASCII symboles drawing the board.
	vector<vector<vector<index>>> neighbor;//Container storing the neighbor for every node.
	vector<vector<vector<index>>> B_neighbor;//Container storing the neighbors having the color blue of every node having the color blue.
	vector<vector<vector<index>>> R_neighbor;//Container storing the neighbors having the color red of every node having the color red.
	int num_column;
	int num_row;
	int dim_brd;
};
#endif