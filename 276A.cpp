// Example program
#include <iostream>
#include <string>
 
int main()
{
    int n = 0; int k = 0;
    std::cin >> n >> k;
    // std::cout << n << " " << k;
    int m = -std::pow(10,9);
    int f = 0; int t = 0;
    for (int i = n; i > 0; i--)
    {
        // std::cout << i;
        std::cin >> f >> t;
        m = std::max( m, std::min(f-(t-k), f) );
    }
    std::cout << m;
}