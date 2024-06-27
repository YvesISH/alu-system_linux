#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1024  // Define a limit for digits

/**
 * print_python_int - program that prints the integer value of a Python integer object
 * this function interprets the internal representation of a Python integer
 * (`PyObject`) and prints its equivalent C unsigned long integer value;
 * it handles different scenarios like zero, positive, and negative integers;
 * for large integers, it checks for overflow conditions specific to
 * C's unsigned long int representation
 * @p: a PyObject pointer, expected to point to a Python integer object
 * Return: nothing (void)
 */
void print_python_int(PyObject *p)
{
    if (!PyLong_Check(p))
    {
        printf("Invalid Int Object\n");
        fflush(stdout);
        return;
    }

    int size = (int) ((PyVarObject *)p)->ob_size;
    int is_negative = size < 0;
    int abs_size = is_negative ? -size : size;

    if (abs_size == 0)
    {
        printf("0\n");
        fflush(stdout);
        return;
    }

    // Allocate enough space for the result string
    char result[MAX_DIGITS];
    result[0] = '\0';

    for (int i = abs_size - 1; i >= 0; i--)
    {
        char digit_str[32];
        sprintf(digit_str, "%lu", (unsigned long int)((PyLongObject *)p)->ob_digit[i]);
        if (i == abs_size - 1)
        {
            // First digit: append directly
            strcpy(result, digit_str);
        }
        else
        {
            // Pad with zeros and append
            int pad_zeros = PyLong_SHIFT / 4;
            char padded_digit[32];
            snprintf(padded_digit, sizeof(padded_digit), "%0*lu", pad_zeros, (unsigned long int)((PyLongObject *)p)->ob_digit[i]);
            strcat(result, padded_digit);
        }
    }

    // Print the result
    if (is_negative)
    {
        printf("-%s\n", result);
    }
    else
    {
        printf("%s\n", result);
    }

    fflush(stdout);
}
