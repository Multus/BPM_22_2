#include <iostream>
#include <string>
 
void fix_middle(std::string& str, int& a, int& b){

	if(std::ssize(str) % 2 == 1){
		int middle = std::ssize(str) / 2;
		
		if(str[middle] == '?'){
			if(a % 2 == 1){
				str[middle] = '0';
				a -= 1;
			}
			else{
				str[middle] = '1';
				b -= 1;
			}
		}
		else if(str[middle] == '0'){
			a -= 1;			
		}
		else {
			b -= 1;
		}
	}
}

void fix_pairable_slots(std::string& str, int& a, int& b){
	int opp = std::ssize(str);
	bool is_palyndrome = true;

	for(int cur = 0; a >= 0 && b >= 0 && cur < opp - 1 && is_palyndrome;cur += 1){
		opp -= 1;
		if((str[cur] == '?') && (str[opp] != '?')){
			str[cur] = str[opp];
		}
		else if((str[cur] != '?') && (str[opp] == '?')){
			str[opp] = str[cur];
		}
		else if(str[cur] != str[opp]){
			is_palyndrome = false;
			break;
		}
			
		if(str[cur] == '0' && str[opp] == '0'){
			a -= 2;
		}
		else if(str[cur] == '1' && str[opp] == '1'){
			b -= 2;
		}
	}	
}

void guess_unpairable_slots(std::string& str, int& a, int& b){
	int opp = -1;

	for(int cur = 0; a >= 0 && b >= 0 && cur < std::ssize(str) / 2;cur += 1){
		if (str[cur] != '?'){
			continue;
		}
		opp = std::ssize(str) - cur - 1;
		if (a > b){
			a -= 2;
			str[cur] = '0';
			str[opp] = '0';
		}
		else{
			b -= 2;
			str[cur] = '1';
			str[opp] = '1';
		}
	}
}

int main(){
	int t = 0;
	std::cin >> t;
	int a = 0;
	int b = 0;
	std::string str = "";
	
	for(int i = 0; i < t; i++){
		std::cin >> a >> b;
		std::cin >> str;
		
		//проверка середины
		fix_middle(str, a, b);
		// проверка отдельных '?'
		fix_pairable_slots(str, a, b);
		// проверка двойных '?'
		guess_unpairable_slots(str, a, b);
		
		if(b != 0 || a != 0){
			std::cout << "-1" << std::endl;
		}
		else{
			std::cout << str << std::endl;
		}
	}
}
