#include <stdexcept>
#include <unordered_map>
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include "Monomial.h"

class Polynomial {
public:
    std::list<Monomial> monoms;     // list of monomials

    // Default constructor
    Polynomial() {
        monoms = {};
    }

    // Adding a monomial to a polynomial
    void push(const Monomial& monomial) {
        for (auto it = monoms.begin(); it != monoms.end(); ++it) {
            if (it->variables == monomial.variables) {
                it->coef += monomial.coef;
                if (it->coef == 0) {
                    monoms.erase(it);
                }
                return;
            }
        }
        if (monomial.coef != 0) {
            monoms.push_back(monomial);
        }
    }

    // Метод для проверки корректности входной строки
    bool isValidInput(const std::string& str) {
        for (char c : str) {
            if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '^' && !std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    // Оператор сложения
    Polynomial operator+(const Polynomial& other) {
        Polynomial result = *this;
        for (const auto& monom : other.monoms) {
            result.push(monom);
        }
        return result;
    }

    // Оператор вычитания
    Polynomial operator-(const Polynomial& other) {
        Polynomial result = *this;
        for (auto& monom : other.monoms) {
            Monomial negative_monom(monom);
            negative_monom.coef = -monom.coef;
            result.push(negative_monom);
        }
        return result;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& Polynomial) {
        for (std::list<Monomial>::const_iterator it = Polynomial.monoms.begin(); it != Polynomial.monoms.end(); ++it) {
            if (it != Polynomial.monoms.begin()) {
                os << " + ";
            }
            os << *it;
        }
        return os;
    }

    // Оператор ввода
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