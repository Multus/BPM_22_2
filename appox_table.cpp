#include <array>
#include <string>
#include <iostream>
#include <cmath>
#include <functional>

//https://www.desmos.com/calculator/ndmljyj4jy

struct input_holder{
	std::function<float(float, int)> s = [](float x, int i){return 0.0;};
	std::function<float(float)> f = [](float x){return 0.0;};
	float a = 0.0;
	float b = 1.0;
	float delta = 1.0;
	float epsilon = 0.1;
};

int main(){
	int set_i = -1;
	std::function<float(float, int)> s = [](float x, float i){return 0.0;}; //не уверен, как правильно определения делать с функциями
	std::function<float(float)> f = [](float x){return 0.0;};
	float a = 0.0;
	float b = 1.0;
	float delta = 1.0;
	float epsilon = 0.1;
	
	int i = 0;
	std::cin >> set_i;
	
	std::array<input_holder, 1> input = {
		input_holder{
			[&a, &b](float x, int i){
			    static float sum = 0; 
			    static float last_x = 0;
			    if(x < a || x > b){return sum;};
			    if(x != last_x){
			        last_x = x;
			        sum = 0;
			    }
			    sum += (i % 2 == 0 ? 1 : -1) * std::pow(x, i) / std::tgamma(2 * i + 1);
			    return sum;
			    }, 
			static_cast<std::function<float(float)>>(std::cosf), -1, 1, 0.1, static_cast<float>(std::pow(10,-3))
		}
	};
	
	while(0 <= set_i && set_i < std::ssize(input)){		
		s = input[set_i].s;
		f = input[set_i].f;
		a = input[set_i].a;
		b = input[set_i].b;
		delta = input[set_i].delta;
		epsilon = input[set_i].epsilon;
		std::cout << "x | s(x) | f(x)" << std::endl;
		for(float x = a; x <= b; x += delta){
			i = 0;
		
			while(std::abs(s(x,i) - f(x)) > epsilon){
			    i += 1;
				if(i > 5){break;};
			    std::cout << x << " " << s(a - 1, 0) << " " << f(x) << std::endl;
			}   
		    std::cout << x << " | " << s(a - 1, 0) << " | " << f(x) << std::endl;
			// std::cout << s(a - 1, 0) << ", ";
		}
		
		std::cin >> set_i;
	}

}
