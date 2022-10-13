#include <iostream>
#include <string>
#include <array>

int main(){
	int t = 0;
	std::cin >> t;
	int n = 0;
	int ai = 0;
	bool flag = false;
	std::array<bool, 100> a = {false};
	int nonzero = n;
	for(int cur = 0; cur < t; cur++){
		a = {false};
		std::cin >> n;
		for(int i = 0; i < n; i++){
			std::cin >> ai;
			if(a[ai]){
				flag = true;
			}
			if(ai == 0){
				nonzero--;
			}
		}
		if(n - nonzero == 0){
			if(flag){
				std::cout << n - 1 << std::endl;
			}
			else{
				std::cout << n << std::endl;
			}
		}
		else{
			if(flag){
				std::cout << nonzero << std::endl;
			}
			else{
				std::cout << nonzero << std::endl;
			}
		}
	}
}
