#include "multithreading.h"
#include "list.h"

/**
 * prime_factors - factorizes a number into a list of prime factors
 * @s: string representation of the number to factorize
 * Return: pointer to head of doubly-linked list of prime factors
 */
list_t *prime_factors(char const *s)
{
	unsigned long x;
	unsigned long num = 0;
	list_t *factors;

	if (!s)
		return (NULL);

	factors = calloc(1, sizeof(list_t));
	if (!factors)
		return (NULL);

	num = strtoul(s, NULL, 10);

	printf("[%lu]\n", num);

	for (x = 2; x < num; x++)
	{
		while ((num % x) == 0)
		{
			num = num / x;
		}
	}
	list_add(factors, (void *)num);
	return(factors);
}
