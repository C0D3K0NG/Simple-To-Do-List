#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TODOS 50
#define FILE_NAME "todos.txt"

typedef struct {
  char description[500];
  int completed;
} Todo;

// Function prototypes
void add_todo(Todo *todos, int *count);
void view_todos(Todo *todos, int count);
void delete_todo(Todo *todos, int *count);
void mark_complete(Todo *todos, int count);
void save_todos(Todo *todos, int count);
void load_todos(Todo *todos, int *count);

int main() {
  Todo todos[MAX_TODOS];
  int count = 0;
  int choice;

  load_todos(todos, &count);

  while (1) {
    printf("\nTodo Manager\n");
    printf("1. Add Todo\n");
    printf("2. View Todos\n");
    printf("3. Delete Todo\n");
    printf("4. Mark Complete\n");
    printf("5. Save and Exit\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input! Please enter a number.\n");
      while (getchar() != '\n')
        ; // Clear input buffer
      continue;
    }

    switch (choice) {
    case 1:
      add_todo(todos, &count);
      break;
    case 2:
      view_todos(todos, count);
      break;
    case 3:
      delete_todo(todos, &count);
      break;
    case 4:
      mark_complete(todos, count);
      break;
    case 5:
      save_todos(todos, count);
      printf("Exiting...\n");
      exit(0);
    default:
      printf("Invalid choice! Please try again.\n");
    }
  }
  return 0;
}

// Function to add a todo
void add_todo(Todo *todos, int *count) {
  if (*count >= MAX_TODOS) {
    printf("Todo list is full!\n");
    return;
  }

  printf("Enter todo description: ");
  getchar(); // Clear buffer
  fgets(todos[*count].description, sizeof(todos[*count].description), stdin);
  todos[*count].description[strcspn(todos[*count].description, "\n")] =
      0; // Remove newline
  todos[*count].completed = 0;
  (*count)++;

  printf("Todo added successfully!\n");
}

// Function to view todos
void view_todos(Todo *todos, int count) {
  printf("\nCurrent Todos:\n");
  if (count == 0) {
    printf("No todos found!\n");
    return;
  }

  for (int i = 0; i < count; i++) {
    printf("%d. %s [%s]\n", i + 1, todos[i].description,
           todos[i].completed ? "DONE" : "TODO");
  }
}

void delete_todo(Todo *todos, int *count) {
  if (*count == 0) {
    printf("No todos to delete!\n");
    return;
  }

  int index;
  printf("Enter the number of the todo to delete: ");
  if (scanf("%d", &index) != 1 || index < 1 || index > *count) {
    printf("Invalid input! Please enter a valid number.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
    return;
  }

  for (int i = index - 1; i < *count - 1; i++) {
    todos[i] = todos[i + 1];
  }

  (*count)--;
  printf("Todo deleted successfully!\n");
}

void mark_complete(Todo *todos, int count) {
  if (count == 0) {
    printf("No todos available!\n");
    return;
  }

  int index;
  printf("Enter the number of the todo to mark as complete: ");
  if (scanf("%d", &index) != 1 || index < 1 || index > count) {
    printf("Invalid input! Please enter a valid number.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
    return;
  }

  todos[index - 1].completed = 1;
  printf("Todo [%d] marked as complete!\n", index);
}

void save_todos(Todo *todos, int count) {
  FILE *file = fopen(FILE_NAME, "w");
  if (file == NULL) {
    printf("Error saving todos!\n");
    return;
  }

  for (int i = 0; i < count; i++) {
    fprintf(file, "%s,%d\n", todos[i].description, todos[i].completed);
  }

  fclose(file);
  printf("Todos saved successfully!\n");
}

void load_todos(Todo *todos, int *count) {
  FILE *file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    printf("No existing todos found.\n");
    return;
  }

  char line[220];
  while (fgets(line, sizeof(line), file)) {
    char *token = strtok(line, ",");
    if (token != NULL) {
      strncpy(todos[*count].description, token,
              sizeof(todos[*count].description) - 1);
      todos[*count].description[sizeof(todos[*count].description) - 1] =
          '\0'; // Ensure null termination

      token = strtok(NULL, ",");
      if (token != NULL) {
        todos[*count].completed = atoi(token);
        (*count)++;
      }
    }
  }

  fclose(file);
  printf("Todos loaded successfully!\n");
}
