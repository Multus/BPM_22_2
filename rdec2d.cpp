#include <cmath>
#include <numbers>

constexpr auto tau = std::numbers::pi * 2.0;

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

int main(){

    
    return 0;

}

/* #include <cmath>
#include <numbers>

constexpr auto tau = std::numbers::pi * 2.0;

struct Rdec2D{
	double x = 0.0;
	double y = 0.0;
};
struct Rpol2D{
	double r = 0.0;
	double theta = tau;
};


Rdec2D operator+(Rdec2D lhs, Rdec2D rhs){
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}
Rdec2D operator-(Rdec2D vec){
	return {-vec.x, -vec.y};
}
Rdec2D operator-(Rdec2D lhs, Rdec2D rhs){
	return lhs + (-rhs);
}
Rdec2D operator*(Rdec2D vec, double sca){
	return {sca * vec.x, sca * vec.y};
}
Rdec2D operator*(double sca, Rdec2D vec){
	return {sca * vec.x, sca * vec.y};
}
double dot(Rdec2D lhs, Rdec2D rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y;
}
double norm(Rdec2D vec){
	return std::sqrt(std::pow(vec.x,2) + std::pow(vec.y,2));
}

Rpol2D pol(Rdec2D vec){
	Rdec2D E = {1,1};
	double r = norm(vec);

	return {r, std::fmod(std::acos(dot(vec, E)/r) * (std::signbit(vec.y) ? -1 : 1), tau)};
}
Rdec2D dec(Rpol2D vec){
	return {vec.r * std::cos(vec.theta), vec.r * std::sin(vec.theta)};
}

Rpol2D operator+(Rpol2D lhs, Rpol2D rhs){
	return pol(dec(lhs) + dec(rhs))
}
Rpol2D operator-(Rpol2D vec){
	return {vec.r, std::fmod(vec.theta + std::numbers::pi, tau)};
}
Rpol2D operator-(Rpol2D lhs, Rpol2D rhs){
	return lhs + (-rhs);
}
Rpol2D operator*(Rpol2D vec, double sca){
	return {sca * vec.r, vec.theta};
}
Rpol2D operator*(double sca, Rpol2D vec){
	return {sca * vec.r, vec.theta};
}
double dot(Rpol2D lhs, Rdec2D rhs){
	lhs = dec(lhs);
	rhs = dec(rhs);

	return lhs.x * rhs.x + lhs.y * rhs.y;
}
double norm(Rpol2D vec){
	return vec.r;
}

int main(){

    
    return 0;

} */
