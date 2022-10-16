// Example program
#include <iostream>
#include <string>
 
int main()
{
  int num;
  for (int i = 0; i<5; i++){
      for (int j = 0; j<5; j++){
          std::cin >> num;
          if (num == 1){
              std::cout << abs(i-2) + abs (j-2);
          }
      }
  }
}