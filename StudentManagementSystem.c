/*******************************************************************************
 *  Name:	StudentManagementSystem.c
 *  Date:   Aug 13, 2024
 *  Author: Nadine
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

/*******************************************************************************
 *	                     Global Definitions			               *
 *******************************************************************************/

struct student{
	int id;				/* Student ID */
	char name[SIZE];		/* Student Name */
	int age;			/* Student Age */
	float gpa;			/* Student GPA */
};

struct node{
	struct student data;
	struct node *next;
};

enum menuChoices{
	ADD=1, DISPLAY, SEARCH, UPDATE, DELETE, CALC, HIGH, EXIT
};

struct node *head = NULL;  /* Head Initialization */

/*******************************************************************************
 *			     Functions Prototype			       *
 *******************************************************************************/

void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

/*******************************************************************************
 *			       	  Main Logic		               	       *
 *******************************************************************************/

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	enum menuChoices choice;    /* To hold the user choice for the menu */
	int id;		/* To hold the ID provided by the user */
	/* To continuously show the main menu display */
	while(1){
		/*Printing the main menu */
		printf("=========================================================\n");
		printf("1. Add Student\n"
		       "2. Display Students\n"
		       "3. Search Student by ID\n"
		       "4. Update Student Information\n"
		       "5. Delete Student\n"
		       "6. Calculate Average GPA\n"
		       "7. Search for Student with Highest GPA\n"
		       "8. Exit\n");
		printf("Please Enter your choice: ");
		scanf("%d",(int*)&choice);
		printf("=========================================================\n");

		switch(choice){
			case ADD:
				/* Creating new struct to hold new students information */
				struct student newStudent;
				printf("Enter Student ID: ");
				scanf("%d",&(newStudent.id));
				printf("Enter Student Name: ");
				scanf("%s",newStudent.name);
				printf("Enter Student Age: ");
				scanf("%d",&(newStudent.age));
				printf("Enter Student GPA: ");
				scanf("%f",&(newStudent.gpa));
				addStudent(&newStudent);
				break;
			case DISPLAY:
				displayStudents();
				break;
			case SEARCH:
				printf("Enter Student ID to search for: ");
				scanf("%d",&id);
				searchStudentByID(id);
				break;
			case UPDATE:
				printf("Enter Student ID to update info: ");
				scanf("%d",&id);
				updateStudent(id);
				break;
			case DELETE:
				printf("Enter Student ID to delete info: ");
				scanf("%d",&id);
				deleteStudent(id);
				break;
			case CALC:
				printf("The Average GPA of all students is %f\n",calculateAverageGPA());
				break;
			case HIGH:
				searchHighestGPA();
				break;
			case EXIT:
				printf("Exciting the program...");
				return 0;
			default:
				printf("You didn't enter any valid choice\n");
		}
	}
	return 0;
}

/*******************************************************************************
 *			     Function Definitions			       *
 *******************************************************************************/

void addStudent(const struct student *const ptr){
	struct node *traversePtr = head;    /* pointer to traverse across the list */
	/* Looping on the linked list to check if ID already exists*/
	while(traversePtr != NULL){
		/* Matching new student ID with an old one */
		if (ptr->id == traversePtr->data.id){
			printf("Error: Student ID already exists\n");
			return;
		}
		traversePtr = traversePtr->next;
	}
	/*Allocating a new node*/
	struct node *link = (struct node *)malloc(sizeof(struct node));
	/* Failed allocation*/
	if(link == NULL){
		printf("Error: Failed Allocation, there is no space for the student\n");
		return;
	}
	/* Successful allocation */
	link->data = *ptr;      /* copying new student data to the node */
	link->next = NULL;		/* Nulling the last node */
	/* In case of no students in the system */
	if(head == NULL){
		head = link;
		return;
	}
	traversePtr = head;
	/* Looping to find the last node */
	while(traversePtr->next != NULL){
		traversePtr = traversePtr->next;		/* To go to the next node */
	}
	traversePtr->next=link;						/* Attaching the new node to the end of the list */
}

void displayStudents(void){
	struct node *traversePtr = head;
	/* Looping across the list to print its content */
	if(head == NULL){
		printf("There is no students in the system\n");
		return;
	}
		while(traversePtr != NULL){
			printf("[ID: %d, Name: %s, Age: %d, GPA: %f]\n",traversePtr->data.id,traversePtr->data.name,traversePtr->data.age,traversePtr->data.gpa);
			traversePtr = traversePtr->next;		/* Moving to the next node */
		}
}

void searchStudentByID(int id){
	struct node *traversePtr = NULL;
	/* In case of no students in the system */
	if(head == NULL){
		printf("The list is empty, student not found\n");
		return;
	}
	traversePtr = head;
	/* Looping to find the given ID*/
	while(traversePtr != NULL){
		if(traversePtr->data.id == id){
			printf("Found! Here is the student information:\n");
			printf("[ID: %d, Name: %s, Age: %d, GPA: %f]\n"
					,traversePtr->data.id,traversePtr->data.name,traversePtr->data.age,traversePtr->data.gpa);
			return;
		}
		traversePtr = traversePtr->next;		/* Moving to the next node */
	}
	/* The ID is not in the list */
	printf("Student with ID %d is not found\n",id);
}

void updateStudent(int id){
	struct node *traversePtr = NULL;
	int newAge;  	    /* For Updating Student Age */
	float newGPA;		/* For Updating Student GPA */
	char newName[SIZE];	/* For Updating Student Name */
	/*In case of no students in the system*/
	if(head == NULL){
		printf("The list is empty\n");
		return;
	}
	traversePtr = head;
	/* Looping to find the student id to update his info*/
	while(traversePtr != NULL){
		if(traversePtr->data.id == id){
			/* Taking the new info from the user */
			printf("Enter New Student Name: ");
			scanf("%s",newName);
			printf("Enter New Student Age: ");
			scanf("%d",&newAge);
			printf("Enter New Student GPA: ");
			scanf("%f",&newGPA);
			for(int i=0;i<SIZE;i++){
				traversePtr->data.name[i] = newName[i];
			}
			/* Assigning new info to the node */
			traversePtr->data.age = newAge;
			traversePtr->data.gpa = newGPA;
			printf("Student info has been updated to: \n");
			printf("[ID: %d, Name: %s, Age: %d, GPA: %f]\n"
					,traversePtr->data.id,traversePtr->data.name,traversePtr->data.age,traversePtr->data.gpa);
			return;
		}
		traversePtr = traversePtr->next;    /* Moving to the next node */
	}
	printf("Student is not in the list\n");

}

float calculateAverageGPA(void){
	float sum = 0;    			 /* Student GPAs summation */
	int studentCount = 0;    	/* Student number */
	struct node* traversePtr = NULL;
	/* in case of no pre-existed list*/
	if(head == NULL){
		printf("The list is empty\n");
		return 0.0;
	}
	traversePtr = head;
	/* Looping to get each student GPA*/
	while(traversePtr != NULL){
		sum += traversePtr->data.gpa;
		studentCount++;
		traversePtr = traversePtr->next;	/* Moving to the next node */
	}
	/*Returning the average GPA*/
	return sum/studentCount;
}

void searchHighestGPA(void){
	struct node* traversePtr = NULL;		/* To traverse across the list*/
	struct node* highestGPA = NULL;			/* To hold the location of the highest GPA*/
	/* In case of no students in the system */
	if(head == NULL){
		printf("The list is empty\n");
	}
	traversePtr = head;
	float max = 0;
	/* Looping to find the student with the highest GPA*/
	while(traversePtr != NULL){
		if(max < traversePtr->data.gpa){
			max = traversePtr->data.gpa;
			highestGPA = traversePtr;       /*Holding the location of the node of the highest GPA */
		}
		traversePtr = traversePtr->next;	/* Moving to the next node */
	}
	printf("Here is the student with the highest GPA information:\n");
	printf("[ID: %d, Name: %s, Age: %d, GPA: %f]\n"
			,highestGPA->data.id,highestGPA->data.name,highestGPA->data.age,highestGPA->data.gpa);
}

void deleteStudent(int id){
	struct node *prevptr = NULL;        /* To hold the previous pointer */
	struct node *currentptr = NULL;		/* To hold the current pointer */
	struct node *deleteptr = NULL;		/* To hold the location of the required deleted node */
	/* In case of no students in the system*/
	if(head == NULL){
		printf("There is no students in the system");
		return;
	}
	/* Checking the first node*/
	if(head->data.id == id){
		deleteptr = head;
		head = head->next;
		free(deleteptr);
		printf("The student with ID %d has been deleted\n",id);
		return;
	}
	prevptr = head;
	currentptr = head->next;
	/* Checking for the rest of the nodes */
	while(currentptr != NULL){
		if(currentptr->data.id == id){
			deleteptr = currentptr; 				/* Holding the location of the required deleted pointer*/
			prevptr->next = currentptr->next;   	/* Adjusting the pointers in the list */
			free(deleteptr);     					/* Deleting the node from the heap */
			printf("The student with ID %d has been deleted\n",id);
			return;
		}
		currentptr = currentptr->next;              /* Moving to the next node */
		prevptr = prevptr->next;					/* Moving to the next node */
	}
	/* In case of not finding the student in the list */
	if(deleteptr == NULL){
		printf("The student with ID %d is not in the system\n",id);
	}
}
