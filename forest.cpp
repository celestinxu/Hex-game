#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<iterator>
#include<string>
#include<functional>
#include"forest.h"
#include"board.h"
#include"index.h"
using namespace std;
bool forest::compare(index ind_a, index ind_b)
{
	bool bln = false;
	for (auto it = set_tree.begin(); it != set_tree.end(); ++it)
	{
		if (find_if(it->begin(), it->end(), bind2nd(ptr_fun(equal_index), ind_a)) != it->end() && find_if(it->begin(), it->end(), bind2nd(ptr_fun(equal_index), ind_b)) != it->end()) { bln = true;  break; }
		//Browse the container "set_tree", using the STL function find_if to determine if the two coordinate are in the same tree. Here applicating the function bind2nd for fixing the second parameter,
		//then compare the element selected from "set_tree" with the fixed parameter.
	}
	return bln;
}
bool forest::search(index &ind)
{   //Determine if the coordinate is in the container "set_tree", if it is, return "true", else return "false"
	bool b = false;
	for(auto it_1=set_tree.begin();it_1!= set_tree.end();++it_1)
		for (auto it_2 = it_1->begin(); it_2 != it_1->end(); ++it_2)
		{
			if (it_2->row == ind.row && it_2->column == ind.column) { b = true; break; }
		}
	return b;
}

void forest::collect(index ind) 
{ 
	mov.push_back(ind);
}

void forest::associate(board b)
{   
	set_tree.clear();//Firstly clear the container every time invoke the function "associate".

    //Definition of 4 containers which will be used in this algorithm. "vec_tree" is intended for storing the coordinate for one single tree.
	//In the process of traversal of one tree, basically we need two container, "vec_iteration" for storing the coordinates for which we will search for their neighbors, "vec_neighbor"
	//in which we will push back all the neighbors of the nodes in "vec_iteration". For convenience, we need also a container to store the neighbor of each node in "neighbor_temp".
	vector<index>vec_tree(0);
	vector<index>vec_iteration(0);
	vector<index>vec_neighbor(0);
	vector<index>neighbor_temp(0);
	std::vector<index>::iterator it;
	mov_temp.insert(mov_temp.end(), mov.begin(), mov.end());//Duplicate the vector "mov" with "mov_temp"
	while (mov.size()!=0 && search(*mov.begin())==false)
	{
		//For each iteration of traversal of one tree, we will update container "vec_iteraion" and "vec_neighbor", and put every node in "vec_neighbor" into "vec_iteration".
		//In this way, the "vec_neighbor" found in the last iteration becomes the "vec_iteration" in next iteration, at the end of each iteration,we put all the nodes in "vec_iteration"
		//into "vec_tree".When rhe traversal of one tree is over, we push "vec_tree" into "set_tree", which is a vector consisted of "trees".
		vec_tree.push_back(rt_ind(mov.begin()->row, mov.begin()->column));//
		 vec_iteration.push_back(rt_ind(mov.begin()->row, mov.begin()->column));
		do
		{    
			for (auto it_1 = vec_iteration.begin(); it_1 != vec_iteration.end(); ++it_1)
			{
				neighbor_temp= b.rtn_neigh(it_1->row, it_1->column);
				vec_neighbor.insert(vec_neighbor.end(), neighbor_temp.begin(), neighbor_temp.end());
			}

		 //In the found neighbors,we exclude all nodes that already exist in "vec_tree" 
			for (auto it_2 = vec_neighbor.begin(); it_2 != vec_neighbor.end();)
			{
				if (find_if(vec_tree.begin(), vec_tree.end(), bind2nd(ptr_fun(equal_index), *it_2)) != vec_tree.end())
					it_2 = vec_neighbor.erase(it_2);
				else ++it_2;
			}
			vec_tree.insert(vec_tree.end(), vec_neighbor.begin(), vec_neighbor.end());
			vector<index>().swap(vec_iteration);//Clear "vec_iteration" and update it with "vec_neighbor" 
			vec_iteration.insert(vec_iteration.end(), vec_neighbor.begin(), vec_neighbor.end());
			vector<index>().swap(vec_neighbor);//Clear "vec_neighbor"
		} while (vec_iteration.size() != 0);
		set_tree.push_back(vec_tree);//Put every "tree" into "set_tree"
		//Exclude al the node in "vec_tree" from "mov"
		for (auto it_3 = vec_tree.begin(); it_3 != vec_tree.end(); ++it_3)
		{
			it=find_if(mov.begin(), mov.end(), bind2nd( ptr_fun(equal_index), *it_3));
			if ( it!= mov.end())
			{
				mov.erase(it);
			}
		}
		vector<index>().swap(vec_tree);//Clear the container "vec_tree" for next iteration
	}
	mov.clear();//Clear vector "mov"
	mov.insert(mov.end(),mov_temp.begin(),mov_temp.end());//Initialize the vector "mov" with its initial data that has been stored in "mov_temp"
	mov_temp.clear();
}


bool equal_index(index ind_a, index ind_b)
{
	if (ind_a.row == ind_b.row && ind_a.column == ind_b.column) { return true; }
	else { return false; }
}
bool forest::judge_win(int &dim,string color,board &b)
{
	bool indicator = false;
	int frt_rw = 1;
	int frt_col = 1;
    //Using two different ways according to the "color" to judge if the player concerned wins or not.
	if(color=="B ")
	{
	for (int i = 1; i < dim + 1; ++i)
		for (int j = 1; j < dim + 1; ++j)
		{  // Try to find two nodes, which are respectively from the first and last row of the board, in the same tree. If we can find them, it means the player concerned has won.
			if(b.rtn_val(frt_rw,i)==color&&b.rtn_val(dim,j)==color&&compare(rt_ind(frt_rw,i), rt_ind(dim,j)) == true)
			  { indicator = true; break; }
		}
	}
	else if (color == "R ")
	{
		for (int i = 1; i < dim + 1; ++i)
			for (int j = 1; j < dim + 1; ++j)
			{  // Try to find two nodes, which are respectively from the first and last column of the board, in the same tree. If we can find them, it means the player concerned has won.
				if (b.rtn_val(i, frt_col) == color && b.rtn_val(j, dim) == color && compare(rt_ind(i, frt_col), rt_ind(j, dim)) == true)
				{	indicator = true; break;}
			}
	}

	return indicator;
}