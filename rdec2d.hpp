#pragma once

#include <Rdec2D>

struct Rdec2D{
	double x = 0.0;
	double y = 0.0;
};
struct Rpol2D{
	double r = 0.0;
	double theta = tau;
};


Rdec2D operator+(const Rdec2D& lhs, const Rdec2D& rhs);
Rdec2D operator-(const Rdec2D& vec);
Rdec2D operator-(const Rdec2D& lhs, const Rdec2D& rhs);
Rdec2D operator*(const Rdec2D& vec, const double& sca);
Rdec2D operator*(const double& sca, const Rdec2D& vec);
double dot(const Rdec2D& lhs, const Rdec2D& rhs);
double norm(const Rdec2D& vec);

Rpol2D pol(const Rdec2D& vec);
Rdec2D dec(const Rpol2D& vec);

Rpol2D operator+(const Rpol2D& lhs, const Rpol2D& rhs);
Rpol2D operator-(const Rpol2D& vec);
Rpol2D operator-(const Rpol2D& lhs, const Rpol2D& rhs);
Rpol2D operator*(const Rpol2D& vec, const double& sca);
Rpol2D operator*(const double& sca, const Rpol2D& vec);
double dot(const Rpol2D& lhsp, const Rdec2D& rhsp);
double norm(const Rpol2D& vec);

/* #pragma once

#include <Rdec2D>

struct Rdec2D{
	double x = 0.0;
	double y = 0.0;
};
struct Rpol2D{
	double r = 0.0;
	double theta = tau;
};


Rdec2D operator+(Rdec2D lhs, Rdec2D rhs);
Rdec2D operator-(Rdec2D vec);
Rdec2D operator-(Rdec2D lhs, Rdec2D rhs);
Rdec2D operator*(Rdec2D vec, double sca);
Rdec2D operator*(double sca, Rdec2D vec);
double dot(Rdec2D lhs, Rdec2D rhs);
double norm(Rdec2D vec);

Rpol2D pol(Rdec2D vec);
Rdec2D dec(Rpol2D vec);

Rpol2D operator+(Rpol2D lhs, Rpol2D rhs);
Rpol2D operator-(Rpol2D vec);
Rpol2D operator-(Rpol2D lhs, Rpol2D rhs);
Rpol2D operator*(Rpol2D vec, double sca);
Rpol2D operator*(double sca, Rpol2D vec);
double dot(Rpol2D lhs, Rdec2D rhs);
double norm(Rpol2D vec);
*/
