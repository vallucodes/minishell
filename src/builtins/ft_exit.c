#include "../../inc/minishell.h"

// int ft_is_numeric(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str == NULL || str[0] == '\0')
// 		return (0);
// 	if (str[i] == '+' || str[i] == '-')
// 		i++;
// 	if (str[i] == '\0')
// 		return (0);
// 	while (str[i] != '\0')
// 	{
// 		if (!ft_isdigit((unsigned char)str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


#include <stdio.h>

int main(void)
{
	printf("%ld\n", ft_atol("9223372036854775807"));  // LONG_MAX
	printf("%ld\n", ft_atol("9223372036854775808"));  // overflow → LONG_MAX
	printf("%ld\n", ft_atol("-9223372036854775808")); // LONG_MIN
	printf("%ld\n", ft_atol("-9223372036854775809")); // underflow → LONG_MIN
	printf("%ld\n", ft_atol("0000123"));              // 123
	printf("%ld\n", ft_atol("  +42"));                // 42
}



// int ft_exit(t_minishell *mshell)
// {
//     write(1, "exit\n", 5);
// 	//free_all(&mshell);
//     exit(mshell->exitcode);
//     exit(0);
// }
