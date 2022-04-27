int Easy_difficulty(node* head)
{
	node* current = head;
	bool Test = true;
	srand(time(0));
	int random_no = rand() % 9 + 1;

	while (Test)
	{
		for (int j = 1; j < random_no; j++)
			current = current->next;
		if (current->data == 'X' || current->data == 'O')
		{
			Test = true;
			srand(time(0));
			random_no = rand() % 9 + 1;
			current = head;
		}
		else
			Test = false;
	}
	return random_no;
}

char gridChar(int i)
{
	switch (i) {
	case -1:
		return 'X';
	case 0:
		return ' ';
	case 1:
		return 'O';
	}
}

void draw(int a[9])
{
	system("CLS");    // to clear screen
	cout << "\n";
	cout << "                ___________________\n";
	cout << "                |  1  |  2  |  3  |  " << endl;
	cout << "                |     |     |     |  " << endl;

	cout << "                |  " << gridChar(a[0]) << "  |  " << gridChar(a[1]) << "  |  " << gridChar(a[2]) << "  |  " << endl;


	cout << "                |_____|_____|_____|" << endl;
	cout << "                |  4  |  5  |  6  |  " << endl;
	cout << "                |     |     |     |  " << endl;


	cout << "                |  " << gridChar(a[3]) << "  |  " << gridChar(a[4]) << "  |  " << gridChar(a[5]) << "  |  " << endl;

	cout << "                |_____|_____|_____|" << endl;
	cout << "                |  7  |  8  |  9  |  " << endl;
	cout << "                |     |     |     |  " << endl;

	cout << "                |  " << gridChar(a[6]) << "  |  " << gridChar(a[7]) << "  |  " << gridChar(a[8]) << "  |  " << endl;
	cout << "                |_____|_____|_____|     " << endl << endl << endl;

}
int win(const int board[9])
{

	//determines if a player has won, returns 0 otherwise.
	unsigned wins[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	int i;
	for (i = 0; i < 8; ++i) {
		if (board[wins[i][0]] != 0 &&
			board[wins[i][0]] == board[wins[i][1]] &&
			board[wins[i][0]] == board[wins[i][2]])
			return board[wins[i][2]];
	}
	return 0;
}

int minimax(int board[9], int player)
{


	//How is the position like for player (their turn) on board?
	int winner = win(board);
	if (winner != 0) return winner * player;

	int move = -1;
	int score = -2;//Losing moves are preferred to no move
	int i;
	for (i = 0; i < 9; ++i) {//For all moves,
		if (board[i] == 0) {//If legal,
			board[i] = player;//Try the move
			int thisScore = -minimax(board, player * -1);
			if (thisScore > score) {
				score = thisScore;
				move = i;
			}//Pick the one that's worst for the opponent
			board[i] = 0;//Reset board after try
		}
	}
	if (move == -1) return 0;
	return score;
}
void computerMove(int board[9])
{
	int move = -1;
	int score = -2;
	int i;
	for (i = 0; i < 9; ++i)
	{
		if (board[i] == 0)
		{
			board[i] = 1;
			int tempScore = -minimax(board, -1);
			board[i] = 0;
			if (tempScore > score) {
				score = tempScore;
				move = i;
			}
		}
	}
	//returns a score based on minimax tree at a given node.
	board[move] = 1;
}

void playerMove(int board[9])
{
	int move;
label1:
	cout << "Please enter a number from 1 to 9: ";
	cin >> move;
	cout << "\n";
	if (move > 9 || move < 1)
	{
		cout << "invalid try againg\n";
		goto label1;
	}
	else if (board[move - 1] == 1)
	{
		cout << "invalid try again\n";
		goto label1;
	}
	else
	{
		board[move - 1] = -1;
	}
}