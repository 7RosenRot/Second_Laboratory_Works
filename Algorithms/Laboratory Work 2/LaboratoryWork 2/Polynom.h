#include "Monom.h"
#pragma once

class Polynom {
private: 
    vector<Monom> v_Monom;
public:
	void addMonom(const Monom& newMonom);
	void m_Sort();

	Polynom& operator=(const Polynom& other);
	Polynom operator+(const Polynom& other);
	Polynom operator-(const Polynom& other);
	Polynom operator*(const Polynom& other);
	Polynom operator/(const Monom& divMonom) const;
	Polynom operator*(const Monom& mulMonom) const;
	Polynom operator*(const int mulInteger) const;

    pair<Polynom, Polynom> operator/(const Polynom& other) const;

    friend std::ostream& operator<<(std::ostream& m_Ostream, Polynom& m_Polynom) {
        m_Polynom.m_Sort();
        if (m_Polynom.v_Monom.size() == 0) {
            m_Ostream << "0";
            return m_Ostream;
        }

        for (int i = 0; i < m_Polynom.v_Monom.size(); i++) {
            if (m_Polynom.v_Monom[i].Coefficient < 0) m_Ostream << "-";
            else if (i != 0) m_Ostream << "+";

            if (i != 0) m_Ostream << " ";

            if (m_Polynom.v_Monom[i].Coefficient == 1 && m_Polynom.v_Monom[i].Power == 0) m_Ostream << m_Polynom.v_Monom[i].Coefficient;
            else if (m_Polynom.v_Monom[i].Coefficient != 1) m_Ostream << abs(m_Polynom.v_Monom[i].Coefficient);

            if (m_Polynom.v_Monom[i].Power == 1) m_Ostream << "x";
            else if (m_Polynom.v_Monom[i].Power != 0) m_Ostream << "x^" << m_Polynom.v_Monom[i].Power;

            if (i < m_Polynom.v_Monom.size() - 1) m_Ostream << " ";
        }
        return m_Ostream;
    }

    friend std::istream& operator>>(std::istream& m_Istream, Polynom& m_Polynom) {
        string line;
        getline(m_Istream, line);
        if (line.empty())
            return m_Istream;

        std::istringstream m_Istringstream(line);
        double m_Coefficient;
        int m_Power;

        while (m_Istringstream >> m_Coefficient >> m_Power) {
            m_Polynom.addMonom(Monom(m_Coefficient, m_Power));
        }

        m_Polynom.m_Sort();
        return m_Istream;
    }
};