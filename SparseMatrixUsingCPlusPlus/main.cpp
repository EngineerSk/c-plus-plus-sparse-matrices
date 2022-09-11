#include <iostream>
#include<stdexcept>

using namespace std;

class Element {
private:
    int rowNumber, columnNumber, element;
public:

    ~Element() = default;

    void setRowNumber(const int row) {
        this->rowNumber = row;
    }

    void setColumnNumber(const int column) {
        this->columnNumber = column;
    }

    void setElement(const int value) {
        this->element = value;
    }

    int getRowNumber() const {
        return this->rowNumber;
    }

    int getColumnNumber() const {
        return this->columnNumber;
    }

    int getElement() const {
        return this->element;
    }
};

class Sparse {
private:
    int numberOfRows, numberOfColumns, numberOfNonZeroElements;
    Element *nonZeroElements;
public:
    explicit Sparse() {
        this->numberOfRows = 0;
        this->numberOfColumns = 0;
        this->numberOfNonZeroElements = 0;
        nonZeroElements = new Element[0];
    }

    Sparse(const int rows, const int columns, const int totalElements) {
        this->numberOfRows = rows;
        this->numberOfColumns = columns;
        this->numberOfNonZeroElements = totalElements;
        this->nonZeroElements = new Element[totalElements];
    }

    ~Sparse() {
        delete[] nonZeroElements;
    }

    friend istream &operator>>(istream &is, const Sparse &sparse);

    friend ostream &operator<<(ostream &os, const Sparse &sparse);

    Sparse operator+(const Sparse &sparse) const;

    void setNumberOfRows(const int totalRows) {
        this->numberOfRows = totalRows;
    }

    void setNumberOfColumns(const int totalColumns) {
        this->numberOfColumns = totalColumns;
    }

    void setNumberOfNonZeroElements(const int totalElements) {
        this->numberOfNonZeroElements = totalElements;
    }

    void setNonZeroElements(const int totalElements) {
        if (totalElements <= (this->numberOfRows * this->numberOfColumns) && totalElements >= 0)
            this->nonZeroElements = new Element[totalElements];
        else
            this->nonZeroElements = new Element[0];
    }

    int getNumberOfRows() const {
        return this->numberOfRows;
    }

    int getNumberOfColumns() const {
        return this->numberOfColumns;
    }

    int getNumberOfNonZeroElements() const {
        return this->numberOfNonZeroElements;
    }

    Element *getNonZeroElements() const {
        return this->nonZeroElements;
    }
};

istream &operator>>(istream &is, const Sparse &sparse) {
    cout << "Enter non-zero elements" << endl;
    for (int i = 0; i < sparse.getNumberOfNonZeroElements(); ++i) {
        int rowNumber, columnNumber, element;
        cin >> rowNumber >> columnNumber >> element;
        sparse.getNonZeroElements()[i].setRowNumber(rowNumber);
        sparse.getNonZeroElements()[i].setColumnNumber(columnNumber);
        sparse.getNonZeroElements()[i].setElement(element);
    }
    return is;
}

ostream &operator<<(ostream &os, const Sparse &sparse) {
    int k = 0;
    for (int i = 0; i < sparse.getNumberOfRows(); ++i) {
        for (int j = 0; j < sparse.getNumberOfColumns(); ++j) {
            if (sparse.getNonZeroElements()[k].getRowNumber() == i &&
                sparse.getNonZeroElements()[k].getColumnNumber() == j &&
                k < sparse.getNumberOfNonZeroElements())
                cout << sparse.getNonZeroElements()[k++].getElement() << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    return os;
}

Sparse Sparse::operator+(const Sparse &sparse) const {
    if (this->numberOfRows != sparse.numberOfRows || this->numberOfColumns != sparse.numberOfColumns) {
        return Sparse();
    }
    auto *result = new Sparse(this->numberOfRows, this->numberOfColumns,
                              this->numberOfNonZeroElements + sparse.numberOfNonZeroElements);

    int i, j, k;
    i = j = k = 0;
    while (i < this->numberOfNonZeroElements && j < sparse.numberOfNonZeroElements) {
        if (this->nonZeroElements[i].getRowNumber() < sparse.nonZeroElements[j].getRowNumber())
            result->nonZeroElements[k++] = this->nonZeroElements[i++];
        else if (this->nonZeroElements[i].getRowNumber() > sparse.nonZeroElements[j].getRowNumber())
            result->nonZeroElements[k++] = sparse.nonZeroElements[j++];
        else {
            if (this->nonZeroElements[i].getColumnNumber() < sparse.nonZeroElements[j].getColumnNumber()) {
                result->nonZeroElements[k++] = this->nonZeroElements[i++];
            } else if (this->nonZeroElements[i].getColumnNumber() > sparse.nonZeroElements[j].getColumnNumber()) {
                result->nonZeroElements[k++] = sparse.nonZeroElements[j++];
            } else {
                result->nonZeroElements[k] = this->nonZeroElements[i];
                result->nonZeroElements[k++].setElement(
                        this->nonZeroElements[i++].getElement() + sparse.nonZeroElements[j++].getElement()
                        );
            }
        }
    }
    while (i < this->numberOfNonZeroElements)
        result->nonZeroElements[k++] = this->nonZeroElements[i++];

    while (j < sparse.numberOfNonZeroElements)
        result->nonZeroElements[k++] = sparse.nonZeroElements[j++];

    result->numberOfNonZeroElements = k;
    return *result;
}


int main() {
    Sparse s1(5, 5, 0), s2(5, 5, 7);
    cin >> s1;
    cin >> s2;
    cout << "First Matrix: \n" << s1;
    cout << "Second Matrix: \n" << s2;
    cout << "Sum Matrix: \n" << s1 + s2;
}
