#include "hash_tables.h"

/**
 * hash_table_set - Adds an element to the hash table
 * @ht: Pointer to the hash table
 * @key: The key, cannot be an empty string
 * @value: The value associated with the key, must be duplicated
 *
 * Return: 1 on success, 0 on failure
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	hash_node_t *node, *temp;
	char *value_copy;

	if (ht == NULL || key == NULL || value == NULL || *key == '\0')
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	temp = ht->array[index];

	/* Update value if key already exists */
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
		{
			value_copy = strdup(value);
			if (value_copy == NULL)
				return (0);
			free(temp->value);
			temp->value = value_copy;
			return (1);
		}
		temp = temp->next;
	}

	/* Key not found: create a new node */
	node = malloc(sizeof(hash_node_t));
	if (node == NULL)
		return (0);

	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(node);
		return (0);
	}

	node->value = strdup(value);
	if (node->value == NULL)
	{
		free(node->key);
		free(node);
		return (0);
	}

	/* Insert new node at the beginning (handle collision) */
	node->next = ht->array[index];
	ht->array[index] = node;

	return (1);
}
