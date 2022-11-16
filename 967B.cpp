#include <iostream>
#include <array>
#include <algorithm>
// #include <format>
 
int main(){
	
	int n = 0;
	float A = 0;
	float B = 0;
	std::cin >> n >> A >> B;
	// B >= s[0] * A/S  ->  S >= s[0] * A/B
	std::array<int,100001> s = {0};
	
	float s0 = 0;
	std::cin >> s0;
	float sum = s0;
	float S = s0 * A/B;
	for(int i = 1; i < n; i += 1){
		std::cin >> s[i];
		sum += s[i];
	}
	std::sort(s.begin(), s.end(), std::greater<int>());
	/*if(n == 1000){
		for(int i : s){
			std::cout << i << " ";
		}	
		std::cout << std::endl;
	}	*/
	int i = 0;
	for(; sum > S && s[i /*> 0 ? i - 1 : 0*/] != 0; i += 1){
		sum -= s[i];
	}
	std::cout << (/*(i == n) ? i - 1 : */i);
	// if(n == 1000){std::cout << std::endl << "sum: " << sum << " S: " << S << " " << s[i - 1] << " " << s[i] << " " << s[i + 1] /* std::format("…{}, {}, {},…", s[i - 1], s[i], s[i + 1])*/;}
}
