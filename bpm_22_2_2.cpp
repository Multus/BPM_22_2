#include <cmath>
#include <iostream>
#include <stdexcept>

int main(){
    double count_all = 0;
    double count_nice = 0;
    double x = 0;
    double y = 0;
    while(std::cin){
        std::cin >> x >> y;
        count_all += 1;
        if(y >= std::fabs(x) && y <= 2 - std::pow(x,2)){
            count_nice += 1;
        }
    }
    std::cout << count_nice / count_all;
    return 0;
}
