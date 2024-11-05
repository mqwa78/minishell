
#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (count);
	while (s[count])
		count++;
	return (count);
}
