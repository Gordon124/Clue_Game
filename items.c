#include "items.h"

struct Item *item(char* nam, char* des, struct Item* nextItem){
  // allocate space for *item based on the struct definition
  struct Item *item = (struct Item*) malloc(sizeof(struct Item));  
  item -> name = nam;
  item -> description = des;
  item -> next = nextItem;
  return item;
}

//prints the item list given the head of the list
void prtItemList(struct Item* itemList){
  if (itemList ==NULL)
    printf("Empty");
  else{
    struct Item* temp = itemList;
    //traverse and prints name of linked list
    while (temp!=NULL){
      printf("%s ",temp->name);
      temp = temp->next;
    }
  }
}

// returns and remove the item with search_name
struct Item* item_take(char* search_name, struct Item** link){
  struct Item *current = *link;
  struct Item *prev = NULL;
  struct Item* returnItem;
  while(current!=NULL){
    if (strcmp(search_name, current-> name) == 0){
     // edge case when head is the target node
     if (prev == NULL){
        returnItem = *link;
        *link = current->next;
      }
      else{
        returnItem = current;
        prev->next = current->next;
      }
      return returnItem;
    }
    prev = current;
    current = current->next;
    
  }
  return NULL;
}
// add item to list via head insertion 
void putItem(struct Item** destination, struct Item* roomItem){
  roomItem->next = *destination;
  *destination = roomItem;
}

 
