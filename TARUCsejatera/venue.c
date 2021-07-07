#include "venue.h"

void printVenueInfo(venueInfo venue)
{
    printf("\n\n\t .---------------------------------------------------------.\n");
    printf("\t |                                                         |\n");
    printf("\t |  Venue ID : %4d                                        |\n", venue.venueID);
    printf("\t |  Venue Category : %-25s             |\n", venue.category);
    printf("\t |  Venue description : %-25s          |\n", venue.description);
    printf("\t |                                                         |\n");
    printf("\t |  Max number of visitor : %3d                            |\n", venue.maxVisitor);
    printf("\t |  Current visitor : %3d                                  |\n", venue.currentVisitor);
    printf("\t |                                                         |\n");
    printf("\t |  Sanitization date : %02d/%02d/%4d                         |\n", xd.day, xd.month, xd.year);
    printf("\t |  Current event : %-25s              |\n", venue.currentEvent);
    printf("\t |  Venue Name : %-25s                 |\n", venue.venueName);
    printf("\t |                                                         |\n");
    printf("\t '---------------------------------------------------------'\n");
}

void addRecord(venueInfo* venueArr, int* index, int* maxSize, venueMetaData* md)
{
    (md->numAdd)++;

    char ans = 'Y';
    venueInfo venueData;

    //char* usrInput = malloc(BUFFER_SIZE); // holds user input to check for errors

    while (toupper(ans) == 'Y')
    {
        if (*index == *maxSize) // check for max size
        {
            void* temp = realloc(venueArr, (*index + 10) * sizeof(venueInfo));
            if (!temp)
            {
                free(temp);
                temp = NULL;
                printf("\n\t\t\t.-----------------------------------------------------------------------.\n");
                printf("\t\t\t|  Error with adding venue record. Please save the data and try again.  |\n");
                printf("\t\t\t.-----------------------------------------------------------------------.");
                return;
            }
            venueArr = temp;
            *maxSize = *index + 10;
        }
        printf("\n\t ________________");
        printf("\n\n\t Venue ID              -> ");
        scanf("%d", &venueData.venueID); rewind(stdin);
        printf("\n\t Venue catogary        -> ");
        fgets(&venueData.category, BUFFER_SIZE, stdin); rewind(stdin);
        venueData.category[strcspn(venueData.category, "\n")] = 0;   //to avoid the blank space after enter(in file)
        printf("\n\t Venue description     -> ");
        fgets(&venueData.description, BUFFER_SIZE, stdin);
        venueData.description[strcspn(venueData.description, "\n")] = 0;

        printf("\n\t ________________________________________________\n\n");
        printf("\t  Enter venue max no.of vistor   -> ");
        scanf("%d", &venueData.maxVisitor); rewind(stdin);
        while (venueData.maxVisitor < 0)
        {
            printf("\n\t      Invalid input. Please enter again : ");
            scanf("%d", &venueData.maxVisitor); rewind(stdin);
        }
        printf("\n\t Enter venue current visitors    -> ");
        scanf("%d", &venueData.currentVisitor); rewind(stdin);
        while (venueData.currentVisitor < 0)
        {
            printf("\n\t      Invalid input. Please enter again : ");
            scanf("%d", &venueData.currentVisitor);
        }

        printf("\n\t ________________________________________________\n\n");
        printf("\t Enter sanitization year         -> ");
        scanf("%d", &venueData.sanitizationDate.year); rewind(stdin);
        while (venueData.sanitizationDate.year < 0 || venueData.sanitizationDate.year > 2021)
        {
            printf("\n\t      Invalid input. Please enter again : ");
            scanf("%d", &venueData.sanitizationDate.year);
        }
        printf("\n\t Enter sanitization month (1-12) -> ");
        scanf("%d", &venueData.sanitizationDate.month); rewind(stdin);
        while (venueData.sanitizationDate.month < 1 || venueData.sanitizationDate.month > 12)
        {
            printf("\n\t      Invalid input. Please enter again : ");
            scanf("%d", &venueData.sanitizationDate.month);
        }
        printf("\t Enter sanitization day (1-31)    -> ");
        scanf("%d", &venueData.sanitizationDate.day); rewind(stdin);
        while (venueData.sanitizationDate.day < 1 || venueData.sanitizationDate.day > 31)
        {
            printf("\n\t      Invalid input. Please enter again : ");
            scanf("%d", &venueData.sanitizationDate.day);
        }
        rewind(stdin);

        printf("\n\t ________________________________________________\n\n");
        printf("\t Enter current event    -> ");
        fgets(&venueData.currentEvent, BUFFER_SIZE, stdin);
        venueData.currentEvent[strcspn(venueData.currentEvent, "\n")] = 0;
        printf("\n\t Enter the venue name   -> ");
        fgets(&venueData.venueName, BUFFER_SIZE, stdin);
        venueData.venueName[strcspn(venueData.venueName, "\n")] = 0;
        venueArr[(*index)++] = venueData;   //save input into array, add numbering 

        system("cls");
        printf("\n\n\t          .----------------------------.\n");
        printf("\t          |   Added successful ! ! !   |\n");
        printf("\t          '----------------------------'\n");
        printf("\n\t __________________________________________________\n\n");

        printf("\n\n\t    More record (Y or N) >> ");
        scanf("%c", &ans);
        rewind(stdin);
        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Add More record ??? (Y or N) ->   ");
            scanf("%c", &ans);
            rewind(stdin);
        }
    }
    system("cls");

}

void showRecord(venueInfo* venueArr, int size)
{
    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }

    int index = 0;

    while (index < size)
    {
        printVenueInfo(venueArr[index]);

        index++;
    }
    system("pause");
    system("cls");
}

// loop through the array and find the record
// returns venueInfo with venueID -1 if not found
venueInfo findRecord(venueInfo* venueArr, int size, int searchID)
{
    venueInfo temp;
    temp.venueID = -1; // value if not found 

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return temp;
    }

    for (int i = 0; i < size; i++)
        if (venueArr[i].venueID == searchID)
            return venueArr[i];

    return temp;
}

// performs findRecord and displays the result if found 
void searchRecord(venueInfo* venueArr, int size)
{
    int searchID; char cont = 'Y';
   
    while (toupper(cont) == 'Y') {
        printf("\n\n\t Enter [Venue ID] to search: ");
        scanf("%d", &searchID); rewind(stdin);

        venueInfo temp = findRecord(venueArr, size, searchID);

        if (temp.venueID == -1)
        {
            system("cls");
            printf("\n\n\t    .--------------------------------------.\n");
            printf("\t    |   No record found for venue ID.%3d   |\n", searchID);
            printf("\t    '--------------------------------------'\n\n");
        }
        else
            printVenueInfo(temp);

        printf("\n\t ___________________________________________________________\n\n");
        printf("\n\t Continue to search venue record ? ( Y or N ) :  ");
        scanf("%c", &cont);
        rewind(stdin);
        while (toupper(cont) != 'Y' && toupper(cont) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No :  ");
            scanf("%c", &cont);
            rewind(cont);
        }
        system("cls");
    }

    system("cls");

}

void modifyRecord(venueInfo* venueArr, int size, venueMetaData* md)
{
    (md->numModify)++;

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }

    int usrInput;
    printf("\t\t\t ________________________________________________________________\n");
    printf("\t\t\t|            |           |                                       |\n");
    printf("\t\t\t|            |   Venue   |               Name of                 |\n");
    printf("\t\t\t|     No.    |    ID.    |                Venue                  |\n");
    printf("\t\t\t|____________|___________|_______________________________________|\n");
    for (int index = 0; index < size; index++)
    {
        printf("\t\t\t|            |           |                                       |\n");
        printf("\t\t\t|     %2d     |    %3d    |       %-30s  |\n", index + 1, venueArr[index].venueID, venueArr[index].venueName); //not sure what to print
        printf("\t\t\t|____________|___________|_______________________________________|\n");

    }
    printf("\n\t\t\t    Select which [No.] to modify : ");
    scanf("%d", &usrInput); rewind(stdin);

    while (usrInput > size)
    {
        printf("\n\t\t '``````````````````````````````````````````````````````````````'\n");
        printf("\t\t '       No. not found. Please choose number shown in above.    '\n");
        printf("\t\t '                                                              '\n");
        printf("\t\t ````````````````````````````````````````````````````````````````\n\n");

        printf("\t\t\t    Select [No.] to modify : ");
        scanf("%d", &usrInput);
        rewind(stdin);
    }
    usrInput--; //follow the array rules
    system("cls");

    printf("\n\n\t Enter venue category     : ");
    fgets(&venueArr[usrInput].category, BUFFER_SIZE, stdin); rewind(stdin);
    venueArr[usrInput].category[strcspn(venueArr[usrInput].category, "\n")] = 0;
    printf("\n\t Enter venue description  : ");
    fgets(&venueArr[usrInput].description, BUFFER_SIZE, stdin); rewind(stdin);
    venueArr[usrInput].description[strcspn(venueArr[usrInput].description, "\n")] = 0;

    printf("\n\n\t Enter venue max no.of vistor : ");
    scanf("%d", &venueArr[usrInput].maxVisitor); rewind(stdin);
    while (venueArr[usrInput].maxVisitor < 0)
    {
        printf("\n\t      Invalid input. Please enter again : ");
        scanf("%d", &venueArr[usrInput].maxVisitor);
    }
    printf("\n\t Enter venue current visitors : ");
    scanf("%d", &venueArr[usrInput].currentVisitor); rewind(stdin);
    while (venueArr[usrInput].currentVisitor < 0)
    {
        printf("\n\t      Invalid input. Please enter again : ");
        scanf("%d", &venueArr[usrInput].currentVisitor);
    }

    printf("\n\n\t Enter sanitization year         : ");
    scanf("%d", &venueArr[usrInput].sanitizationDate.year); rewind(stdin);
    while (venueArr[usrInput].sanitizationDate.year < 0 || venueArr[usrInput].sanitizationDate.year > 2021)
    {
        printf("\n\t      Invalid input. Please enter again : ");
        scanf("%d", &venueArr[usrInput].sanitizationDate.year);
    }
    printf("\n\t Enter sanitization month (1-12) : ");
    scanf("%d", &venueArr[usrInput].sanitizationDate.month);
    while (venueArr[usrInput].sanitizationDate.month < 1 || venueArr[usrInput].sanitizationDate.month > 12)
    {
        printf("\n\t      Invalid input. Please enter again : ");
        scanf("%d", &venueArr[usrInput].sanitizationDate.month);
    }
    printf("\n\t Enter sanitization day          : ");
    scanf("%d", &venueArr[usrInput].sanitizationDate.day); rewind(stdin);
    while (venueArr[usrInput].sanitizationDate.day < 1 || venueArr[usrInput].sanitizationDate.day > 31)
    {
        printf("\n\t      Invalid input. Please enter again : ");
        scanf("%d", &venueArr[usrInput].sanitizationDate.day); rewind(stdin);
    }
    rewind(stdin);

    printf("\n\n\t Enter current event      : ");
    fgets(&venueArr[usrInput].currentEvent, BUFFER_SIZE, stdin);
    venueArr[usrInput].currentEvent[strcspn(venueArr[usrInput].currentEvent, "\n")] = 0;
    printf("\n\t Enter the venue name     : ");
    fgets(&venueArr[usrInput].venueName, BUFFER_SIZE, stdin);
    venueArr[usrInput].venueName[strcspn(venueArr[usrInput].venueName, "\n")] = 0;

    system("cls");
    printf("\n\n\t\t\t     .---------------------------------------.\n");
    printf("\t\t\t     |   Modify successful ! Data updated.   |\n");
    printf("\t\t\t     '---------------------------------------'\n");
    printf("\n\t\t\t _________________________________________________\n\n\n\n");
    system("pause");
    system("cls");
}

venueInfo* readData(int* size)
{
    FILE* fp;
    fp = fopen("./Files/Venue.dat", "rb");

    if (fp == NULL) {
        fp = fopen("./Files/Venue.dat", "wb");
        fclose(fp);
        *size = 0;
        venueInfo* ok = malloc(10 * sizeof(venueInfo)); // allocate extra 10 slots for new data
        return ok;
    }

    fseek(fp, 0, SEEK_END);
    int lSize = ftell(fp);
    rewind(fp);
    *size = lSize / sizeof(venueInfo);
    venueInfo* ok = malloc(10 * sizeof(venueInfo) + lSize); // allocate extra 10 slots for new data
    int i = 0;
    while (fread(&ok[i++], sizeof(venueInfo), 1, fp) == 1);
    fclose(fp);
    return ok;
}

void writeData(venueInfo* venueArr, int size)
{
    FILE* fp;
    fp = fopen("./Files/Venue.dat", "wb");
    for (int i = 0; i < size; i++)
    {
        fwrite(&venueArr[i], sizeof(venueInfo), 1, fp);
    }
    fclose(fp);
}

void deleteData(venueInfo* venueArr, int* size, venueMetaData* md)
{
    int venueID; char delVen = 'Y';

    while (toupper(delVen) == 'Y') {
        printf("\n\n\t Enter venue ID to delete: ");
        scanf("%d", &venueID); rewind(stdin);
        // check if search term exists in array
        if (findRecord(venueArr, *size, venueID).venueID == -1)
        {
            system("cls");
            printf("\n\n\t       .-------------------------------.\n");
            printf("\t       |       Unknown Venue ID !      |\n");
            printf("\t       '-------------------------------'\n");
            printf("\n\t _____________________________________________\n\n");
            printf("\n\t Please enter again :   ");
            scanf("%s", &venueID);
            rewind(stdin);
        }
        printf("\n\t _________________________________________________\n");
        printf("\n\n\t DELETE this venue ID record ? ( Y or N ) : ");
        scanf("%c", &delVen);
        rewind(stdin);
        while (toupper(delVen) != 'Y' && toupper(delVen) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t DELETE this venue ID record ? ( Y or N ) : ");
            scanf("%c", &delVen);
            rewind(stdin);
        }
        if (toupper(delVen) == 'Y')
        {

            for (int i = 0; i < *size; i++)
                if (venueArr[i].venueID == venueID)
                    for (; i + 1 < *size; i++)
                        venueArr[i] = venueArr[i + 1];

            (*size)--;
            (md->numDelete)++;

            system("cls");
            printf("\n\n\t          .-----------------------------.\n");
            printf("\t          |   Delete successful ! ! !   |\n");
            printf("\t          '-----------------------------'\n");
            printf("\n\t _________________________________________________\n\n");
        }

        printf("\n\t Delete more venue record ?? ( Y or N ) ->   ");
        scanf("%c", &delVen);
        rewind(stdin);
        while (toupper(delVen) != 'Y' && toupper(delVen) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No -> ");
            scanf("%c", &delVen);
            rewind(stdin);
        }
        system("cls");
    }
    system("cls");
}

void reportVenue(venueMetaData* md)
{
    printf("\n\n\t\t\t ________________________________________________\n");
    printf("\t\t\t|                                        |       |\n");
    printf("\t\t\t|    Number of visitor records added     |  %2d   |\n", (md->numAdd));
    printf("\t\t\t|________________________________________|_______|\n");
    printf("\t\t\t|                                        |       |\n");
    printf("\t\t\t|    Number of visitor records modified  |  %2d   |\n", (md->numModify));
    printf("\t\t\t|________________________________________|_______|\n");
    printf("\t\t\t|                                        |       |\n");
    printf("\t\t\t|    Number of visitor records deleted   |  %2d   |\n", (md->numDelete));
    printf("\t\t\t|________________________________________|_______|\n");
}

void venue(venuePass venPass, venueMetaData* md)
{
    int selection = 0;

    do {
        printf("\n\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t     !         Venue Menu          !\n");
        printf("\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
        printf("\t\t\t.---------------------------------------.\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [1]  Add new record              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [2]  Search record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [3]  Modify records              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [4]  Show all records            |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [5]  Delete record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [6]  Report actions done         |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [7]  Back to Main Menu           |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t'---------------------------------------'\n");
        printf("\n\t\t\t Please enter your option :  ");
        scanf("%d", &selection);

        if (selection == 1)
        {
            system("cls");
            addRecord(venPass.venArr, venPass.size, venPass.maxSize, md);
        }
        else if (selection == 2)
        {
            system("cls");
            searchRecord(venPass.venArr, *(venPass.size));
        }
        else if (selection == 3)
        {
            system("cls");
            modifyRecord(venPass.venArr, *(venPass.size), md);
        }
        else if (selection == 4)
        {
            system("cls");
            showRecord(venPass.venArr, *(venPass.size));
        }
        else if (selection == 5)
        {
            system("cls");
            deleteData(venPass.venArr, venPass.size, md);
        }
        else if (selection == 6)
        {
            system("cls");
            reportVenue(md);
        }
        else if (selection == 7)
        {
            printf("\n\n\n");
            system("pause");
            system("cls");
            printf("\n\n\t\t_____________________________________\n\n");
            printf("\t\t      Returning to main menu...\n");
            printf("\t\t_____________________________________\n\n\n\n\n");
            system("pause"); system("cls");
            return;
        }
        else
        {
            system("cls");
            printf("\n\n\t\t======================================================\n\n");
            printf("\t\tInvalid choice! Please enter the NUMBER shown in menu.\n\n");
            printf("\t\t======================================================\n\n\n\n");
            system("pause"); system("cls");
        }
    } while (selection != 7);
}