#include "../../inc/libft.h"

void	*ft_realloc(void *ptr, unsigned int new_size)
{
	char			*new;
	char			*temp;
	unsigned int	i;

	i = 0;
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	if (new_size == 0)
		return (free(ptr), NULL);
	new = malloc(new_size + 1);
	if (new == NULL)
		return (free(ptr), NULL);
	temp = ptr;
	while (i < new_size && temp[i] != '\0')
		i++;
	return (free(ptr), new);
}
