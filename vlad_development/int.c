#include <stdio.h>
#include <limits.h>

static size_t	lenint(unsigned int n)
{
	size_t	len;

	len = 0;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

unsigned int get_signess(int sign, int n)
{
	unsigned int	unsigned_n;

	if (sign)
		unsigned_n = -(unsigned int)(-(long)n);
	else
		unsigned_n = (unsigned int)n;
	return (unsigned_n);
}


char	*ft_itoa_buf(int n, char *buf, size_t bufsize)
{
	size_t			len;
	int				sign;
	unsigned int	unsigned_n;

	sign = (n < 0);
	unsigned_n = get_signess(sign, n);
	len = lenint(unsigned_n);
	if (sign)
		len++;
	if (len + 1 > bufsize)
		return (NULL);
	buf[len] = '\0';
	while (len > 0)
	{
		len--;
		buf[len] = unsigned_n % 10 + '0';
		unsigned_n /= 10;
	}
	if (sign)
		buf[0] = '-';
	return (buf);
}


int main(void)
{
    char buf[32];
    int test_cases[] = {0, 1, -1, 123, -123, INT_MAX, INT_MIN};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for (size_t i = 0; i < num_cases; ++i)
    {
        if (ft_itoa_buf(test_cases[i], buf, sizeof(buf)) == NULL)
            printf("Error: buffer too small for %d\n", test_cases[i]);
        else
            printf("ft_itoa_buf(%d) = \"%s\"\n", test_cases[i], buf);
    }
    return 0;
}
