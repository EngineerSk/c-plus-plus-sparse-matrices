#include <iostream>
#include <cmath>

using namespace std;

class Term {
private:
    int coefficient, exponent;
public:
    explicit Term() {
        coefficient = 0;
        exponent = 0;
    }

    Term(int coefficientValue, int expValue) {
        this->coefficient = coefficientValue;
        this->exponent = expValue;
    }

    ~Term() = default;

    void setCoefficient(const int coEfficient) {
        this->coefficient = coEfficient;
    }

    void setExponent(const int expValue) {
        this->exponent = expValue;
    }

    int getCoefficient() const {
        return this->coefficient;
    }

    int getExponent() const {
        return this->exponent;
    }
};

class Polynomial {
private:
    int numberOfNonZeroTerms;
    Term *nonZeroTerms;

public:
    explicit Polynomial() {
        this->numberOfNonZeroTerms = 0;
        this->nonZeroTerms = new Term[numberOfNonZeroTerms];
    }

    explicit Polynomial(int numberOfTerms) {
        this->numberOfNonZeroTerms = numberOfTerms;
        this->nonZeroTerms = new Term[numberOfTerms];
    }

    ~Polynomial() {
        delete[] nonZeroTerms;
    }

    friend istream &operator>>(istream &is, Polynomial &polynomial);

    friend ostream &operator<<(ostream &os, const Polynomial &polynomial);

    Polynomial *operator+(const Polynomial &polynomial);

    void setNumberOfTerms(const int numberOfTerms) {
        this->numberOfNonZeroTerms = numberOfTerms;
    }

    void allocateNonZeroTermsInMemory(const int sizeOfTerms) {
        this->nonZeroTerms = new Term[sizeOfTerms];
    }

    int getNumberOfTerms() const {
        return this->numberOfNonZeroTerms;
    }

    Term *getTerms() const {
        return this->nonZeroTerms;
    }
};

istream &operator>>(istream &is, Polynomial &polynomial) {
    cout << "Enter number of terms" << endl;
    int numberOfTerms;
    cin >> numberOfTerms;
    polynomial.setNumberOfTerms(numberOfTerms);
    polynomial.allocateNonZeroTermsInMemory(numberOfTerms);
    cout << "Enter polynomial terms" << endl;
    for (int i = 0; i < polynomial.getNumberOfTerms(); ++i) {
        cout << "enter coefficient and exponent of polynomial term " << (i + 1) << endl;
        int coefficient, exponent;
        cin >> coefficient >> exponent;
        polynomial.nonZeroTerms[i].setCoefficient(coefficient);
        polynomial.nonZeroTerms[i].setExponent(exponent);
    }
    return is;
}

ostream &operator<<(ostream &os, const Polynomial &polynomial) {
    for (int i = 0; i < polynomial.numberOfNonZeroTerms; ++i) {
        if (abs(polynomial.nonZeroTerms[i].getCoefficient()) >= 1) {
            if (abs(polynomial.nonZeroTerms[i].getCoefficient()) >= 1) {
                if (i > 0 && polynomial.nonZeroTerms[i].getCoefficient() >= 1)
                    cout << " +";
                else if (i >= 0 && polynomial.nonZeroTerms[i].getCoefficient() < 1)
                    cout << " -";
            }
        }
        if (abs(polynomial.nonZeroTerms[i].getCoefficient()) > 1)
            cout << " " << abs(polynomial.nonZeroTerms[i].getCoefficient());
        if (polynomial.nonZeroTerms[i].getExponent() > 0
            && abs(polynomial.nonZeroTerms[i].getCoefficient()) >= 1) {
            if (abs(polynomial.nonZeroTerms[i].getCoefficient()) == 1)
                cout << " ";
            cout << "X^" << polynomial.nonZeroTerms[i].getExponent();
        } else if (polynomial.nonZeroTerms[i].getExponent() == 0
                   && abs(polynomial.nonZeroTerms[i].getCoefficient()) == 1)
            cout << " 1";
    }

    cout << endl;
    return os;
}

Polynomial *Polynomial::operator+(const Polynomial &polynomial) {
    if (this->numberOfNonZeroTerms == 0 && polynomial.numberOfNonZeroTerms == 0)
        return new Polynomial();
    auto *result = new Polynomial(this->numberOfNonZeroTerms + polynomial.numberOfNonZeroTerms);
    int i, j, k;
    i = j = k = 0;
    while (i < this->numberOfNonZeroTerms && j < polynomial.numberOfNonZeroTerms) {
        if (this->nonZeroTerms[i].getExponent() > polynomial.nonZeroTerms[j].getExponent())
            result->nonZeroTerms[k++] = this->nonZeroTerms[i++];
        else if (this->nonZeroTerms[i].getExponent() < polynomial.nonZeroTerms[j].getExponent())
            result->nonZeroTerms[k++] = polynomial.nonZeroTerms[j++];
        else {
            result->nonZeroTerms[k] = this->nonZeroTerms[i];
            result->nonZeroTerms[k++].setCoefficient(
                    this->nonZeroTerms[i++].getCoefficient() + polynomial.nonZeroTerms[j++].getCoefficient());
        }
    }
    while (i < this->numberOfNonZeroTerms) {
        result->nonZeroTerms[k++] = this->nonZeroTerms[i++];
    }
    while (j < polynomial.numberOfNonZeroTerms)
        result->nonZeroTerms[k++] = polynomial.nonZeroTerms[j++];
    result->numberOfNonZeroTerms = k;
    return result;
}


int main() {
    Polynomial first, second;
    cout << "Enter first polynomial: " << endl;
    cin >> first;
    cout << "Enter second polynomial: " << endl;
    cin >> second;
    cout << first;
    cout << second;
    cout << first << " + " << second << " = " << endl << *(first + second) << endl;
    return 0;
}
