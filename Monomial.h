#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

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

    //Copy constructor
    Monomial(const Monomial& other) {
        this->coef = other.coef;
        this->variables = other.variables;
    }

    // Addition operator
    Monomial operator+(const Monomial& other) {
        if (this->variables == other.variables) {
            return Monomial(this->coef + other.coef, this->variables);
        }
        else {
            throw std::invalid_argument("Monomials have different variables and cannot be added.");
        }
    }

    // Subtraction operator
    Monomial operator-(const Monomial& other) {
        if (this->variables == other.variables) {
            return Monomial(this->coef - other.coef, this->variables);
        }
        else {
            throw std::invalid_argument("Monomials have different variables and cannot be subtracted.");
        }
    }

    // Getter for variables
    const std::unordered_map<char, int>& getVariables() const {
        return variables;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Monomial& monomial) {
        os << monomial.coef;
        for (const auto& var : monomial.getVariables()) {
            os << "*" << var.first << "^" << var.second;
        }
        return os;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Monomial& monomial) {
        std::string str;
        is >> str;

        int stage = 0;
        std::string int_part = "";
        char var;
        for (int i = 0; i < str.length(); i++) {
            if ((stage == 0) & (str[i] != '*')) {
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
