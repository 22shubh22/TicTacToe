#include <bits/stdc++.h>
#include <ncurses.h>

using namespace std;

class TicTacToe{
    char board[3][3];
public:
    TicTacToe()
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                board[i][j]='-';     
    }
    void display()
    {
        cout << "\033[36m \t1\t2\t3\033[0m\n\n";
        for(int i=0;i<3;i++)
        {
            cout << "\033[36m" << i+1 << "\033[0m\t";
            for(int j=0;j<3;j++)
            {
                cout << board[i][j] << "\t";
            }
            cout << "\n\n";
        }
    }
    void markX(int x, int y)
    {
        board[x-1][y-1] = 'X'; 
    }
    void markO(int x, int y)
    {
        board[x-1][y-1] = 'O';
    }
    bool checkMarking(int x, int y)
    {
        if(x<=3 && x>=1 && y<=3 && y>=1){
            if(board[x-1][y-1]!='-')
            {
                cout << "\033[37m" << "Cannot overwrite a mark. Please retry :)\033[0m\n";
                return false;
            }
            else
            {
                return true;
            }
            
        }
        else
        {
            cout << "\033[37m" << "Please enter correct location :)\033[0m\n";
            return false;
        }
    }
/* If Player 1 wins return 'X', if Player 2 wins return 'O', else return '-' */
    char checkGameState()
    {
        //Check horizontal
        for(int i=0;i<3;i++){
            if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0]!='-')
                return (board[i][0] == 'X') ? 'X' : 'O';
        }

        //Check vertical
        for(int j=0;j<3;j++){
            if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j]!='-')
                return (board[0][j] == 'X') ? 'X' : 'O';
        }

        // 1st diagonal
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0]!='-')
            return (board[0][0] == 'X') ? 'X' : 'O';
        
        //2nd diagonal
        if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='-')
            return board[0][2]=='X' ? 'X' : 'O';

        else
            return '-';
        
    }
};

struct Player{
    string name;
    int points;
};

tuple<int,int> helperTrim(string s){
    vector<int> v;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]<=51 && s[i]>=49)
        {
            v.push_back((int)s[i] - 48);
        }
    }
    
    if(v.size() == 2)
        return make_tuple(v[0],v[1]);
    else
        return make_tuple(0, 0);
    
}

int main()
{
    Player p1,p2;
    cout << "Player 1 (O) select a name\n";
    cin >> p1.name;
    cout << "Player 2 (X) select a name\n";
    cin >> p2.name;

    TicTacToe game = TicTacToe();

    int turn = 0;

    do
    {
        cout << "\033[2J\033[1;1H";
    
        cout << "\033[33mTic-Tac-Toe\033[0m\n";     //May can include blinking text.

        if(turn%2==0)
            cout << "\033[32m" << p1.name <<  "'s (X) turn \033[0m\n";
        else
            cout << "\033[34m" << p2.name <<  "'s (0) turn \033[0m\n";
            
        cout << "\n\n";

        game.display();

        char state = game.checkGameState();
        
        if(state == 'X'){
            cout  << "\033[32m" << p1.name << " (X) wins the game \033[0m\n";
            return 0;
        }
        else if(state == 'Y')
        {
            cout  << "\033[34m" << p2.name << " (O) wins the game \033[0m\n";
            return 0;
        }

        if(turn == 9)
        {
            cout  << "\033[32m Draw \033[0m\n";
            return 0;
        }

        int x=0, y=0;
        cout << "Type 'x y'; x is Row, y is Column : ";

        do
        {
            string tempInput;
            cin >> tempInput;
            do
            {
                tie(x,y) = helperTrim(tempInput);
            }while(x == 0 || y == 0);
            
            //checkMarking() - checks if the game inputs are valid. 
            if(game.checkMarking(x,y))
            {
                (turn%2==0)? game.markX(x, y) : game.markO(x,y);
                turn++;
                break;
            }
        }while(1);

    }while(turn<=9);
    //Fill the X and O's , take input.+
}