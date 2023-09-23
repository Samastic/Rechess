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

			/*const Piece* operator=(const Piece* pointer) {
				return pointer;
			}*/



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
		
		//getSlider overload for non-limted pieces
		void const getSlider(Piece&, int);

		//intput:
		//- casts 4 rays in either:
		//	1, Orthogonal
		//	2, Diagonal
		//output:
		//- adds all found spaces to Piece movelist
		//- marks all found spaces in sightlines as 1
		void const getSlider(Piece&, int, int);

		//get horse movement
		void const getHopper(Piece&);

		//finds 1 forward move, and 2 diagonal takes
		void const getPawn(Piece&);

		//removes any of the king's potential moves that are in a sightline
		void const checkKing(Piece&);

		bool const findHit(Piece&, Piece&);

		int const hardCheck(Piece&);
		
		bool const softCheck(Piece&);

		bool const sliderCheck(Piece&);

		bool const hopperCheck(Piece&);

		//AllMove		
		// functions that sets every possible move to each piece a board for each team
		void const getPieceMoves(Piece&);

		void const getEveryMove();		

		//user input
		std::string const inputPos();

		//Processes user input and send calls to move pieces
		void const takeTurn(int);

		//Displays moves from chosen piece
		bool const showMoves(Piece*);

		//- Moves reference to piece on board to chosen state
		//- Sets previous to nullptr
		//- Updates Piece x,y information
		bool const movePiece(Piece*, int B[2]);

		//variable controll
		void const clearSightlines();

		//copies board to boardtemp
		void const setBoardtemp();

		//copies boardtemp to board
		void const setBoard();

		//VARIABLES
		Piece* board[8][8] = { nullptr }; //fills board with nullptr
		Piece* boardtemp[8][8] = { nullptr };

		Piece teams[2][16]; //0 = white, 1 = black
		int sightlines[2][8][8];
		std::vector<int> checkmoves[2], softcheckmoves[2];

		

		
	};
}

#endif