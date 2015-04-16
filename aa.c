#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct hash
{
	char *key;
	char *value;
	struct hash *next;
};

void main()
{
	struct hash node1;
	
	node1.key = "asdasdad";
	node1.value = "uiqwueiqweq";

	printf("%s	%s\n", node1.key, node1.value );

	
	struct hash *node1_point = ( struct hash*)malloc(sizeof(struct hash) );

	memset( node1_point, 0, sizeof(struct hash) );

	node1_point->key = (char *)malloc(sizeof(char)*(strlen("hello")+1));
	strcpy( node1_point->key, "hello" );

	node1_point->value = (char *)malloc(sizeof(char)*(strlen("world")+1));
	strcpy( node1_point->value, "world");

	printf("%s	%s\n", node1_point->key, node1_point->value);


}
