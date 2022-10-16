// Example program
#include <iostream>
 
bool year(int num){
    int one = floor(num / 1000);
    int two = floor(num / 100) - one * 10;
    int three = floor(num / 10) - one * 100 - two * 10;
    int four = num - one * 1000 - two * 100 - three * 10;
    if (one == two || one == three || one == four || two == three || two == four || three == four){
        return false;
    }
    else{
    return true;
    }
}
int main()
{
    int w = 0;
    std::cin >> w;
    w++;
    while (!year(w)){
        w++;
    }
    std::cout << w;
}