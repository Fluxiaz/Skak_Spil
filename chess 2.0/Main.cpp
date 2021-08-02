#include <SFML/Graphics.hpp>


// chess game

//defining the board and the pices

#define LENGTH 7
#define BLACK_PAWN 1
#define WHITE_PAWN -1
#define BLACK_ROOK 2
#define WHITE_ROOK -2
#define WHITE_KNIGHT -3
#define BLACK_KNIGHT 3
#define BLACK_BISHOP 4
#define WHITE_BISHOP -4
#define WHITE_QUEEN -5
#define BLACK_QUEEN 5
#define BLACK_KING 6
#define WHITE_KING -6


using namespace sf;

// position of the bricks
struct poz
{
	int x, y;
} oldPoz, whiteKing, blackKing, transformWHITE, transformBLACK;

// creating the board
int size = 100, isMoving;
int board[8][8] =
{
	2, 3, 4, 5, 6, 4, 3, 2,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
   -1,-1,-1,-1,-1,-1,-1,-1,
   -2,-3,-4,-5,-6,-4,-3,-2,
};

int rightWhiteRookM, leftWhiteRookM, whiteKingFirstMove;
int rightBlackRookM, leftBlackRookM, blackKingFirstMove;

int move; // 0 = white is moving, 1 = black is moving

int checkWhite, checkBlack;

int transformationWhite, transformationBlack;

//pieces movement

int PawnW(int ox, int oy, int nx, int ny)//old x,y; new x,y
{
	if (oldPoz.y == 6)
	{
		if ((ny == oy - 1 && ny == ox && board[oy - 1][ox] == 0) || (ny == oy - 2 && nx == ox && board[oy - 2][ox] == 0))
		{
			return 1;
		}
	}
	else if (ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0)
	{
		return 1;
	}
	if (board[oy - 1][ox - 1] > 0)
	{
		if (ny == oy - 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy - 1][ox + 1] > 0)
	{
		if (ny == oy - 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int PawnB(int ox, int oy, int nx, int ny)//old x,y; new x,y
{
	if (oldPoz.y == 6)
	{
		if ((ny == oy + 1 && ny == ox && board[oy + 1][ox] == 0) || (ny == oy + 2 && nx == ox && board[oy + 2][ox] == 0))
		{
			return 1;
		}
	}
	else if (ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0)
	{
		return 1;
	}
	if (board[oy + 1][ox - 1] > 0)
	{
		if (ny == oy + 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] > 0)
	{
		if (ny == oy + 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int RookW(int ox, int oy, int nx, int ny)//old x,y; new x,y
{
	for (int i = ox - 1; i >= 0; i--) //left
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--)// up
	{
		if (board[i][ox] >= 0 && (ny == 1 && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= LENGTH; i++) //to right
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= LENGTH; i++) //down 
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int RookB(int ox, int oy, int nx, int ny)//old x,y; new x,y
{
	for (int i = ox - 1; i >= 0; i--) //left
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--)// up
	{
		if (board[i][ox] <= 0 && (ny == 1 && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= LENGTH; i++) //to right
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= LENGTH; i++) //down 
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int BishopW(int ox, int oy, int nx, int ny)
{

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	int j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;

}

int BishopB(int ox, int oy, int nx, int ny)
{

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	int j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;

}

int QueenW(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) 
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) 
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) 
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) 
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenB(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) 
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) 
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) 
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) 
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) 
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) 
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int KnightW(int ox, int oy, int nx, int ny)
{
	if(oy-2>=0 && ox-1>=0 && ny==oy-2 && nx==ox-1 && board [ny][nx] >=0)
	{
		return 1;
	}
	if(oy -2 >=0 && ox + 1 <= LENGTH && ny == oy -2 && nx == ox + 1 && board [ny] [nx] >=0)
	{
	    return 1;
	}
	if (oy -1 >=0 && ox + 2 <= LENGTH &&  ny == oy -1 && nx == ox +2 && board [ny] [nx] >= 0)
	{
		return 1;
	}
	if (oy +1 <= LENGTH && ox + 2 <=LENGTH && ny == oy +1 && nx == ox +2 && board [ny] [nx] >= 0)
	{
		return 1;
	}
	if ( oy +2 <= LENGTH && ox + 1	<= LENGTH && ny == oy + 2 && nx==ox +1 && board [ny] [nx] >=0)
	{
		return 1;
	}
	if (oy +2 <= LENGTH && ox -1 >= 0 && ny == oy +2 && nx==ox -1 && board[ny] [nx] >=0)
	{
		return 1;
	}
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && ny == oy +1 && nx == ox -2 && board [ny] [nx] >= 0)
	{
		return 1;
	}
	if (oy - 1 >=0 && ox -2 >= 0 && ny == oy - 1 && nx == ox - 2 && board [ny] [nx] >=0)
	{
		return 1;
	}
	return 0;
}

int KnightB (int ox, int oy, int nx, int ny)
{
	if(oy-2>=0 && ox-1>=0 && ny==oy-2 && nx==ox-1 && board [ny][nx] <=0)
	{
		return 1;
	}
	if(oy -2 >=0 && ox + 1 <= LENGTH && ny == oy -2 && nx == ox + 1 && board [ny] [nx] <=0)
	{
	    return 1;
	}
	if (oy -1 >=0 && ox + 2 <= LENGTH &&  ny == oy -1 && nx == ox +2 && board [ny] [nx] <= 0)
	{
		return 1;
	}
	if (oy +1 <= LENGTH && ox + 2 <=LENGTH && ny == oy +1 && nx == ox +2 && board [ny] [nx] <= 0)
	{
		return 1;
	}
	if ( oy +2 <= LENGTH && ox + 1	<= LENGTH && ny == oy + 2 && nx==ox +1 && board [ny] [nx] <=0)
	{
		return 1;
	}
	if (oy +2 <= LENGTH && ox -1 >= 0 && ny == oy +2 && nx==ox -1 && board[ny] [nx] <=0)
	{
		return 1;
	}
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && ny == oy +1 && nx == ox -2 && board [ny] [nx] <= 0)
	{
		return 1;
	}
	if (oy - 1 >=0 && ox -2 >= 0 && ny == oy - 1 && nx == ox - 2 && board [ny] [nx] <=0)
	{
		return 1;
	}
	return 0;
}

int PawnWCheck(int ox, int oy, int Kingx, int Kingy)
{
	if (board [oy - 1][ox - 1] >= 0)
	{
		if (oy - 1 == kingy && ox - 1 == kingx)
		{
			return 1;
		}
	}
	if (board [oy - 1] [ox + 1] >= 0)
	{
		if (oy - 1 == kingy && ox + 1 == kingx)
		{
			return 1;
		}
	}
	return 0;
}

int RookWCheck (int ox, int oy, int Kingx, int Kingy)
for (int i = ox - 1; i >= 0; i--) //left
	{
		if (board[oy][i] >= 0 && (kingx == i && kingy == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--)// up
	{
		if (board[i][ox] >= 0 && (kingy == 1 && kingx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= LENGTH; i++) //to right
	{
		if (board[oy][i] >= 0 && (kingy == oy && kingx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= LENGTH; i++) //down 
	{
		if (board[i][ox] >= 0 && (kingy == i && nx == kingx))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int BishopWCheck (int ox, int oy, int Kingx, int Kingy)
{

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	int j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenWCheck (int ox, int oy, int Kingx, int Kingy)
for (int i = ox - 1; i >= 0; i--) //left
	{
		if (board[oy][i] >= 0 && (kingx == i && kingy == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--)// up
	{
		if (board[i][ox] >= 0 && (kingy == 1 && kingx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= LENGTH; i++) //to right
	{
		if (board[oy][i] >= 0 && (kingy == oy && kingx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= LENGTH; i++) //down 
	{
		if (board[i][ox] >= 0 && (kingy == i && nx == kingx))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	int j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;

}

int KnightWCheck (int ox, int oy, int Kingx, int Kingy)
{
	if(oy-2>=0 && ox-1>=0 && kingy==oy-2 && kingx==ox-1 && board [kingy][kingx] >=0)
	{
		return 1;
	}
	if(oy -2 >=0 && ox + 1 <= LENGTH && kingy == oy -2 && kingx == ox + 1 && board [kingy] [kingx] >=0)
	{
	    return 1;
	}
	if (oy -1 >=0 && ox + 2 <= LENGTH &&  kingy == oy -1 && kingx == ox +2 && board [kingy] [kingx] >= 0)
	{
		return 1;
	}
	if (oy +1 <= LENGTH && ox + 2 <=LENGTH && kingy == oy +1 && kingx == ox +2 && board [kingy] [kingx] >= 0)
	{
		return 1;
	}
	if ( oy +2 <= LENGTH && ox + 1	<= LENGTH && kingy == oy + 2 && kingx==ox +1 && board [kingy] [kingx] >=0)
	{
		return 1;
	}
	if (oy +2 <= LENGTH && ox -1 >= 0 && kingy == oy +2 && kingx==ox -1 && board[kingy] [kingx] >=0)
	{
		return 1;
	}
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && kingy == oy +1 && kingx == ox -2 && board [kingy] [kingx] >= 0)
	{
		return 1;
	}
	if (oy - 1 >=0 && ox -2 >= 0 && kingy == oy - 1 && kingx == ox - 2 && board [kingy] [kingx] >=0)
	{
		return 1;
	}
	return 0;
}

int KingWCheck (int ox, int oy, int Kingx, int Kingy)
{
    if(ox - 1 >= 0 && oy -1 >= 0 && kingy == oy - 1 && kingx == ox - 1 && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if ( oy - 1 >= 0 && kingy == ox && kingy == oy - 1 && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LENGTH && kingx == ox + 1 && kingy == oy - 1 && board[kingy [kingx] <= 0)
	{
		return 1;
	}
	if (ox + 1 <= LENGTH && kingy == oy && kingx == ox + 1 && board[kingy] [kingx] <=0)
	{
		return 1;
	}
	if (ox +1 <= LENGTH && oy + 1 <= LENGTH && kingy == oy +1 && kingx == ox +1 && board [kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (oy + 1 <= LENGTH && kingy == oy + 1 && kingx == ox && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 LENGTH && kingx == ox + 1 && kingy == oy + 1 && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && kingy == oy && kingx == ox - 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	return 0;
}

int PawnBCheck (int ox, int oy, int kingx, int kingy)
{
	if (board[oy + 1 ][ox - 1 ] <= 0)
	{
		if (kingy == oy + 1 && kingx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] <= 0)
	{
		if(kingy == oy + 1 && kingx == ox +1)
		{
			return 1;
		}
	}
	return 0;
}

int RookBCheck (int ox, int oy, int kingx, int kingy)
for (int i = ox - 1; i >= 0; i--) //left
	{
		if (board[oy][i] <= 0 && (kingx == i && kingy == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--)// up
	{
		if (board[i][ox] <= 0 && (kingy == 1 && kingx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= LENGTH; i++) //to right
	{
		if (board[oy][i] <= 0 && (kingy == oy && kingx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= LENGTH; i++) //down 
	{
		if (board[i][ox] <= 0 && (kingy == i && nx == kingx))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int BishopBCheck (int ox, int oy, int Kingx, int Kingy)
{

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	int j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int QueenBCheck (int ox, int oy, int Kingx, int Kingy)
{

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	int j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int KnightBcheck (int ox, int oy, int Kingx, int Kingy)
if(oy-2>=0 && ox-1>=0 && kingy==oy-2 && kingx==ox-1 && board [kingy][kingx] >=0)
	{
		return 1;
	}
	if(oy -2 >=0 && ox + 1 <= LENGTH && kingy == oy -2 && kingx == ox + 1 && board [kingy] [kingx] <=0)
	{
	    return 1;
	}
	if (oy -1 >=0 && ox + 2 <= LENGTH &&  kingy == oy -1 && kingx == ox +2 && board [kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (oy +1 <= LENGTH && ox + 2 <=LENGTH && kingy == oy +1 && kingx == ox +2 && board [kingy] [kingx] <= 0)
	{
		return 1;
	}
	if ( oy +2 <= LENGTH && ox + 1	<= LENGTH && kingy == oy + 2 && kingx==ox +1 && board [kingy] [kingx] <=0)
	{
		return 1;
	}
	if (oy +2 <= LENGTH && ox -1 >= 0 && kingy == oy +2 && kingx==ox -1 && board[kingy] [kingx] <=0)
	{
		return 1;
	}
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && kingy == oy +1 && kingx == ox -2 && board [kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (oy - 1 >=0 && ox -2 >= 0 && kingy == oy - 1 && kingx == ox - 2 && board [kingy] [kingx] <=0)
	{
		return 1;
	}
	return 0;
}

int KingBCheck (int ox, int oy, int Kingx, int Kingy)
{
    if(ox - 1 >= 0 && oy -1 >= 0 && kingy == oy - 1 && kingx == ox - 1 && board[kingy] [kingx] >= 0)
	{
		return 1;
	}
	if ( oy - 1 >= 0 && kingy == ox && kingy == oy - 1 && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LENGTH && kingx == ox + 1 && kingy == oy - 1 && board[kingy [kingx] >= 0)
	{
		return 1;
	}
	if (ox + 1 <= LENGTH && kingy == oy && kingx == ox + 1 && board[kingy] [kingx] <=0)
	{
		return 1;
	}
	if (ox +1 <= LENGTH && oy + 1 <= LENGTH && kingy == oy +1 && kingx == ox +1 && board [kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (oy + 1 <= LENGTH && kingy == oy + 1 && kingx == ox && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 LENGTH && kingx == ox + 1 && kingy == oy + 1 && board[kingy] [kingx] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && kingy == oy && kingx == ox - 1 && board[kingy][kingx] <= 0)
	{
		return 1;
	}
	return 0;
}

int BlackKingCheck(int posKingx, int posKingy)
{
	int ok = 0;
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j=0; j <= LENGTH: j++)
		{
			if (board[i][j] <= 0) {
					
					if (board[i][j] == WHITE_PAWN)
					{
						ok = PawnWCheck(j, i, posKingx, posKingy);
					}
					if (board[i][j] == WHITE_ROOK)
					{
						ok = RookWCheck(j, i, posKingx, posKingy);
					}
					
					if (board[i][j] == WHITE_KNIGHT)
					{
						ok = KnightWCheck(j, i, posKingx, posKingy);
					}
				
					if (board[i][j] == WHITE_BISHOP )
					{
						ok = BishopWCheck(j, i, posKingx, posKingy);
					}
					
					if (board[i][j] == WHITE_QUEEN )
					{
					    ok = QueenWCheck(j, i, posKingx, posKingy);
					}
					
					if (board[i][j] == WHITE_KING )
					{
						ok = KingWCheck(j, i, posKingx, posKingy);
					}
					if (ok == 1)
					{
						return 0;
					}
			}
			return 0;
		}
		
	}
}

int BlackKing (int ox, int oy, int nx, int ny)
{
    if(ox - 1 >= 0 && oy -1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny] [nx] >= 0)
	{
	    int ok = BlackKingCheck(ox - 1, oy - 1);
		if (ok==1)
		{
			return 1;
		}
		
	}
	if ( oy - 1 >= 0 && ny == ox && ny == oy - 1 && board[ny] [nx] <= 0)
	{
	    int ok = BlackKingCheck(ox, oy - 1);
		if(ok == 1)
	    {
			return 1;
		}
		
	}
	if (oy - 1 >= 0 && ox + 1 < LENGTH && nx == ox + 1 && ny == oy - 1 && board[ny [nx] >= 0)
	{
	    int ok = BlackKingCheck(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1;
		}
		
	}
	if (ox + 1 <= LENGTH && ny == oy && nx == ox + 1 && board[ny] [nx] <=0)
	{
	    int ok = BlackKingCheck(ox + 1, oy);
		if (ok== 1)
		{
			return 1;
		}
		
	}
	if (ox +1 <= LENGTH && oy + 1 <= LENGTH && ny == oy +1 && nx == ox +1 && board [ny] [nx] <= 0)
	{
		int ok = BlackKingCheck(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (oy + 1 <= LENGTH && ny == oy + 1 && nx == ox && board[ny] [nx] <= 0)
	{
		int ok = BlackKingCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (ox - 1 >= 0 && oy + 1 LENGTH && nx == ox + 1 && ny == oy + 1 && board[ny] [nx] <= 0)
	{
		int ok = BlackKingCheck(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKing(ox - 1, oy);
		if (ok == 1)
		{
			return 1;
		}
	}
	if(rightBlackRookM==0 && blackKingFirstMove==0 && board[0][5]==0 && board[0][6]==0 && ny==0 && ny==6)
	{
	     int ok = BlackKingCheck(4, 0);
		 if (ok == 1)
		 {
			  ok = BlackKingCheck(5, 0);
			  if (ok == 1)
			  {
					ok = BlackKingCheck(6, 0);
					if (ok == 1)
					{
						blackKingFirstMove = 1;
						rightBlackRookM = 1;
						board[0][7] = 0;
						board[0][5] = BLACK_ROOK;
						return 1;
					}
			  }
		 }
	}
	if(leftBlackRookM==0 && blackKingFirstMove==0 && board[0] [3]== 0 && board [0][2]== 0 && board[0][1]==0 && ny==0 && nx==2)
	{
		int ok = BlackKingCheck(4, 0);
		if (ok == 1)
		{
			ok = BlackKingCheck(3, 0);
			if (ok == 1)
			{
				ok BlackKingCheck(2, 0);
				if (ok == 1)
				{
					ok = BlackKingCheck(1, 0);
					if (ok == 1)
					{
						blackKingFirstMove = 1;
						leftBlackRookM = 1;
						board[0][0] = 0;
						board[0][3] = BLACK_ROOK;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int WhiteKingCheck (int posKingx, int posKingy)
{
	int ok = 0;
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if(board[i][j] > 0)
			{
				if (board[i][j] == BLACK_PAWN)
				{
					ok = PawnBCheck(j, i, posKingx, posKingy);
				}

				if (board[i][j] == BLACK_ROOK)
				{
					 ok = RookBCheck(j, i, posKingx, posKingy);
				}
					
				if (board[i][j] == BLACK_KNIGHT)
				{
					ok = KnightBcheck(j, i, posKingx, posKingy);
				}
				
				if (board[i][j] == BLACK_BISHOP)
				{
					ok = BishopBCheck(j, i, posKingx, posKingy);
				}
				
		    	if (board[i][j] == BLACK_QUEEN)
				{
					ok = QueenBCheck(j, i, posKingx, posKingy);
				}
			
				if (board[i][j] == BLACK_KING)
				{
					ok = KingBCheck(j, i, posKingx, posKingy);
				}
				if ( ok == 1)
				{
					return 0;
				}
			}
		}
	}
	retun 1;
}

int whiteKing (int ox, int oy, int nx, int ny)
{
	if(ox - 1 >= 0 && oy -1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny] [nx] >= 0)
	{
	    int ok = WhiteKingCheck(ox - 1, oy - 1);
		if (ok==1)
		{
			return 1;
		}
		
	}
	if ( oy - 1 >= 0 && ny == ox && ny == oy - 1 && board[ny] [nx] >= 0)
	{
	    int ok = WhiteKingCheck(ox, oy - 1);
		if(ok == 1)
	    {
			return 1;
		}
		
	}
	if (oy - 1 >= 0 && ox + 1 < LENGTH && nx == ox + 1 && ny == oy - 1 && board[ny [nx] >= 0)
	{
	    int ok = WhiteKingCheck(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1;
		}
		
	}
	if (ox + 1 <= LENGTH && ny == oy && nx == ox + 1 && board[ny] [nx] >=0)
	{
	    int ok = WhiteKingCheck(ox + 1, oy);
		if (ok== 1)
		{
			return 1;
		}
		
	}
	if (ox +1 <= LENGTH && oy + 1 <= LENGTH && ny == oy +1 && nx == ox +1 && board [ny] [nx] >= 0)
	{
		int ok = WhiteKingCheck(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (oy + 1 <= LENGTH && ny == oy + 1 && nx == ox && board[ny] [nx] >= 0)
	{
		int ok = WhiteKingCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (ox - 1 >= 0 && oy + 1 LENGTH && nx == ox + 1 && ny == oy + 1 && board[ny] [nx] >= 0)
	{
		int ok = WhiteKingCheck(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKing(ox - 1, oy);
		if (ok == 1)
		{
			return 1;
		}
	}
	if (whiteKingFirstMove==0 && rightWhiteRookM == 0 && board [7][6]==0 && board[7][6]== 0 && ny==7 && nx==6)
	{
		int ok = WhiteKingCheck(4,7);
		if (ok == 1)
		{
			ok = WhiteKingCheck(5, 7);
			if(ok == 1)
			{
				ok = WhiteKingCheck(6, 7);
				if (ok == 1)
				{
					board[7][7] = 0;
					board[7][5] = WHITE_ROOK;
					whiteKingFirstMove = 1;
					rightWhiteRookM = 1;
					return 1;
				}
			}
		}
	}
	if (whiteKingFirstMove==0 && rightWhiteRookM==0 && board[7][3]==0 && board[7][2]==0 && board[7][1]==0 && ny==7 nx==2)
	{
		int ok = WhiteKingCheck(4,7);
		if (ok == 1)
		{
			ok = WhiteKingCheck(3, 7);
			if(ok == 1)
			{
				ok = WhiteKingCheck(2, 7);
				if (ok == 1)
				{
					ok = WhiteKingCheck(1, 7);
					if (ok == 1)
					{
					board[7][0] = 0;
					board[7][3] = WHITE_ROOK;
					whiteKingFirstMove = 1;
					leftWhiteRookM = 1;
					return 1;
				    }
					
				}
				
			}
		}
	}
	return 0;
}

void posWhiteKing()
{
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if (board[i][j] == WHITE_KING)
			{
				whiteKing.x = j;
				WhiteKing.y = i;
				break;
			}
		}
	}
}

void posBlackKing()
{  
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if (board[i][j] == BLACK_KING)
			{
				blackKing.x = j;
				blackKing.y = i;
				break;
			}
		}
	}
}


//loading in the textures of the board and pices
int main()
{
	RenderWindow window(VideoMode(800, 800), "skak spil");
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/Black_Pawn.png");
	t3.loadFromFile("images/White_Pawn.png");
	t4.loadFromFile("images/White_Rook.png");
	t5.loadFromFile("images/Black_Rook.png");
	t6.loadFromFile("images/White_Knight.png");
	t7.loadFromFile("images/Black_knight.png");
	t8.loadFromFile("images/White_Bishop.png");
	t9.loadFromFile("images/Black_Bishop.png");
	t10.loadFromFile("images/White_Queen.png");
	t11.loadFromFile("images/Black_Queen.png");
	t12.loadFromFile("images/Black_King.png");
	t13.loadFromFile("images/White_King.png");
	t14.loadFromFile("images/TransformationWhite.png");
	t15.loadFromFile("images/TransformationBlack.png");

	Sprite Table(t1);
	Sprite BlackPawn(t2);
	Sprite WhitePawn(t3);
	Sprite WhiteRook(t4);
	Sprite BlackRook(t5);
	Sprite Whiteknight(t6);
	Sprite BlackKnight(t7);
	Sprite WhiteBishop(t8);
	Sprite BlackBishop(t9);
	Sprite WhiteQueen(t10);
	Sprite BlackQueen(t11);
	Sprite BlackKing(t12);
	Sprite WhiteKing(t13);
	Sprite WhiteTransformation(t14);
	Sprite BlackTransformation(t15);
	Sprite MoveImages;

	//moving the pices

	float dx = 0, dy = 0;
	int noMovedpiece = 0;

	while (window.isOpen()) {
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / size;
		int y = pos.y / size;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (TransformationWhite == 1)
					{
						if(pos.y>=transformWHITE.y*size && pos.y <=( transformWHITE.y+1)*size && pos.x >=transformWHITE.x*size && pos.x<=(transformWHITE.x+1)*size)
						{
							int xx == pos.x % size, yy = pos.y % size;
							if (xx < 50 && yy < 50 && xx>0 && yy<0)
							{
								board[transformWHITE.y][transformWHITE.x] = WHITE_ROOK;
								transformationWhite = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[transformWHITE.y][transformWHITE.x] = WHITE_KNIGHT;
								transformationWhite = 0;
							}
							if (xx < 50 && xx > 100 && yy>50 && yy < 100)
							{
								board[transformWHITE.y][transformWHITE.x] = WHITE_BISHOP;
								transformationWhite = 0;
							}
							if (transformationWhite == 0)
							{
								posBlackKing();
								int h = BlackKingCheck(blackKing.x, blackKing.y);
								if (h == 0)
								{
									checkBlack = 1;
								}

							}
						}
					}
					
					if (transformationBlack == 1)
					{
						if (pos.y>= transformBLACK.y*size && pos.y<=(transformBLACK.y+1)*size && pos.x>= transformBLACK.x*size && pos.x<=(transformBLACK.x+1)*size )
						{
							int xx = pos.x % size, yy = pos.y % size;
							if (xx < 50 && yy < 50 && xx>0 && yy>0)
							{
								board[transformBlack.y][transformBlack.x] = BLACK_ROOK;
								transformationBlack = 0;
							}
							if (xx > 50 && xx <100 && yy < 50 && yy >0)
							{
								board[transformBlack.y][transformBlack.x] = BLACK_QUEEN;
								transformationBlack = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy <100)
							{
								board[transformBlack.y][transformBlack.x] = BLACK_KNIGHT;
								transformationBlack = 0;
							}
							if ( xx < 50 && xx>0 && yy > 50 && yy < 100)
							{
								board[transformBlack.y][transformBlack.x] = BLACK_BISHOP;
								transformationBlack = 0;
							}
							if (transformationBlack == 0)
							{
								posWhiteKing();
								int h = WhiteKingCheck(whiteKing.x, whiteKing.y);
								if (h == 1)
								{
									checkWhite = 1;
								}
							}
						}
					}

					if (board[y][x] != 0)
					{
						dx = pos.x - x * size;
						dy = pos.y - y * size;

						if (board[y][x] == BLACK_PAWN && move == 1)
						{
							noMovedpiece = BLACK_PAWN;
							MoveImages = BlackPawn;
							board[y][x] = 0;
						}

						if (board[y][x] == WHITE_PAWN && move == 0)
						{
							noMovedpiece = WHITE_PAWN;
							MoveImages = WhitePawn;
							board[y][x] = 0;
						}
						if (board[y][x] == WHITE_ROOK && move == 0)
						{
							noMovedpiece = WHITE_ROOK;
							MoveImages = WhiteRook;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_ROOK && move == 1)
						{
							noMovedpiece = BLACK_ROOK;
							MoveImages = BlackRook;
							board[y][x] = 0;
						}
						if (board[y][x] == WHITE_KNIGHT && move == 0)
						{
							noMovedpiece = WHITE_KNIGHT;
							MoveImages = Whiteknight;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_KNIGHT && move == 1)
						{
							noMovedpiece = BLACK_KNIGHT;
							MoveImages = BlackKnight;
							board[y][x] = 0;
						}
						if (board[y][x] == WHITE_BISHOP && move == 0)
						{
							noMovedpiece = WHITE_BISHOP;
							MoveImages = WhiteBishop;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_BISHOP && move == 1)
						{
							noMovedpiece = BLACK_BISHOP;
							MoveImages = BlackBishop;
							board[y][x] = 0;
						}
						if (board[y][x] == WHITE_QUEEN && move == 0)
						{
							noMovedpiece = WHITE_QUEEN;
							MoveImages = WhiteQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_QUEEN && move == 1)
						{
							noMovedpiece = BLACK_QUEEN;
							MoveImages = BlackQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == WHITE_KING && move == 0)
						{
							noMovedpiece = WHITE_KING;
							MoveImages = WhiteKing;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_KING && move == 1)
						{
							noMovedpiece = BLACK_KING;
							MoveImages = BlackKing;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							isMoving = 1;
							oldPoz.x = x;
							oldPoz.y = y;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
				{
					int ok;
					if (noMovedpiece == WHITE_PAWN && isMoving == 1)
					{
						ok = PawnW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == BLACK_PAWN && isMoving == 1)
					{
						ok = PawnB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == WHITE_ROOK && isMoving == 1)
					{
						ok = RookW(oldPoz.x, oldPoz.y, x, y);;
						if ( ok == 1 && leftWhiteRookM == 0 && oldPoz.y == 7 && oldPoz.x == 0)
						{
							leftBlackRookM = 1;
						}
						if (ok == 1 && rightWhiteRookM==0 && oldPoz.y == 7 && oldPoz.x == 7)
						{
							rightWhiteRookM = 1;
						}
					}
					if (noMovedpiece == BLACK_ROOK && isMoving == 1)
					{
						ok = RookB(oldPoz.x, oldPoz.y, x, y);;
						if ( ok == 1 && rightBlackRookM == 0 && oldPoz.y == 0 && oldPoz.x == 7)
						{
							rightBlackRookM = 1;
						}
						if (ok == 1 && leftBlackRookM==0 && oldPoz.y == 0 && oldPoz.x == 0)
						{
							leftBlackRookM = 1;
						}
					}
					if (noMovedpiece == WHITE_BISHOP && isMoving == 1)
					{
						ok = BishopW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == BLACK_BISHOP && isMoving == 1)
					{
						ok = BishopB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == WHITE_QUEEN && isMoving == 1)
					{
						ok = QueenW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == BLACK_QUEEN && isMoving == 1)
					{
						ok = QueenB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == WHITE_KNIGHT && isMoving == 1)
					{
						ok = KnightW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == BLACK_KNIGHT && isMoving == 1)
					{
						ok = KnightB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedpiece == BLACK_KING && isMoving == 1)
					{
						ok = BlackKing(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && blackKingFirstMove==0)
						{
							blackKingFirstMove = 1;
						}
					}
					if (noMovedpiece == WHITE_KING && isMoving == 1)
					{
						ok = WhiteKing(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && whiteKingFirstMove==0)
						{
							whiteKingFirstMove = 1;
						}
					}
					if (y == 0 && noMovedpiece == WHITE_PAWN)
					{
						transformationWhite = 1;
						transformWHITE.x = x;
						transformWHITE.y = y;
						board[y][x] = 0;
					}
					if (y == 0 && noMovedpiece == BLACK_PAWN)
					{
						transformationBlack = 1;
						transformBLACK.x = x;
						transformBLACK.y = y;
						board[y][x] = 0;
					}
					if (move == 0)
					{
						if (checkWhite == 1)
						{
							posWhiteKing();
							int s = WhiteKingCheck(whiteKing.x, whiteKing.y);
							if (s == 0)
							{
								board[oldPoz.y][oldPoz.x] = noMovedpiece;
								board[y][x] = nr;
							}
							else
							{
								checkWhite = 0;
								posBlackKing();
								int check = BlackKingCheck(blackKing.x, blackKing.y);
								if (check == 0)
								{
									checkBlack = 1;
								}
								move = 1;
							}
							else
							{
							    posWhiteKing();
								int sa = WhiteKingCheck(whiteKing.x, whiteKing.y);
								if (sa == 0 )
								{
									board[oldPoz.y][oldPoz.x] = noMovedpiece;
									board[y][x] = nr;
								}
								else
								{
								   posBlackKing();
								   int check = BlackKingCheck(blackKing.x, blackKing.y);
								   if( check == 0)
								   {
									 checkBlack = 1;
								   }
								   move = 1;
								}
							}
						}
						else
						{
							if(checkBlack==1)
							{
								int s = BlackKingCheck(blackKing.x, blackKing.y);
								if (s == 0)
								{
									board[oldPoz.y][oldPoz.x] = noMovedpiece;
									board[y][x] = nr;
								}
								else
								{
									checkBlack = 0;
									posWhiteKing();
									int check = WhiteKingCheck(whiteKing.x, whiteKing.y);
									if (check == 0)
									{
										checkWhite = 1;
									}
									move = 0;
								}
							}
							else
							{
								posBlackKing();
								int sa = BlackKingCheck(blackKing.x, blackKing.y);
								if (sa == 0)
								{
									board[oldPoz.y][oldPoz.x] = noMovedpiece;
									board[y][x] = nr;
								}
								else
								{
								    posWhiteKing();
									int check= WhiteKingCheck(whiteKing.x, WhiteKing.y);
									if (check == 0)
									{
										checkWhite = 1;  
									}
									move = 0;
								}
							}
						}
					}
					else if (ok == 0)
					{
					  board[oldPoz.y][oldPoz.x] = noMovedpiece;
					}
					isMoving = 0;

				}
			}
		}
		window.clear();
		window.draw(Table);
		if (transformationWhite == 1)
		{
			WhiteTransformation.setPosition(transformWHITE.x* size, transformBLACK.y* size);
			window.draw(WhiteTransformation);
		}
		if (transformationBlack == 1)
		{
			WhiteTransformation.setPosition(transformBLACK.x * size, transformWHITE.y * size);
			window.draw(BlackTransformation);
		}
		if (isMoving == 1)
		{
			MoveImages.setPosition(pos.x - dx, pos.y - dy);
			window.draw(MoveImages);
		}
		//table

		for (int i = 0; i <= LENGTH; i++)
		{
			for (int j = 0; j <= LENGTH; j++)
			{
				if (board[i][j] != 0) {
					if (board[i][j] == BLACK_PAWN)
					{
						BlackPawn.setPosition(j* size, i* size);
					    window.draw(BlackPawn);
					}

					if (board[i][j] == WHITE_PAWN)
					{
						WhitePawn.setPosition(j* size, i* size);
						window.draw(WhitePawn);
					}
					if (board[i][j] == WHITE_ROOK)
					{
						WhiteRook.setPosition(j* size, i* size);
						window.draw(WhiteRook);
					}
					if (board[i][j] == BLACK_ROOK)
					{
						BlackRook.setPosition(j* size, i* size);
						window.draw(BlackRook);
					}
					if (board[i][j] == WHITE_KNIGHT)
					{
						Whiteknight.setPosition(j* size, i* size);
						window.draw(Whiteknight);
					}
					if (board[i][j] == BLACK_KNIGHT)
					{
						BlackKnight.setPosition(j* size, i* size);
						window.draw(BlackKnight);
					}
					if (board[i][j] == WHITE_BISHOP )
					{
						WhiteBishop.setPosition(j* size, i* size);
						window.draw(WhiteBishop);
					}
					if (board[i][j] == BLACK_BISHOP)
					{
						BlackBishop.setPosition(j* size, i* size);
						window.draw(BlackBishop);
					}
					if (board[i][j] == WHITE_QUEEN )
					{
						WhiteQueen.setPosition(j* size, i* size);
						window.draw(WhiteQueen);
					}
					if (board[i][j] == BLACK_QUEEN)
					{
						BlackQueen.setPosition(j* size, i* size);
						window.draw(BlackQueen);
					}
					if (board[i][j] == WHITE_KING )
					{
						WhiteKing.setPosition(j* size, i* size);
						window.draw(WhiteKing);
					}
					if (board[i][j] == BLACK_KING)
					{
						BlackKing.setPosition(j* size, i* size);
						window.draw(BlackKing);
					}
			  }
			}
		} 
		window.display();
	}
	return 0;
}