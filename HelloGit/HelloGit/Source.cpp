#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    void normalize() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction() : numerator(0), denominator(1) {}

    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        normalize();
    }
    0
    Fraction(int num) : numerator(num), denominator(1) {}

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    Fraction operator+(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(
            numerator * other.numerator,
            denominator * other.denominator
        );
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Деление на ноль");
        }
        return Fraction(
            numerator * other.denominator,
            denominator * other.numerator
        );
    }

    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
};

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.getNumerator() << "/" << frac.getDenominator();
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& frac) {
    int num, denom;
    char slash;

    is >> num >> slash >> denom;

    if (slash != '/') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (denom == 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    frac = Fraction(num, denom);
    return is;
}

int main() {
    try {
        Fraction a(1, 2);
        Fraction b(2, 3);

        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;

        std::cout << "a + b = " << a + b << std::endl;
        std::cout << "a - b = " << a - b << std::endl;
        std::cout << "a * b = " << a * b << std::endl;
        std::cout << "a / b = " << a / b << std::endl;

        Fraction c(1, 3);
        std::cout << "\nc = " << c << std::endl;

        c += Fraction(1, 6);
        std::cout << "c += 1/6 -> " << c << std::endl;

        c *= Fraction(2, 1);
        std::cout << "c *= 2 -> " << c << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}