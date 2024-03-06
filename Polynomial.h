#include <unordered_map>
#include <string>
#include <iostream>
#include "Monomial.h"
#include "MyList.h"

class Polynomial {
public:
    List <Monomial> monomials;     // list of monomials

    // Default constructor
    Polynomial() : monomials() {}


    // Constructor from string
    Polynomial(std::string str) : monomials() {
        if (!isValidInput(str)) {
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
        for (auto iter = monomials.begin(); iter != monomials.end(); ++iter) {
            if (iter->variables == monomial.variables) {
                iter->coef += monomial.coef;
                if (iter->coef == 0) {
                    monomials.erase(iter);
                }
                return;
            }
        }
        if (monomial.coef != 0) {
            monomials.push_back(monomial);
        }
    }

    // Method for checking the validity of the input string
    bool isValidInput(const std::string& str) {
        for (char c : str) {
            if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '^' && !std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    // Addition operator
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result = *this;
        for (auto monomial : other.monomials) {
            result.push(monomial);
        }
        return result;
    }

    // Subtraction operator
    Polynomial operator-(Polynomial& other) {
        Polynomial result = *this;
        for (auto iter = other.monomials.begin(); iter != other.monomials.end(); ++iter) {
            Monomial negative_monom = *iter;
            negative_monom.coef = -negative_monom.coef;
            result.push(negative_monom);
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
    friend std::istream& operator>>(std::istream& is, Polynomial& Polynomial) {
        std::string str;
        is >> str;
        if (!Polynomial.isValidInput(str)) {
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
                Polynomial.push(monomial);
                monomial_str = "-";
            }
            else if (symbol == '+') {
                Monomial monomial(monomial_str);
                Polynomial.push(monomial);
                monomial_str = "";
            }
            else {
                monomial_str += symbol;
            }
        }

        Monomial monomial(monomial_str);
        Polynomial.push(monomial);
    }
};
