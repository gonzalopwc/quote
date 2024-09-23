
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*src;

	if (nmemb * size >= SIZE_MAX)
		return (NULL);
	src = malloc(nmemb * size);
	if (src == NULL)
		return (NULL);
	ft_bzero(src, nmemb * size);
	return (src);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*scr;
	int		j;

	i = ft_strlen(s1) + ft_strlen(s2);
	scr = malloc(i + 1);
	if (scr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		scr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		scr[i] = s2[j];
		i++;
		j++;
	}
	scr[i] = '\0';
	return (scr);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_error(char *str, char *file)
{
	char	*msg;

	if (file)
	{
		msg = ft_strjoin(str, file);
		if (!msg)
			return (perror("Error\n"));
		ft_putstr_fd(msg, 2);
	}
	else
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int quote_close(char *str)
{
    int i;
    int close_s;
    int close_d;
    
    i = -1;
    close_s = 1;
    close_d = 1;
    while (str[++i])
    {
        if (str[i] == '\'' && close_d == 1)
            close_s = close_s * -1;
        if (str[i] == '\"' && close_s == 1)
            close_d = close_d * -1;
    }
    if (close_s == -1)
        printf("Error single quote no close\n");
    if (close_d == -1)
        printf("Error double quote no close\n");
    if (close_s == -1 || close_d == -1)
        return (-1);
    return (1);
}


void    *mini_qte(char *str, char *lit, int clsd, int clss)
{
    int i;
    
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\'' && clsd == 1)
        {
            clss = clss * -1;
            lit[i] = 's';
        }
        else if (str[i] == '\"' && clss == 1)
        {
            clsd = clsd * -1;
            lit[i] = 'd';
        }
        else if (clss == -1)
            lit[i] = 's';
        else if (clsd == -1)
            lit[i] = 'd';
        else
            lit[i] = 'n';
    }
}

char    *quote_line(char *str)
{
    int     close_s;
    int     close_d;
    char    *lit;
    
    if (quote_close(str) == -1)
        return (NULL);
    lit = ft_calloc(ft_strlen(str) + 1, sizeof(char));
    if (!lit)
        ft_error("Malloc error", NULL); /*MALLOC MALLOC*/
    close_s = 1;
    close_d = 1;
    mini_qte(str, lit, close_d, close_s);
    return (lit);
}

int jump_line(char *line, int i)
{
    int jump;

    jump = 0;
    if (i == 0 && (line[i] == 's' || line[i] == 'd'))
        jump = 1;
    else if (line[i] == 's' && line[i - 1] != 's')
        jump = 1;
    else if (line[i] == 'd' && line[i - 1] != 'd')
        jump = 1;
    else if (line[i] == 's' && line[i + 1] != 's')
        jump = 1;
    else if (line[i] == 'd' && line[i + 1] != 'd')
        jump = 1;
    return (jump);
}

char    *clean_qt(char *str)
{
    int i;
    int j;
    char    *cl_line;
    char    *line;
    
    cl_line = ft_calloc(ft_strlen(str) + 1, sizeof(char));
    if (!cl_line)
        ft_error("Malloc error", NULL); /*MALLOC MALLOC*/
    line = quote_line(str);
    if (!line)
        ft_error("Malloc error", NULL); /*MALLOC MALLOC*/
    printf("la line es: %s\n");
    i = -1;
    j = -1;
    while (line[++i])
    {
        if (jump_line(line, i) == 1)
            continue ;
        cl_line[++j] = str[i];
    }
    free(line);
    return (cl_line);
}

char    *clean_other(char *str)
{
    int i;
    int j;
    char    *cl_other;
    char    *line;
    
    cl_other = ft_calloc(ft_strlen(str) + 1, sizeof(char));
    if (!cl_other)
        ft_error("Malloc error", NULL); /*MALLOC MALLOC*/
    line = quote_line(str);
    if (!line)
        ft_error("Malloc error", NULL); /*MALLOC MALLOC*/
    i = -1;
    j = -1;
    while (line[++i])
    {
        if (jump_line(line, i) == 1)
            continue ;
        cl_other[++j] = line[i];
    }
    free(line);
    return (cl_other);
}

int main() {
    //char *str = "\"\"hola\'\"\'";
    char *str = "\'\'\"\'\'\"\'efjol\' \'\'\"\'\"";
    printf("str: %s\n", str);
    char *cl = clean_qt(str);
    char *ocl = clean_other(str);
    printf("\nEste es cl : %s\n", cl);
    printf("\nEste es ocl : %s\n", ocl);
    free(ocl);
    free(cl);
    return 0;
}
