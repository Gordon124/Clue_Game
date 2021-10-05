#ifndef ROOMS_H
#define ROOMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct representing room
struct Room {
    char *description;
    struct Item *items;
    struct Character* cList;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

// goal create a room struct given a description, item list, character list, directions 
// param des: char* representing the description of the room
// param item_first: item struct pointer representing the items in the room
// param person: character struct pointer representing the characters in the room
// param North: struct room pointer that represents the room north of the current room
// param South: struct room pointer that represents the room south of the current room
// param East: struct room pointer that represents the room east of the current room
// param West: struct room pointer that represents the room west of the current room
// return: a room struct pointer with the specified fields
struct Room *room(char* des, struct Item* item_first, struct Character* person,
                    struct Room *North, struct Room *South,
                    struct Room *East, struct Room *West);

// goal prints out description of the room, items and characters in the room and available exits
// param curLoc: struct room pointer that represents the room that the player is in 
void look(struct Room* curLoc);

// goal sets the north south east west fields of every room in the gameBoard
// param gameBoard: struct room* array represents 9 romm structs
void setDirections(struct Room* gameBoard[3][3]);

// goal swap the room structs at 2 indexes
// param arr: struct room pointer reperesents the gameboard which contains 9 room structs
// param room1x: int represents the row value of room 1
// param room1y: int represents the col value of room 1
// param room2x: int represents the row value of room 2
// param room2y: int represents the col value of room 2
// param whatStruct: char represents the swapping of i for items and r for rooms
void swapPointers(struct Room* arr[3][3], int room1x, int room1y, int room2x, int room2y, char whatStruct);

// goal converts a random number from 1 to 9 to 2 numbers and store it into an array
// param arr: array that will store 2 numbers from num1to9
// param num1to9: represents a random number that was generated
void randomHelper(int arr[2], int num1to9);

#endif
