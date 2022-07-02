#include <iostream>
#include<cmath>
#include<conio.h>
using namespace std;

char dimension = 9, sub_dimension = sqrt(dimension);

void print_matrix(char matrix[][16], int dimension)
{
    for(char row = 0; row < dimension; ++row)
    {
        if(row % sub_dimension == 0 && dimension == 9)
            cout << "+-------+-------+-------+\n";
        else if(row % sub_dimension == 0 && dimension == 16)
            cout <<"+---------+---------+---------+---------+\n";
        for(char column = 0; column < dimension; ++column)
        {
            if(column % sub_dimension == 0)
                cout << "| ";
            if(matrix[row][column] == '0')
                cout << "- ";
            else
            {
                if(matrix[row][column] > '0' && matrix[row][column] <= '9')
                    cout << matrix[row][column] << " ";
                else
                {
                    cout <<(char)(matrix[row][column]+7) <<" ";
                }
            }
        }
        cout << "|\n";
    }
    if(dimension == 9)
        cout << "+-------+-------+-------+\n";
    else if(dimension == 16)
        cout <<"+---------+---------+---------+---------+\n";
}

bool place(char matrix[][16], char row, char column, char number)
{
    for(char index = 0; index < dimension; index++)
        if(matrix[index][column] == number || matrix[row][index] == number)
            return false;

    char subx = (row / sub_dimension) * sub_dimension;
    char suby = (column / sub_dimension) * sub_dimension;

    for(char sub_row = 0; sub_row < sub_dimension; sub_row++)
        for(char sub_column = 0; sub_column < sub_dimension; sub_column++)
            if(matrix[sub_row + subx][sub_column + suby] == number)
                return false;
    return true;
}

bool sudoku_solver(char matrix[][16], char row, char column)
{
    if(matrix[row][column] != '0')
        if(column + 1 < dimension)
            return sudoku_solver(matrix, row, column + 1);
        else if(row + 1 < dimension)
            return sudoku_solver(matrix, row + 1, 0);
        else
            return true;
    else
    {
        for(char number = '1'; number < '1' + dimension; number++)
            if(place(matrix, row, column, number))
            {
                matrix[row][column] = number;
                if(column + 1 < dimension)
                {
                    if(sudoku_solver(matrix, row, column + 1))
                        return true;
                }
                else if(row + 1 < dimension)
                {
                    if(sudoku_solver(matrix, row + 1, 0))
                        return true;
                }
                else
                    return true;
            }
        matrix[row][column] = '0';
        return false;
    }
}

int main()
{
    int temp;
    cout <<"Enter the dimentions of the sudoku: ";
    cin >>temp;
    dimension = (char)temp;
    sub_dimension = sqrt(dimension);

    cout <<"The dimentions is : " <<(int)dimension <<endl;

    char matrix[16][16];
    cout << "Enter 0 for empty space: " << endl;
    cout << "Enter the Sudoku: \n";

    for(char row = 0; row < dimension; ++row)
    {
        if(row % sub_dimension == 0 && dimension == 9)
            cout << "+-------+-------+-------+\n";
        else if(row % sub_dimension == 0 && dimension == 16)
            cout <<"+---------+---------+---------+---------+\n";
        for(char column = 0, ch; column < dimension; ++column)
        {
            if(column % sub_dimension == 0)
                cout << "| ";
            ch = getche();
            if((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'G'))
            {
                if(ch >= 'A' && ch <= 'G')
                    ch = ch - 7;
                matrix[row][column] = ch;
            }
            else
            {
                cout <<"Wrong Input !!!";
            }
            cout << " ";
        }
        cout << "|\n";
    }
    if(dimension == 9)
        cout << "+-------+-------+-------+\n";
    else if(dimension == 16)
        cout <<"+---------+---------+---------+---------+\n";

    cout << "\nThe entered Sudoku is: \n";
    print_matrix(matrix, dimension);

    sudoku_solver(matrix, 0, 0);

    cout << "\nThe solved Sudoku is: \n";
    print_matrix(matrix, dimension);
    return 0;
}
