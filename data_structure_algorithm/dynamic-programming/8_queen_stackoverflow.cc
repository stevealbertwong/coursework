/*
 * Filename     : queens.cpp
 * Author       : Kevin F. 
 * License      : CopyLeft, Feb 2017
 * Eight Queens : Print solutions which have N non-attacking queens placed on NxN chess board
 * Input        : Adjust BOARD_SIZE to change the size of the N
 * Output       : ASCII printed board and runtime statistics
 * Requires     : C++11
 * Compilation  : g++ -std=c++11 -O3 -o queens queens.cpp
 * Source       : http://pastebin.com/qy483BEi
 * Speed        : Found: 92 solutions in: 0.002582 seconds using: 2747 recursions
 * Without Opt  : Found: 92 solutions in: 0.132239 seconds using: 139049 recursions

https://codereview.stackexchange.com/questions/156050/n-queens-recursive-implementation-in-c11

for loop not recursion
*/

#include <algorithm>
#include <iostream>
#include <set>

#define BOARD_SIZE 8

using namespace std;

struct queen_t {
    uint8_t x;
    uint8_t y;
};

static vector< vector<queen_t> > _boards;
static uint32_t _num_recursions;

/* Forward declare for validate_and_continue */
void recurse(vector<queen_t> *board, set<uint8_t> *avail_x,
    set<uint8_t> *avail_y, uint16_t cur_iteration);

void print_board(vector<queen_t> *board){

    /* Sample Output
     *  |12345678
     * 1|xxxxxQxx
     * 2|xxxQxxxx
     * 3|xxxxxxQx
     * 4|Qxxxxxxx
     * 5|xxxxxxxQ
     * 6|xQxxxxxx
     * 7|xxxxQxxx
     * 8|xxQxxxxx
    */

    /* Generate empty board */
    vector<string> rows = {" |"};
    for(int i=1; i <= BOARD_SIZE; i++){
        rows[0].append(to_string(i));
        rows.push_back(to_string(i) + "|" + string(BOARD_SIZE, 'x'));
    }

    /* Fill boards with queens */
    for_each(board->begin(), board->end(), [&](const queen_t queen){
        rows[queen.y].replace(queen.x+1, 1, "Q"); // +1 to skip #|
    });

    for(int i=0; i <= BOARD_SIZE; i++){
        cout << rows[i] << endl;
    }
}

/*
 * Slope can be calculated as rise/run = (Y2-Y1)/(X2-X1)
 * A slope of 1 (perfect diagonal) implies (Y2-Y1) = (X2-X1)
*/
bool diagonal_slope(const queen_t *first_queen, const queen_t *second_queen){

    /* May be sent empty queens */
    if (first_queen->x == 0 || second_queen->x == 0){
        return false;
    }

    return abs(second_queen->y - first_queen->y) == abs(second_queen->x - first_queen->x);
}

/* Return true when new queen(s) trigger a diagonal attack */
bool can_attack(const vector<queen_t> *board, const queen_t *first_queen,
        const  queen_t *second_queen){

    for(const queen_t &queen : *board){
        if (diagonal_slope(first_queen, &queen) == true ||
                diagonal_slope(&queen, second_queen) == true){
            return true;
        }
    }

    return diagonal_slope(first_queen, second_queen);
}

/* If 0..2 queens added are valid, continue recursion */
void validate_and_continue(vector<queen_t> *board, set<uint8_t> *avail_x,
        set<uint8_t> *avail_y, uint16_t cur_iteration,
        queen_t first_queen, queen_t second_queen){

    /* Early prune any entries that produce diagonal attacks */
    if (can_attack(board, &first_queen, &second_queen) == true){
        return;
    }

    /* Update availability lists and create a new board */
    set<uint8_t> new_avail_x = *avail_x;
    set<uint8_t> new_avail_y = *avail_y;
    vector<queen_t> new_board = *board;

    if (first_queen.x != 0){
        new_avail_x.erase(first_queen.x);
        new_avail_y.erase(first_queen.y);
        new_board.push_back(first_queen);
    }

    if (second_queen.x != 0){
        new_avail_x.erase(second_queen.x);
        new_avail_y.erase(second_queen.y);
        new_board.push_back(second_queen);
    }

    /* Recurse with new modified copy of data */
    recurse(&new_board, &new_avail_x, &new_avail_y, cur_iteration + 1);
}

/* Iterate through 1..BOARD_SIZE queens based on X,Y availability lists */
void recurse(vector<queen_t> *board, set<uint8_t> *avail_x,
        set<uint8_t> *avail_y, uint16_t cur_iteration) {

    //cout << "CurIter: " << cur_iteration <<  ", queens placed: " << board->size() << endl;
    _num_recursions ++;

    /* Completion conditions */
    uint16_t queens_left = BOARD_SIZE - board->size();
    if (cur_iteration > BOARD_SIZE){
        if (queens_left == 0) {
            if (avail_x->size() != 0 || avail_y->size() != 0){
                cout << "ERROR: Board is full, but avail lists are non empty!" << endl;
                print_board(board);
                exit(1);
            }else{
                //cout << "Adding solution, recursions so far: " << _num_recursions << endl;
                _boards.push_back(*board);
            }
        }
        return;
    }

    /* Current iteration is now available for X and Y positions */
    avail_x->insert(cur_iteration);
    avail_y->insert(cur_iteration);

    uint16_t rounds_left = BOARD_SIZE - cur_iteration + 1; // including this round
    uint16_t queens_to_add = 0;
    if (queens_left >= (rounds_left * 2)) {
        /* Optimize for perfect 2 and skip 3+ saves ~5000 recursions */
        queens_to_add = ceil((double)queens_left / rounds_left);
    } else if (queens_left > ((rounds_left - 1) * 2)) {
        /* Avoid adding 0 queens this round saves ~500 recursions */
        queens_to_add = 1;
    }

    /* Add 0, 1, or 2 queens this round */
    for (queens_to_add; queens_to_add <= min(queens_left, (uint16_t)2); queens_to_add ++) {
        switch (queens_to_add) {
        case 1:
            /* Possible (X,cur_iteration) pairs */
            for_each(avail_x->begin(), avail_x->end(), [&](const uint8_t cur_x) {
                validate_and_continue(board, avail_x, avail_y,
                    cur_iteration, {cur_x, (uint8_t)cur_iteration}, {});
            });

            /* Possible (cur_iteration,Y) pairs */
            for_each(avail_y->begin(), avail_y->end(), [&](const uint8_t cur_y) {
                /* Equivalent to X = cur_iteration case above */
                if (cur_y == cur_iteration) {
                    return;
                }

                validate_and_continue(board, avail_x, avail_y,
                    cur_iteration, {(uint8_t)cur_iteration, cur_y}, {});
            });
            break;
        case 2:
            /*
             * Example outcomes for cur_iteration = 2
             * x = 1, y = 1... queens 1,2 and 2,1 ** valid
             * x = 1, y = 2....queens 1,2 and 2,2 ** skip in Y
             * x = 2, y = 1... queens 2,2 and 2,1 ** skip in X
             * x = 2, y = 2... queens 2,2 and 2,2 ** skip in X
            */

            for_each(avail_x->begin(), avail_x->end(), [&](const uint8_t cur_x) {
                /* First queen would generate a diagonal */
                if (cur_x == cur_iteration) {
                    return;
                }

                /* Possible (cur_iteration,Y) pairs */
                for_each(avail_y->begin(), avail_y->end(), [&](const uint8_t cur_y) {

                    /* Second queen would generate a diagonal */
                    if (cur_y == cur_iteration) {
                        return;
                    }

                    validate_and_continue(board,
                        avail_x, avail_y, cur_iteration,
                        {cur_x, (uint8_t)cur_iteration},
                        {(uint8_t)cur_iteration, cur_y});
                });
            });
            break;
        default:
            /* Place 0 queens this round, impossible >2 without collision */
            validate_and_continue(board, avail_x, avail_y,
                cur_iteration, {}, {});
            break;
        }
    }
}

int main(int argc, char *argv[]){

    cout << "Calculating solutions..." << endl;

    vector<queen_t> board;
    set<uint8_t> avail_x;
    set<uint8_t> avail_y;
    clock_t start_time = clock();

    /*
    * Recurse through possible outcomes that wont attack in row/column
    * Validate each placed queen against diagonal attacks via slope = 1
    */
    recurse(&board, &avail_x, &avail_y, 1);

    cout << "Found: " << _boards.size() << " solutions in: " <<
        ((double_t)(clock() - start_time)/CLOCKS_PER_SEC) <<
        " seconds using: " << _num_recursions << " recursions" << endl;

    print_board(&(*_boards.begin()));
}