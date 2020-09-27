#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<iterator>
#include<string>
#include"forest.h"
#include"monte_carlo.h"
#include"board.h"
using namespace std;
void main()
{   
	int dim;//Definition of parameter "dim" that represents the dimension of the board.
	//Notice for entering the dimension of the board.
	cout << "         ####################################"<<endl;
	cout<<  "         # Enter the dimension of the board #"<<endl;
	cout << "         ####################################" << endl;
	cin >>dim;

	board b(dim);//Construction of the board with the dimension "dim".
	b.init_brd();//Initialization of the board.
	b.init_neigh();//Initialization of the container "neighbor".
	b.init_ply_neighbor();//Initialization of the container "B_neighbor" and "R_neighbor" .
	forest f_human,f_AI;///Definition of two forest "f_human" and "f_AI" for determing if they win of not.

    //Notice for the human player to choose its color.
	cout << "       #########################################"<<endl;
	cout << "       # Humain:please choose your color(B/R)  #" << endl;
	cout << "       #            (Blue go first)            #" << endl;
	cout << "       #########################################" << endl;


	string Human;//Definition of "Human" that stands for the color of the human player.
	string AI;//Definition of "AI" that stands for the color of AI.

	enum order { Human_go_first, AI_go_first };//Definition of enumerator for the convenience of arraning which player goes first.
	order ord_go;
	cin >> Human; //Input of the color chooesen by human player.
	//If human player chooses color "B", human player will go first, if not, AI will go first.
	if (Human == "B") { AI = "R"; ord_go = Human_go_first; }
	else{ AI = "B"; ord_go = AI_go_first; }

	//Displaying the color of both player.
	cout << "              ##########################" << endl;
	cout << "              #  Humain's color is" <<" "<<Human<<"   #"<< endl;
	cout << "              #   AI's color is" <<" "<<AI<<"      #"<< endl;
	cout << "              ##########################" << endl;

	//Definition of the integers that represent the coordinate of the moves choosen by human player and the index representing the move of AI.
	int cor_i_human, cor_j_human;
	index mov_ai;
	//Different order to execuate the move according to the color choosen by human player.
	switch (ord_go)
	{
	case(Human_go_first):
	{
		do {
			//Human player's turn.
			///////////////////////////////////////////////////////////////////
			//Notice for entering the coordinate of the move for human player.
			cout << "                                        " << endl;
			cout << "          ##################################" << endl;
			cout << "          # Human's move: cord_i & cord_j  #" << endl;
			cout << "          ##################################" << endl;
			cin >> cor_i_human >> cor_j_human;

			b.move(cor_i_human, cor_j_human, "B");//Executing the move on the "board" for human player.
			b.judge_neigh("B ");//Finding the neighbors that have the same color as each node having the color blue, and storing them in the container cooresponding.
			f_human.collect(rt_ind(cor_i_human, cor_j_human));//Collecting the move into forest for human player.
			f_human.associate(b);//Generating the set of "trees" of human player for determing if human player wins.
			
			system("CLS");//Clear the screen.
			//Showing the boqrd updated on the screen.
			cout << "The actual board is as below" << endl;
			cout << "                            " << endl;
			b.show_brd();
			if (f_human.judge_win(dim, "B ", b) == true)break;//Determine if the human wins,if yes, break the loop.


			//AI's turn.
			/////////////////////////////////////////////////////////
			cout << "                            " << endl;
			cout << "AI is thinking...." << endl;//Showing that AI is thinking.
			mov_ai=MC(b, dim, "R");//Executing the monte carlo algorithme and return the index representing the move choosen by AI
			b.move(mov_ai.row, mov_ai.column, "R");//Executing the move on the "board" for AI.
			b.judge_neigh("R ");//Finding the neighbors that have the same color as each node having the color red, and storing them in the container cooresponding.
			f_AI.collect(mov_ai);//Collecting the move into forest for AI.
			f_AI.associate(b);////Generating the set of "trees" of AI for determing if human player wins.
			
			system("CLS");//Clear the screen.
			//Showing the boqrd updated on the screen.
			cout << "The actual board is as below:" << endl;
			cout << "                            " << endl;
			b.show_brd();
			if (f_AI.judge_win(dim, "R ", b) == true)break;//Determine if the AI wins,if yes, break the loop.
		} while (1);// Continuing to play the game until there is a winner.
	}; break;


	//Another version of executing the move, besides the order of game, the other aspects are almost the same.
	case(AI_go_first):
	{
		do {
			//AI's turn
			///////////////////////////////////////////////////////////////
			cout << "AI is thinking...." << endl;
			mov_ai = MC(b, dim, "B");
			b.move(mov_ai.row, mov_ai.column, "B");

			b.judge_neigh("B ");
			f_AI.collect(mov_ai);
			f_AI.associate(b);

			system("CLS");
			cout << "The actual board is as below" << endl;
			cout << "                            " << endl;
			b.show_brd();
			cout << "                            " << endl;

			if (f_AI.judge_win(dim, "B ", b) == true) break;


			//Human player's turn
			///////////////////////////////////////////////////////////////
			cout << "                                        " << endl;
			cout << "          ##################################" << endl;
			cout << "          # Human's move: cord_i  &  cord_j #" << endl;
			cout << "          ##################################" << endl;
			cin >> cor_i_human >> cor_j_human;

			//If human player has chosen a illegal, remind the human player to choose a legal move. 
			if (b.move(cor_i_human, cor_j_human, "R") == true) {}
			else {
				do {
				cout << "                                        " << endl;
				cout << "          ##################################" << endl;
				cout << "          #   Please choose anthoer move   #" << endl;
				cout << "          # Ply1's move: cord_i  &  cord_j #" << endl;
				cout << "          ##################################" << endl;
				cin >> cor_i_human >> cor_j_human;
				} while (b.move(cor_i_human, cor_j_human, "R") != true);
				b.move(cor_i_human, cor_j_human, "R");
			}

			b.judge_neigh("R ");
			f_human.collect(rt_ind(cor_i_human, cor_j_human));
			f_human.associate(b);	


			system("CLS");
			cout << "The actual board is as below:" << endl;
			cout << "                            " << endl;
			b.show_brd();
			if (f_human.judge_win(dim, "R ", b) == true)break;
		} while ( 1);
	}; break;
	}

	//Annoncing who wins in the screen.
	switch (ord_go)
	{
		//If human player goes first, displaying the winner on the screen as the follow way.
	    case(Human_go_first):
		{
			if (f_human.judge_win(dim, "B ", b) == true)
			{
				cout << "B(Human) has won" << endl;
			}
			else if (f_AI.judge_win(dim, "R ", b) == true)
			{
				cout << "R(AI) has won" << endl;
			}
		}; break;
		//If AI goes first, displaying the winner on the screen as the follow way.
		case(AI_go_first):
		{
			if (f_human.judge_win(dim, "R ", b) == true)
			{
				cout << "R(Human) has won" << endl;
			}
			else if (f_AI.judge_win(dim, "B ", b) == true)
			{
				cout << "B(AI) has won" << endl;
			}
		}; break;
	}
}