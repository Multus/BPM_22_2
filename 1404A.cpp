#include <string>
bool check_window(std::string& s, int window_i, int k){
	int balance = 0;
	int question_marks = 0;

	if(window_i == 0){
		for(int letter_i = 0; letter_i < k; letter_i += 1){
			if(s[letter_i] == '1'){
				balance += 1;
			}
			else if(s[letter_i] == '0'){
				balance -= 1;
			}
			else{
				question_marks += 1;
			}
		}
		if(question_marks == 0){
			return balance == 0;
		}
		// если есть ?
	}
	
	else{
		if(s[window_i - 1] == s[window_i + k - 1] && s[window_i] != '?'){
			return true
		}
		else if(s[window_i - 1] == '?' && s[window_i + k - 1] != '?'){
			s[window_i - 1] = s[window_i + k - 1]
			question_marks -= 1;
		}
		else if(s[window_i - 1] != '?' && s[window_i + k - 1] == '?'){
			s[window_i + k - 1] = s[window_i - 1]
			question_marks -= 1;
		}
		// если первый и последний ?
	}
}

int main(){
	
	int t = 0;
	int k = 0;
	int n = 0;
	bool has_s_failed = false;
	std::string s = "";
	
	std::cin >> t;

	for(int i = 0; i < t; i += 1){
		std::cin >> n >> k;
		std::cin >> s;
		is_first_window = true;
		has_s_failed = false;
		for(int window_i = 0; window_i + k < n && !has_s_failed; window_i += 1){
			if(!check_window(s, window_i, k, is_first_window)){
				has_s_failed = true;
			}
		}
		if(has_s_failed){
			std::cout << "NO";
		}
		else{
			std::cout >> "YES";
		}
	}

}
