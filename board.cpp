#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<iterator>
#include<assert.h>
#include<string>
#include "board.h"
#include"forest.h"

using namespace std;
void board::init_brd()//Construction of the initial board with the symbol ".", "-","\\" and "/"
{
	vector<string> temp;
	for (int i = 0; i < num_column; ++i)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < num_column; ++j)
			{
				if (j % 2 == 0)
					temp.push_back(". ");
				else
					temp.push_back("- ");
			}
		}
		else
		{
			for (int j = 0; j < num_column; ++j)
			{
				if (j % 2 == 0)
					temp.push_back("\\ ");
				else
					temp.push_back("/ ");
			}
		}

		brd.push_back(temp);
		temp.clear();
	}
}

void board::show_brd()// Display the current board
{  

	for (int i = 0; i < num_column; ++i)
	{   
		cout << "                 ";
		for (int j = 0; j < i; ++j)
		{
			cout << " ";
		}
		for (auto temp : brd[i])
			cout << temp;

		cout << endl;
	}

}
bool board::move(int& i, int& j, string ply)// Execuate the move according to the color that has been enterred 
{
	if (brd[2 * i - 2][2 * j - 2] == ". ")//If the place the node that has been moved on is available, execuate the move.
	{
		brd[2 * i - 2][2 * j - 2] = ply + " ";
		return true;
	}
	else {
		cout << "move is illegal" << endl;//If not available, give the warning.
		return false;
	}
}
string board::rtn_val(int& i, int& j)//Return the string that represent the color of the coordinate that has been input
{
	return brd[2 * i - 2][2 * j - 2];
}

void board::init_neigh()//Initialize the neighbor for every node, stock the neighbors in form of vector<index>.

{
	for (int i = 1; i < dim_brd + 1; ++i)
	{
		vector<vector<index>>row_temp;
		for (int j = 1; j <dim_brd + 1; ++j)
		{
			vector<index> temp;
			if (i > 1 && i < dim_brd && j>1 && j < dim_brd)
			{
				temp.push_back(rt_ind(i + 1, j));
				temp.push_back(rt_ind(i + 1, j-1));
				temp.push_back(rt_ind(i, j + 1));
				temp.push_back(rt_ind(i, j-1));
				temp.push_back(rt_ind(i -1, j+1));
				temp.push_back(rt_ind(i -1, j));
			}
			else if (i == 1 && j == 1)
			{
				temp.push_back(rt_ind(2,1));
				temp.push_back(rt_ind(1,1));
			}
			else if (i == dim_brd && j == dim_brd)
			{
			
				temp.push_back(rt_ind(dim_brd,dim_brd-1));
				temp.push_back(rt_ind(dim_brd-1,dim_brd));
			}
			else if (i == 1 && j == dim_brd)
			{
				temp.push_back(rt_ind(2,dim_brd-1));
				temp.push_back(rt_ind(2,dim_brd));
				temp.push_back(rt_ind(1,dim_brd-1));
			}
			else if (i == dim_brd && j == 1)
			{
				temp.push_back(rt_ind(dim_brd,2));
				temp.push_back(rt_ind(dim_brd-1,2));
				temp.push_back(rt_ind(dim_brd,1));
			}
			else if (i == 1 && j > 1 && j < dim_brd)
			{
				temp.push_back(rt_ind(2,j));
				temp.push_back(rt_ind(2,j-1));
				temp.push_back(rt_ind(1,j+1));
				temp.push_back(rt_ind(1,j-1));
			}
			else if (i == dim_brd && j > 1 && j < dim_brd)
			{
				temp.push_back(rt_ind(dim_brd,j+1));
				temp.push_back(rt_ind(dim_brd,j-1));
				temp.push_back(rt_ind(dim_brd-1,j+1));
				temp.push_back(rt_ind(dim_brd-1,j));
			}
			else if (j == dim_brd && i > 1 && i < dim_brd)
			{
				temp.push_back(rt_ind(i+1,dim_brd));
				temp.push_back(rt_ind(i+1,dim_brd-1));
				temp.push_back(rt_ind(i,dim_brd-1));
				temp.push_back(rt_ind(i-1,dim_brd));
			}
			else if (j == 1 && i > 1 && i < dim_brd)
			{
				temp.push_back(rt_ind(i+1,1));
				temp.push_back(rt_ind(i,2));
				temp.push_back(rt_ind(i-1,2));
				temp.push_back(rt_ind(i-1,1));
			}
			row_temp.push_back(temp);
			temp.clear();
		}
		neighbor.push_back(row_temp);
		row_temp.clear();
		
	}
	void init_ply_neighbor();//Initialize the vector that contain the neighbor which has the same color as the node.
}

void board::init_ply_neighbor()//Initialize the vector B_neighbor and R_neighbor, allocate the memory for these vectors.
{

	B_neighbor.resize(dim_brd);
	R_neighbor.resize(dim_brd);
	for (int i = 0;i < dim_brd;++i)
	{
		B_neighbor[i].resize(dim_brd);
		R_neighbor[i].resize(dim_brd);
	}
}

void board::judge_neigh( string color)// Make a judgement among all the neighbors of every node having the color of "color", put the one that has the same color as the node 
//into the vector B_neighbor or R_neighbor(according to the "color").
//In fact, we prepare this vector for judging if the player selected has won or not.
{
#ifndef NBUG
	assert(neighbor.size() > 0);
#endif

	if(color=="B ")vector<vector<vector<index>>>().swap(this->B_neighbor);
	else vector<vector<vector<index>>>().swap(this->R_neighbor);
	this->init_ply_neighbor();
	for (int i = 1; i < dim_brd + 1; ++i)
		for (int j = 1; j < dim_brd + 1; ++j)
		   if(rtn_val(i, j) == color){
			for (auto iter=neighbor[i-1][j-1].begin();iter!=neighbor[i-1][j-1].end(); ++iter)
			{
				if (rtn_val(iter->row,iter->column)==color)
				{  
					if(color=="B ")B_neighbor[i-1][j-1].push_back(*iter);
					else R_neighbor[i - 1][j - 1].push_back(*iter);
				}
			}
		   }
}
vector<index> board::rtn_neigh(int &i, int& j)//Return the vector that contain the neighbors which have the same color as the node.
{
    #ifndef NBUG
	assert(neighbor[i-1][j-1].size() > 0);
   #endif
	if (rtn_val(i, j) == "B ")
	{
		if (B_neighbor[i - 1][j - 1].size() > 0)
		{
			return B_neighbor[i - 1][j - 1];
		}
		else
		{
			vector<index> temp;
			temp.clear();
			return temp;
		}
	}
	else if (rtn_val(i, j) == "R ")
	{
		if (R_neighbor[i - 1][j - 1].size() > 0)
		{
			return R_neighbor[i - 1][j - 1];
		}
		else
		{
			vector<index> temp;
			temp.clear();
			return temp;
		}
	}
}
