/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "double_linked_list/double_linked_list.h"

#include "points/2d_points.h"

#include <stdlib.h>
#include <stdio.h>

list* init_double_linked_list()
{
	struct double_linked_list* list;
	list = (struct double_linked_list*) malloc(sizeof(struct double_linked_list));
	

	if (list == NULL) {
		printf("Ya no hay memoria disponible: init_double_linked_list()\n");
		exit(EXIT_FAILURE);
	}

	list->size = 0;
	list->head = list->tail = NULL;

	return list;
}

void destroy_double_linked_list(list* list)
{
	if (list == NULL)
		return;
		
	while(!empty_list(list))
		pop_front(list);

	free(list);
}

int empty_list(list* list)
{
	if (list == NULL) {
		return 1;
	} else if (list->size == 0) {
	 	return 1;
	} else {
		return 0;
	}
}

item* init_list_item()
{
	struct list_item* item;
	item = (struct list_item*) malloc(sizeof(struct list_item));
	
	if (item == NULL) {
		printf("Ya no hay memoria disponible: init_list_item()");
		exit(EXIT_FAILURE);
	}

	item->element = NULL;
	item->left = NULL;
	item->right = NULL;
	
	return item;
}

void destroy_list_item(item* item)
{
	free(item);
}

list* create_copy_list(list* list)
{
	struct double_linked_list* copy;
	copy = init_double_linked_list();
	
	struct list_item* tmp;
	tmp = list->head;
	
	while(tmp != NULL) {
		push_back(copy, tmp->element);
		tmp = tmp->right;
	}

	return copy;
}

void push_back(list* list,  vertex* element)
{
	struct list_item *tmp1, *tmp2;

	tmp2 = init_list_item();
	tmp2->element = element;

	if (empty_list(list)) {
		list->head = list->tail = tmp2;
		list->size += 1;
		return;
	}
	
	tmp1 = list->tail;
	tmp1->right = tmp2;
	
	tmp2->left = tmp1;
  	list->tail = tmp2;
	list->size += 1;
	return;
}

void push_front(list* list, vertex* element)
{
	struct list_item *tmp1, *tmp2;

	tmp2 = init_list_item();

	tmp2->element = element;

	
	if (empty_list(list)) {
		list->head = list->tail = tmp2;
		list->size += 1;
		return;
	}
	
	tmp1 = list->head;
	tmp1->left = tmp2;
	
	tmp2->right = tmp1;
	list->head = tmp2;

	list->size += 1;
	return;
}

vertex* pop_back(list* list)
{
	
	if (empty_list(list))
		return NULL;

	struct list_item *tmp1, *tmp2;
	tmp1 = list->tail;
	tmp2 = tmp1->left;
	
	vertex* element;
	
	list->size -= 1;
	if (list->size == 0) {
		list->head = list->tail = NULL;
	} else {
		tmp2->right = NULL;
		list->tail = tmp2;
	}
	
	element = tmp1->element;
	destroy_list_item(tmp1);
	
	return element;
}

vertex* pop_front(list* list)
{
	if (empty_list(list)) 
		return NULL;

	struct list_item *tmp1, *tmp2;
	tmp1 = list->head;	
	tmp2 = tmp1->right;
	
	vertex* element;
	
	list->size -= 1;
	if (list->size == 0) {
		list->head = list->tail = NULL;
	} else {
		tmp2->left = NULL;
		list->head = tmp2;
	}

	element = tmp1->element;

	destroy_list_item(tmp1);
	return element;
}

vertex* pick_back(list* list)
{
	if (empty_list(list))
		return NULL;
	else
		return list->tail->element;
}

vertex* pick_front(list* list)
{
	if (empty_list(list))
		return NULL;
	else
		return list->head->element;
}
