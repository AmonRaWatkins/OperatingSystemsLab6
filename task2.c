#include <stdio.h>
#include <stdlib.h>

/* Function declarations */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
void exit_program();

int main(void) {
    int a = 6;
    int b = 3;

    // Array of function pointers for operations
    void (*operations[])(int, int) = {add, subtract, multiply, divide, exit_program};

    while (1) {
        printf("Operand 'a': %d | Operand 'b': %d\n", a, b);
        printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : multiply | 3 : divide | 4 : exit): ");

        char input = getchar();
        getchar(); // Consume the newline character

        // Convert input character to index
        int index = input - '0';

        // Use the index to call the appropriate function
        // If index is out of bounds (negative or greater than 4), it will call exit_program by default.
        (index >= 0 && index <= 4 ? operations[index] : exit_program)();

        if (index >= 0 && index < 4) {
            // Only perform operations if the index is valid
            operations[index](a, b);
        }
    }

    return 0;
}

/* Function definitions */
int add(int a, int b) {
    printf("Adding 'a' and 'b'\n");
    return a + b;
}

int subtract(int a, int b) {
    printf("Subtracting %d from %d\n", b, a);
    return a - b;
}

int multiply(int a, int b) {
    printf("Multiplying %d and %d\n", a, b);
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 0;
    }
    printf("Dividing %d by %d\n", a, b);
    return a / b;
}

void exit_program() {
    printf("Exiting the program.\n");
    exit(0);
}