#include "Monom.h"

Monom Monom::operator+(const Monom& other) {
	if (Power != other.Power) { throw invalid_argument("power mismatch"); }
	
	return Monom(Coefficient + other.Coefficient, Power);
}

Monom Monom::operator-(const Monom& other) {
	if (Power != other.Power) { throw invalid_argument("power mismatch"); }
	
	return Monom(Coefficient - other.Coefficient, Power);
}

Monom Monom::operator*(const Monom& other) const {
	return Monom(Coefficient * other.Coefficient, Power + other.Power);
}

Monom Monom::operator/(const Monom& other) const {
	if (other.Coefficient == 0) { throw invalid_argument("cant divide by 0"); }
	
	return Monom(Coefficient / other.Coefficient, Power - other.Power);
}