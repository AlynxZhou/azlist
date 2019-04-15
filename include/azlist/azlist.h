#ifndef __AZLIST_H__
#define __AZLIST_H__
#include <stddef.h>

enum status { AZLIST_SUCCESS, AZLIST_MALLOC_FAILED, AZLIST_WRONG_POSITION };

typedef struct aznode aznode;
struct aznode {
	void *data;
	struct aznode *next;
};

typedef struct azlist azlist;
struct azlist {
	struct aznode *head;
	size_t size;
	size_t length;
};

azlist *azlist_create(size_t size);
void azlist_delete(azlist *list);
size_t azlist_length(azlist *list);
void *azlist_put(azlist *list, int pos, void *data, void (*assign)(void *, void *));
void *azlist_del(azlist *list, int pos);
void *azlist_set(azlist *list, int pos, void *data, void (*assign)(void *, void *));
void *azlist_get(azlist *list, int pos);

#endif
