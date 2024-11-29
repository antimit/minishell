#include "utils.h"

char	*str_join(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	len1 = s1 ? strlen(s1) : 0;
	len2 = s2 ? strlen(s2) : 0;
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	if (s1)
		strcpy(joined, s1);
	else
		joined[0] = '\0';
	if (s2)
		strcat(joined, s2);
	return (joined);
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}
