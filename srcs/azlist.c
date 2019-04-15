#include "azlist/azlist.h"
#include <stdlib.h>
#include <string.h>

azlist *azlist_create(void)
{
	azlist *list = malloc(sizeof(*list));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	list->length = 0;
	return list;
}

void azlist_delete(azlist *list)
{
	if (list == NULL)
		return;
	for (aznode *node = list->head; node != NULL; list->head = node) {
		node = list->head->next;
		if (list->head->data != NULL)
			free(list->head->data);
		free(list->head);
	}
	list->head = NULL;
	list->length = 0;
	free(list);
}

size_t azlist_length(azlist *list)
{
	return list->length;
}

int azlist_put(azlist *list, int pos, void *data, size_t size)
{
	pos = pos < 0 ? list->length + pos : pos;
	pos = pos > list->length ? list->length : pos;
	aznode *node = malloc(sizeof(*node));
	if (node == NULL)
		return AZLIST_MALLOC_FAILED;
	node->size = size;
	node->data = malloc(node->size);
	memcpy(node->data, data, node->size);
	if (pos == 0) {
		node->next = list->head;
		list->head = node;
	} else {
		aznode *prev = list->head;
		for (size_t i = 0; i < pos - 1; ++i)
			prev = prev->next;
		node->next = prev->next;
		prev->next = node;
	}
	++(list->length);
	return AZLIST_SUCCESS;
}

int azlist_del(azlist *list, int pos, void **data_ptr, size_t *size_ptr)
{
	pos = pos < 0 ? list->length + pos : pos;
	if (pos >= list->length)
		return AZLIST_WRONG_POSITION;
	if (pos == 0) {
		if (data_ptr != NULL)
			*data_ptr = list->head->data;
		if (size_ptr != NULL)
			*size_ptr = list->head->size;
		aznode *head = list->head;
		list->head = head->next;
		free(head);
	} else {
		aznode *prev = list->head;
		for (size_t i = 0; i < pos - 1; ++i)
			prev = prev->next;
		if (data_ptr != NULL)
			*data_ptr = prev->next->data;
		else
			free(prev->next->data);
		if (size_ptr != NULL)
			*size_ptr = prev->next->size;
		aznode *next = prev->next;
		prev->next = next->next;
		free(next);
	}
	--(list->length);
	return AZLIST_SUCCESS;
}

int azlist_set(azlist *list, int pos, void *data, size_t size)
{
	pos = pos < 0 ? list->length + pos : pos;
	if (pos >= list->length)
		return AZLIST_WRONG_POSITION;
	aznode *curr = list->head;
	for (size_t i = 0; i < pos; ++i)
		curr = curr->next;
	curr->data = data;
	curr->size = size;
	return AZLIST_SUCCESS;
}

int azlist_get(azlist *list, int pos, void **data_ptr, size_t *size_ptr)
{
	pos = pos < 0 ? list->length + pos : pos;
	if (pos >= list->length)
		return AZLIST_WRONG_POSITION;
	aznode *curr = list->head;
	for (size_t i = 0; i < pos; ++i)
		curr = curr->next;
	if (data_ptr != NULL)
		*data_ptr = curr->data;
	if (size_ptr != NULL)
		*size_ptr = curr->size;
	return AZLIST_SUCCESS;
}
