#include "Board.hpp"
#include <iostream>
#include <chrono>
using namespace std;
int main()
{
    int N;
    cout << "Enter N: ";
    cin >> N;
    Board board(N);
    auto start = std::chrono::high_resolution_clock::now();
    board.solve();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    if (N < 50)
    {
        board.Print();
    }
    cout << "FINISHED!" << endl;
    cout << "Execution Time: " << duration.count() / 1000 << '.' << duration.count() % 1000 << " seconds" << endl;
}