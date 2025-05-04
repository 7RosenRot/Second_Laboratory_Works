#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;
#pragma once

class Monom {
public:
	double Coefficient;
	int Power;

	Monom(double m_Coefficient = 0, int m_Power = 0) : Coefficient(m_Coefficient), Power(m_Power) {}
	~Monom() {}

	Monom operator+(const Monom& other);
	Monom operator-(const Monom& other);
	Monom operator*(const Monom& other) const;
	Monom operator/(const Monom& other) const;

	friend std::ostream& operator<<(std::ostream& m_Ostream, const Monom& m_Monom) {
		m_Ostream << m_Monom.Coefficient << "x^" << m_Monom.Power;
		return m_Ostream;
	}

	friend std::istream& operator>>(std::istream& m_Istream, Monom& m_Monom) {
		m_Istream >> m_Monom.Coefficient >> m_Monom.Power;
		return m_Istream;
	}
};