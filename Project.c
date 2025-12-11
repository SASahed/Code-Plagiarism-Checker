#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 20000
#define REGISTER "register.txt"

// --------------------- REMOVE NEWLINE ---------------------

void removeNewline(char str[])
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

// --------------------- REMOVE ALL COMMENTS ---------------------

void removeComments(const char src[], char dest[])
{
    int i = 0, j = 0;

    while (src[i] != '\0')
    {

        if (src[i] == '/' && src[i + 1] == '/')
        {
            while (src[i] != '\n' && src[i] != '\0')
                i++;
        }

        else if (src[i] == '/' && src[i + 1] == '*')
        {
            i += 2;
            while (!(src[i] == '*' && src[i + 1] == '/') && src[i] != '\0')
                i++;
            if (src[i] != '\0') i += 2;
        }

        else
        {
            dest[j++] = src[i++];
        }
    }

    dest[j] = '\0';
}

// --------------------- NORMALIZE ---------------------

void normalize(char str[])
{
    char tmp[MAX];
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isspace(str[i]))
        {
            tmp[j++] = tolower(str[i]);
        }
    }

    tmp[j] = '\0';
    strcpy(str, tmp);
}

// --------------------- FILE TO STRING ---------------------

int readFileToString(const char filename[], char buffer[])
{
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    size_t len = fread(buffer, 1, MAX - 1, fp);
    buffer[len] = '\0';

    fclose(fp);
    return 1;
}

// --------------------- PLAGIARISM CHECK ---------------------

float plagiarismCheck()
{
    char file1[500], file2[500];
    char code1[MAX], code2[MAX];
    char clean1[MAX], clean2[MAX];

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nEnter first file path: ");
    fgets(file1, sizeof(file1), stdin);
    removeNewline(file1);

    printf("Enter second file path: ");
    fgets(file2, sizeof(file2), stdin);
    removeNewline(file2);

    if (!readFileToString(file1, code1) || !readFileToString(file2, code2))
    {
        printf("\nError: Could not open one of the files.\n");
        return -1;
    }

    removeComments(code1, clean1);
    removeComments(code2, clean2);

    normalize(clean1);
    normalize(clean2);

    int len1 = strlen(clean1);
    int len2 = strlen(clean2);
    int comparable = (len1 < len2) ? len1 : len2;

    int match = 0;
    for (int i = 0; i < comparable; i++)
    {
        if (clean1[i] == clean2[i])
            match++;
    }

    float similarity = (match * 100.0f) / comparable;

    printf("\n----------------------------------------\n");
    printf("          PLAGIARISM CHECK RESULT\n");
    printf("----------------------------------------\n");
    printf("Comparable Lines: %d\n", comparable);
    printf("Matching Lines  : %d\n", match);
    printf("Similarity      : %.2f%%\n", similarity);
    if (similarity > 60)
        printf("\nHIGH similarity detected!\n");
    else
        printf("\nSimilarity acceptable.\n");

    // Save report
    FILE *rep = fopen("report.txt", "w");
    fprintf(rep, "COMPARABLE LINES : %d\n", comparable);
    fprintf(rep, "MATCHING LINES   : %d\n", match);
    fprintf(rep, "SIMILARITY       : %.2f%%\n", similarity);
    fclose(rep);

    printf("\nReport saved in 'report.txt'\n");

    return similarity;
}

// --------------------- VIEW REPORT FUNCTION ---------------------

void viewReport()
{
    FILE *f = fopen("report.txt", "r");
    if (!f)
    {
        printf("\nNo report found! Run a plagiarism check first.\n");
        return;
    }

    printf("\n===== LAST GENERATED REPORT =====\n\n");

    char line[200];
    while (fgets(line, sizeof(line), f))
    {
        printf("%s", line);
    }

    fclose(f);
}

// --------------------- REGISTER FUNCTION ---------------------

void registerUser()
{
    FILE *fp = fopen(REGISTER, "w");
    char username[50], password[50];

    printf("\n--- Register New User ---\n");
    printf("Create Username: ");
    scanf("%s", username);

    printf("Create Password: ");
    scanf("%s", password);

    fprintf(fp, "%s %s", username, password);
    fclose(fp);

    printf("\nRegistration Successful!\n");
}

// --------------------- LOGIN FUNCTION ---------------------

int loginUser()
{
    FILE *fp = fopen(REGISTER, "r");
    char savedUser[50], savedPass[50];
    char user[50], pass[50];

    if (!fp)
    {
        printf("\nNo user found. Registering first...\n");
        registerUser();
        return 2;
    }

    if (fscanf(fp, "%s %s", savedUser, savedPass) != 2)
    {
        fclose(fp);
        printf("User file empty. Registering first...\n");
        registerUser();
        return 2;
    }

    fclose(fp);

    printf("\n--- Login ---\n");
    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, savedUser) == 0 && strcmp(pass, savedPass) == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }
    else
    {
        printf("\nIncorrect Username or Password!\n");
        return 0;
    }
}

// --------------------- MAIN MENU FUNCTION ---------------------

void menu()
{
    int choice;

    do
    {
        printf("\n============= MAIN MENU =============\n");
        printf("1. Plagiarism Check\n");
        printf("2. View Last Report\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            plagiarismCheck();
            break;
        case 2:
            viewReport();
            break;
        case 3:
            printf("\nExiting program...\n");
            break;
        default:
            printf("\nInvalid choice! Try again.\n");
        }

    }
    while (choice != 3);
}

// -------------------- AUTHENTICATION MENU ---------------------

void authMenu()
{
    int choice;
    int loginResult;

    do
    {
        printf("\n=========== WELLCOME TO CODE PLAGIARISM CHECKER ===========\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit Program\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            registerUser();
            printf("\nNow please Login\n");
            loginResult = loginUser();
            if (loginResult == 1)
            {
                menu();
            }
            break;

        case 2:
            loginResult = loginUser();
            if (loginResult == 2)
            {
                registerUser();
                printf("\nNow please Login\n");
                loginResult = loginUser();
            }

            if (loginResult == 1)
            {
                menu();
            }
            break;

        case 3:
            printf("\nExiting program...\n");
            break;

        default:
            printf("\nInvalid choice! Try again.\n");
        }

    }
    while (choice != 3);
}

// -------------------- MAIN FUNCTION ---------------------------
int main()
{
    authMenu();
    return 0;
}
