#include "Polynom.h"
#include "Monom.h"

int main(void) {
    Polynom p1, p2;
    cout << "Enter 1st polynomial's monoms separating all variables by space (e.g. 1 2 3 4 => x^2 + 3x^4):\n";
    cin >> p1;

    cout << "Enter 2nd polynomial's monoms:\n";
    cin >> p2;

    cout << "First polynomial: " << p1 << endl;
    cout << "Second polynomial: " << p2 << endl;

    Polynom sum = p1 + p2;
    Polynom diff = p1 - p2;
    Polynom mult = p1 * p2;
    Polynom div = (p1 / p2).first;
    Polynom rem = (p1 / p2).second;
    cout << "p1 + p2: " << sum << endl;
    cout << "p1 - p2: " << diff << endl;
    cout << "p1 * p2: " << mult << endl;
    cout << "p1 / p2: (" << p2 << ")*(" << div << ") + " << rem << endl;

    cout << endl;
    Monom m(2, 6);
    Polynom divm = p1 / m;
    Polynom multm = p1 * m;
    cout << "p1 * 2x^6: " << multm << endl;
    cout << "p1 / 2x^6: " << divm << endl;

	return 0;
}