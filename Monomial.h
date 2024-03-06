#include <unordered_map>
#include <iostream>
#include "helper_functions.h"

class Monomial {
public:
    double coef;        // monom's coefficient
    std::unordered_map<char, int> variables;        // monomial variables and their powers

    // Constructor
    Monomial(double coef, const std::unordered_map<char, int>& variables) {
        this->coef = coef;
        this->variables = variables;
    }

    // Default constructor
    Monomial() {
        coef = 0;
        variables = {};
    }

    // Constructor from string
    Monomial(std::string str) {
        if (!is_valid_input(str)) {
            throw std::invalid_argument("Invalid input");
        }

        int stage = 0;
        std::string int_part = "";
        char var;
        for (int i = 0; i < str.length(); i++) {
            if ((stage == 0) & (str[i] != '*')) {
                int_part += str[i];
            }
            else if ((stage == 0) & (str[i] == '*')) {
                this->coef = std::stoi(int_part);
                int_part = "";
                stage = 1;
            }
            else if (stage == 1) {
                var = str[i];
                stage = 2;
            }
            else if (stage == 2) {
                stage = 3;
            }
            else if ((stage == 3) & (str[i] != '*')) {
                int_part += str[i];
            }
            else if ((stage == 3) & (str[i] == '*')) {
                this->variables[var] = std::stoi(int_part);
                int_part = "";
                stage = 1;
            }
            else {
                std::cout << "Unexpected input element: " << str[i] << std::endl;
            }
        }
        if ((stage == 0) & (int_part != "")) {
            this->coef = std::stoi(int_part);
        }
        else if (stage == 3) {
            this->variables[var] = std::stoi(int_part);
        }
    }

    // Addition operator
    Monomial operator+(const Monomial& other) const{
        if (this->variables == other.variables) {
            return Monomial(this->coef + other.coef, this->variables);
        }
        else {
            throw std::invalid_argument("Monomials have different variables and cannot be added.");
        }
    }

    // Subtraction operator
    Monomial operator-(const Monomial& other) const{
        if (this->variables == other.variables) {
            return Monomial(this->coef - other.coef, this->variables);
        }
        else {
            throw std::invalid_argument("Monomials have different variables and cannot be subtracted.");
        }
    }

    // Multiplication by scalar
    Monomial operator*(const double scalar) const {
        Monomial result;
        result.coef = this->coef * scalar;
        result.variables = this->variables;
        return result;
    }

    // Multiplication by monomial
    Monomial operator*(const Monomial& other) const {
        Monomial result;
        result.coef = this->coef * other.coef;
        result.variables = this->variables;

        for (const auto& var : other.variables) {
            if (result.variables.count(var.first)) {
                result.variables[var.first] += var.second;
            }
            else {
                result.variables[var.first] = var.second;
            }
            if (result.variables.count(var.first) == 0) {
                result.variables.erase(var.first);
            }
        }

        return result;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Monomial& monomial) {
        os << monomial.coef;
        for (const auto& var : monomial.variables) {
            os << "*" << var.first << "^" << var.second;
        }
        return os;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Monomial& monomial) {
        monomial.coef = 0;
        monomial.variables = {};

        std::string str;
        std::getline(is, str);
        if (!is_valid_input(str)) {
            throw std::invalid_argument("Invalid input");
        }

        int stage = 0;
        std::string int_part = "";
        char var;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ') {
                continue;
            }
            else if ((stage == 0) & (str[i] != '*')) {
                int_part += str[i];
            }
            else if ((stage == 0) & (str[i] == '*')) {
                monomial.coef = std::stoi(int_part);
                int_part = "";
                stage = 1;
            }
            else if (stage == 1) {
                var = str[i];
                stage = 2;
            }
            else if (stage == 2) {
                stage = 3;
            }
            else if ((stage == 3) & (str[i] != '*')) {
                int_part += str[i];
            }
            else if ((stage == 3) & (str[i] == '*')) {
                monomial.variables[var] = std::stoi(int_part);
                int_part = "";
                stage = 1;
            }
            else {
                std::cout << "Unexpected input element: " << str[i] << std::endl;
            }
        }
        if ((stage == 0) & (int_part != "")) {
            monomial.coef = std::stoi(int_part);
        }
        else if (stage == 3) {
            monomial.variables[var] = std::stoi(int_part);
        }
        return is;
    }
};

