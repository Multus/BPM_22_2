#include <string>
#include <iostream>

int main(){
    int length = -1;
    std::string input = "";
    std::cin >> length >> input;
    int step = -2;
    for(int i = length - 2; i < length; i += step){
        if(i < 0){
            i = 0;
            step = -step;
            std::cout << input[i];
            continue;
        }
        std::cout << input[i];
        if(i == 0){
            step = -step;
            i += 1;
            std::cout << input[i];
        }
    }
    
}
