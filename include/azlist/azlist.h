#ifndef __AZLIST_H__
#define __AZLIST_H__
#include <stddef.h>

enum status { AZLIST_SUCCESS, AZLIST_MALLOC_FAILED, AZLIST_WRONG_POSITION };

typedef struct aznode aznode;
struct aznode {
	size_t size;
	void *data;
	struct aznode *next;
};

typedef struct azlist azlist;
struct azlist {
	struct aznode *head;
	size_t length;
};

azlist *azlist_create(void);
void azlist_delete(azlist *list);
size_t azlist_length(azlist *list);
int azlist_put(azlist *list, int pos, void *data, size_t size);
int azlist_del(azlist *list, int pos, void **data_ptr, size_t *size_ptr);
int azlist_set(azlist *list, int pos, void *data, size_t size);
int azlist_get(azlist *list, int pos, void **data_ptr, size_t *size_ptr);

#endif
