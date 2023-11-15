#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef Node* listPointer;
void insertNode(listPointer* list, int data);
void deleteNode(listPointer* list, int data);
void print_forward(listPointer list);
void print_reverse(listPointer list);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s input_filename\n", argv[0]);
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("The input file does not exist.\n");
        return 1;
    }

    listPointer list = NULL;
 
    char command[10];
    int data;

    while (fscanf(inputFile, "%s", command) == 1) {
        printf("%s  ", command);
        if (strcmp(command, "INSERT") == 0 || strcmp(command, "DELETE") == 0){
            if(fscanf(inputFile, "%d", &data) == 1){
                printf(" %d\n", data);
            } else{
                printf("error reading data for this command %s\n", command);
                return 1;
            }
        }
 
        if(strcmp(command, "INSERT") == 0){
            insertNode(&list, data);
        } else if (strcmp(command, "DELETE") == 0) {
            deleteNode(&list, data);
        } else if (strcmp(command, "ASCEND") == 0) {
            print_forward(list);
        } else if (strcmp(command, "DESCEND") == 0) {
            print_reverse(list);
        }
    }
    fclose(inputFile);

    return 0;
}

void insertNode(listPointer* list, int data) {
   
    listPointer newNode = (listPointer)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "allocation failed\n");
        return;
    }

    newNode->data = data;
    if(*list == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        *list = newNode;
    } else{
        listPointer current =*list;
        listPointer prev = NULL;

        while(current->next !=*list && current->data< data){
            prev = current;
            current = current->next;
        }
        
        if(current->data >= data && prev == NULL){
            newNode->next= *list;
            newNode->prev=(*list)->prev;
            (*list)->prev->next=newNode;
	    (*list)->prev= newNode;
	    *list=newNode;
    }   
       else if(current->data <= data && current->next == *list){
            newNode->next = *list;
            newNode->prev = current;
            current->next = newNode;
            (*list)->prev = newNode;
        }
        else{
            newNode->next = current;
            newNode->prev = prev;
            prev->next = newNode;
            current->prev = newNode;
        }
    }
}
void deleteNode(listPointer* list, int data) {
    if (*list == NULL) {
        return;
    }
    listPointer current = *list;
   
   do {
       if(current->data == data){
            if(current->next == current){
                   
                    *list = NULL;
                } else{
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    if(current == *list){
                        *list = current->next;
                    }
                }
                free(current);
                return;
            }
            current = current->next;
        } while(current != *list);
        return;
}

///// Professor's code:
void print_forward(listPointer list){
    listPointer curr;
    FILE *outfile;

    outfile = fopen("hw2_result.txt", "a");
    if(list){
        curr = list;
        while(1){
            fprintf(outfile, "%d ", curr->data);
            printf("%d ", curr->data);
            curr = curr->next;
            if(curr == list) break;
        }
    }
    fprintf(outfile, "\n");
    printf("\n");
    fclose(outfile);
}

void print_reverse(listPointer list){
    listPointer curr;
    FILE *outfile;

    outfile = fopen("hw2_result.txt", "a");
    if(list){
        curr = list->prev;

        while(curr != list){
            fprintf(outfile, "%d ", curr->data);
            printf("%d ", curr->data);
            curr = curr->prev;
        } 
        fprintf(outfile, "%d ", curr->data);
        printf("%d ",curr->data);
    }
    fprintf(outfile, "\n");
    printf("\n");
    fclose(outfile);
}
