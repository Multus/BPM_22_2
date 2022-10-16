// Example program
#include <iostream>
#include <vector>
 
void strip(int num, int layer = 0)
{
    /* int base = std::log10(num);
    int cur = num / std::pow(10, base);
    cur *= std::abs(std::pow(10, base));
    layer++;
    // std::cout << layer << " " << num << " " << base << " " << cur << std::endl;
    if (base < 1){
        std::cout << layer << std::endl << num << " ";
        return;
    }
    strip(num - cur, layer);
    std::cout << cur << " "; */
    int base = std::log10(num);
    std::vector<int> ar = {};
    for (int i = 0; i <= base; i++)
    {
        if (num % 10 != 0)
        {
            ar.push_back(num % 10 * std::pow(10,i));
        }    
        num /= 10;
    }
    std::cout << ar.size() << std::endl;
    for (int i = 0; i < ar.size(); i++)
    {
        std::cout << ar[i] << " ";
    }
}
 
int main()
{
  int n;
  std::cin >> n;
  for (int i = 0; i<n; i++){
      int full;
      std::cin >> full;
      strip(full);
      std::cout << std::endl;
  }
}