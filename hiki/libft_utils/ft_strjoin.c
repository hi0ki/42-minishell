#include "minishell.h"

char    *ft_strjoin(char *s1, char *s2)
{
    char    *ptr;
    int        i;
    int        j;

    i = 0;
    if (!s1 || !s2)
        return (NULL);
    ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) +1);
    if (ptr == NULL)
        return (NULL);
    while (s1[i])
    {
        ptr[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        ptr[i + j] = s2[j];
        j++;
    }
    ptr[i + j] = '\0';
    return (ptr);
}