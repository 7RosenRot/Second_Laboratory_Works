#include "Polynom.h"

void Polynom::addMonom(const Monom& newMonom) {
	for (Monom& m_Monom : v_Monom) {
		if (m_Monom.Power == newMonom.Power) {
			m_Monom = m_Monom + newMonom;
			return;
		}
	}
	
	v_Monom.push_back(newMonom);
}

void Polynom::m_Sort() {
	sort(v_Monom.begin(), v_Monom.end(), [](const Monom& firstMember, const Monom& secondMember) { return firstMember.Power > secondMember.Power; });
	
	for (int i = 0; i < v_Monom.size(); i++) {
		if (v_Monom[i].Coefficient == 0) v_Monom.erase(v_Monom.begin() + i);
	}
}

Polynom& Polynom::operator=(const Polynom& other) {
	if (this != &other) {
		v_Monom.clear();
		
		for (const Monom& m : other.v_Monom) addMonom(m);
	}
	
	return *this;
}

Polynom Polynom::operator+(const Polynom& other) {
	Polynom result = *this;
	
	for (const Monom& m_Monom : other.v_Monom) result.addMonom(m_Monom);
	result.m_Sort();
	
	return result;
}

Polynom Polynom::operator-(const Polynom& other) {
	Polynom result = *this;
	
	for (const Monom& m_Monom : other.v_Monom) result.addMonom(Monom(-m_Monom.Coefficient, m_Monom.Power));
	result.m_Sort();
	
	return result;
}

Polynom Polynom::operator*(const Polynom& other) {
	Polynom result;

	for (const Monom& firstMonom : v_Monom) {
		for (const Monom& secondMonom : other.v_Monom) result.addMonom(firstMonom * secondMonom);
	}
	result.m_Sort();

	return result;
}

Polynom Polynom::operator/(const Monom& divMonom) const {
	Polynom result;

	for (const Monom& m_Monom : v_Monom) result.addMonom(m_Monom / divMonom);
	result.m_Sort();

	return result;
}

Polynom Polynom::operator*(const Monom& mulMonom) const {
	Polynom result;

	for (const Monom& m_Monom : v_Monom) result.addMonom(m_Monom * mulMonom);
	result.m_Sort();

	return result;
}

Polynom Polynom::operator*(const int mulInteger) const {
	Polynom result;
		
	for (const Monom& m_Monom : v_Monom) result.addMonom(m_Monom * mulInteger);
	result.m_Sort();

	return result;
}

pair<Polynom, Polynom> Polynom::operator/(const Polynom& other) const {
	if (other.v_Monom.empty() || (other.v_Monom.size() == 1 && other.v_Monom[0].Coefficient == 0)) throw std::invalid_argument("Zero division!");

	Polynom result;
	Polynom Divisible = *this;

	while (!Divisible.v_Monom.empty() && Divisible.v_Monom[0].Power >= other.v_Monom[0].Power) {
		Monom currentMonom = Divisible.v_Monom[0] / other.v_Monom[0];
		result.addMonom(currentMonom);

		Polynom temp = other * currentMonom;
		Divisible = Divisible - temp;
		Divisible.m_Sort();
	}
	result.m_Sort();
	
	return { result, Divisible };
}