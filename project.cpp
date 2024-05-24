#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[50];
    char course[10];
    float marks;
    struct student* next;
};
typedef struct student Student;



// 1. Function to add a student record
void addStudent(Student** head, int id, char* name, char* course, float marks) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    strcpy(newStudent->course, course);
    newStudent->marks = marks;
    newStudent->next = NULL;

    if (*head == NULL) {
        *head = newStudent;
        return;
    }

    Student* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newStudent;
}

// 2. Function to delete a student record by ID
void deleteStudent(Student** head, int id) {
    Student* temp = *head;
    Student* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}


// 3. Funtion for only ID update
void updateStudentID(Student* head, int id, int nid){
    Student* temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    temp->id = nid;
}

// 3. Function to update a student's record
void updateStudent(Student* head, int id, char* name, char* course, float marks) {
    Student* temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    //if (temp == NULL) return;
    strcpy(temp->name, name);
    strcpy(temp->course, course);
    temp->marks = marks;
}

// 4. Function to display course-wise student information
void displayCourseStudents(Student* head, const char* course) {
    Student* temp = head;
    printf("Students enrolled in %s:-\n", course);
    while (temp != NULL) {
        if (strcmp(temp->course, course) == 0) {
            printf("ID   :- %d\nName :- %s\nMarks:- %.2f\n", temp->id, temp->name, temp->marks);
            printf("-----------------\n");
        }
        temp = temp->next;
    }
}

// 5. Function to display a student's information
void displayStudent(Student* head, int id) {
    Student* temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    printf("ID: %d\nName: %s\nCourse: %s\nMarks: %.2f\n", temp->id, temp->name, temp->course, temp->marks);
}

// 6. Function to prepare a grade sheet for a student
void prepareGradeSheet(Student* head, int id) {
    Student* temp = head;
    Student* tempp = head;
    Student* topper = NULL;
    char grade;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("\nWrong Student ID entered.\n");
        return;
    }
    else{
        if(temp->marks<40){
            grade = 'F';
        }
        else if(temp->marks > 39 && temp->marks < 51){
            grade = 'D';
        }
        else if(temp->marks > 50 && temp->marks < 61){
            grade = 'C';
        }
        else if(temp->marks > 60 && temp->marks < 71){
            grade = 'B';
        }
        else if(temp->marks > 70 && temp->marks < 81){
            grade = 'A';
        }
        else if(temp->marks > 80 && temp->marks < 91){
            grade = 'E';
        }
        else if(temp->marks > 90 && temp->marks < 101){
            grade = 'O';
        }
        printf("----  Grade Card  ----\n");
        printf("\nStudent ID : %d\nStudent Name : %s\nDepartment : %s\nGrade : %c\nPercentage of Marks : %.2f%", temp->id, temp->name, temp->course, grade, temp->marks);
        
        if(temp->marks < 40){
            printf("\nStatus : Fail\n");
        }
        else{
            printf("\nStatus : Pass\n");
            while (tempp != NULL) {
                if (strcmp(tempp->course, temp->course) == 0) {
                    if (topper == NULL || tempp->marks > topper->marks){
                        topper = tempp;
                    }
                }
                tempp = tempp->next;
            }
            if(strcmp(temp->name,topper->name)==0){
                printf("Topper of %s department.\n", temp->course);
            }
        }
        
        
        printf("\n ----  End Of Grade Card  ----\n");
    }
}

// 7. Function to find the topper of each course
void findCourseTopper(Student* head, char* course) {
    Student* temp = head;
    Student* topper = NULL;
    while (temp != NULL) {
        if (strcmp(temp->course, course) == 0) {
            if (topper == NULL || temp->marks > topper->marks) {
                topper = temp;
            }
        }
        temp = temp->next;
    }
    if (topper != NULL) {
        if(topper->marks >= 40){
            printf("\n ---  Topper of %s  ---\n ID: %d \n Name: %s \n Marks: %.2f\n", course, topper->id, topper->name, topper->marks);
        }
        else{
            printf("All students of %s department are failed.\n", course);
        }
    }
    else {
        printf("No students enrolled in %s.\n", course);
    }
}

// 8. Function to display the success ratio of each course
void displaySuccessRatio(Student* head, const char* course) {
    Student* temp = head;
    int totalStudents = 0;
    int successfulStudents = 0;
    while (temp != NULL) {
        if (strcmp(temp->course, course) == 0) {
            totalStudents++;
            if (temp->marks >= 40) {
                successfulStudents++;
            }
        }
        temp = temp->next;
    }
    if (totalStudents > 0) {
        float successRatio = ((float)successfulStudents / totalStudents) * 100;
        printf("Success ratio of %s department : %.2f%%\n", course, successRatio);
    } else {
        printf("No students enrolled in %s.\n", course);
    }
}

// Function to check if a student ID is unique
int isUniqueID(Student* head, int id) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return 0; // ID is not unique
        }
        temp = temp->next;
    }
    return 1; // ID is unique
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to check student recode is emnpty or not
int isEmpty(Student* head){
    Student* temp = head;
    if(temp == NULL){
        return 1;
    }
    return 0;
}


// Funtion to check marks are between 0-100
int checkMarks(float marks){
    if (marks >= 0 && marks <= 100){
        return 1;
    }
    else{
        printf("Please enter valid marks!\n");
        return 0;
    }
}


int main() {
    Student* head = NULL;
    int ch, nid;
    int choice, id;
    char name[50], course[10];
    float marks;

    while (1) {
        printf("\n-----:Student Information Repository:-----\n");
        printf("1. Add a student record\n");
        printf("2. Delete a student record\n");
        printf("3. Update a student record\n");
        printf("4. Display course-wise student information\n");
        printf("5. Display a student information\n");
        printf("6. Prepare a grade sheet for a student\n");
        printf("7. Find out the topper of each course\n");
        printf("8. Display the success ratio of each course\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                do{
                    printf("Enter ID: ");
                    scanf("%d", &id);
                    clearInputBuffer();
                    if (!isUniqueID(head, id)) {
                        printf("ID already exists. Please enter a unique ID.\n");
                    }
                }while(!isUniqueID(head, id));
                printf("Enter Name: ");
                gets(name);
                printf("Enter Course: ");
                gets(course); 
                do{
                    printf("Enter marks: ");
                    scanf("%f", &marks);
                    clearInputBuffer();
                }while(!checkMarks(marks));
                
                addStudent(&head, id, name, course, marks);
                break;

            case 2:
                if(isEmpty(head)){
                    printf("\nStudent record is empty.\n");
                }
                else{
                    printf("Enter ID of the student to delete: ");
                    scanf("%d", &id);
                    clearInputBuffer();
                    deleteStudent(&head, id);
                }
                break;

            case 3:
                if(isEmpty(head)){
                    printf("\nStudent record is empty.\n");
                }
                else{
                    do{
                        printf("Enter ID of the student to update: ");
                        scanf("%d", &id);
                        clearInputBuffer();
                        if (isUniqueID(head, id)) {
                            printf("ID does not exist. Please enter a valid ID.\n");
                        }
                        else{
                            printf("Enter 1 for only ID update or enter any other number for update of other details: ");
                            scanf("%d", &ch);
                            clearInputBuffer();
                            if(ch == 1){
                                do{
                                    printf("Enter New ID: ");
                                    scanf("%d", &nid);
                                    clearInputBuffer();
                                    if(isUniqueID(head, nid)){
                                        updateStudentID(head, id, nid);
                                    break;
                                    }
                                    else{
                                        printf("ID already exists. Please enter a unique ID.\n");
                                    }
                                }while(!isUniqueID(head, nid));
                                break;
                            }
                            else{
                                printf("Enter New Name: ");
                                gets(name);
                                printf("Enter New Course: ");
                                gets(course);
                                do{
                                    printf("Enter marks: ");
                                    scanf("%f", &marks);
                                    clearInputBuffer();
                                }while(!checkMarks(marks));
                                updateStudent(head, id, name, course, marks);
                            }
                        }
                    }while(isUniqueID(head, id));
                }
                break;

            case 4:
                if(isEmpty(head)){
                    printf("\nStudent record is empty.\n");
                }
                else{
                printf("Enter course to display students: ");
                gets(course);
                displayCourseStudents(head, course);
                }
                break;

            case 5:
                if(isEmpty(head)){
                    printf("\nStudent record is empty.\n");
                    break;
                }
                else{
                    do{
                    printf("Enter ID of the student to display: ");
                    scanf("%d", &id);
                    clearInputBuffer();
                    if (isUniqueID(head, id)) {
                        printf("ID does not exist. Please enter a valid ID.\n");
                    }
                    else{
                        displayStudent(head, id);
                    }
                    }while(isUniqueID(head, id));
                    break;
                }
                

            case 6:
                if(isEmpty(head)){
                    printf("\nStudent record is empty.\n");
                }
                else{
                printf("Enter ID of the student to prepare grade sheet: ");
                scanf("%d", &id);
                clearInputBuffer();
                prepareGradeSheet(head, id);
                }
                break;

            case 7:
                printf("Enter course to find topper:");
                gets(course);
                findCourseTopper(head, course);
                break;

            case 8:
                printf("Enter course to display success ratio: ");
                gets(course);
                displaySuccessRatio(head, course);
                break;

            case 9:
                exit(0);

            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}