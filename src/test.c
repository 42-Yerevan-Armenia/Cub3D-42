// typedef struct s_tokens    t_tokens;

// struct s_tokens
// {
//     t_tokens    *next;
//     char        *rdl;
//     char        **cmd;
//     int         *hrd_count;
//     // t_redirects    *head_redct;
// };



// typedef struct s_env    t_env;

//  struct    s_env
// {
//     t_env    *next;
//     char    *key;
//     char    *value;
//     int     flag;
// };

// t_tokens    *new_t_tokens(char *rdl, char **cmd, int *hrd_count)
// {
//     t_tokens    *new_node;

//     new_node = malloc(sizeof(t_tokens));;
//     new_node->rdl = rdl;
//     new_node->cmd = cmd;
//     new_node->hrd_count = hrd_count;
//     // new_node->head_redct = NULL;
//     new_node->next = NULL;
//     return (new_node);
// }

// void    t_redirects_add_back(void **head, void *new_node, size_t size)
// {
//     void    *tmp;

// 	printf("new_node = %p\n", new_node);
//     if (*head == NULL)
//     {
//         *head = new_node;
//         return ;
//     }
//     tmp = *head;
//     // while ((*(char *)(tmp + size - 8))
//     //     tmp = tmp->next;
// 	// (*head) += size;
//    	(**head) = new_node;
// 	*head = tmp;
// }

// int main()
// {
// 	t_tokens	*tmp = NULL;

// 	t_redirects_add_back((void **)&tmp, new_t_tokens("barev\n", NULL, NULL), sizeof(t_tokens));
// 	t_redirects_add_back((void **)&tmp, new_t_tokens("ev\n", NULL, NULL), sizeof(t_tokens));
// 	printf("tmp->next = %p\n", tmp->next);
// 	printf("%s\n", tmp->rdl);
// 	// printf("%s\n", tmp->next->rdl);
// }