#include <iostream>
#include <queue>

#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

using namespace std;

namespace
{
    /* Maze size  */
    const int ROWS = 3; 
    const int COLS = 3;
};


enum maze_result_t
{
    SOLVED = 0,
    NOT_SOLVED,
    INVALID_PARAM
};


struct Cell
{
    int val;
    int row_index; // Row index from 0 to [rows-1]
    int col_index; // Column index from 0 to [cols-1]
};


void set_entrance_and_exit(int** maze, int rows, int cols)
{
    /* Top-left always enter - 1 */
    maze[0][0] = 1;

    /* Bottom-right always exit - 3 */
    maze[rows-1][cols-1] = 3;
}


void fill_maze_by_random_numbers(int** maze, int rows, int cols)
{
    for (auto row = 0; row < 3; row++)
    {
        for (auto col = 0; col < 3; col++)
        {
            maze[row][col] = rand() % 2; // fill cell by 0 or 1
        }
    }
}


void print_maze(int** maze, int rows, int cols)
{
    for (auto row = 0; row < rows; row++)
    {
        for (auto col = 0; col < cols; col++)
        {
            cout << maze[row][col] << " ";
        }
        cout << endl;
    }
}


int check_top_neighbor(int** maze, int row, int col)
{
    if (row == 0)
    {
        return 0;
    }

    return maze[row-1][col];
}


int check_left_neighbor(int** maze, int row, int col)
{
    if (col == 0)
    {
        return 0;
    }

    return maze[row][col-1];
}


int check_bottom_neighbor(int** maze, int row, int col)
{
    if (row == (ROWS - 1))
    {
        return 0;
    }

    return maze[row + 1][col];
}


int check_right_neighbor(int** maze, int row, int col)
{
    if (col == (COLS - 1))
    {
        return 0;
    }

    return maze[row][col+1];
}



maze_result_t check_maze(int** maze, int rows, int cols)
{
    maze_result_t result = NOT_SOLVED;

    if ((!maze) || (rows < 2) || (cols < 2))
    {
        return INVALID_PARAM;
    }

    /* Print maze */
    print_maze(maze, rows, cols);

    /* Queue, where inputting valid (not passed 1) cells */
    std::queue<Cell> cells{};

    /* Top-left always valid, cause it forced to 1*/

    Cell cell;
    cell.val = maze[0][0]; // Always enter, always 1
    cell.row_index = 0;    // First row
    cell.col_index = 0;    // First column
    
    cells.push(cell);

    /* Cycle */

   while(!cells.empty())
   {

       Cell extracted_front_cell = cells.front();   
       
       cout << "Extracted data: val = " << extracted_front_cell.val
        << ", row_index = " << extracted_front_cell.row_index 
        << ", col_index = " << extracted_front_cell.col_index << endl; 

        cells.pop();

        if (extracted_front_cell.val == 3)
        {
            result = SOLVED;
            return result;
        }

        /* Marking passed cells as 9 */
        maze[extracted_front_cell.row_index][extracted_front_cell.col_index] = 9;

        print_maze(maze, rows, cols);

        /* Check top neighbor */

        int top_val = check_top_neighbor(maze,
                                        extracted_front_cell.row_index,
                                        extracted_front_cell.col_index);
        switch(top_val)
        {
            case 3:
            result = SOLVED;
            return result;
            // break;

            case 1:
            Cell cell;
            cell.val = maze[extracted_front_cell.row_index - 1][extracted_front_cell.col_index];
            cell.row_index = (extracted_front_cell.row_index - 1);
            cell.col_index = extracted_front_cell.col_index;
            
            cells.push(cell);
            break;

            default:
            break;
        }

        int left_val = check_left_neighbor(maze,
                                        extracted_front_cell.row_index,
                                        extracted_front_cell.col_index);
        switch(left_val)
        {
            case 3:
                result = SOLVED;
                return result;
                // break;

            case 1:
                Cell cell;
                cell.val = maze[extracted_front_cell.row_index][extracted_front_cell.col_index - 1];
                cell.row_index = (extracted_front_cell.row_index);
                cell.col_index = (extracted_front_cell.col_index - 1);
                
                cells.push(cell);
                break;

            default:
                break;
        }

        int bottom_val = check_bottom_neighbor(maze,
                                        extracted_front_cell.row_index,
                                        extracted_front_cell.col_index);
        switch(bottom_val)
        {
            case 3:
                result = SOLVED;
                return result;
                //break;

            case 1:  
                Cell cell;
                cell.val = maze[extracted_front_cell.row_index + 1][extracted_front_cell.col_index];
                cell.row_index = (extracted_front_cell.row_index + 1);
                cell.col_index = (extracted_front_cell.col_index);
                
                cells.push(cell);
                break;

            default:
                break;
        }

        int right_val = check_right_neighbor(maze,
                                        extracted_front_cell.row_index,
                                        extracted_front_cell.col_index);
        switch(right_val)
        {
            case 3:
                result = SOLVED;
                return result;
                // break;

            case 1:
                Cell cell;
                cell.val = maze[extracted_front_cell.row_index][extracted_front_cell.col_index + 1];
                cell.row_index = (extracted_front_cell.row_index);
                cell.col_index = (extracted_front_cell.col_index + 1);
                
                cells.push(cell);
                break;

            default:
                break;
        }
    }

    /* Result */

    return result;
}


int main()
{
    /* initialize random seed: */
    srand (time(NULL));
    
    int** maze;
    maze = new int*[ROWS];
    for (size_t row = 0; row < ROWS; row++)
    {
        maze[row] = new int[COLS];
    }

    /* Testcases. */

    /* Testcase 1. Pass */

    maze[0][0] = 0;
    maze[0][1] = 1;
    maze[0][2] = 1;
    maze[1][0] = 0;
    maze[1][1] = 1;
    maze[1][2] = 0;
    maze[2][0] = 0;
    maze[2][1] = 1;
    maze[2][2] = 0;
    
    /*
    0 1 1
    0 1 0
    0 1 0
    */
    
    set_entrance_and_exit(maze, ROWS, COLS);

    maze_result_t expected_result = SOLVED;
    maze_result_t tested_result = check_maze(maze, ROWS, COLS);

    if (expected_result == tested_result)
    {
        cout << "Test 1 passed" << endl;
    }
    else
    {
        cout << "Test 1 not passed" << endl;
    }
    
    /* End of Testcase 1 */

    /* Testcase 2. Unable to pass */
    maze[0][0] = 0;
    maze[0][1] = 1;
    maze[0][2] = 1;
    maze[1][0] = 0;
    maze[1][1] = 0;
    maze[1][2] = 0;
    maze[2][0] = 0;
    maze[2][1] = 1;
    maze[2][2] = 0;
    
    /*
    0 1 1
    0 0 0
    0 1 0
    */
    
    set_entrance_and_exit(maze, ROWS, COLS);

    expected_result = NOT_SOLVED;
    tested_result = check_maze(maze, ROWS, COLS);

    if (expected_result == tested_result)
    {
        cout << "Test 2 passed" << endl;
    }
    else
    {
        cout << "Test 2 not passed" << endl;
    }
    
    /* End of Testcase 2 */

    /* Testcase 3. Nullptr */
    expected_result = INVALID_PARAM;
    tested_result = check_maze(nullptr, ROWS, COLS);

    if (expected_result == tested_result)
    {
        cout << "Test 3 passed" << endl;
    }
    else
    {
        cout << "Test 3 not passed" << endl;
    }

    /* End of Testcase 3 */

    /* Testcase 4. Invalid size */

    maze[0][0] = 0;
    maze[0][1] = 1;
    maze[0][2] = 1;
    /*
    0 1 1
    */
    expected_result = INVALID_PARAM;
    tested_result = check_maze(nullptr, 1, COLS);

    if (expected_result == tested_result)
    {
        cout << "Test 4 passed" << endl;
    }
    else
    {
        cout << "Test 4 not passed" << endl;
    }
    /* End of Testcase 4 */

    fill_maze_by_random_numbers(maze, ROWS, COLS);
    
    // set_entrance_and_exit(maze, ROWS, COLS);

    // if (check_maze(maze, ROWS, COLS) == SOLVED)
    // {
    //     cout << "MAZE SOLVED!" << endl;
    // }
    // else
    // {
    //     cout << "MAZE NOT SOLVED!" << endl;         
    // }

    for (size_t row = 0; row < ROWS; row++)
    {
        delete [] maze[row];
    }

    delete [] maze;
    maze = nullptr;

    return 0;
}
