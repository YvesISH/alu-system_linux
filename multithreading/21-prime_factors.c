#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * prime_factors - factors a number into a list of prime factors
 * @s: string representation of the number to factor
 * Return: list_t of prime factors
 **/
list_t *prime_factors(char const *s) {
    unsigned long n = strtoul(s, NULL, 10);
    unsigned long *tmp, p = 2;
    list_t *list = malloc(sizeof(list_t));

    list_init(list);
    while (p * p <= n) {
        while (n % p == 0) {
            tmp = malloc(sizeof(unsigned long));
            *tmp = p;
            list_add(list, (void *)tmp);
            n /= p;
        }

        p += 1 + (p != 2);
    }

    if (n >= 2) {
        tmp = malloc(sizeof(unsigned long));
        *tmp = n;
        list_add(list, (void *)tmp);
    }
    return (list);
}

static void print_factors(char const *s, list_t const *factors) {
    list_node_t *current = factors->head;
    printf("Prime factors of %s: ", s);
    while (current != NULL) {
        printf("%lu ", *(unsigned long *)current->data);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int i;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s number...\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; ++i) {
        list_t *factors = prime_factors(argv[i]);
        print_factors(argv[i], factors);
        list_destroy(factors);
        free(factors);
    }

    return 0;
}

