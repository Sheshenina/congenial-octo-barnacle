
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define NUM_GRADES 5
void freeList();
void inputStudentData();
void removeLowScorers();
void printStudents();

int main() {
    int numStudents;

    printf("Enter the number of students: ");
    scanf("%d", &numStudents);

    for (int i = 0; i < numStudents; i++) {
        printf("Student %d:\n", i + 1);
        inputStudentData();
    }

    removeLowScorers();
    printStudents();

    freeList();

    return 0;
}

typedef struct Student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char gender;
    int grades[NUM_GRADES];
    struct Student* next;
    struct Student* prev;
} Student;

Student* head = NULL;



Student* createStudent(char* firstName, char* lastName, char gender, int grades[]) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strncpy(newStudent->firstName, firstName, MAX_NAME_LEN);
    strncpy(newStudent->lastName, lastName, MAX_NAME_LEN);
    newStudent->gender = gender;
    memcpy(newStudent->grades, grades, sizeof(int) * NUM_GRADES);
    return newStudent;
}



void inputStudentData() {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char gender;
    int grades[NUM_GRADES];

    printf("Enter first name: ");
    scanf("%s", firstName);

    printf("Enter last name: ");
    scanf("%s", lastName);

    printf("Enter gender (M/F): ");
    scanf(" %c", &gender);

    printf("Enter 5 grades: ");
    for (int i = 0; i < NUM_GRADES; i++) {
        scanf("%d", &grades[i]);
    }

    Student* student = createStudent(firstName, lastName, gender, grades);
    if (head == NULL) {
        head = student;
        head->next = head;
        head->prev = head;
    }
    else {
        student->prev = head->prev;
        student->next = head;
        head->prev->next = student;
        head->prev = student;
    }
}


void removeLowScorers() {
    if (head == NULL) {
        return;
    }

    Student* current = head;
    do {
        float sum = 0;
        for (int i = 0; i < NUM_GRADES; i++) {
            sum += current->grades[i];
        }
        float average = sum / NUM_GRADES;

        if (average < 2.5) {
            Student* toDelete = current;

            if (head == current) {
                head = current->next;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;

            free(toDelete);
        }
        else {
            current = current->next;
        }
    } while (current != head);
}


void printStudents() {
    if (head == NULL) {
        printf("No students left.\n");
        return;
    }

    Student* current = head;
    printf("Remaining students:\n");
    do {
        printf("%s %s\n", current->firstName, current->lastName);
        current = current->next;
    } while (current != head);
}


void freeList() {
    if (head == NULL) {
        return;
    }

    Student* current = head;
    do {
        Student* next = current->next;
        free(current);
        current = next;
    } while (current != head);
}


