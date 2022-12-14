#include <cmath>
#include <numbers>
#include <limits>
#include <iostream>
#include <string>

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
	cat_speed = (mouse - cat) * (speed_modulo/norm(mouse - cat));
	return cat_speed;
}

Rdec2D additional_mouse_speed(std::string mode, const Rdec2D& cat, const Rdec2D& mouse, const double dt){
    if(mode == "classic"){
        return {0,0};
    }
    else if(mode == "cowardly mouse"){
        static Rdec2D cumulative_speed = {0,0};
        cumulative_speed = cumulative_speed + 0.001 * ((mouse - cat) * (1 / (norm(mouse - cat) + 5)) * dt); //требуется выбрать объективные константы, а не это вот всё
        /* std::cout << "Speeding up! " << cumulative_speed.x << ", " << cumulative_speed.y << std::endl; */
        return cumulative_speed;
    }
    else{
        std::cout << "MODE NOT FOUND!!!" << std::endl;
        return {0,0};
    }
}

int catch_attempt(
    Rdec2D cat, Rdec2D mouse, Rdec2D mouse_speed, Rdec2D cat_speed, 
    double touch_bound = epsilon * 2, std::string mode = "classic"
    ){
	double t = 0.0;
	double overflow_norm = 1.0;
	static double dt = 0.001;
    /*const double finish_t = norm(mouse)/norm(mouse_speed);
	long current_step = -1;*/
	static int limit = 0;
	// std::cout << /*std::endl <<  */"############# Catch started! speed to speed: " << norm(cat_speed) / norm(mouse_speed) << ", dt: " << dt << std::endl;
	if(limit > 40){return 13;} //если плохо сходится, обрубаем исполнение
	limit += 1;
	for (; mouse != cat && mouse.y <= epsilon * 2; t += dt){
		mouse = mouse + (mouse * (-norm(mouse_speed)/norm(mouse)) + additional_mouse_speed(mode, cat, mouse, dt)) * dt;
		cat = cat + cat_speed_vector(cat, mouse, norm(cat_speed), cat_speed) * dt;
		if(norm(mouse - cat) < norm((cat_speed - mouse_speed) * dt)){
		    overflow_norm = std::log10f(norm((cat_speed - mouse_speed) * dt) - norm(mouse - cat));
		    // std::cout << "Overflow: " << overflow_norm << ", dt magnitude: " << std::log10f(dt) << std::endl;
		    cat = mouse;
		    dt *= std::pow(2, (overflow_norm - std::log10f(dt)) / 4);
		}
		/*if(t > finish_t * (1 - std::pow(4, current_step))){
		    current_step -= 1;
		    dt /= 2;
		}*/
		/*if (std::fmod(t - std::trunc(t), 1) < dt){
		    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		    std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;
		}*/
	}
	/*std::cout << std::endl;*/
	if (norm(mouse) < touch_bound){
	    /*std::cout << "Yay! ";
	    std::cout << "t: " << t << ", mouse: " << mouse.x << " " << mouse.y;
		std::cout << ", cat: " << cat.x << " " << cat.y << std::endl;*/
		return 0;
	}
	else if (mouse.y > touch_bound){
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
		cat_speed = cat_speed * ((higher + lower)/norm(cat_speed)) * 0.5;
	}
	else if (success == 1){
		higher = norm(cat_speed);
		cat_speed = cat_speed * ((higher + lower)/norm(cat_speed)) * 0.5;
	}
	/*std::cout << "Rebounded to: " << lower << ", " << higher <<  ", _______diff: " << higher - lower << std::endl;*/
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
	    success = catch_attempt(cat, mouse, mouse_speed, cat_speed, epsilon * std::pow(10,10), "cowardly mouse");
	    if(higher - lower <= epsilon * 2){
	        success = 0;
	    }
	    if(norm(cat_speed) > 10 || success == 13){
	        std::cout << "Oh oh, stinky! Cat speed: ";
	        break;
	    }
	    else if(success == 0){
	        std::cout << "Speed successfully found: ";
	    }
	}
	std::cout << norm(cat_speed);

}
