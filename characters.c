#include "characters.h"
#include "rooms.h"
#include "items.h"

struct Character* makeProfile(char* name, struct Room *room, struct Character* person){
  struct Character *newPerson = (struct Character*)malloc(sizeof(struct Character));
  newPerson -> name = name;
  newPerson -> curLoc = room;
  newPerson -> next = person;
  return newPerson;
}

struct Player* newPlayer(char* name, struct Room *room, struct Item *inventory){
  struct Player *player = (struct Player*)malloc(sizeof(struct Character));
  player -> name = name;
  player -> curLoc = room;
  player -> inventory = inventory;
  return player;
}

//change a characters pointer location to murder room
void move_character(struct Character* person, struct Room* murderRoom){
  person -> curLoc = murderRoom;
}

//add character to list via head inseration
void putCharacter(struct Character** list, struct Character* add){
  add -> next = *list;
  *list = add;
}

//Changes player location to DIRECTION
void room_exit_north(struct Player* player){
  player->curLoc = player->curLoc->north;
}

void room_exit_east(struct Player* player){
  player->curLoc = player->curLoc->east;
}

void room_exit_south(struct Player* player){
  player->curLoc = player->curLoc->south;
}

void room_exit_west(struct Player* player){
  player->curLoc = player->curLoc->west;
}

// prints out the character list given the head
void prtCList(struct Character* cList){
  if (cList ==NULL)
    printf("Empty");
  else{
    struct Character* temp = cList;
    // loops through the list of characters in a room and prints them
    while (temp!=NULL){
      printf("%s ",temp->name);
      temp = temp->next;
    }
  }
}

// checks if the second command typed is valid
bool contains(struct Player* player, char* firstCommand, char* secondCommand, struct Character* characterArr[5]){
  
  if (strcmp(firstCommand,"take")==0){
    //check to see if the item in secondCommand is in the current room
    struct Item* temp = player->curLoc->items;
    while (temp!=NULL){
      if (strcmp(temp->name,secondCommand)==0)
        return true;
      temp = temp->next;
    }
  }
  if (strcmp(firstCommand,"drop")==0){
    struct Item* temp = player->inventory;
    //check if the item in secoond command is in the inventory
    while (temp!=NULL){
      if (strcmp(temp->name,secondCommand)==0)
        return true;
      temp = temp->next;
    }
  }
  if (strcmp(firstCommand,"clue")==0){
    //checks to see if the character in second command exist in the game
    for (int i = 0; i < 5; i ++){
      if (strcmp(characterArr[i]->name,secondCommand)==0)
        return true;
    }
  }
  if (strcmp(firstCommand,"go")==0){
    // checks if the direction in second command is a north east west south
    // and checks to see if the room has an exit in that direction
    if (strcmp("north",secondCommand)==0 && player->curLoc->north !=NULL)
      return true;
    if (strcmp("east",secondCommand)==0 && player->curLoc->east !=NULL)
      return true;
    if (strcmp("south",secondCommand)==0 && player->curLoc->south !=NULL)
      return true;
    if (strcmp("west",secondCommand)==0 && player->curLoc->west !=NULL)
      return true;
  }
  return false;
}

//returns the amount of matches from a clue command
bool clueMatch(char* answers[3],struct Player* player){
  bool itemMatch = false;
  bool characterMatch = false;
  struct Item* temp = player->curLoc->items;

  // checks if the roomatches wit the correct room in answers[0]
  bool roomMatch = (strcmp(answers[0],player->curLoc->description)==0) ? true:false;
  
  //loops through the item list and looks for the correct item stored in answer
  while (temp!=NULL){
    if (strcmp(temp->name,answers[1])==0)
      itemMatch = true;
    temp = temp->next;
  }
  
 // checks to see if correct item is in inventory
  temp = player->inventory;
  while (temp!=NULL){
    if (strcmp(temp->name,answers[1])==0)
      itemMatch = true;
    temp = temp->next;
  }
  
  // checks to see if the correct character is in the character list in the room
  struct Character* ctemp = player->curLoc->cList;
    while (ctemp!=NULL){
      if (strcmp(ctemp->name,answers[2])==0)
        characterMatch = true;
      ctemp = ctemp->next;
  }
  // prints outs whether room item and characters are a match
  if (roomMatch)
    printf("Room MATCH\n");
  if (itemMatch)
    printf("Item MATCH\n");
  if (characterMatch)
    printf("Character MATCH\n");
 
  // returns whether there is 3 matches or not
  return(roomMatch && itemMatch && characterMatch);
} 

struct Character* character_take(char* search_name, struct Character** link){
  struct Character* current = *link;
  struct Character *prev = NULL;
  struct Character* returnCharacter;
  // loops through ands looks for the character with search_name
  // removes its from list and returns it
  while(current!=NULL){
    if (strcmp(search_name, current-> name) == 0){
      // if head is the target node
      if (prev == NULL){
        returnCharacter = *link;
        *link = current->next;
      }
      // all other cases
      else{
        returnCharacter = current;
        prev->next = current->next;
      }
      return returnCharacter;
   }
    prev = current;
    current = current->next;
  }
  return NULL;
}
 
