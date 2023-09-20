GOALS:
1. Functioning Chess Engine in C++
(2). Custom Pieces and Piece Swapping
(3). gold pair of pants

TO DO:
----------rewrite chess constructor so the teams are flipped (moron)
- king everythinng (VERY IN PROGRESS);
	* hardCheck()
		- 1. check how many pieces are checking king
		- 2. find all spaces that are inbetween the king and the attacking pieces
		- 3. put all the spaces from 2. and the spaces the king can move to into an array
		- 4. if 3. array size = 0, checkmate
		- 5. if 3. array size > 0, trim all non 2. moves from the king's team (not the king)
	* softCheck()
		- slider
			* shoot ray out in orth and diag directions
			* if 2 pieces, enemy can't pin
			* if 1 piece is inbetween the enemy and king, softcheck
				- send piece to trimMoves()
	* getCheckmoves(enemy, king)
		- finds all the spaces between enemy and king
	* trimMoves(vector<int> newmoves)
		- trims moves from a piece that don't match newmoves
- checkmate
	
- en passant
	* probably needs to be a 2d array like sightlines but only 2 rows

DONE:
- kingstuff
	* validating king moves; checkKing()
			- move not in enemy sightlines
- piece premoves; getEveryMove()
	* sliders; getSlider()
		- casts ray in both othogonal (n,e,s,w) and diagional (nw,ne,sw,se) directions
		- adds all empty and enemy spaces to piece moves and sightlines list
		- handles:
			* orthagonal (rook)
			* bishop
			* queen
			* king
	* knight; getHopper()
	* pawn; getPawn()
	
- store premoves as vector and 2d array;
- moving pieces; takeTurn()
	* show player all possible moves for a piece; showMoves()
	* get player input; inputPos()
	* decode player input; strtoint()
	* validate movement against premoves; movePiece()
	* update board
- turn clock


NOTES:
to get opposite team do 1-n; 1-1 = 0, 1-0 = 1,
changed teams from teams[0][16], teams[1][16] to teams[2][16]