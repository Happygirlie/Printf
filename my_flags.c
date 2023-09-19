#include "main.h"

/**
 * get_my_flags - This program calculates active flags
 * @frmat: The formatted string to print the arguments to
 * @j: The parameter
 * Return: Flags
 */
int get_my_flags(const char *frmat, int *j)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int k, curr_a;
	int flags = 0;
	const char FLGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_a = *j + 1; frmat[curr_a] != '\0'; curr_a++)
	{
		for (k = 0; FLGS_CH[k] != '\0'; k++)
			if (frmat[curr_a] == FLGS_CH[k])
			{
				flags |= FLGS_ARR[k];
				break;
			}

		if (FLGS_CH[k] == 0)
			break;
	}

	*j = curr_a - 1;

	return (flags);
}
