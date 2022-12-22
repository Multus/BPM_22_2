#include <iostream>
#include <cmath>

constexpr auto dx = 0.05;
constexpr auto epsilon = 0.0001; 
// constexpr auto e = std::numbers.e;


double s(double x){
	static int i = 0;
	static double sum = 0;
	static int sign = 1;
	if (x > 1){
		i = 0;
		sum = 0;
		sign = 1;
		return sum;
	}
	sum += sign * std::pow(x, 2*i + 1) / (2*i + 1);
	sign = -sign;
	i += 1;
//	if(i / 1000 == 0){
//	    std::cout << sum - std::atan(x) << std::endl;
//	}
	return sum;
}

int main(){
	
	std::cout << "x\tf\n";
	double cur_value = 0;
	for(double x = 0.1; x <= 1.0; x += dx){
		const double cur_target = std::atan(x);
		while(std::fabs(cur_target - cur_value) > epsilon){
			cur_value = s(x);
		}
		std::cout << x << "\t" << cur_value << "\n";
//		std::cout << "\t" << std::fabs(cur_value - cur_target) << "\n";
		cur_value = s(13);
	}
	std::cout << 1 << "\t" << std::atan(1) << std::endl;
	return 0;

}
