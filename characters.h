#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// struct representing Character
struct Character {
  char* name;
  struct Room* curLoc;
  struct Character* next;
};

//struct representing Player
struct Player{
  char* name;
  struct Room* curLoc;
  struct Item* inventory;
};

// goal create a player struct given a name, room and inventory
// param name: char* representing the name
// param room: room struct pointer  representing the room
// param item: item struct pointer representing the inventory
// return: a player struct pointer with the specified fields
struct Player* newPlayer(char* name, struct Room *room, struct Item *inventory);

// goal create a character struct given a name, room and inventory
// param name: char* representing the name
// param room: room struct pointer  representing the room
// param item: item struct pointer representing the inventory
// return: a character struct pointer with the specified fields
struct Character* makeProfile(char* name, struct Room *room, struct Character* person);

// goal change a characters location to another room
// param person: character struct pointer representing the characater that is to be moved
// param murderRoom: a room struct pointer represeting the room that character will be placed in
void move_character(struct Character* person, struct Room* murderRoom);

// goal inserts a character node to another list  via head insertion 
// param list: character struct double pointer that represents the head of the list
// param add: charatcer struct pointer that represents the character to be placed in the list
void putCharacter(struct Character** list, struct Character* add);

// goal print out all names of a character list
// param cList: character struct pointer that represents the head of list
void prtCList(struct Character* cList);

// goal change the player location to north
// param player: player struct pointer that represents the player
void room_exit_north(struct Player* player);

// goal change the player location to east
// param player: player struct pointer that represents the player
void room_exit_east(struct Player* player);

// goal change the player location to south
// param player: player struct pointer that represents the player
void room_exit_south(struct Player* player);

// goal change the player location to west
// param player: player struct pointer that represents the player 
void room_exit_west(struct Player* player);

// goal determine the the number of matches
// param answers: char* array that contains the answers for the game
// param player: player struct pointer that represents the player  
// prints: prints Match for room, item or character if the player location is a correct, correct item and character is in the room
// return: boolean that represents if there is 3 matches 
bool clueMatch(char* answers[3],struct Player* player);

// goal determine if the second command is valid
// param player: player struct pointer that represents the player 
// param firstCommand: char* that represents the first command of what is inputed by the user
// param secondCommand: char* that represents the second command of what is inputed by the user
// param characterArr: character stuct pointer array represents the list of all characters in the game
// returns whether the second command is valid based on the first command
bool contains(struct Player* player, char* firstCommand, char* secondCommand, struct Character* characterArr[5]);

// goal remove and return the character node with the name search_name
// param search_name: char* represents the target name that we are looking to remove
// param link: character struct double pointer that represents the head of the list that will be traversed to find the target
// return: returns the character struct pointer with the target name, returns NULL if list does not contain the target
struct Character* character_take(char* search_name, struct Character** link);

#endif
