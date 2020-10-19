// Tries to place N Queens on an NxN Chessboard without each of them
// being attacked

// ITERATIVE (BRUTE FORCE) METHOD
// Note: no chessboard array is used! N^2 increase in space is not good lol

// Compile with: gcc 8queens.cpp -o queens -lm -O

#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;

class Queen
{   
    public:
    Queen(){ rowNumber = 0; columnNumber = -1;}
    virtual ~Queen(){}
    bool MoveQueenRight(){ if(++columnNumber < chessBoardSize) return(true); else {columnNumber = -1; return(false);} }
    void ResetQueenToLeft(){ columnNumber = 0; } 
    int GetRow(){ return(rowNumber); }
    int GetColumn(){ return(columnNumber); }
    int GetChessBoardSize() { return(chessBoardSize); }
    void SetRow(int a){ rowNumber = a; }
    void SetColumn(int a){ columnNumber = a; }
    void SetChessBoardSize( int a ){ chessBoardSize = a; } 
    
    private:
    int rowNumber;
    int columnNumber;
    static int chessBoardSize;
};

int Queen::chessBoardSize = 0;
bool IsQueenAttacked(int row, Queen * &Q);
bool PrintQueenPositionsASCI( Queen * &Q, int solutions );
bool PrintQueenPositionsHTML( Queen * &Q, int solutions, bool TorF );



int main( void )
{
    int row = 0, solutions = 0; 
    Queen *pQ = NULL;
    while( true )
    {
        cout << "\nEnter number of Queens (N):";
        cin  >> row;
        if(!isnan(row) &&  row > 1){
            cout << "\nPositions of " << row << "-Queens on an\n" << row <<"-by-" << row << " chessboard will now be found\n";
            break;}
        cout << "\nInput error!\nNumber of Queens should be greater than 1\n .. try again!\n";         
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    if( (pQ = new Queen[row]) == NULL ){
        cout<< "\nCouldnt allocate space for Queens ... exiting programz\n";
        exit(0);}
    //Initialise Queen positions
    pQ[0].SetChessBoardSize( row );
    for( row = pQ[0].GetChessBoardSize() ; row > -1; row--)
        pQ[row].SetRow(row);
    cout << "Chessboard size is " << pQ[0].GetChessBoardSize() <<endl;
    cin.ignore();
    row = 0; /*Start Queen/row*/
    do
    {
        if( pQ[row].MoveQueenRight() )
        {
            if( !IsQueenAttacked(row, pQ) )
            {
                if(row + 1 == pQ[0].GetChessBoardSize())
                {
                    cout << "\nSolution " << ++solutions << " found! ... Writing solution";
                    PrintQueenPositionsASCI(pQ, solutions); 
                    PrintQueenPositionsHTML( pQ, solutions, true);
                    cout << " .. continuing search ..";
                }
                else
                    row++;
            }
            continue;
         }       
        else
            row--;
    } while( pQ[0].GetColumn() > -1 );
    if( solutions > 0)
        PrintQueenPositionsHTML( pQ, solutions, false);
    cout << "\nTotal of " << solutions << " solutions found.\n";
    delete[] pQ;
	   return(0); 
}


// Every Queen is positioned off the board initially
// Results to be printed in HTML file

bool IsQueenAttacked(int row, Queen * &Q)
{
//Check if Queen Q[row] is in the same column or diagonal as previous queens  
    if( Q != NULL )  
        for( int i = row - 1; i > -1; --i  )
            if( Q[row].GetColumn() == Q[i].GetColumn() || ( abs(Q[row].GetColumn() - Q[i].GetColumn()) == abs(Q[row].GetRow() - Q[i].GetRow())) )
                return(true); //Queen is attacked
    return(false); 
}

bool PrintQueenPositionsASCI( Queen * &Q, int solutions )
{
    int row = 0, column = 0, n = 0, colPosition = 0; 
    ofstream fileQueens;
    if( Q != NULL)
    {        
        if( solutions == 1)             
            fileQueens.open("queen_positions.txt", ios::out);
        else
            fileQueens.open("queen_positions.txt", ios::app);
        if( fileQueens.is_open() )
        {  
           if( solutions == 1)
            fileQueens << Q[0].GetChessBoardSize() << " Queens on an " << Q[0].GetChessBoardSize() <<" by " << Q[0].GetChessBoardSize() << " chessboard.\n" <<
              "Reflected and rotationally-symmetric solutions are included below.\n";  
           fileQueens << "\nSolution " << solutions << "\n";
           for( n = Q[0].GetChessBoardSize(), row = 0; row < n ; row++ )
            fileQueens << " _";
           fileQueens << "\n";
           for( row = 0; row < n; row++)
            {
                colPosition = Q[row].GetColumn();
                for(column = 0; column < n; column++)
                {
                    if( colPosition == column )
                        fileQueens << "|Q";
                    else
                        fileQueens << "|_";                    
                }                          
                fileQueens << "|\n";     
            }
            fileQueens << "\n\n";  
            fileQueens.close();
        }
        return(true);
    }
    return(false);
}

bool PrintQueenPositionsHTML( Queen * &Q, int solutions, bool TorF )
{
    int row = 0, column = 0, n = 0, colPosition = 0;
    ofstream fileQueens;
    if( Q != NULL && TorF == true)
    {   
        if( solutions == 1)             
            fileQueens.open("queen_positions.html", ios::out);
        else
            fileQueens.open("queen_positions.html", ios::app);
        if( fileQueens.is_open() )
        {  
           if( solutions == 1)
            {
              fileQueens << "<html>\n<head>\n<style type =\"text/css\">";
              fileQueens << "\ntable {bordercolor=\"#111111\"; padding: 3; spacing: 1; font: 16 Georgia; color: #FF0000; font-weight: bold; }";
              fileQueens << "\nBODY {text-align: left; font-size: 20}";  
              fileQueens << "\ntd {width: 17; text-align: center; vertical-align:middle}";
              fileQueens << "\nh3{color: blue}";
              fileQueens << "\np{font-size:15; color: #CC0066}";
              fileQueens << "\n.bk{background-color: #C0C0C0; text-align: center}";
              fileQueens << "\n</style>\n</head>\n<body>\n";
              fileQueens << "<p>" << Q[0].GetChessBoardSize() << " Queens on an " << Q[0].GetChessBoardSize() <<" by " << Q[0].GetChessBoardSize() << " chessboard.<br>\n" <<
              "Reflected and rotationally-symmetric solutions are included below.</p>\n";  
            }
           fileQueens << "\n<h3>Solution "<< solutions << "</h3>\n<table border = \"4\">\n";
 
           n = Q[0].GetChessBoardSize();
           for( row = 0; row < n; row++)
            {
                colPosition = Q[row].GetColumn();
                fileQueens << "<tr>\n";
                for(column = 0; column < n; column++)
                {
                    fileQueens << "<td";
                    if( (row + column)%2 == 0 ) //Colour the chessbaord
                       fileQueens << " class=\"bk\">";
                    else 
                        fileQueens << ">";
                    if( colPosition == column )
                        fileQueens << "Q";
                    else
                        fileQueens << "&nbsp;";
                    fileQueens << "</td>\n";                    
                }                          
                fileQueens << "</tr>\n";     
            }
            fileQueens << "</table>\n<br>\n";  
            fileQueens.close();
        }
        return(true);
    }
    else
        if( !TorF  )
        {
            fileQueens.open("queen_positions.html", ios::app);
            if( fileQueens.is_open() )
            {
                fileQueens << "\n</body>\n</html>\n\n";
                fileQueens.close();
                return(true);
            }
        }
    return(false);
}
