#include <iostream>
#include <string>
#include <array>

int main(){
	int t = 0;
	std::cin >> t;
	
	int n = 0;
	int k = 0;
	std::string c = "";
	
	int cur_blackness = 0;
	int max_blackness = 0;
	/* int max_length = 0;
	int black_line_start = -1;
	int current_length = 0;
	int current_start = -1; */
	
	for (int input_num = 0; input_num < t; input_num += 1){
		/* max_length = 0;
		black_line_start = -1; */
	
		std::cin >> n >> k;
		std::cin >> c;
		cur_blackness = 0;
		max_blackness = 0;
		
		for (int letter_i = 0; letter_i < n; letter_i += 1){
			if(c[letter_i] == 'B'){
				max_blackness += 1;
			}
		}
		cur_blackness = max_blackness;
     for (int window_i = 1; window_i + k - 1 < n; window_i += 1){	 	
	 		 cur_blackness -= c[window_i - 1] == 'B' ? 1 : 0;
			 cur_blackness += c[window_i + n - 1] == 'B' ? 1 : 0;
			 max_blackness == (max_blackness > cur_blackness) ? max_blackness : cur_blackness;
	 	}
		std::cout << (k - max_blackness > 0) ? k - max_blackness : 0;
	}
}
