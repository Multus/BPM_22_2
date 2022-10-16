// Example program
#include <iostream>
#include <array>

int main()
{
  int t = 0;
  /* int n = 0;
  int x = 0;
  std::array <bool, 101> a = {0};
  std::cin >> t;
  int place = 0; */
  std::cin >> t;
  for (int cur_t = 0; cur_t < t; cur_t++)
  {
      int n = 0;
      int x = 0;
      std::array <bool, 201> a = {0};
      int place = 0;
      std::cin >> n >> x;
      for (int i = 0; i < n; i++)
      {
          std::cin >> place;
          a[place] = 1;
      }
      int i = 1;
      // std::cout << "cycle " << n << ' ' << i << ' ' << a[i] << ' ' << x << std::endl;
      for (; i<201 && x > -1; i++)
      {
          // std::cout << "i " << i << " a "<< a[i] << " x " << x << std::endl;
          if (!a[i])
          {
              x--;
          }
      }
      std::cout << i - (x == -1 ? 2 : 1) << std::endl;
  }
}