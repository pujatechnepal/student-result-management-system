#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char name[50];
    int roll;
    float marks[5];
    float total;
    float percentage;
};

char subjects[5][20] =
{
    "Math",
    "Physics",
    "C Programming",
    "Digital Logic",
    "IIT"
};

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("result.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\n====================================\n");
    printf("          ADD NEW STUDENT\n");
    printf("====================================\n");

    printf("Enter Name: ");
    getchar(); // clear buffer
    fgets(s.name, sizeof(s.name), stdin);

    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);

    s.total = 0;

    for(int i = 0; i < 5; i++)
    {
        printf("%s: ", subjects[i]);
        scanf("%f", &s.marks[i]);

        s.total += s.marks[i];
    }

    s.percentage = s.total / 5;

    fprintf(fp, "%s|%d", s.name, s.roll);

    for(int i = 0; i < 5; i++)
    {
        fprintf(fp, "|%.2f", s.marks[i]);
    }

    fprintf(fp, "|%.2f|%.2f\n", s.total, s.percentage);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("result.txt", "r");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\n====================================\n");
    printf("         ALL STUDENT RECORDS\n");
    printf("====================================\n");

    while(fscanf(fp,
                 " %49[^|]|%d|%f|%f|%f|%f|%f|%f|%f",
                 s.name,
                 &s.roll,
                 &s.marks[0],
                 &s.marks[1],
                 &s.marks[2],
                 &s.marks[3],
                 &s.marks[4],
                 &s.total,
                 &s.percentage) == 9)
    {
        printf("\n------------------------------------\n");

        printf("Name       : %s\n", s.name);
        printf("Roll No    : %d\n", s.roll);

        for(int i = 0; i < 5; i++)
        {
            printf("%-13s : %.2f\n",
                   subjects[i],
                   s.marks[i]);
        }

        printf("Total      : %.2f\n", s.total);
        printf("Percentage : %.2f%%\n",
               s.percentage);
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;

    int roll;
    int found = 0;

    fp = fopen("result.txt", "r");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\nEnter Roll No to Search: ");
    scanf("%d", &roll);

    while(fscanf(fp,
                 " %49[^|]|%d|%f|%f|%f|%f|%f|%f|%f",
                 s.name,
                 &s.roll,
                 &s.marks[0],
                 &s.marks[1],
                 &s.marks[2],
                 &s.marks[3],
                 &s.marks[4],
                 &s.total,
                 &s.percentage) == 9)
    {
        if(s.roll == roll)
        {
            printf("\n====================================\n");
            printf("         STUDENT FOUND\n");
            printf("====================================\n");

            printf("Name       : %s\n", s.name);
            printf("Roll No    : %d\n", s.roll);

            for(int i = 0; i < 5; i++)
            {
                printf("%-13s : %.2f\n",
                       subjects[i],
                       s.marks[i]);
            }

            printf("Total      : %.2f\n", s.total);
            printf("Percentage : %.2f%%\n",
                   s.percentage);

            found = 1;
            break;
        }
    }

    if(!found)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(fp);
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n\n====================================\n");
        printf("   STUDENT RESULT MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid Input! Enter 1-4 only.\n");

            while(getchar() != '\n');

            continue;
        }

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                printf("\nThank You For Using The System!\n");
                exit(0);

            default:
                printf("Invalid Choice! Please enter 1-4.\n");
        }
    }

    return 0;
}
