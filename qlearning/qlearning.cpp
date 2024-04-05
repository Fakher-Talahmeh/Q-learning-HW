#include <iostream>
#include <string>
#include <cmath>
using namespace std;
const int MATRIX_ROW = 6;
const int MATRIX_COLUMN = 6;
const int STATE_NUM = 6;
const int ACTION_NUM = 6;
const int DES_STATE = 5;
const int MAX_EPISODE = 1000;
const float alpha = 0.8;

double R[100][100] = { {-1, -1, -1, -1, 0, -1},
                     {-1, -1, -1, 0, -1, 100},
                     {-1, -1, -1, 0, -1, -1},
                     {-1, 0, 0, -1, 0, -1},
                     {0, -1, -1, 0, -1, 100},
                     {-1, 0, -1, -1, 0, 100} };
double Q[100][100];
int possible_action[10];
int possible_action_num;
void print_matrix(double m[100][100], int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << ceil(m[i][j]) << "\t";
        }
        cout << endl;
    }
}

void get_possible_action(double R[100][100], int state, int possible_action[10]) {
    possible_action_num = 0;
    for (int i = 0; i < ACTION_NUM; i++) {
        if (R[state][i] >= 0) {
            possible_action[possible_action_num] = i;
            possible_action_num++;
        }
    }
}
double get_max_q(double Q[100][100], int state) {
    double temp_max = 0;
    for (int i = 0; i < ACTION_NUM; ++i) {
        if ((R[state][i] >= 0) && (Q[state][i] > temp_max)) {
            temp_max = Q[state][i];
        }
    }
    return temp_max;
}
int episode_iterator(int init_state, double Q[100][100], double R[100][100]) {

    double Q_before, Q_after;
    int next_action;
    double max_q;
    int step = 0;
    int w = 0;
        while (1) {
        get_possible_action(R, init_state, possible_action);
        next_action = possible_action[rand() % possible_action_num];
        max_q = get_max_q(Q, next_action);
        Q_before = Q[init_state][next_action];
        Q[init_state][next_action] = R[init_state][next_action] + alpha * max_q;
        Q_after = Q[init_state][next_action];
        if (next_action == DES_STATE) {
            init_state = rand() % STATE_NUM;
            break;
        }
        else {
            init_state = next_action;
        }
        step++;
    }
    return init_state;
}

int inference_best_action(int now_state, double Q[100][100]) {
    double temp_max_q = 0;
    int best_action = 0;
    for (int i = 0; i < ACTION_NUM; ++i) {
        if (Q[now_state][i] > temp_max_q) {
            temp_max_q = Q[now_state][i];
            best_action = i;
        }
    }
    return best_action;
}
void run_training(int init_state) {
    int initial_state = init_state;
    for (int i = 0; i < MAX_EPISODE; ++i) {
        initial_state = episode_iterator(initial_state, Q, R);
    }
}

int main() {
    cout << "Q matrix:" << endl;
    print_matrix(Q, 6, 6);
    cout << "R matrix:" << endl;
    print_matrix(R, 6, 6);
    run_training(1);
    cout << "Q convergence matrix:" << endl;
    print_matrix(Q, 6, 6);
    return 0;
}