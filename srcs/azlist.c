#include "azlist/azlist.h"
#include <stdlib.h>
#include <string.h>

azlist *azlist_create(size_t size)
{
	azlist *list = malloc(sizeof(*list));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	list->size = size;
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
	list->size = 0;
	list->length = 0;
	free(list);
}

size_t azlist_length(azlist *list)
{
	return list->length;
}

void *azlist_put(azlist *list, int pos, void *data, void (*assign)(void *, void *))
{
	pos = pos < 0 ? list->length + pos : pos;
	pos = pos > list->length ? list->length : pos;
	aznode *node = malloc(sizeof(*node));
	if (node == NULL)
		return NULL;
	node->data = malloc(list->size);
	if (assign == NULL)
		memcpy(node->data, data, list->size);
	else
		assign(node->data, data);
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
	return node;
}

void *azlist_del(azlist *list, int pos)
{
	pos = pos < 0 ? list->length + pos : pos;
	if (pos >= list->length)
		return NULL;
	void *ptr = NULL;
	if (pos == 0) {
		ptr = list->head->data;
		aznode *head = list->head;
		list->head = head->next;
		free(head);
	} else {
		aznode *prev = list->head;
		for (size_t i = 0; i < pos - 1; ++i)
			prev = prev->next;
		ptr = prev->next->data;
		aznode *next = prev->next;
		prev->next = next->next;
		free(next);
	}
	--(list->length);
	return ptr;
}

void *azlist_set(azlist *list, int pos, void *data, void (*assign)(void *, void *))
{
	pos = pos < 0 ? list->length + pos : pos;
	if (pos >= list->length)
		return NULL;
	aznode *curr = list->head;
	for (size_t i = 0; i < pos; ++i)
		curr = curr->next;
	if (curr->data != NULL)
		free(curr->data);
	curr->data = malloc(list->size);
	if (assign == NULL)
		memcpy(curr->data, data, list->size);
	else
		assign(curr->data, data);
	return curr;
}

void *azlist_get(azlist *list, int pos)
{
	pos = pos < 0 ? list->length + pos : pos;
	if (pos >= list->length)
		return NULL;
	aznode *curr = list->head;
	for (size_t i = 0; i < pos; ++i)
		curr = curr->next;
	return curr->data;
}
