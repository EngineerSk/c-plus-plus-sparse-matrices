#include <iostream>

using namespace std;

struct Element {
    int rowNumber, columnNumber, element;
};

struct Sparse {
    int numberOfRows, numberOfColumns, numberOfNonZeroElements;
    struct Element *nonZeroElements;
};

void create(struct Sparse *sparse) {
    printf("Enter sparse array dimension");
    scanf("%d%d", &sparse->numberOfRows, &sparse->numberOfColumns);
    printf("\n");
    printf("Enter number of non-zero array elements");
    scanf("%d", &sparse->numberOfNonZeroElements);
    printf("Enter non zero array elements");
    sparse->nonZeroElements = (Element *) malloc(sparse->numberOfNonZeroElements * sizeof(struct Element));
    for (int i = 0; i < sparse->numberOfNonZeroElements; ++i) {
        printf("Enter row number, column number and element");
        scanf("%d%d%d", &sparse->nonZeroElements[i].rowNumber, &sparse->nonZeroElements[i].columnNumber,
              &sparse->nonZeroElements[i].element);
    }
}

struct Sparse *add(const struct Sparse *sparse1, const struct Sparse *sparse2) {
    auto *sum = (struct Sparse *) malloc(sizeof(struct Sparse));
    sum->numberOfRows = sparse1->numberOfRows;
    sum->numberOfColumns = sparse1->numberOfColumns;
    int sumNonZeroElementsArrayMaximumSize = sparse1->numberOfNonZeroElements + sparse2->numberOfNonZeroElements;
    sum->nonZeroElements = (struct Element *) malloc(sumNonZeroElementsArrayMaximumSize * sizeof(struct Element));

    int i, j, k;
    i = j = k = 0;
    while (i < sparse1->numberOfNonZeroElements && j < sparse2->numberOfNonZeroElements) {
        if (sparse1->nonZeroElements[i].rowNumber < sparse2->nonZeroElements[j].rowNumber)
            sum->nonZeroElements[k++] = sparse1->nonZeroElements[i++];
        else if (sparse1->nonZeroElements[i].rowNumber > sparse2->nonZeroElements[j].rowNumber)
            sum->nonZeroElements[k++] = sparse2->nonZeroElements[j++];
        else {
            if (sparse1->nonZeroElements[i].columnNumber < sparse2->nonZeroElements[j].columnNumber)
                sum->nonZeroElements[k++] = sparse1->nonZeroElements[i++];
            else if (sparse1->nonZeroElements[i].columnNumber > sparse2->nonZeroElements[j].columnNumber)
                sum->nonZeroElements[k++] = sparse2->nonZeroElements[j++];
            else {
                sum->nonZeroElements[k] = sparse1->nonZeroElements[i++];
                sum->nonZeroElements[k++].element += sparse2->nonZeroElements[j++].element;
            }
        }
    }
    while (i < sparse1->numberOfNonZeroElements)
        sum->nonZeroElements[k++] = sparse1->nonZeroElements[i++];
    while (j < sparse2->numberOfNonZeroElements)
        sum->nonZeroElements[k++] = sparse2->nonZeroElements[j++];
    sum->numberOfNonZeroElements = k;
    return sum;
}

void displayArray(const struct Sparse sparse) {
    struct Element *nonZeroElements = sparse.nonZeroElements;
    int k = 0;

    for (int i = 0; i < sparse.numberOfRows; ++i) {
        for (int j = 0; j < sparse.numberOfColumns; ++j) {
            if (nonZeroElements[k].rowNumber == i && nonZeroElements[k].columnNumber == j)
                printf("%d ", nonZeroElements[k++].element);
            else
                printf("0 ");
        }
        printf("\n");
    }

}

int main() {
    struct Sparse sparse1{}, sparse2{}, *sparse3;
    create(&sparse1);
    create(&sparse2);
    sparse3 = add(&sparse1, &sparse2);
    printf("First sparse matrix: \n");
    displayArray(sparse1);
    printf("Second sparse matrix: \n");
    displayArray(sparse2);
    printf("The sum of First sparse matrix and Second Sparse Matrix is: \n");
    displayArray(*sparse3);
    return 0;
}
