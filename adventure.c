#include "items.h"
#include "rooms.h"
#include "characters.h"
#include <time.h>

// randomizes placement of rooms, characters and items before every game
void randomizer(struct Room* gameBoard[3][3], int coord[2], struct Character* characterArr[5], char* roomNames[9], char* itemNames[9],char* answers[3]){
  srand(time(NULL));
  int randomNum;
  int counter = 9;
  // Perform Fisher Yates Shuffle on a 2d Array
  for(int i = 2; i >= 0; i --){
    for (int j =2; j>=0; j--){
       if (i == 0 && j ==0)
         break;
       // gets a random number and calls randomHelper to find the placement on the 2d array and swaps with the counter variable
       randomNum = rand()%counter;
       randomHelper(coord,randomNum); // fills in coord[] with 2 numbers that corresponds to a randomNum (ex 1 is 0,0)
       // swaps pointers for rooms at current i j with indexes coord[0] coord[1]
       swapPointers(gameBoard,i,j,coord[0],coord[1],'r');
       randomNum = rand()%counter;
       randomHelper(coord,randomNum);
       //swap item pointers in the room at i j and coord[0] and coord[1]
       swapPointers(gameBoard,i,j,coord[0],coord[1],'i');
       counter-=1;
    }
  }  
  // Randomly place characters in the the room at randomNum
  for (int i =0; i < 5; i++){
    randomNum = rand()%10;
    randomHelper(coord,randomNum); // gets correspond row and col for randonNum (ex 2 is 0,1)
    putCharacter(&(gameBoard[coord[0]][coord[1]]->cList),characterArr[i]);
    move_character(characterArr[i],gameBoard[coord[0]][coord[1]]);
  }

  // fill up itemNames and roomNames array
  counter = 0;
  for (int i =0; i < 3; i++){
    for (int j =0; j < 3; j++){
      roomNames[counter] = gameBoard[i][j]->description;
      itemNames[counter] = gameBoard[i][j]->items->name;
      counter+=1;
    }
  }
  // connects each rooms direction pointers
  setDirections(gameBoard);
  
  // Randomly gets the answers for this current game
  answers[0] = roomNames[rand()%9];
  answers[1] = itemNames[rand()%9]; 
  answers[2] = characterArr[rand()%5]->name;
}

// Prints out the list of available commands 
void help(){
  printf("\nThese are the commands you can type \n");
  printf("  - help\n");
  printf("  - look\n");
  printf("  - list\n");
  printf("  - go north/east/south/west\n");
  printf("  - take ITEM\n");
  printf("  - drop ITEM\n");
  printf("  - inventory\n");
  printf("  - clue CHARACTER\n");
}

// Prints out all rooms items and characters in the game
void list(char* roomNames[9], char* itemNames[9],struct Character* characterArr[5]){
  printf("Rooms:");
  for(int i = 0; i < 9; i++)
    printf(" %s",roomNames[i]);
  printf("\nItems:");
  for(int i = 0; i < 9; i++)
    printf(" %s",itemNames[i]);
  printf("\nCharacters:");
  for(int i = 0; i < 5; i++)
    printf(" %s",characterArr[i]->name);
  printf("\n");
}

//Returns whether a command is valid or not
bool validComInputs(char command[], char* oneCommands[4],char* twoCommands[4], struct Player* player,struct Character* characterArr[5],char* finalComInput[2]){
  char* firstCommand;
  char* secondCommand;
  char* thirdTest;
  int counter = 1;
  bool firstC = false;
  firstCommand = command; 
  if (strcmp(firstCommand,"\n")==0)
    return false;
 //Split the command where there is a space and new Line
 firstCommand = strtok(command," \n");
 /* Loop through the array of one word commands 
    and see if it matches with the first command
 */
 for (int i =0; i < 4; i++){
   if (strcmp(firstCommand,oneCommands[i])==0){
      // saves that command to be able to use later
      finalComInput[0] = firstCommand;
      firstC = true; 
      /*
        returns true if the first command matches
        one of the one word command and if there is
        no commands after the first
        return false otherwise
      */
      secondCommand = strtok(NULL," \n");
      if (secondCommand == NULL){
        return true;
      }
      else{
        printf("Invalid command\n");
        return false;
      }
    }
  }
  /*
     Loops through the 2 word commands and check
     if the command matches with firstCommand
  */
  for (int i =0; i < 4; i++){
    if (strcmp(firstCommand,twoCommands[i])==0){
      // Saves firstCommand and sets firstC to true
      finalComInput[0] = firstCommand;
      firstC = true;
      break;
    }
  }
  
  // if the first command does not match a word command or 2 word command then the command is invalid
  if (firstC == false){
    printf("Invalid command\n");
    return false;
  }
  
  // if the first command is a 2 word commad and the second command is NULL 
  secondCommand = strtok(NULL," \n");
  if (secondCommand ==NULL){
    printf("Invalid Command\n");
    return false;
  }
  // if there is another strtok after the second
  if (strtok(NULL," \n") !=NULL){
    printf("Invalid Command\n");
    return false;
  }
  
  //checks to see if second command is valid given that the first is 
  if (contains(player,firstCommand,secondCommand,characterArr)){
    // saves second command
    finalComInput[1] = secondCommand;
    return true;
 }
 // return false for all other inputs
 printf("Invalid command\n");
 return false;
}

int main(void){ 
  //Player structs
  struct Player* player = newPlayer("Gordon",NULL, NULL); 
  
  //Item structs
  struct Item* item1 = item("Dagger", "a short sword", NULL);
  struct Item* item2 = item("Knife", "item used cut food", NULL);
  struct Item* item3 = item("Wrench", "bolt and nut turner", NULL);
  struct Item* item4 = item("Screwdriver", "tools used to screw", NULL);
  struct Item* item5 = item("Tasor", "deadly item that emits electricity", NULL);
  struct Item* item6 = item("Hammer", "weighted block fixed to a handle", NULL);
  struct Item* item7 = item("Gun", "Pistol", NULL);
  struct Item* item8 = item("Rope", "a leather bound rope", NULL);
  struct Item* item9 = item("Hacksaw", "long saw", NULL);
  
  //Room structs
  struct Room* r1 = room("O2", item1,NULL,NULL,NULL,NULL,NULL);
  struct Room* r2 = room("Electrical", item2,NULL,NULL,NULL,NULL,NULL);
  struct Room* r3 = room("Admin", item3,NULL,NULL,NULL,NULL,NULL);
  struct Room* r4 = room("Cafeteria", item4,NULL,NULL,NULL,NULL,NULL);
  struct Room* r5 = room("Security", item5,NULL,NULL,NULL,NULL,NULL);
  struct Room* r6 = room("Shields", item6,NULL,NULL,NULL,NULL,NULL);
  struct Room* r7 = room("MedBay", item7,NULL,NULL,NULL,NULL,NULL);
  struct Room* r8 = room("Storage", item8,NULL,NULL,NULL,NULL,NULL);
  struct Room* r9 = room("Navigation", item9,NULL,NULL,NULL,NULL,NULL);
 
  //Character structs
  struct Character* Orange = makeProfile("Orange",NULL,NULL);
  struct Character* Black = makeProfile("Black",NULL,NULL);
  struct Character* Green = makeProfile("Green",NULL,NULL);
  struct Character* Yellow = makeProfile("Yellow",NULL,NULL);
  struct Character* White = makeProfile("White",NULL,NULL);
  
  //Array with valid commands
  char* oneCommands[4] = {"help","look","list","inventory"};
  char* twoCommands[4] = {"drop","take","go","clue"};
   
  struct Item* itemArr[9] = {item1,item2,item3,item4,item5,item6,item7,item8,item9};
  struct Character* characterArr[5] = {Orange,Black,Green,Yellow,White};
  struct Room* gameBoard[3][3] = {r1,r2,r3,r4,r5,r6,r7,r8,r9};
  
  int coord[2]; // used to hold row and col that correspond to a randomNum
  char* roomNames[9];
  char* itemNames[9];
  char* answers[3];
  int clueCounter = 0;
  bool threeMatches =false; 
  char command[25];
  char* finalComInput[2]; //array that saves the input if valid

  // Randomizes the gameBoard, rooms, items, characters and answers before every game  
  randomizer(gameBoard,coord, characterArr,roomNames,itemNames,answers);
  
 // printf("Answers: Room %s Item %s Name %s\n",answers[0],answers[1],answers[2]);
  
  //sets player location to the middle room
  player->curLoc = gameBoard[1][1];
  printf("\nAfter returning to Earth from Mars, you realize that your friend Blue is dead and that there is an imposter among us. \n");
  printf("You must find who the imposter is before anyone else is killed and before the imposter sabotages the entire ship.\n");
  help();
  
  // loops game till player used all clue counters or they have 3 matches
  while ((clueCounter < 10)&&(!threeMatches)){
    struct Item* temp;
    struct Character* charTemp;  
        
    //prompts the user for input till its a valid input
    do{
      printf("\nPlease type a vaild command \n> ");
      fgets(command,25,stdin);  
    }
    while(!(validComInputs(command,oneCommands,twoCommands,player,characterArr,finalComInput)));
    
    //validComInputs saves the value of the commands if valid into array finalComInput
    // perform the function of the command that was saved
    if (strcmp(finalComInput[0],"look")==0)
      look(player->curLoc);
    if (strcmp(finalComInput[0],"help")==0)
      help();
    if (strcmp(finalComInput[0],"list")==0)
      list(roomNames,itemNames,characterArr);
    if (strcmp(finalComInput[0],"inventory")==0){
      prtItemList(player->inventory);
      printf("\n");
    }
    
    // performed the function the the 2 word command that was saved
    if (strcmp(finalComInput[0],"take")==0){
      // removes and saves node from room and sets its next to NULL
      temp = item_take(finalComInput[1],&(player->curLoc->items));
      temp -> next = NULL;
      //put removed node into inventory
      putItem(&(player->inventory),temp);
    }
    if (strcmp(finalComInput[0],"drop")==0){
      //removes and saves node from inventory and set its next to NULL
      temp = item_take(finalComInput[1],&(player->inventory));
      temp -> next = NULL;
      // put removed node into room
      putItem(&(player->curLoc->items),temp);
    }
    if (strcmp(finalComInput[0],"go")==0){
      //place player into room that is DIRECTION of current room
      if (strcmp(finalComInput[1],"north")==0)
        room_exit_north(player);  
      if (strcmp(finalComInput[1],"south")==0)
        room_exit_south(player);
      if (strcmp(finalComInput[1],"east")==0)
        room_exit_east(player);
      if (strcmp(finalComInput[1],"west")==0)
        room_exit_west(player);
    }
    if (strcmp(finalComInput[0],"clue")==0){
      //loops through the board to find the room with the character being called
      for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
          charTemp = character_take(finalComInput[1],&(gameBoard[i][j]->cList));
          if (charTemp!=NULL){
          // once the character is found set its next to NULL
          // add the character to players current room character list
          // change the characters current room pointer to players current room
            charTemp -> next = NULL;
            putCharacter(&(player->curLoc->cList),charTemp);
            move_character(charTemp,player->curLoc);
            break;
          }
        }
      }
      // checks to see if that clue command has 3 matches
      threeMatches = clueMatch(answers,player);
      // increment clue counter
      clueCounter+=1;
    }
  }
  
  printf((threeMatches) ? ("The imposter has been sucessfully ejected. You Win\n"):("The imposter hijacked the ship. You Lose\n"));
 
  //free all allocated memory
  int itemCount = 0;
  int charCount = 0;
  // loop through the game board and free the rooms and also free items and characters
  for (int i = 0; i<3; i++){
    for (int j = 0; j<3; j++){
      free(gameBoard[i][j]); 
      // free the item
      if (itemCount < 9){
        free(itemArr[itemCount]);
      }
      // free characters
      if (charCount < 5){
        free(characterArr[charCount]);
      }
      itemCount+=1;
      charCount+=1;
    }
  }
  free(player);
}
