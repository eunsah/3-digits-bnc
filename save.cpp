#include <iostream>
#include <algorithm>
#include <ctime>
#include <deque>
#include <random>
#include <string>

void try_seq(int a, int b, int c){std::cout << "Try number sequence : " << a << " " << b << " " << c << ". " << std::endl;}

int ask(std::string s){
    int boo = 0;
    std::cout << s;
    std::cin >> boo;
    return boo;
}

void get_result(int* right, int* wrong, int* sum){
    // do while sum not in range
    int CORRECT = *right;
    int INCORRECT = *wrong;
    int SUM = *sum;

    do{
        if (SUM > 3 || SUM < 0 || (CORRECT == 2 && INCORRECT == 1)) std::cout << "invalid input !" << std::endl;
        CORRECT = ask("Correct : ");
        INCORRECT = ask("INCORRECT : ");
        SUM = CORRECT+INCORRECT;
    }while(SUM > 3 || SUM < 0 || (CORRECT == 2 && INCORRECT == 1));

    *right = CORRECT;
    *wrong = INCORRECT;
    *sum = SUM;
}

void _3A(){
    std::cout << "Congrats !" << std::endl;
}

void _1A2B(int a, int b, int c){
    std::cout << "There are only 3 possible answers, try" << std::endl;
    std::cout << a << " " << c << " " << b << ", " << std::endl;
    std::cout << c << " " << b << " " << a << ", " << std::endl;
    std::cout << b << " " << a << " " << c << ". " << std::endl;
}

int main(){
    std::srand (unsigned (std::time(0)));
    std::deque<int> dq;
    for (auto i=1; i<10; ++i) dq.push_back(i);
    std::shuffle(dq.begin(), dq.end(), std::default_random_engine(std::time(0)));

    // for (int& i : dq){std::cout << i << std::endl;}

    int CORRECT = 0;
    int INCORRECT = 0;
    int SUM = 0;

    while (true){
        SUM = 0;
        try_seq(dq[0], dq[1], dq[2]);

        get_result(&CORRECT, &INCORRECT, &SUM);

        if (SUM == 3){
            // std::cout << "sum is 3" << std::endl;
            if (CORRECT == 3){
                _3A();
                return 0;
            }
            dq.resize(3); // since the first three numbers are correct, resize deque to 3
            if (CORRECT == 1){
                _1A2B(dq[0], dq[1], dq[2]);
                return 0;
            }
            else{
                // 3B senario, rotate numbers until we find 1A2B || 3A
                dq.push_back(dq[0]);
                dq.pop_front();
            }

        }
        else if (SUM == 0){
            // std::cout << "sum is 0" << std::endl;
            // since all 3 numbers aren't valid, we pop out the first 3 numbers in dq
            dq.pop_front();
            dq.pop_front();
            dq.pop_front();

        }
        else if (SUM == 2){
            // std::cout << "sum is 2" << std::endl;
            if (CORRECT == 2){

            }
            else if (CORRECT == 1){

            }
            else{
                // 2B senario
            }
        }
        else{
            std::cout << "sum is 1" << std::endl;
        }

        // break;
    }

    std::cout << "\ndone!" << std::endl;
    return 0;
}