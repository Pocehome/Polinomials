#include <stdexcept>
#include <unordered_map>
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include "Monomial.h"

class Polynomial {
public:
    std::list<Monomial> monomials;      // polynomial as a list of monomials

    // Default constructor
    Polynomial() : monomials({}) {}

    // adding a monomial to a polynomial
    void push(const Monomial& monomial) {
        for (auto el = monomials.begin(); el != monomials.end(); ++el) {
            if (el->variables == monomial.variables) {
                el->coef += monomial.coef;
                if (el->coef == 0) {
                    monomials.erase(el);
                }
                return;
            }
        }
        if (monomial.coef != 0) {
            monomials.push_back(monomial);
        }
    }


    // Checking the correctness of the input string
    bool isValidInput(const std::string& str) {
        for (char c : str) {
            if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '^' && !std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    // Addition operator
    Polynomial operator+(const Polynomial& other) {
        Polynomial result = *this;
        for (const auto& monomial : other.monomials) {
            result.push(monomial);
        }
        return result;
    }

    // Subtraction operator
    Polynomial operator-(const Polynomial& other) {
        Polynomial result = *this;
        for (auto& monomial : other.monomials) {
            Monomial negative_monomial(monomial);
            negative_monomial.coef = -monomial.coef;
            result.push(negative_monomial);
        }
        return result;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& Polynomial) { // !!!!!!!!!! изменить под свой список с -
        for (std::list<Monomial>::const_iterator el = Polynomial.monomials.begin(); el != Polynomial.monomials.end(); ++el) {
            if (el != Polynomial.monomials.begin()) {
                os << " + ";
            }
            os << *el;
        }
        return os;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Polynomial& Polynomial) {
        std::string str;
        is >> str;
        if (!Polynomial.isValidInput(str)) {
            throw std::invalid_argument("Некорректный ввод");
        }

        std::string monom_str = "";

        if (str[0] == '-') {
            monom_str = "-";
            str = str.substr(1);
        }

        for (char symbol : str) {

            if (symbol == '-') {
                Monomial monom;
                std::istringstream monom_iss(monom_str);
                monom_iss >> monom;
                Polynomial.push(monom);

                monom_str = "-";
            }

            else if (symbol == '+') {
                Monomial monom;
                std::istringstream monom_iss(monom_str);
                monom_iss >> monom;
                Polynomial.push(monom);

                monom_str = "";
            }

            else {
                monom_str += symbol;
            }
        }

        Monomial monom;
        std::istringstream monom_iss(monom_str);
        monom_iss >> monom;
        Polynomial.push(monom);
    }
};
