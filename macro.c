#include "macro.h"

/* Creates the macros table */
void macroTable(struct Macro *head, char name[], char data[])
{
    struct Macro *temp = (struct Macro*)malloc(sizeof(struct Macro));
    struct Macro *current = head;

    strcpy(temp->name, name);
    strcpy(temp->data, data);
    temp->next = NULL;

    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = temp;
}

/* Prints the name and the data of the macro */
void printMacro(struct Macro *tail)
{
    struct Macro *temp;
    for (temp = tail->next; temp != NULL; temp = temp->next)
    {
        printf("\n The macro's name: %s\n The Data: %s\n", temp->name, temp->data);
    }
}

/* Checks if there is a macro */
int isMacro(char line[])
{
    int index = 0;
    int mindex = 0;
    char macro[MAX];
    strcpy(macro, "");

    while (isspace(line[index]))
        index++;

    while (!isspace(line[index]) && line[index] != '\n')
    {
        macro[mindex] = line[index];
        mindex++;
        index++;
    }

    if (strcmp(macro, "macro") == 0)
        return 1;

    return 0;
}

/* Checks where the macro ends */
int isEndMacro(char line[])
{
    int index = 0;
    int mindex = 0;
    char macro[MAX];
    strcpy(macro, "");

    while (isspace(line[index]))
        index++;

    while (!isspace(line[index]) && line[index] != '\n')
    {
        macro[mindex] = line[index];
        mindex++;
        index++;
    }

    if (strcmp(macro, "endmacro") == 0)
        return 1;

    return 0;
}

/* Adds macro to the macros table */
void insertMacro(struct Macro *temp, char line[], FILE *fp)
{
    int index = 0;
    int nindex = 0;
    char mname[MAX];
    char mdata[MAX];
    strcpy(mname, "");
    strcpy(mdata, "");

    while (isspace(line[index]))
        index++;

    while (!isspace(line[index]) && line[index] != '\n')
    {
        mname[nindex] = line[index];
        nindex++;
        index++;
    }

    strncpy(temp->name, mname, sizeof(temp->name) - 1);

    while (fgets(line, MAX, fp))
    {
        if (isEndMacro(line))
            break;

        strncat(mdata, line, sizeof(mdata) - strlen(mdata) - 1);
    }

    strncpy(temp->data, mdata, sizeof(temp->data) - 1);
}

int firstRead(int i, char *argv[], struct Macro *head)
{
    char line[MAX];
    FILE *fp;
    fp = fopen(argv[i], "r");
    if (fp == NULL)
    {
        printf("Error ! can't open the file");
        errorsMassages(MISSING_ARGUMENT);
        return 1;
    }

    while (fgets(line, MAX, fp))
    {
        struct Macro *temp = (struct Macro *)malloc(sizeof(struct Macro));
        if (isMacro(line))
        {
            insertMacro(temp, line, fp);
            head->next = temp;
            head = temp;
        }
    }

    fclose(fp);
    return 0;
}

int isCall(char line[], FILE *fpw, struct Macro *tail)
{
    int index = 0, mindex = 0;
    char Mname[MAX];
    struct Macro *temp = tail;
    int i;

    for (i = 0; i < MAX; i++)
    {
        Mname[i] = '\0';
    }

    while (isspace(line[index]))
        index++;

    while (!isspace(line[index]) && line[index] != '\n')
    {
        Mname[mindex] = line[index];
        mindex++;
        index++;
    }

    while (temp != NULL)
    {
        if (!strcmp(temp->name, Mname))
        {
            fprintf(fpw, "%s", temp->data);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int preFile(int i, char *argv[], struct Macro *tail)
{
    int macroflag = 0;
    FILE *fpw;
    FILE *fpr;
    char line[MAX];
    char fname[MAX];
    char fname2[MAX];
    int lineLength;


    strcpy(fname, argv[i]);
    strcpy(fname2, argv[i]);
    strncat(fname2, ".am", 3);
    fpr = fopen(fname, "r");
    fpw = fopen(fname2, "w");
    if (fpr == NULL)
    {
        printf("Can't open the file: %s \n \n", argv[i]);
        return 1;
    }

    while (fgets(line, MAX, fpr))
    {
        lineLength = strlen(line);
        if (line[lineLength - 1] == '\n'){
            line[lineLength - 1] = '\0';
        }
        if (!macroflag)
        {
            if (!isCall(line, fpw, tail))
            {
                if (isEndMacro(line) == 0)
                {
                    fprintf(fpw, "%s\n", line);
                }
                else
                {
                    macroflag = 1;
                }
            }
        }
        else
        {
            if (isEndMacro(line) == 2)
                macroflag = 0;
        }
    }

    fclose(fpw);
    fclose(fpr);
    return 0;
}
