#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<iterator>
#include<string>
#include<cstddef>
#include<random>
#include<functional>
#include<ctime>
#include<stdlib.h>
#include"board.h"
#include"forest.h"
#include"index.h"
using namespace std;
//In this library, we will define a function "MC" for implementing the AI based on monte carlo.
default_random_engine e(time(nullptr));//Creating the random engine
uniform_real_distribution<double> u(0, 1);//Definition of a uniform ditribution between 0 and 1
vector<index>::iterator pickRandEl(vector<index>::iterator first, vector<index>::iterator last);// Declaration  of a function which picks the element randomly between two iterators
string alternate_color(string color);
index MC(board &brd, int dim,string color)
{
	//Declaration of a duplicate of the board brd and its initialization 
	board duplicate_brd(dim);
	duplicate_brd.init_brd();
	duplicate_brd.init_neigh();
	duplicate_brd.init_ply_neighbor();
	//Definition of a forest 
	forest f,duplicate_f;

	//Creation of a vector next_mov for collecting all the coordinates which has not yet been put move on
	//All these coordinates can be the potential next move.
	vector<index> next_mov;
	for(int i=1;i<dim+1;++i)
		for(int j=1;j<dim+1;++j)
		{
			if (brd.rtn_val(i, j) == ". ")
			{ 
				next_mov.push_back(rt_ind(i,j));
			}
			if(brd.rtn_val(i, j) == "B ")
			{
				f.collect(rt_ind(i, j));
			}
		}

	vector<double> ratio;//Definition of a vector "ratio" for storing the win rate for every next move. 
	int nb_trial = 2000/(next_mov.size());//Defintion of number of trial for every possible next move.
	int nb_win = 0;//Definition of the variable "nb_win"" for  counting the nombre of winning in these trials.
	vector<index> vec_iteration;//Defintion of a container for the convenience of the iteration.
	string ply_alte;//Defintion of a variable "ply_alte" that can altenate between "R" and "B" according to the move should be carried out.
	vector<index>::iterator pickrd;//Iterator that will receive the returning result of function pickRandE1.
	vector<index>::iterator iter;//Iterator that will receive the result found by function "find_if" in "vec_iteration".

	//For each element in the container next_mov, we try to execute nb_trial trials and calculate the win rate corresponding.
	for (auto it = next_mov.begin(); it != next_mov.end(); ++it)
	{
		nb_win = 0;//Intialisation the nb_win as 0.
		for (int i = 1; i < nb_trial; ++i)
		{
			duplicate_brd = brd;//Duplicate the board brd.
			duplicate_f=f;//Intialisation the forest f.
			duplicate_brd.move(it->row, it->column, color);//For the element addressed, take its coordiante for carrying out the first move of each trial.  
			if (color == "B")duplicate_f.collect(rt_ind(it->row,it->column)); 
			vec_iteration = next_mov;//Duplicate next_mov.
			//Delete the element addressed form vec_iteration.
			iter = find_if(vec_iteration.begin(), vec_iteration.end(), bind2nd(ptr_fun(equal_index), *it));
			vec_iteration.erase(iter);
			ply_alte = color;
			do {
				if (ply_alte == "R")ply_alte = "B";
				else ply_alte = "R";
				//Pick an element randomly in "vec_iteration" and take its coordinate for carrying out the move.
				pickrd = pickRandEl(vec_iteration.begin(), vec_iteration.end());
				duplicate_brd.move(pickrd->row, pickrd->column, ply_alte);
				//If  the move being carried out is "B", "forest" f will collect it.
				if (ply_alte == "B") duplicate_f.collect(rt_ind(pickrd->row, pickrd->column));
				vec_iteration.erase(pickrd);//Delete the element selected randomlt from "vec_iteration".
			} while (vec_iteration.size() != 0);//Iteration until there is no element remain in "vec_iteration".
			//For every node that has the color concerned in the filled up board, find and collect the neighbors that have the same color as it.
			duplicate_brd.judge_neigh("B ");
			//Generating the relative trees. 
			duplicate_f.associate(duplicate_brd);
			//Adding the nb_win by one if the player concerned has won in this trial.
			if (duplicate_f.judge_win(dim,"B ",duplicate_brd) == true) { ++nb_win;}
		}
		//Put the win rate for every move in "next_move" into the container "ratio".
		ratio.push_back(double(nb_win)/nb_trial);
	}
	//Find the potential move that can make the humain player has the smallest rate to win.
	vector<double>::iterator selection;
	int delta;
	if (color == "R")
	{
		selection = min_element(ratio.begin(), ratio.end());
		//Select the smallest win rate move as the next move.
	    delta = distance(ratio.begin(), selection);
		
	}
	else 
	{
		selection = max_element(ratio.begin(), ratio.end());
		//Select the smallest win rate move as the next move.
		delta = distance(ratio.begin(), selection);
	}
	index next_ind(rt_ind((delta + next_mov.begin())->row, (delta + next_mov.begin())->column));
	//brd.move(next_ind.row, next_ind.column, color);
	return next_ind;
}

//Function that will return the "pointer" of next move randomly.
vector<index>::iterator pickRandEl(vector<index>::iterator first, vector<index>::iterator last)
{
	ptrdiff_t temp = last - first;
	return first + u(e) * temp;
}
string alternate_color(string color)
{
	if (color == "B") return "R";
	else return "B";
}
#endif