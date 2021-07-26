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

int BitshopW(int ox, int oy, int nx, int ny)
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

int BitshopB(int ox, int oy, int nx, int ny)
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

int BitshopWCheck (int ox, int oy, int Kingx, int Kingy)
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
					//transformation

					//
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
					//pieces movement
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