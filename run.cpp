#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>

using namespace std;

bool SHOW_POOL = false;

vector<int> digits;
vector<int> combination;
struct Combo {
    // struct for 3 numbers
    int A;
    int B;
    int C;
};
vector<Combo> possible;
vector<Combo> POOL;
struct not_v {
    vector<int> nA;
    vector<int> nB;
    vector<int> nC;
} NOT_V = {.nA={}, .nB={}, .nC={}};


void go(int offset, int k) {
    vector<int> foo;
    if (k == 0) {
        for (auto i : combination){
            foo.push_back(static_cast<int>(i));
        }
        struct Combo p = {.A=foo[0], .B=foo[1], .C=foo[2]};
        possible.push_back(p);
        return;
    }
    for (int i = offset; i <= digits.size() - k; ++i) {
        combination.push_back(digits[i]);
        go(i+1, k-1);
        combination.pop_back();
    }
}

void basic(){
    Combo foo = {.A=9, .B=1, .C=2};
    POOL.push_back(foo);
    foo = {.A=5, .B=3, .C=4};
    POOL.push_back(foo);
    foo = {.A=8, .B=6, .C=7};
    POOL.push_back(foo);
}

void try_seq(Combo* tar){
    cout << "$ Try number sequence : " << tar->A << " " << tar->B << " " << tar->C << endl;
    }

void POOL_water(bool b){
    if (b){
        cout << "{" ;
    }
    int count = 0;
    auto it = POOL.begin();
    while (it != POOL.end()-1){
        if (b){
            cout << it->A << it->B << it->C << ", ";
        }
        ++it;
        ++count;
        if (count > 510){
            cout << "While loop exceeded 510, escape triggered" << endl;
            return;
            }
    }
    if (b){
        cout << it->A << it->B << it->C << "}" << endl;
    }
}

void POOL_status(bool water){
    cout << ">>> Current POOL size : " << POOL.size() << endl;
    POOL_water(water);
}

int ask(std::string s){
    int boo = 0;
    std::cout << s;
    std::cin >> boo;
    return boo;
}

void get_result(Combo* res){
    // do while sum not in range
        do{
        if (res->C > 3 || res->C < 0 || (res->A == 2 && res->B == 1))
            std::cout << ">>> invalid input !" << std::endl;
        res->A = ask("Correct : ");
        res->B = ask("INCORRECT : ");
        res->C = res->A + res->B;
    }while(res->C > 3 || res->C < 0 || (res->A == 2 && res->B == 1));
}

void UPDATE_CLEARED(){
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            (find(NOT_V.nA.begin(), NOT_V.nA.end(), it->A) != NOT_V.nA.end()) ||
            (find(NOT_V.nB.begin(), NOT_V.nB.end(), it->B) != NOT_V.nB.end()) ||
            (find(NOT_V.nC.begin(), NOT_V.nC.end(), it->C) != NOT_V.nC.end())
        ){
            it = POOL.erase(it);
        }
        else{
            ++it;
        }
    }

}

void CLEAR_SELF(Combo* tar){
    NOT_V.nA.push_back(tar->A);
    NOT_V.nB.push_back(tar->B);
    NOT_V.nC.push_back(tar->C);
}

void CLEAR_OTHERS(Combo* tar){
    NOT_V.nA.push_back(tar->B);
    NOT_V.nA.push_back(tar->C);

    NOT_V.nB.push_back(tar->A);
    NOT_V.nB.push_back(tar->C);

    NOT_V.nC.push_back(tar->A);
    NOT_V.nC.push_back(tar->B);
}

void CLEAR_ALL_NOT_IN(Combo* tar){
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            ((it->A == tar->A) || (it->B == tar->A) || (it->C == tar->A)) &&
            ((it->A == tar->B) || (it->B == tar->B) || (it->C == tar->B)) &&
            ((it->A == tar->C) || (it->B == tar->C) || (it->C == tar->C))
            ){
            it++;
        }
        else {
            it = POOL.erase(it);
        }
    }
    POOL.pop_back();
}

void CLEAR_ALL_WITH(Combo* tar){
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            (it->A == tar->A) || (it->B == tar->A) || (it->C == tar->A) ||
            (it->A == tar->B) || (it->B == tar->B) || (it->C == tar->B) ||
            (it->A == tar->C) || (it->B == tar->C) || (it->C == tar->C)
        ){
            it = POOL.erase(it);
        }
        else {
            it++;
        }
    }
}

void _2A_divider(){
    vector<int> A;
    auto it = POOL.begin();
    while (it != POOL.end()){
        A.push_back(it->A);
        A.push_back(it->B);
        A.push_back(it->C);
        ++it;
    }
    map<int, int> M;
    for (auto at : A){
        if(M.find(at) == M.end()){
            M[at] = 1;
        }
        else{
            M[at]++;
        }
    }
    A.clear();
    for (auto item : M){
        if (item.second == 1)
            A.push_back(item.first);
    }
    shuffle(A.begin(), A.end(), std::default_random_engine(std::time(0)));
    Combo foo = {.A=A[0], .B=A[1], .C=A[2]};
    POOL.push_back(foo);
}

void _3A(){
    cout << "Done" << endl;
}

void _1A_2B(Combo* tar){
    cout << "target is " << tar->A << tar->B << tar->C << endl;
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            (it->A == tar->A && it->B == tar->C && it->C == tar->B) ||
            (it->B == tar->B && it->A == tar->C && it->C == tar->A) ||
            (it->C == tar->C && it->A == tar->B && it->B == tar->A)
        ){
            ++it;
        }
        else{
            it = POOL.erase(it);
        }
    }
}

void _3B(Combo* tar){
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (it->A == tar->A || it->B == tar->B || it->C == tar->C){
            it = POOL.erase(it);
        }
        else{
            ++it;
        }
    }
}

void _2A(Combo* tar){
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            (it->A == tar->A && it->B == tar->B && it->C != tar->C) ||
            (it->A == tar->A && it->C == tar->C && it->B != tar->B) ||
            (it->B == tar->B && it->C == tar->C && it->A != tar->A)
        ){
            ++it;
        }
        else{
            it = POOL.erase(it);
        }
    }
}

void _1A_1B(Combo* tar){
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            (it->A == tar->A && (((it->B == tar->B || it->B == tar->C) && (it->C != tar->B && it->C != tar->C)) || ((it->B != tar->B && it->B != tar->C ) && (it->C == tar->C || it->C == tar->B)))) ||
            (it->B == tar->B && (((it->A == tar->A || it->A == tar->C) && (it->C != tar->A && it->C != tar->C)) || ((it->A != tar->C && it->A != tar->A ) && (it->C == tar->C || it->C == tar->A)))) ||
            (it->C == tar->C && (((it->A == tar->A || it->A == tar->B) && (it->B != tar->A && it->B != tar->B)) || ((it->A != tar->A && it->A != tar->B ) && (it->B == tar->B || it->B == tar->A))))
        ){
            ++it;
        }
        else{
            it = POOL.erase(it);
        }
    }
}

void _2B(Combo* tar){
    CLEAR_SELF(tar);
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            ((it->A == tar->A || it->A == tar->B || it->A == tar->C) && (it->B == tar->B || it->B == tar->A || it->B == tar->C) && (it->C != tar->A && it->C != tar->B && it->C != tar->C)) ||
            ((it->C == tar->C || it->C == tar->B || it->C == tar->A) && (it->B == tar->B || it->B == tar->C || it->B == tar->A) && (it->A != tar->A && it->A != tar->B && it->A != tar->C)) ||
            ((it->A == tar->A || it->A == tar->C || it->A == tar->B) && (it->C == tar->C || it->C == tar->A || it->C == tar->B) && (it->B != tar->A && it->B != tar->B && it->B != tar->C))
        ){
            ++it;
        }
        else{
            it = POOL.erase(it);
        }

    }
}

void _1A(Combo* tar){
    CLEAR_OTHERS(tar);
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            ((it->A == tar->A) && (it->B != tar->B) && (it->C != tar->C) && (it->B != tar->C) && (it->C != tar->B)) ||
            ((it->A != tar->A) && (it->B == tar->B) && (it->C != tar->C) && (it->A != tar->C) && (it->C != tar->A)) ||
            ((it->A != tar->A) && (it->B != tar->B) && (it->C == tar->C) && (it->A != tar->B) && (it->B != tar->A))
        ){
            ++it;
        }
        else{
            it = POOL.erase(it);
        }
    }
}

void _1B(Combo* tar){
    CLEAR_SELF(tar);
    auto it = POOL.begin();
    while (it != POOL.end()){
        if (
            ((it->A != tar->A) && ((it->A == tar->B) || (it->A == tar->C)) && (it->B != tar->A && it->B != tar->B && it->B != tar->C) && (it->C != tar->A && it->C != tar->B && it->C != tar->C)) ||
            ((it->B != tar->B) && ((it->B == tar->A) || (it->B == tar->C)) && (it->A != tar->A && it->A != tar->B && it->A != tar->C) && (it->C != tar->A && it->C != tar->B && it->C != tar->C)) ||
            ((it->C != tar->C) && ((it->C == tar->A) || (it->C == tar->B)) && (it->A != tar->A && it->A != tar->B && it->A != tar->C) && (it->B != tar->A && it->B != tar->B && it->B != tar->C))
        ){
            ++it;
        }
        else{
            it = POOL.erase(it);
        }
    }
}

// -----------------------------------------------------------------------------------------------

int main() {
    // create POOL
    int k = 3;
    for (int i = 0; i < 9; ++i)
        digits.push_back(i+1);
    go(0, k); // all combinations
    for (auto i : possible){ // all permutations
        int thiscombo[] = {i.A, i.B, i.C};
        sort(thiscombo, thiscombo+3);
        do{
            struct Combo p = {.A=thiscombo[0], .B=thiscombo[1], .C=thiscombo[2]};
            POOL.push_back(p);
        }while(next_permutation(thiscombo, thiscombo+3));
    }

    // shuffle POOL
    shuffle(POOL.begin(), POOL.end(), std::default_random_engine(std::time(0)));

    // play game
    int rounds = 0;
    struct Combo result = {.A=0, .B=0, .C=0}; // correct, incorrect, and sum
    Combo target;
    basic();
    bool _2A_div = false;

    // test
    // for (auto i : POOL) cout << i.A << i.B << i.C << endl;

    while (true){
        if (POOL.size() <= 0){
            cout << "Error, no more possible options" << endl;
            return -1;
        }
        if (POOL.size() < 10 && POOL.size() > 2 && _2A_div){
            _2A_divider();
        }
        cout << "Round : " << ++rounds << endl;
        POOL_status(SHOW_POOL);
        target = POOL.back();
        try_seq(&target);// grab last from POOL
        if (POOL.size() == 1){
            cout << "Last possbile answer" << endl;
            return 0;
        }
        get_result(&result);

        if (result.C == 3){
            if (result.A == 3){
                cout << "Done" << endl;
                return 0;
            }
            CLEAR_ALL_NOT_IN(&target);
            if (result.A == 1){
                _1A_2B(&target);
            }
            else{
                _3B(&target);
            }
        }
        else if (result.C  == 0){
            CLEAR_ALL_WITH(&target);
        }
        else if (result.C  == 2){
            if (result.A == 2){
                _2A(&target);
                _2A_div = true;
            }
            else if (result.A == 1){
                _1A_1B(&target);
            }
            else{
                _2B(&target);
            }
        }
        else if (result.C  == 1){
            if (result.A == 1){
                _1A(&target);
            }
            else{
                _1B(&target);
            }
        }
        else{
            cout << "Unexpected error" << endl;
            return -1;
        }
        // break;
        UPDATE_CLEARED();
    }

    cout << "End of main" << endl;
    return 0;
}
