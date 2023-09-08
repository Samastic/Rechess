GOALS:
1. Functioning Chess Engine in C++
(2). Custom Pieces and Piece Swapping
(3). gold pair of pants

TO DO:
----------rewrite chess constructor so the teams are flipped (moron)
- turn logic
	- king everythinng; getKing()
		a. validating king moves
			i. not in enemy sightlines
		b. check and protecting the king; 
			1. run through every move and see if any match the square the B king is on, if it is, find W piece
			2. if there are 2 W pieces checking the king:
				i. **the game is over**
			3. if there is 1 white piece checking the king:
				ii. find all moves inbetween W piece and B king
					+ add to array of vectors, checkmoves[#]
						https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/
				iii. find all B pieces that can move to ii spaces, and all the spaces the king can move
					+ record piece address and move location
				iv. if when in check, all the moves from iii are 0, **the game is over**
				v. force player to pick a piece from the iii list
				v. flag protection = true
		c. 	pinning (softcheck);
			i. shoot out ray in every direction from the king, distinguish direction by type
			ii. record tiles that have been gone over, discard if no enemy is found
			iii. record if it hits a piece
				+ it should not be an enemy first. this function is to find enemy pieces that are indirectly hitting the king.
			iv. if a friendly piece is hit before an enemy, and the piece matches the direction type,
				the friendly is flagged protection = true;
		d. checkPinmoves()
			i. function turns on if protection is true
			ii. deletes any move that isn't on the checkmoves list
		e. protection flag for every other piece
	- turn clock
	- a pinned piece's movement, moveCheck()
		i. checks to see if a move is in the available moves during check
	- checkmate

	
- en passant
	\\ probably needs to be a 2d array like allmoves but only 2 rows

DONE:
- piece premoves; getAllMoves()
	+ sliders; getSlider()
		* rook
		* bishop
		* queen
		* king
	+ knight; getHopper()
	+ pawn; getPawn()
	
- store premoves as vector and 2d array;
- moving pieces; takeTurn()
	+ show player all possible moves for a piece; showMoves()
	+ get player input; inputPos()
	+ decode player input; strtoint()
	+ validate movement against premoves; movePiece()
	+ update board


NOTES:
to get opposite team do 1-n; 1-1 = 0, 1-0 = 1,
changed teams from teams[0][16], teams[1][16] to teams[2][16]