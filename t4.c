#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100
//To store a entry of game review
typedef struct GameReviews GameReviews;
struct GameReviews{
    char title[MAX_STRING_SIZE];
    char platform[MAX_STRING_SIZE];
    int score;
    int release_year;
};
// A linked list to store every row - every game review of the csv file
typedef struct GameReviewsList GameReviewsList;
struct GameReviewsList{
  GameReviews data;
  GameReviewsList *next;
};

GameReviewsList *head = NULL;
// another pointer used to sort the linked list
GameReviewsList *sorted = NULL;


//Adding a node to the linked list
void add_node(GameReviews *data){
    GameReviewsList *newNode = (GameReviewsList *)malloc(sizeof(GameReviewsList));
    strcpy(newNode->data.title, data->title);
    strcpy(newNode->data.platform, data->platform);
    newNode->data.score = data->score;
    newNode->data.release_year = data->release_year;
    newNode->next = head;
    head = newNode;
}

void sorted_insert(GameReviewsList *node){
  // first step of sorting or if the node's score is greater than sorted linked lists score - adding the current node to the head of linked list
  if(sorted == NULL || sorted->data.score <= node->data.score){
    node->next = sorted;
    sorted = node;
  }
  else{
    GameReviewsList *current = sorted;
    //Traversing the linked list and finding the node which has score lesser than the node's score
    while(current->next != NULL && current->next->data.score > node->data.score){
      current = current->next;
    }
    //when found, inserting that node in front of it.
    node->next = current->next;
    current->next = node;
  }
}

void insertionSort(){
  GameReviewsList *current = head;
  while(current != NULL){
    //Comparing scores of current node with following nodes and inserting that node at correct location - insertion sort
    GameReviewsList *next = current->next;
    sorted_insert(current);
    current = next;
  }
  //reassigning the head pointer to the sorted linked list
  head = sorted;
}


void print_reviews(GameReviewsList *list){
  int count = 0;
  printf("%32s%32s%32s%32s\n", "Title", "Platform", "Score", "Release Year");
  while(list != NULL && count < 10){
    printf("%32s%32s%32d%32d\n", list->data.title, list->data.platform, list->data.score, list->data.release_year);
    list = list -> next;
    count++;
  }
}

//Next token function from my assignment 0
void next_token ( char *buf, FILE *f, int string_max ) {
    int bufferpos = 0;
    int inQuotes = 0;
    char c;
    for(int i = 0; i < string_max; i++){
        c = fgetc(f);
        if (c == '"'){
            inQuotes = !inQuotes;
            continue;
        }
        if (c == ',' && !inQuotes){
            bufferpos++;
            break;
        }
        else if(c == '\n' || feof(f)){
            bufferpos++;
            break;
        }
        buf[bufferpos] = c;
        bufferpos++;
    }
    buf[bufferpos] = '\0';
}


int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];
  int field_count = 0;
  GameReviews *data = (GameReviews *)malloc(sizeof(GameReviews));
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	printf("File %s loaded\n", fname);
	while ( !feof(f) ) {
        memset(buf, 0, sizeof(buf)); //resetting buffer
        next_token(buf, f, MAX_STRING_SIZE);
        // printf("%s\n", buf);
        //Corresponding data are added to the structure using following logic
        if(field_count == 0) {
          strcpy(data->title, buf);
        }
        else if(field_count == 1) {
          strcpy(data->platform, buf);
        }
        else if(field_count == 2) {
          data->score = atoi(buf);
        }
        else if(field_count == 3) {
          data->release_year = atoi(buf);
        }
        field_count++;
        if (field_count == 4){
            field_count = 0;
            //ignoring the first row of the csv file
            if(strcmp(data->title, "title") == 0) continue;
            add_node(data);
        }
    }
	fclose(f);
  free(data); //freeing extra memory that was used.
	return 1;
}


int main(int argc, char** argv)
{

    load_file(argv[1]);
    insertionSort();
    print_reviews(head);
    return 0;
}