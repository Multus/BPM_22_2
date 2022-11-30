#include <cmath>
#include <numbers>
#include <limits>
#include <iostream>

constexpr auto tau = std::numbers::pi * 2.0;
constexpr auto epsilon = std::numeric_limits<double>::min();
struct Rdec2D{
	double x = 0.0;
	double y = 0.0;
};
struct Rpol2D{
	double r = 0.0;
	double theta = tau;
};


Rdec2D operator+(const Rdec2D& lhs, const Rdec2D& rhs){
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}
Rdec2D operator-(const Rdec2D& vec){
	return {-vec.x, -vec.y};
}
Rdec2D operator-(const Rdec2D& lhs, const Rdec2D& rhs){
	return lhs + (-rhs);
}
Rdec2D operator*(const Rdec2D& vec, const double& sca){
	return {sca * vec.x, sca * vec.y};
}
Rdec2D operator*(const double& sca, const Rdec2D& vec){
	return {sca * vec.x, sca * vec.y};
}
bool operator==(const Rdec2D& lhs, const Rdec2D& rhs){
	return ((std::fabs(lhs.x - rhs.x) < epsilon * 2) && (std::fabs(lhs.y - rhs.y) < epsilon * 2));
}
bool operator!=(const Rdec2D& lhs, const Rdec2D& rhs){
	return !(lhs == rhs);
}
double dot(const Rdec2D& lhs, const Rdec2D& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y;
}
double norm(const Rdec2D& vec){
	return std::sqrt(std::pow(vec.x,2) + std::pow(vec.y,2));
}

Rpol2D pol(const Rdec2D& vec){
	Rdec2D E = {1,1};
	double r = norm(vec);

	return {r, std::fmod(std::acos(dot(vec, E)/r) * (std::signbit(vec.y) ? -1 : 1), tau)};
}
Rdec2D dec(const Rpol2D& vec){
	return {vec.r * std::cos(vec.theta), vec.r * std::sin(vec.theta)};
}

Rpol2D operator+(const Rpol2D& lhs, const Rpol2D& rhs){
	return pol(dec(lhs) + dec(rhs));
}
Rpol2D operator-(const Rpol2D& vec){
	return {vec.r, std::fmod(vec.theta + std::numbers::pi, tau)};
}
Rpol2D operator-(const Rpol2D& lhs, const Rpol2D& rhs){
	return lhs + (-rhs);
}
Rpol2D operator*(const Rpol2D& vec, const double& sca){
	return {sca * vec.r, vec.theta};
}
Rpol2D operator*(const double& sca, const Rpol2D& vec){
	return {sca * vec.r, vec.theta};
}
double dot(const Rpol2D& lhsp, const Rpol2D& rhsp){
	Rdec2D lhs = dec(lhsp);
	Rdec2D rhs = dec(rhsp);

	return dot(rhs, lhs);
}
double norm(const Rpol2D& vec){
	return vec.r;
}

//###############################

Rdec2D cat_speed_vector(const Rdec2D& cat, const Rdec2D& mouse, const float speed_modulo, Rdec2D& cat_speed){
	cat_speed = (mouse - cat) * (speed_modulo/std::fabs(norm(mouse - cat)));
	return cat_speed;
}

int catch_attempt(Rdec2D cat, Rdec2D mouse, const Rdec2D& mouse_speed, Rdec2D cat_speed){
	double t = 0.0;
	// std::cout << /*std::endl <<  */"############# Catch started! speed: " << norm(cat_speed) << std::endl;
	for (double dt = 0.01; mouse != cat && mouse.y <= epsilon * 5; t += dt){
		mouse = mouse + mouse_speed * dt;
		cat = cat + cat_speed_vector(cat, mouse, norm(cat_speed), cat_speed) * dt;
		if(std::fabs(norm(mouse - cat)) < std::fabs(norm(cat_speed * dt))){
		    cat = mouse;
		}
		/*if (std::fmod(t - std::trunc(t), 1) < dt){
		    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		    std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		}*/
	}
	/*std::cout << std::endl;*/
	if (std::fabs(norm(mouse)) < epsilon * 2){
	    std::cout << "Yay! ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		return 0;
	}
	else if (mouse.y > epsilon * 2){
	    /*std::cout << "Fat, fat cat... ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;*/
		return -1;
	}
	else{
	    /*std::cout << "Too fast! ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;*/
		return 1;
	}
}

void rebound(double& lower, double& higher, Rdec2D& cat_speed, int success){
    static bool is_upper_set = false;
    if (!is_upper_set){
        if (success == 1){
           higher = norm(cat_speed);
		   cat_speed = cat_speed * ((higher + lower)/norm(cat_speed)) * 0.5; 
		   is_upper_set = true;
        }
        else{
            higher *= 2;
            cat_speed = cat_speed * 2;
        }
    }
	else if (success == -1){
		lower = norm(cat_speed);
		cat_speed = cat_speed * ((higher)/norm(cat_speed));
	}
	else if (success == 1){
		higher = norm(cat_speed);
		cat_speed = cat_speed * ((higher + lower)/norm(cat_speed)) * 0.5;
	}
}

int main(){
	// std::cout << epsilon;
	double x = 0;
	double y = 0;
	std::cin >> x >> y;
	Rdec2D cat = {x,0.0};
	Rdec2D mouse = {0.0,-y};
	// std::cout << (int)(cat == mouse) << (int)(cat != mouse) << (int)(mouse == cat) << (int)(mouse != cat);
	Rdec2D mouse_speed = {0,y/5.0};
	Rdec2D cat_speed = (mouse - cat) * (2 * norm(mouse_speed)/norm(mouse - cat));
	
	double lower = norm(mouse_speed);
	double higher = norm(mouse_speed) * 2;
	
	for(int success = 2; success != 0; rebound(lower, higher, cat_speed, success)){
	    success = catch_attempt(cat, mouse, mouse_speed, cat_speed);
	    if(higher - lower <= epsilon * 2){
	        success = 0;
	    }
	    if(norm(cat_speed) > 10){
	        std::cout << "Oh oh, stinky! Cat speed: ";
	        break;
	    }
	}
	std::cout << norm(cat_speed);

}


/* #include <cmath>
#include <numbers>
#include <limits>
#include <iostream>

constexpr auto tau = std::numbers::pi * 2.0;
constexpr auto epsilon = std::numeric_limits<double>::min();
struct Rdec2D{
	double x = 0.0;
	double y = 0.0;
};
struct Rpol2D{
	double r = 0.0;
	double theta = tau;
};


Rdec2D operator+(const Rdec2D& lhs, const Rdec2D& rhs){
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}
Rdec2D operator-(const Rdec2D& vec){
	return {-vec.x, -vec.y};
}
Rdec2D operator-(const Rdec2D& lhs, const Rdec2D& rhs){
	return lhs + (-rhs);
}
Rdec2D operator*(const Rdec2D& vec, const double& sca){
	return {sca * vec.x, sca * vec.y};
}
Rdec2D operator*(const double& sca, const Rdec2D& vec){
	return {sca * vec.x, sca * vec.y};
}
bool operator==(const Rdec2D& lhs, const Rdec2D& rhs){
	return ((std::fabs(lhs.x - rhs.x) < epsilon * 2) && (std::fabs(lhs.y - rhs.y) < epsilon * 2));
}
bool operator!=(const Rdec2D& lhs, const Rdec2D& rhs){
	return !(lhs == rhs);
}
double dot(const Rdec2D& lhs, const Rdec2D& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y;
}
double norm(const Rdec2D& vec){
	return std::sqrt(std::pow(vec.x,2) + std::pow(vec.y,2));
}

Rpol2D pol(const Rdec2D& vec){
	Rdec2D E = {1,1};
	double r = norm(vec);

	return {r, std::fmod(std::acos(dot(vec, E)/r) * (std::signbit(vec.y) ? -1 : 1), tau)};
}
Rdec2D dec(const Rpol2D& vec){
	return {vec.r * std::cos(vec.theta), vec.r * std::sin(vec.theta)};
}

Rpol2D operator+(const Rpol2D& lhs, const Rpol2D& rhs){
	return pol(dec(lhs) + dec(rhs));
}
Rpol2D operator-(const Rpol2D& vec){
	return {vec.r, std::fmod(vec.theta + std::numbers::pi, tau)};
}
Rpol2D operator-(const Rpol2D& lhs, const Rpol2D& rhs){
	return lhs + (-rhs);
}
Rpol2D operator*(const Rpol2D& vec, const double& sca){
	return {sca * vec.r, vec.theta};
}
Rpol2D operator*(const double& sca, const Rpol2D& vec){
	return {sca * vec.r, vec.theta};
}
double dot(const Rpol2D& lhsp, const Rpol2D& rhsp){
	Rdec2D lhs = dec(lhsp);
	Rdec2D rhs = dec(rhsp);

	return dot(rhs, lhs);
}
double norm(const Rpol2D& vec){
	return vec.r;
}

//###############################

Rdec2D cat_speed_vector(const Rdec2D& cat, const Rdec2D& mouse, const float speed_modulo, Rdec2D& cat_speed){
	cat_speed = (mouse - cat) * (speed_modulo/std::fabs(norm(mouse - cat)));
	return cat_speed;
}

int catch_attempt(Rdec2D cat, Rdec2D mouse, const Rdec2D& mouse_speed, Rdec2D cat_speed){
	double t = 0.0;
	std::cout << std::endl <<  "############# Catch started! speed: " << norm(cat_speed) << std::endl;
	for (double dt = 0.001; mouse != cat && mouse.y <= epsilon * 5; t += dt){
		mouse = mouse + mouse_speed * dt;
		cat = cat + cat_speed_vector(cat, mouse, norm(cat_speed), cat_speed) * dt;
		if (std::fmod(t - std::trunc(t), 0.1) < dt/2.0){
		    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		    std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		}
	}
	std::cout << std::endl;
	if (std::fabs(mouse.y) < epsilon * 2){
	    std::cout << "Yay! ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		return 0;
	}
	else if (mouse.y > epsilon * 2){
	    std::cout << "Fat, fat cat... ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		return -1;
	}
	else{
	    std::cout << "Too fast! ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		return 1;
	}
}

void rebound(double& lower, double& higher, Rdec2D& cat_speed, int success){
	
	if (success == -1){
		higher *= 2;
		cat_speed = cat_speed * ((higher)/norm(cat_speed));
	}
	else if (success > 0){
		lower = norm(cat_speed);
		cat_speed = cat_speed * ((higher + lower)/norm(cat_speed)) * 0.5;
	}
}

int main(){
	// std::cout << epsilon;
	double x = 0;
	double y = 0;
	std::cin >> x >> y;
	Rdec2D cat = {x,0.0};
	Rdec2D mouse = {0.0,-y};
	
	Rdec2D mouse_speed = {0,y/5.0};
	Rdec2D cat_speed = (mouse - cat) * (2 * norm(mouse_speed)/norm(mouse - cat));
	
	double lower = norm(mouse_speed);
	double higher = norm(mouse_speed) * 2;
	
	for(int success = 2; success != 0; rebound(lower, higher, cat_speed, success)){
	    success = catch_attempt(cat, mouse, mouse_speed, cat_speed);
	    if(norm(cat_speed) > 10000){
	        std::cout << "Oh oh, stinky! Cat speed: ";
	        break;
	    }
	}
	std::cout << norm(cat_speed);

}
*/