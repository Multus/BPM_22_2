#include <iostream>
#include <string>

int main(){
	int n = 0;
	std::string str = "";
	
	int x = 0;
	int y = 0;
	int debt = 0;
	int isabove = 2;
	std::cin >> n >> str;
	for(int i = 0; i < n; i++){
		// std::cout << "i'm in" << std::endl;
	
		if(str[i] == 'U'){
			y += 1;
			if(x < y && isabove == 0){
				debt += 1;
			}
			if(x < y){
				isabove = 1;
			}
		}
		else{
			x += 1;
			if(x > y && isabove == 1){
				debt += 1;
			}
			if(x > y){
				isabove = 0;
			}
		}
		// std::cout << x <<", "<<y<<" "<< debt << std::endl; 
	}
	// std::cout << "kuk";
	std::cout << debt;
}
