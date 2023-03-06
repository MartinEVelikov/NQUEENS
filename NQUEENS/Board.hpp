#ifndef BOARD
#define BOARD

class Board {
public:
    Board(int n);
    ~Board();
    Board(const Board&);
    Board& operator=(const Board&);
    void solve();
    bool isPositionOccupiedByQueen(int row, int col) const;
    void Print() const;
    bool isSolved() const;
private:
    int size;
    int* cols;
    int* queensInRow;
    int* queensInMainDiagonal;
    int* queensInSecondaryDiagonal;
    void copy(const Board&);
    void clearAllDynamic();
    void shuffle();
    void addToMainDiagonal(int row, int col, int value);
    void addToSecondaryDiagonal(int row, int col, int value);
    int numberOfConflicts(int row, int col) const;
};
#endif

