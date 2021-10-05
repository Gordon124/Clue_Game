#include "rooms.h"
#include "items.h"
#include "characters.h"
struct Room* room(char* des, struct Item* item_first, struct Character* person,
                    struct Room *North, struct Room *South,
                    struct Room *East, struct Room *West){
  struct Room* room = (struct Room*) malloc(sizeof(struct Room));  
  room -> description = des;
  room -> items = item_first;
  room -> cList = person;
  room -> north = North;
  room -> south = South;
  room -> east = East;
  room -> west = West;
  return room;
}
//prints out the room description, items, characters and exits
void look(struct Room* curLoc){
  printf("Room description: %s\n",curLoc->description);
  printf("Items: ");
  prtItemList(curLoc->items);
  printf("\nCharacters: ");
  prtCList(curLoc->cList);  
  
  printf("\nRoom exits:");
  if (curLoc->north!=NULL)
    printf(" north");
  if (curLoc->south!=NULL)
    printf(" south");
  if (curLoc->east!=NULL)
    printf(" east");
  if (curLoc->west!=NULL)
    printf(" west");
  printf("\n");
}

// loops through the board and set the exits for each room
void setDirections(struct Room* gameBoard[3][3]){
  for(int i =0; i < 3; i++){
    for(int j =0; j < 3; j++){
      // 1st row 
      if (i ==0){
        gameBoard[i][j]->north = NULL;
        gameBoard[i][j] -> south = gameBoard[i+1][j];
      }
      // 2nd row
      if (i == 1){
        gameBoard[i][j]->north = gameBoard[i-1][j];
        gameBoard[i][j] -> south = gameBoard[i+1][j];
      }
      // 3rd row
      if (i == 2){
        gameBoard[i][j] ->south = NULL;
        gameBoard[i][j] -> north = gameBoard[i-1][j];
      }
      // 1st col
      if (j ==0){
        gameBoard[i][j]->west = NULL;
        gameBoard[i][j] -> east = gameBoard[i][j+1];
      }
      // 2nd col
      if (j == 1){
        gameBoard[i][j]->west = gameBoard[i][j-1];
        gameBoard[i][j] -> east = gameBoard[i][j+1];
      }
      // 3rd col
      if (j == 2){
        gameBoard[i][j] ->east = NULL;
        gameBoard[i][j] -> west = gameBoard[i][j-1];
      }
    }
  }
}

// swap 2 spots of a 2d array
void swapPointers(struct Room* arr[3][3], int room1x, int room1y, int room2x, int room2y, char whatStruct){
  //swap room struct pointers
  if (whatStruct = 'r'){
    struct Room* temp1x = arr[room1x][room1y];
    arr[room1x][room1y] = arr[room2x][room2y];
    arr[room2x][room2y] = temp1x; 
  }
  //swap item struct pointers
  if (whatStruct == 'i'){
    struct Item* temp1x = (arr[room1x][room1y])->items;
    arr[room1x][room1y]->items = arr[room2x][room2y]->items;
    arr[room2x][room2y]->items = temp1x;
  }
} 

//takes a number from 1-9 and finds its position in a 2d array
void randomHelper(int arr[2], int num1to9){
  int counter = 1;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j <3; j++){
      if (counter == num1to9){
        arr[0] = i;
        arr[1] = j;
      }
    counter+=1;
    }
  }
}

