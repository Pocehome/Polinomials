#include "Monomial.h"
#include "MyList.h"

class Polynomial {
public:
    List <Monomial> monomials;     // list of monomials

    // Default constructor
    Polynomial() : monomials() {}

    // Constructor from string
    Polynomial(std::string str) : monomials() {
        if (!is_valid_input(str)) {
            throw std::invalid_argument("Invalid input");
        }

        std::string monomial_str = "";

        if (str[0] == '-') {
            monomial_str = "-";
            str = str.substr(1);
        }

        for (char symbol : str) {
            if (symbol == '-') {
                Monomial monomial(monomial_str);
                push(monomial);
                monomial_str = "-";
            }
            else if (symbol == '+') {
                Monomial monomial(monomial_str);
                push(monomial);
                monomial_str = "";
            }
            else {
                monomial_str += symbol;
            }
        }

        Monomial monomial(monomial_str);
        push(monomial);
    }

    // Adding a monomial to a polynomial
    void push(const Monomial& monomial) {
        for (auto iter = this->monomials.begin(); iter != this->monomials.end(); ++iter) {
            if (iter->variables == monomial.variables) {
                iter->coef += monomial.coef;
                if (iter->coef == 0) {
                    iter = this->monomials.erase(iter);
                }
                return;
            }
        }
        if (monomial.coef != 0) {
            monomials.push_back(monomial);
        }
    }

    // Addition operator
    Polynomial operator+(const Polynomial& other) {
        Polynomial result;
        for (auto monomial : this->monomials) {
            result.monomials.push_back(monomial);
        }

        for (auto monomial : other.monomials) {
            result.push(monomial);
        }
        return result;
    }

    // Subtraction operator
    Polynomial operator-(Polynomial& other) {
        Polynomial result;
        for (auto monomial : this->monomials) {
            result.monomials.push_back(monomial);
        }

        for (auto iter = other.monomials.begin(); iter != other.monomials.end(); ++iter) {
            Monomial negative_monom = *iter;
            negative_monom.coef = -negative_monom.coef;
            result.push(negative_monom);
        }
        return result;
    }

    // Multiplication by scalar
    Polynomial operator*(const double scalar) const {
        Polynomial result;
        for (auto monomial : this->monomials) {
            result.monomials.push_back(monomial * scalar);
        }
        return result;
    }

    // Multiplication by monomial
    Polynomial operator*(const Monomial other) const {
        Polynomial result;
        for (auto monomial : this->monomials) {
            result.monomials.push_back(monomial * other);
        }
        return result;
    }

    // Multiplication by polynomial
    Polynomial operator*(const Polynomial other) const {
        Polynomial result;
        for (auto monomial : this->monomials) {
            result = result + (other * monomial);
        }
        return result;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, Polynomial& Polynomial) { // !!!!!!!!!! изменить под свой список с -
        for (auto iter = Polynomial.monomials.begin(); iter != Polynomial.monomials.end(); ++iter) {
            if (iter != Polynomial.monomials.begin()) {
                os << " + ";
            }
            os << *iter;
        }
        return os;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Polynomial& polynomial) {
        std::string str;
        std::getline(is, str);
        if (!is_valid_input(str)) {
            throw std::invalid_argument("Invalid input");
        }

        std::string monomial_str = "";

        if (str[0] == '-') {
            monomial_str = "-";
            str = str.substr(1);
        }

        for (char symbol : str) {
            if (symbol == '-') {
                Monomial monomial(monomial_str);
                polynomial.push(monomial);
                monomial_str = "-";
            }
            else if (symbol == '+') {
                Monomial monomial(monomial_str);
                polynomial.push(monomial);
                monomial_str = "";
            }
            else {
                monomial_str += symbol;
            }
        }

        Monomial monomial(monomial_str);
        polynomial.push(monomial);
    }
};
