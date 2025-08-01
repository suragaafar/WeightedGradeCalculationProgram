#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char name[50];
    int weight;
    int maxAllocatedPoints;
    int earnedScore;
} CourseComponent;

typedef struct {
    char name[50];
    CourseComponent *components;
    int numComponents;
    double finalGrade;
    char letterGrade[4];
} Student;

const char* letter_grade(double final_weighted_grade) {
    if (final_weighted_grade >= 90) {
        return "A+";
    } else if (final_weighted_grade >= 85) {
        return "A";
    } else if (final_weighted_grade >= 80) {
        return "A-";
    } else if (final_weighted_grade >= 75) {
        return "B+";
    } else if (final_weighted_grade >= 70) {
        return "B";
    } else if (final_weighted_grade >= 65) {
        return "C+";
    } else if (final_weighted_grade >= 60) {
        return "C";
    } else if (final_weighted_grade >= 50) {
        return "D";
    } else {
        return "F";
    }
}

// Recursive weighted grade calculation
float weighted_grade(int i, Student *student) {
    if (i >= student->numComponents) {
        return 0;  // Base case: no more components
    }
    float component_grade = ((float)student->components[i].earnedScore / 
                           (float)student->components[i].maxAllocatedPoints) * 
                           (float)student->components[i].weight;
    return component_grade + weighted_grade(i + 1, student);  // Recursive step
}

void class_summary(float final_grades[], int n, Student *students) {
    // n includes the template student at index 0
    if (n <= 1) return;  // Only template student exists

    float maximum = final_grades[1];  // Start with first real student
    float average = 0.0;
    float median = 0.0;
    int maxStudent = 1;  // First real student index

    // Calculate maximum and average (skip index 0)
    for (int i = 1; i < n; i++) {
        if (maximum < final_grades[i]) {
            maximum = final_grades[i];
            maxStudent = i;
        }
        average += final_grades[i];
    }
    average /= (n - 1);  // Divide by number of real students

    // Sort only the real student grades (indices 1 to n-1)
    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (final_grades[i] > final_grades[j]) {
                float temp = final_grades[i];
                final_grades[i] = final_grades[j];
                final_grades[j] = temp;
            }
        }
    }

    // Calculate median using only real students (n-1 total)
    int middle = (n - 1) / 2;
    if ((n - 1) % 2 == 0) {
        median = (final_grades[1 + middle - 1] + final_grades[1 + middle]) / 2.0;
    } else {
        median = final_grades[1 + middle];
    }

    printf("\nMaximum: %.0f%% (Student: %s)\n", maximum, students[maxStudent].name);
    printf("Average: %.0f%%\n", average);
    printf("Median: %.0f%%\n", median);
}

void reading_component_data(Student **students, int choice, int *numOfStudents) {
    int totalWeight = 0;
    int counter = 0;
    int capacity = 1;

    if (choice == 1) {
        printf("\nEnter the student's full name: ");
        scanf(" %49[^\n]", (*students)[*numOfStudents].name);
        
        while (1) {
            totalWeight = 0;
            printf("Enter the number of course components: ");
            scanf("%d", &(*students)[*numOfStudents].numComponents);
            
            (*students)[*numOfStudents].components = malloc((*students)[*numOfStudents].numComponents * sizeof(CourseComponent));
            if ((*students)[*numOfStudents].components == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            
            for (int i = 0; i < (*students)[*numOfStudents].numComponents; i++) {
                printf("\nComponent %d:\n", i + 1);
                printf("  Name: ");
                scanf(" %49[^\n]", (*students)[*numOfStudents].components[i].name);
                
                printf("  Weight (as percentage): ");
                while (scanf("%d", &(*students)[*numOfStudents].components[i].weight) != 1 || 
                       (*students)[*numOfStudents].components[i].weight <= 0 || 
                       (*students)[*numOfStudents].components[i].weight > 100) {
                    printf("Invalid weight. Please enter a value between 1 and 100: ");
                    while (getchar() != '\n');
                }
                totalWeight += (*students)[*numOfStudents].components[i].weight;
                
                printf("  Max Allocated Points: ");
                while (scanf("%d", &(*students)[*numOfStudents].components[i].maxAllocatedPoints) != 1 || 
                       (*students)[*numOfStudents].components[i].maxAllocatedPoints <= 0) {
                    printf("Invalid max points. Please enter a positive integer: ");
                    while (getchar() != '\n');
                }
                
                printf("  Earned Points: ");
                while (scanf("%d", &(*students)[*numOfStudents].components[i].earnedScore) != 1 || 
                       (*students)[*numOfStudents].components[i].earnedScore < 0 || 
                       (*students)[*numOfStudents].components[i].earnedScore > (*students)[*numOfStudents].components[i].maxAllocatedPoints) {
                    printf("Invalid score. Please enter a value between 0 and %d: ", 
                          (*students)[*numOfStudents].components[i].maxAllocatedPoints);
                    while (getchar() != '\n');
                }
            }
            
            if (totalWeight == 100) break;
            printf("Total weight must be 100, but is %d. Please re-enter the components.\n", totalWeight);
            free((*students)[*numOfStudents].components);
            (*students)[*numOfStudents].components = NULL;
        }
    }
    else if (choice == 2) {
        // First student setup (template)
        if (*numOfStudents == 0) {
            while (1) {
                totalWeight = 0;
                printf("\nEnter the number of course components: ");
                scanf("%d", &(*students)[0].numComponents);
                
                (*students)[0].components = malloc((*students)[0].numComponents * sizeof(CourseComponent));
                if ((*students)[0].components == NULL) {
                    printf("Memory allocation failed.\n");
                    return;
                }
                
                for (int i = 0; i < (*students)[0].numComponents; i++) {
                    printf("\nComponent %d:\n", i + 1);
                    printf("  Name: ");
                    scanf(" %49[^\n]", (*students)[0].components[i].name);
                    
                    printf("  Weight (as percentage): ");
                    while (scanf("%d", &(*students)[0].components[i].weight) != 1 || 
                           (*students)[0].components[i].weight <= 0 || 
                           (*students)[0].components[i].weight > 100) {
                        printf("Invalid weight. Please enter a value between 1 and 100: ");
                        while (getchar() != '\n');
                    }
                    totalWeight += (*students)[0].components[i].weight;
                    
                    printf("  Max Allocated Points: ");
                    while (scanf("%d", &(*students)[0].components[i].maxAllocatedPoints) != 1 || 
                           (*students)[0].components[i].maxAllocatedPoints <= 0) {
                        printf("Invalid max points. Please enter a positive integer: ");
                        while (getchar() != '\n');
                    }
                }
                
                if (totalWeight == 100) break;
                printf("Error: Total weight exceeds 100! Please re-enter all components.\n");
                free((*students)[0].components);
            }
            (*numOfStudents)++;
        }
        
        // Add more students
        while (1) {
            if (*numOfStudents >= capacity) {
                capacity *= 2;
                Student *temp = realloc(*students, capacity * sizeof(Student));
                if (temp == NULL) {
                    printf("Memory reallocation failed.\n");
                    return;
                }
                *students = temp;
            }

            printf("\nEnter student's full name (or 'DONE' to stop): ");
            scanf(" %49[^\n]", (*students)[*numOfStudents].name);

            if (strcmp((*students)[*numOfStudents].name, "DONE") == 0) {
                break;
            }

            (*students)[*numOfStudents].numComponents = (*students)[0].numComponents;
            (*students)[*numOfStudents].components = malloc((*students)[*numOfStudents].numComponents * sizeof(CourseComponent));
            if ((*students)[*numOfStudents].components == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            
            // Copy component data
            for (int i = 0; i < (*students)[*numOfStudents].numComponents; i++) {
                strcpy((*students)[*numOfStudents].components[i].name, (*students)[0].components[i].name);
                (*students)[*numOfStudents].components[i].weight = (*students)[0].components[i].weight;
                (*students)[*numOfStudents].components[i].maxAllocatedPoints = (*students)[0].components[i].maxAllocatedPoints;
                
                printf("Score for \"%s\": ", (*students)[*numOfStudents].components[i].name);
                while (scanf("%d", &(*students)[*numOfStudents].components[i].earnedScore) != 1 || 
                       (*students)[*numOfStudents].components[i].earnedScore < 0 || 
                       (*students)[*numOfStudents].components[i].earnedScore > (*students)[*numOfStudents].components[i].maxAllocatedPoints) {
                    printf("Invalid score. Please enter a value between 0 and %d: ", 
                          (*students)[*numOfStudents].components[i].maxAllocatedPoints);
                    while (getchar() != '\n');
                }
            }
            (*numOfStudents)++;
        }
    }
}

void calculate_final_grade(Student *students, int choice, int *numOfStudents) {
    int j=0;
    if (choice == 1) {
        printf("\n-- Summary of Scores --\n");
        *numOfStudents = 1;
    }
    else {
        printf("\n-- Class Summary --\n");
        j=1; // numOfStudents has an extra index (0) that is solely used for storing components info (would print out an unnecessary student with garbage values)
    }
    float final_grades[*numOfStudents];
    for (int i = j; i < *numOfStudents; i++) {
        float final_weighted_grade = weighted_grade(0, &students[i]);
        students[i].finalGrade = final_weighted_grade;
        final_weighted_grade = round(final_weighted_grade);
        strcpy(students[i].letterGrade, letter_grade(final_weighted_grade));
        if (choice == 1) {
            printf("Final Weighted Grade: %.0f%%\nLetter Grade: %s\n", final_weighted_grade, students[i].letterGrade);
        }
        else {
            printf("%s - %.0f%% (%s)\n", students[i].name, final_weighted_grade, students[i].letterGrade);
        }
        final_grades[i] = final_weighted_grade;
    }
    if(choice == 2) {
        class_summary(final_grades, *numOfStudents, students);
    }
}

void search_for_a_student(Student *students, int *n, char name[]) {
    int found = 0;
    for(int i = 1; i < (*n); i++) {
        if(strcmp(name, students[i].name) == 0) {
            printf("Result: %s - %.0f%% (%s)\n", students[i].name, students[i].finalGrade, students[i].letterGrade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student not found.\n");
    }
}

void sorting_students_by_grade(Student *students, int *n) {
    // Sort only real students (indices 1 to n-1)
    for (int i = 1; i < (*n)-1; i++) {
        for (int j = i+1; j < *n; j++) {
            if (students[i].finalGrade < students[j].finalGrade) {
                // Swap entire student records
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    
    printf("\n======================================\nSorting students by final grade...\n======================================\nClass Ranking:\n");
    for(int i = 1; i < *n; i++) {
        printf("%d. %s - %.0f%% (%s)\n", i, students[i].name, students[i].finalGrade, students[i].letterGrade);
    }
}

int displayMenu() {
    int choice;
    printf("\n======================================\nWeighted Grade Calculation Program\n======================================\n");
    printf("1. Single Student Grades\n2. Multiple Students Grades\n3. Sort Students by Grade\n4. Search for a Student\n5. Exit\nEnter your choice (1/2/3/4/5): ");
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
        printf("Invalid choice. Enter your choice (1/2/3/4/5): ");
        while (getchar() != '\n');
    }
    return choice;
}

void free_memory(Student *students, int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        free(students[i].components);
    }
    free(students);
}

int main() {
    int choice;
    int initial_capacity = 5;
    Student *students = NULL;
    int numOfStudents = 0;
    int previousChoice = 0; // Track option1/option2 being used
    char name[50]; 

    while ((choice = displayMenu()) != 5) {
        if (choice == 1 || choice == 2) {
            // Clear previous data if switching between single/multiple modes
            if (previousChoice == 1 || previousChoice == 2) {
                free_memory(students, numOfStudents);
                students = NULL;
                numOfStudents = 0;
            }
            
            // Allocate fresh memory
            students = malloc(initial_capacity * sizeof(Student));
            if (!students) {
                printf("Memory allocation failed.\n");
                return 1;
            }
            
            reading_component_data(&students, choice, &numOfStudents);
            calculate_final_grade(students, choice, &numOfStudents);
            
            previousChoice = choice; // Remember this choice
        } 
        else if (choice == 3 || choice == 4) {
            if (numOfStudents == 0) {
                printf("\nNo student data available. Please enter student data first (options 1 or 2).\n");
            } else {
                if(choice == 3) {
                    if(numOfStudents<=2) {
                        printf("Sorting not applicable as there aren't enough students.\n");
                    }
                    else{
                        sorting_students_by_grade(students, &numOfStudents); 
                    }
                }
                else {
                    printf("Enter student name to search: ");
                    if (scanf(" %49[^\n]", name) != 1) {
                        printf("Invalid input. Please try again.\n");
                        while (getchar() != '\n');  // Clear input buffer
                        continue;
                    }
                    search_for_a_student(students, &numOfStudents, name); 
                }
            }
        }
    }

    free_memory(students, numOfStudents);
    printf("\n--- HAVE A GOOD DAY! ---\n========================\n");
    return 0;
}