/**
 * KCAU Student Grade Management System
 * This program handles student information, calculates grades,
 * and stores the data in a CSV file.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 // Define the structure to store student information
 typedef struct {
     int studentId;
     char name[50];
     float score;
     char grade;
     int gradePoints;
 } Student;
 
 /**
  * Function to read student data from user input
  * @param student - Pointer to the student structure
  */
 void readStudentData(Student *student) {
     printf("Enter Student ID: ");
     scanf("%d", &student->studentId);
     
     printf("Enter Student Name: ");
     // Clear input buffer
     getchar();
     fgets(student->name, 50, stdin);
     
     // Remove newline character from name if present
     size_t len = strlen(student->name);
     if (len > 0 && student->name[len-1] == '\n') {
         student->name[len-1] = '\0';
     }
     
     printf("Enter Student Score (0-100): ");
     scanf("%f", &student->score);
 }
 
 /**
  * Function to calculate grade and grade points based on score
  * @param student - Pointer to the student structure
  */
 void calculateGrade(Student *student) {
     float score = student->score;
     
     // Assign grade and grade points based on score range
     if (score >= 70 && score <= 100) {
         student->grade = 'A';
         student->gradePoints = 12;
     } else if (score >= 60 && score <= 69) {
         student->grade = 'B';
         student->gradePoints = 9;
     } else if (score >= 50 && score <= 59) {
         student->grade = 'C';
         student->gradePoints = 6;
     } else if (score >= 40 && score <= 49) {
         student->grade = 'D';
         student->gradePoints = 4;
     } else if (score >= 0 && score <= 39) {
         student->grade = 'E';
         student->gradePoints = 3;
     } else {
         // Out of range
         student->grade = 'F';
         student->gradePoints = 0;
     }
 }
 
 /**
  * Function to write student data to a CSV file
  * @param student - Pointer to the student structure
  */
 void writeToCSV(Student *student) {
     FILE *file = fopen("student_grades.csv", "a"); // Append mode
     
     if (file == NULL) {
         printf("Error opening file!\n");
         return;
     }
     
     // Check if the file is empty (new file)
     fseek(file, 0, SEEK_END);
     long fileSize = ftell(file);
     
     // Write header if file is empty
     if (fileSize == 0) {
         fprintf(file, "Student ID,Name,Score,Grade,Grade Points\n");
     }
     
     // Write student data
     fprintf(file, "%d,%s,%.2f,%c,%d\n", 
             student->studentId, 
             student->name, 
             student->score, 
             student->grade, 
             student->gradePoints);
     
     fclose(file);
     printf("Student data successfully written to student_grades.csv\n");
 }
 
 /**
  * Main function
  */
 int main() {
     Student student;
     char choice;
     
     do {
         printf("\n--- KCAU Student Grade Management System ---\n");
         
         // Read student data
         readStudentData(&student);
         
         // Calculate grade and grade points
         calculateGrade(&student);
         
         // Display calculated information
         printf("\nStudent Information:\n");
         printf("ID: %d\n", student.studentId);
         printf("Name: %s\n", student.name);
         printf("Score: %.2f\n", student.score);
         printf("Grade: %c\n", student.grade);
         printf("Grade Points: %d\n", student.gradePoints);
         
         // Write to CSV file
         writeToCSV(&student);
         
         // Ask if user wants to enter another student
         printf("\nDo you want to enter another student? (y/n): ");
         scanf(" %c", &choice);
         
     } while (choice == 'y' || choice == 'Y');
     
     printf("Thank you for using KCAU Student Grade Management System!\n");
     
     return 0;
 }