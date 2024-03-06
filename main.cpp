#include "Polynomial.h"

using namespace std;

int main() {
    //  Monomials:
    cout << "Monomials:" << endl;

    Monomial m1("3*x^5*y^1");
    Monomial m2("7*y^1*x^5");

    //cin >> m1;
    //cin >> m2;

    Monomial m3 = m1 + m2;
    cout << "Sum of m1 and m2:\n(" << m1 << ") + (" << m2 << ") = " << m3 << "\n" << endl;

    Monomial m4 = m1 - m2;
    cout << "Difference of m1 and m2:\n(" << m1 << ") - (" << m2 << ") = " << m4 << "\n" << endl;

    Monomial m5 = m1 * m2;
    cout << "Multiplying m1 by m2:\n(" << m1 << ") * (" << m2 << ") = " << m5 << "\n" << endl;

    Monomial m6 = m1 * 10;
    cout << "Multiplying m1 by 10:\n(" << m1 << ") * 10 = " << m6 << "\n" << endl;

    cout << "m1 and m2 after performing operations : \n" << m1 << '\n' << m2 << '\n' << endl;


    //  Polynomials:
    cout << "Polynomials:" << endl;

    Polynomial p1("5*x^2*y^4+7*y^4*x^2+5*x^1*y^4+6*z^2+10");    //12*x^2*y^4 + 5*x^1*y^4 + 6*z^2 + 10
    Polynomial p2("-12*x^2*y^4-4*x^1*y^4+10*z^2+4");            //-12*x^2*y^4 + -4*x^1*y^4 + 10*z^2 + 4

    //cin >> p1;
    //cin >> p2;

    Polynomial p3 = p1 + p2;
    cout << "Sum of p1 and p2:\n(" << p1 << ") + (" << p2 << ") = " << p3 << "\n" << endl;

    Polynomial p4 = p1 - p2;
    cout << "Difference p1 and p2:\n(" << p1 << ") - (" << p2 << ") = " << p4 << "\n" << endl;

    Polynomial p5 = p1 * 10;
    cout << "Multiplying m1 by 10:\n(" << p1 << ") * 10 = " << p5 << "\n" << endl;

    Polynomial p6 = p1 * m1;
    cout << "Multiplying p1 by m1:\n(" << p1 << ") * (" << m1 << ") = " << p6 << "\n" << endl;

    Polynomial p7 = p1 * p2;
    cout << "Multiplying p1 by p2:\n(" << p1 << ") * (" << p2 << ") = " << p7 << "\n" << endl;

    //cout << "p1 and p2 after performing operations:\n" << p1 << '\n' << p2 << endl;
}
