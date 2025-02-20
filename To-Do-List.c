#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TODOS 50

typedef struct {
    char description[100];
    int completed;
} Todo;

// Function prototypes
void add_todo(Todo *todos, int *count);
void view_todos(Todo *todos, int count);
// TODO: Add prototypes for delete_todo and mark_complete

int main() {
    Todo todos[MAX_TODOS];
    int count = 0;
    int choice;
    
    while(1) {
        printf("\nTodo Manager\n");
        printf("1. Add Todo\n");
        printf("2. View Todos\n");
        printf("3. Delete Todo\n");
        printf("4. Mark Complete\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        
        // TODO: Add input validation
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        switch(choice) {
            case 1:
                add_todo(todos, &count);
                break;
            case 2:
                view_todos(todos, count);
                break;
            case 3:
                // TODO: Implement delete function
                printf("Delete function not implemented yet!\n");
                break;
            case 4:
                // TODO: Implement mark complete
                printf("Mark complete not implemented yet!\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

void add_todo(Todo *todos, int *count) {
    if(*count >= MAX_TODOS) {
        printf("Todo list full!\n");
        return;
    }
    
    printf("Enter todo description: ");
    // TODO: Fix buffer overflow vulnerability
    scanf(" %[^\n]", todos[*count].description);
    todos[*count].completed = 0;
    (*count)++;
}

void view_todos(Todo *todos, int count) {
    printf("\nCurrent Todos:\n");
    if(count == 0) {
        printf("No todos found!\n");
        return;
    }
    
    // TODO: Add numbering and completion status
    for(int i = 0; i < count; i++) {
        printf("%d. %s [%s]\n", 
               i+1,
               todos[i].description,
               todos[i].completed ? "DONE" : "TODO");
    }
}

// TODO: Implement delete_todo function
// TODO: Implement mark_complete function
// TODO: Add file saving/loading functionality
// TODO: Add input validation for all user inputs
// TODO: Add error handling for edge cases