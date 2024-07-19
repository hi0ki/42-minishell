
#include <stdio.h>

int	ft_strncmp(char *s1, char *s2,int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main ()
{
    
    printf(">>>%d \n", ft_strncmp("HELLO=HAHA", "HELLO", 6));
    
}