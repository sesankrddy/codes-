#include<stdio.h>
#include<string.h>

struct student {
    char name[20] , grade;
    int roll_no;
    float mark;

};

void print_student(struct student s) {
    printf("Name: %s\n", s.name);
    printf("Roll No: %d\n", s.roll_no);
    printf("Grade: %c\n", s.grade);
    printf("Mark: %.2f\n", s.mark);

}
int main() {
    struct student s1, s2;

    // Input for first student
    printf("Enter details for student 1 (name roll_no grade mark): ");
    scanf("%s %d %c %f", s1.name, &s1.roll_no, &s1.grade, &s1.mark);

    // Input for second student
    printf("Enter details for student 2 (name roll_no grade mark): ");
    scanf("%s %d %c %f", s2.name, &s2.roll_no, &s2.grade, &s2.mark);

    // Print details of first student
    printf("\nDetails of Student 1:\n");
    print_student(s1);

    // Print details of second student
    printf("\nDetails of Student 2:\n");
    print_student(s2);

    return 0;
}