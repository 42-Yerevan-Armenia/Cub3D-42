#include <stdio.h>

typedef struct s_map1
{
    char        c;
	int			x;
}				t_map1;

typedef struct s_map
{
	int			x;
    t_map1      a;
}				t_map;


// int main()
// {
//     printf("t_map = %zu\n", sizeof(t_map));
//     printf("t_map1 = %zu\n", sizeof(t_map1));
// }
