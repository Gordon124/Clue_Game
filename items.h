#ifndef ITEMS_H
#define ITEMS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct representing item
struct Item {
    char *name;
    char *description;
    struct Item *next;
};

// goal create an struct Item pointer with the given fields
// param nam: char* representing the name
// param des: char* representing the description
// param nextItem: struct item pointer representing the next item
// return a struct Item pointer with the given information
struct Item *item(char* nam, char* des, struct Item* nextItem);

// goal remove and return item with search_name from linked list link
// param search_name: char* represents the target name that we are looking to remove
// param link: character struct double pointer that represents the head of the list that will be traversed to find the target
// return: returns the character struct pointer with the target name, returns NULL if list does not contain the target
struct Item *item_take(char* search_name, struct Item** link);

// goal print out all names of a items in the itemListt
// param itemList: item struct pointer that represents the head of item list
void prtItemList(struct Item* itemList);

// goal inserts a item to another list of items via head insertion 
// param list: item struct double pointer that represents the head of the list
// param add: item struct pointer that represents the character to be placed in the list
void putItem(struct Item** destination, struct Item* roomItem);

#endif
