#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
	int	id;
	struct s_node	*next;
}	t_node;

t_node	*ft_create_node(t_node *linkedlist, int id)
{
	t_node	*newnode;

	newnode = malloc(sizeof(t_node));
	newnode->id = id;
	newnode->next = NULL;
	return (newnode);
}

void	print_list_addr(t_node *linkedlist)
{
	while (linkedlist)
	{
		printf("%p\n", linkedlist);
		linkedlist = linkedlist->next;
	}
}

int	main(void)
{
	t_node	*head;
	t_node	*linkedlist;
	int	i;
	
	linkedlist = ft_create_node(linkedlist, 1);
	head = linkedlist;	
	i = 2;
	while (i < 5)
	{
		linkedlist->next = ft_create_node(linkedlist, i);	
		linkedlist = linkedlist->next;
		i++;
	}
	printf("HEAD BEFORE: %p\n", head);
	print_list_addr(head);
	printf("HEAD AFTER: %p", head);	
}
