#ifndef RECHESS_H
#define RECHESS_H

#include <iomanip>
#include <vector>
#include <string>

/*
Piece types:
K - king
Q - queen
R - rook
B - bishop
N - knight
P - pawn

*/

namespace rechess {


	class Piece {
	public:
		//constructors
			Piece();
			Piece(int team_in, char type_in, int Xpos_in, int Ypos_in, int Tpos_in);
		//getters & setters
			int const getTeam();
			void const setTeam(int);

			char const getType();
			void const setType(char);

			int const getStatus();
			void const setStatus(int);

			int const getXpos();
			void const setXpos(int);

			int const getYpos();
			void const setYpos(int);

			int const getTpos();
			void const setTpos(int);
		
		//moves vector manipulation
			void const clearMoves();
			void const addMove(int, int);
			int const sizeofMoves();
			int const getMove(int);
			void const eraseMove(int, int);

		//operators
			//sets one piece queal to another
			void operator=(const Piece& unit) {
				team = unit.team;
				type = unit.type;
				Xpos = unit.Xpos;
				Ypos = unit.Ypos;
				Tpos = unit.Tpos;
				status = unit.status;
			}

			const Piece* operator=(const Piece* pointer) {
				return pointer;
			}



	private:
		int team; //0 white, 1 black
		char type; //piece type, see header
		int status; //0 = neutral, 1 = protected, 2 = king in check
		int Xpos; //x coord on board
		int Ypos; //y coord on board
		int Tpos; //position in teams[2][16]
		std::vector<int> moves; //list of all potential moves of a piece, where [0] = x, and [1] = y, and so on
	};

	class Chess {
	public:
		//constructor
		Chess();

		//print board to console from teams[0] POV
		void const display();

		//startgame
		void const startGame();

	private:
		//FUNCTIONS
		//board setters
		void const setBoardtemp();
			
		void const setBoard();
		
		//piece getters
		void const getSlider(Piece&, int);

		void const getSlider(Piece&, int, int);

		void const getHopper(Piece&);

		void const getPawn(Piece&);

		void const checkKing(Piece&);

		//AllMove		
		// functions that sets every possible move to each piece a board for each team
		void const addtoAllMoves(Piece&);

		void const getAllMoves();		

		//user input
		std::string const inputPos();

		//user movement functions
		bool const showMoves(Piece*);

		bool const movePiece(Piece*, int B[2]);

		//turn system
		void const takeTurn(int);

		//variable controll
		void const clearAllmoves();


		//VARIABLES
		Piece* board[8][8] = { nullptr };
							/*  {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
								{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
								};*/
		Piece* boardtemp[8][8] = { nullptr };
		Piece teams[2][16];
		//Piece teams[0][16];			
		//Piece teams[1][16];
		int allmoves[2][8][8];
		std::vector<int> checkmoves[2];

		
	};
}

#endif