#include "visitor.h"
char* CATEGORY[4] = { "Student", "Staff", "Outsiders", "General workers" };

void addVisitorRecord(visitorInfo* visitorArr, int* index, int* maxSize)
{
    char ans = 'Y';
    while (toupper(ans) == 'Y') {

        visitorInfo visitorData;

        if (*index == *maxSize) // resize array if needed
        {
            void* temp = realloc(visitorArr, (*index + 10) * sizeof(visitorInfo));
            if (!temp)
            {
                free(temp);
                temp = NULL;
                printf("\n\t\t\t.-------------------------------------------------------------------------.\n");
                printf("\t\t\t|  Error with adding visitor record. Please save the data and try again.  |\n");
                printf("\t\t\t.-------------------------------------------------------------------------.");
                return;
            }
            visitorArr = temp;
            *maxSize = *index + 10;
        }

        printf("\n\n\t Please enter visitor's details\n");
        printf("\t ------------------------------");
        printf("\n\n\t IC : ");
        scanf("%s", &visitorData.icNum); rewind(stdin);
        while (strlen(visitorData.icNum) != 12)
        {
            printf("\n\t      Incorrect IC format. Please enter again: ");
            scanf("%s", &visitorData.icNum); rewind(stdin);
        }
        printf("\t Name : ");
        fgets(&visitorData.visitorName, BUFFER_SIZE, stdin); rewind(stdin);
        visitorData.visitorName[strcspn(visitorData.visitorName, "\n")] = 0;

        printf("\t Gender ( M / F ) : ");
        scanf("%c", &visitorData.gender); rewind(stdin);

        while (toupper(visitorData.gender) != 'M' && toupper(visitorData.gender) != 'F')
        {
            printf("\n\t      Incorrect input. Please enter again: ");
            scanf("%c", &visitorData.gender); rewind(stdin);
        }

        printf("\t Temperature  : ");
        scanf("%f", &visitorData.temp); rewind(stdin);

        while (visitorData.temp < 0)
        {
            printf("\n\t      Incorrect temperature. Please enter again: ");
            scanf("%f", &visitorData.temp); rewind(stdin);
        }
        printf("\t Phone number : ");
        scanf("%s", &visitorData.phoneNo); rewind(stdin);

        printf("\n\t ________________________________________________\n");


        for (int i = 0; i < 4; i++)
            printf("\n\t %d. %s", i + 1, CATEGORY[i]);
        printf("\n");

        printf("\n\t Choose one category (1 - 4) : ");
        scanf("%d", &visitorData.category); rewind(stdin);

        while (visitorData.category < 1 || visitorData.category > 4)
        {
            printf("\n\t      Incorrect input. Please enter again:  ");
            scanf("%d", &visitorData.category); rewind(stdin);
        }

        visitorData.category--;

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        visitorData.visitDate.day = tm.tm_mday;
        visitorData.visitDate.month = tm.tm_mon + 1;
        visitorData.visitDate.year = tm.tm_year + 1900;
        visitorData.visitTime.hour = tm.tm_hour;
        visitorData.visitTime.minit = tm.tm_min;
        visitorData.visitTime.second = tm.tm_sec;

        printf("\n\t ________________________________________________\n");
        printf("\n\t Please enter staff ID (if have, 0 if not) : ");
        scanf("%d", &visitorData.staffID); rewind(stdin);

        while (visitorData.staffID < 0)
        {
            printf("\n\t      Incorrect staff ID. Please enter again: ");
            scanf("%d", &visitorData.staffID); rewind(stdin);
        }

        rewind(stdin);
        visitorArr[(*index)++] = visitorData;

        system("cls");
        printf("\n\n\t          .----------------------------.\n");
        printf("\t          |   Added successful ! ! !   |\n");
        printf("\t          '----------------------------'\n");
        printf("\n\t __________________________________________________\n\n");

        printf("\n\t Add More record ? (Y or N) :   ");
        scanf("%c", &ans);
        rewind(stdin);
        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No : ");
            scanf("%c", &ans);
            rewind(stdin);
        }

    }
    system("cls");
}

void printVisitorInfo(visitorInfo visitor, venueInfo venInfo, staffInfo staff)
{
    printf("\n\n\t .---------------------------------------------------------.\n");
    printf("\t |                                                         |\n");
    printf("\t |   Visit date : %02d/%02d/%02d    Visit time : %02d:%02d:%02d      |\n", xd_.day, xd_.month, xd_.year, xD_.hour, xD_.minit, xD_.second);
    printf("\t |                                                         |\n");
    printf("\t |   Visited Venue ID : %3d                                |\n", visitor.visitID);
    if (venInfo.venueID == -1)
        printf("|   Warning: Venue record not entered. Cannot display name.|\n");
    else
        printf("\t |   Visit venue name : %-25s          |\n", venInfo.venueName);
    printf("\t |                                                         |\n");
    printf("\t |   Visitor's Details                                     |\n");
    printf("\t |   =================                                     |\n");
    printf("\t |                                                         |\n");
    printf("\t |   Name   : %-25s                    |\n", visitor.visitorName);
    printf("\t |   IC     : %-12s                                 |\n", visitor.icNum);
    printf("\t |   Gender   : %c                                          |\n", visitor.gender);
    printf("\t |   Category : %-25s                  |\n", CATEGORY[visitor.category]);
    printf("\t |   Temperature  : %02.2f                                  |\n", visitor.temp);
    printf("\t |   Phone number : %-15s                        |\n", visitor.phoneNo);
    printf("\t |                                                         |\n");
    printf("\t |   Staff ID : %3d                                        |\n", visitor.staffID);
    // for the case when staffID is entered but staff info is not 
    if (visitor.staffID > 0 && visitor.staffID == staff.staffID)
        printf("\t |   Staff faculty: %-36s   |\n", staff.faculty);
    else
        printf("\t |   Not staff of faculty.                                 |\n");
    printf("\t |                                                         |\n");
    printf("\t '---------------------------------------------------------'\n");
}

void showVisitorRecord(visitorInfo* visitorArr, int size, venuePass venPass, vnePass vnePass, staffPass staffPass)
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
        printVisitorInfo(visitorArr[index], findRecord(venPass.venArr, *(venPass.size), findVisitExitRecord(vnePass.vneArr, *(vnePass.size), visitorArr[index].visitID).venueID), findStaffRecord(staffPass.staffArr, *(staffPass.size), visitorArr[index].staffID));

        index++;
    }
    system("pause");
    system("cls");
}

// find the specified record in the array
// returns venueInfo with venueID -1 if not found
visitorInfo findVisitorRecord(visitorInfo* visitorArr, int size, char* searchID)
{
    visitorInfo temp;
    strcpy(temp.icNum, "-1"); // value if not found 

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return temp;
    }

    for (int i = 0; i < size; i++)
    {
        if (strcmp(searchID, visitorArr[i].icNum) == 0)
            temp = visitorArr[i];
    }

    return temp;
}

// performs findRecord and displays the result if found 
void searchVisitorRecord(visitorInfo* visitorArr, int size, venuePass venPass, vnePass vnePass, staffPass staffPass)
{
    char searchID[BUFFER_SIZE], con = 'Y';
    while (toupper(con) == 'Y') {
        printf("\n\t Enter [Visitor IC] to search: ");
        scanf("%s", &searchID); rewind(stdin);

        visitorInfo temp = findVisitorRecord(visitorArr, size, searchID);

        if (temp.icNum == -1)
        {
            system("cls");
            printf("\n\t\t\t.-----------------------------------.\n");
            printf("\t\t\t|  No record found for IC %12d  |\n", searchID);
            printf("\t\t\t'-----------------------------------'\n\n");
        }
        else
            printVisitorInfo(temp, findRecord(venPass.venArr, *(venPass.size), findVisitExitRecord(vnePass.vneArr, *(vnePass.size), temp.visitID).venueID), findStaffRecord(staffPass.staffArr, *(staffPass.size), temp.staffID));

        printf("\n\t ___________________________________________________________\n\n");
        printf("\n\t Continue to search visitor record ? ( Y or N ) : ");
        scanf("%c", &con);
        rewind(stdin);
        while (toupper(con) != 'Y' && toupper(con) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No : ");
            scanf("%c", &con);
            rewind(stdin);
        }
        system("cls");
    }

    system("cls");
}

void modifyVisitorRecord(visitorInfo* visitorArr, int size)
{

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }

    int usrInput;
    printf("\t\t\t ______________________________________________________________________\n");
    printf("\t\t\t|              |                  |                                    |\n");
    printf("\t\t\t|   Visitor    |      Visitor     |              Visitor               |\n");
    printf("\t\t\t|  Record No.  |        IC.       |               Name                 |\n");
    printf("\t\t\t|______________|__________________|____________________________________|\n");
    for (int index = 0; index < size; index++)
    {
        printf("\t\t\t|              |                  |                                    |\n");
        printf("\t\t\t|      %2d      |   %-12s   |     %-30s |\n", index + 1, visitorArr[index].icNum, visitorArr[index].visitorName); //not sure what to print
        printf("\t\t\t|______________|__________________|____________________________________|\n");

    }

    printf("\n\t\t\t Please enter [Record No.] to modify: ");
    scanf("%d", &usrInput); rewind(stdin);
    while (usrInput > size)
    {
        printf("\n\t\t\t '````````````````````````````````````````````````````````````````````'\n");
        printf("\t\t\t '      Record no. not found. Please choose number shown in above.    '\n");
        printf("\t\t\t '                                                                    '\n");
        printf("\t\t\t ``````````````````````````````````````````````````````````````````````\n\n");

        printf("\t\t\t Select record number to modify : ");
        scanf("%d", &usrInput);
        rewind(stdin);
    }
    usrInput--;
    system("cls");

    printf("\n\n\t Visitor's details");
    printf("\n\t -----------------");
    printf("\n\n\t IC (no dash)     : ");
    scanf("%s", &visitorArr[usrInput].icNum); rewind(stdin);
    while (strlen(visitorArr[usrInput].icNum) != 12)
    {
        printf("\n\t      Incorrect IC format. Please enter again: ");
        scanf("%s", &visitorArr[usrInput].icNum);rewind(stdin);
    }
    
    printf("\t Name             : ");
    fgets(&visitorArr[usrInput].visitorName, BUFFER_SIZE, stdin); rewind(stdin);
    visitorArr[usrInput].visitorName[strcspn(visitorArr[usrInput].visitorName, "\n")] = 0; 
    printf("\t Gender ( M / F ) : ");
    scanf("%c", &visitorArr[usrInput].gender); rewind(stdin);
    while (toupper(visitorArr[usrInput].gender) != 'M' && toupper(visitorArr[usrInput].gender) != 'F')
    {
        printf("\n\t      Incorrect input. Please enter again : ");
        scanf("%c", &visitorArr[usrInput].gender);rewind(stdin);
    }

    printf("\t Temperature      : ");
    scanf("%f", &visitorArr[usrInput].temp); rewind(stdin);

    while (visitorArr[usrInput].temp < 0)
    {
        printf("\n\t      Incorrect temperature. Please enter again : ");
        scanf("%f", &visitorArr[usrInput].temp);rewind(stdin);
    }

    printf("\t Phone number     : ");
    scanf("%s", &visitorArr[usrInput].phoneNo); rewind(stdin);
    printf("\n\t ________________________________________________");

    for (int i = 0; i < 4; i++)
        printf("\n\n\t %d. %s", i + 1, CATEGORY[i]);

    printf("\n\n\t Category (1-4) : ");
    scanf("%d", &visitorArr[usrInput].category);
    rewind(stdin);

    visitorArr[usrInput].category--;

    while (visitorArr[usrInput].category < 1 && visitorArr[usrInput].category > 4)
    {
        printf("\n\t      Incorrect input. Please enter again :  ");
        scanf("%d", &visitorArr[usrInput].category);
        rewind(stdin);
    }
    printf("\n\t ________________________________________________\n");

    printf("\n\n\t Times of Visit & Exit");
    printf("\n\t ~~~~~~~~~~~~~~~~~~~~~ ");
    printf("\n\n\t +=================+");
    printf("\n\t |  Time of VISIT  |");
    printf("\n\t +=================+");
    printf("\n\t Hour (0-23) : ");
    scanf("%d", &visitorArr[usrInput].visitTime.hour); rewind(stdin);

    while (visitorArr[usrInput].visitTime.hour < 0 || visitorArr[usrInput].visitTime.hour > 23)
    {
        printf("\n\t      Incorrect input. Please enter again : ");
        scanf("%d", &visitorArr[usrInput].visitTime.hour); rewind(stdin);
    }

    printf("\t Minute (0-59) : ");
    scanf("%d", &visitorArr[usrInput].visitTime.minit); rewind(stdin);
    {
        while (visitorArr[usrInput].visitTime.minit < 0 || visitorArr[usrInput].visitTime.minit > 59)
        {
            printf("\n\t      Incorrect input. Please enter again : ");
            scanf("%d", &visitorArr[usrInput].visitTime.minit); rewind(stdin);
        }
    }
    printf("\t Second (0-59) : ");
    scanf("%d", &visitorArr[usrInput].visitTime.second); rewind(stdin);
    {
        while (visitorArr[usrInput].visitTime.second < 0 || visitorArr[usrInput].visitTime.second > 59)
        {
            printf("\n\t      Incorrect input. Please enter again: ");
            scanf("%d", &visitorArr[usrInput].visitTime.second); rewind(stdin);
        }
    }
    printf("\n\t +================+");
    printf("\n\t |  Time of EXIT  |");
    printf("\n\t +================+");
    printf("\n\t Hour (0-23) : ");
    scanf("%d", &visitorArr[usrInput].visitDate.year); rewind(stdin);
    {
        while (visitorArr[usrInput].visitDate.year < 0 || visitorArr[usrInput].visitDate.year > 2021)
        {
            printf("\n\t      Incorrect input. Please enter again: ");
            scanf("%d", &visitorArr[usrInput].visitDate.year); rewind(stdin);
        }
    }

    printf("\t Minute (0-59) : ");
    scanf("%d", &visitorArr[usrInput].visitDate.month);
    rewind(stdin);
    {

        while (visitorArr[usrInput].visitDate.month < 1 && visitorArr[usrInput].visitDate.month > 12)
        {
            printf("\n\t      Incorrect input. Please enter again: ");
            scanf("%d", &visitorArr[usrInput].visitDate.month); rewind(stdin);
        }

    }

    printf("\t Second (0-59) : ");
    scanf("%d", &visitorArr[usrInput].visitDate.day); rewind(stdin);
    {
        while (visitorArr[usrInput].visitDate.day < 1 && visitorArr[usrInput].visitDate.day > 31)
        {
            printf("\n\t      Incorrect input. Please enter again: ");
            scanf("%d", &visitorArr[usrInput].visitDate.day); rewind(stdin);
        }
    }

    printf("\n\t ________________________________________________\n");
    printf("\n\t Please enter staff ID (if have, 0 if not) : ");
    scanf("%d", &visitorArr[usrInput].staffID); rewind(stdin);

    while (visitorArr[usrInput].staffID < 0)
    {
        printf("\n\t      Incorrect staff ID. Please enter again : ");
        scanf("%d", &visitorArr[usrInput].staffID); rewind(stdin);
    }

    system("cls");
    printf("\n\n\t\t\t     .---------------------------------------.\n");
    printf("\t\t\t     |   Modify successful ! Data updated.   |\n");
    printf("\t\t\t     '---------------------------------------'\n");
    printf("\n\t\t\t _________________________________________________\n\n\n\n");
    system("pause");
    system("cls");
}

void visitorLogin(visitorPass visPass, vnePass vnePass, vneMetaData* md)
{
    visitorInfo* visitorArr = visPass.visitorArr;
    int* size = visPass.size;
    int* maxSize = visPass.maxSize;
    char userIC[BUFFER_SIZE];

    printf("\n\t Enter your IC: ");
    scanf("%s", &userIC);

    visitorInfo temp = findVisitorRecord(visitorArr, *size, userIC);

    if (strcmp(temp.icNum, "-1") == 0)
    {
        // register user 
        printf("\n\t\t\t.-----------------------------------------.\n");
        printf("\t\t\t|      IC not found. Please register!     |\n");
        printf("\t\t\t'-----------------------------------------'\n");
        addVisitorRecord(visitorArr, size, maxSize);
        temp = visitorArr[*size - 1];
    }
    else
    {
        // only update last visit date/time and temperature if user has already registered
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        temp.visitDate.day = tm.tm_mday;
        temp.visitDate.month = tm.tm_mon + 1;
        temp.visitDate.year = tm.tm_year + 1900;
        temp.visitTime.hour = tm.tm_hour;
        temp.visitTime.minit = tm.tm_min;
        temp.visitTime.second = tm.tm_sec;

        printf("\t Enter your temperature: ");
        scanf("%f", &temp.temp);

        while (temp.temp < 0)
        {
            printf("\n\t      Incorrect temperature. Please enter again: ");
            scanf("%f", &temp.temp);
        }
    }

    temp.visitID = addVisitExitRecord(&vnePass, temp.icNum, temp.temp, md); //link to visit & exit (function call visit&exit)

    for (int i = 0; i < *size; i++)
    {
        if (strcmp(visitorArr[i].icNum, temp.icNum) == 0)
        {
            visitorArr[i].visitID = temp.visitID;
        }
    }
}

void deleteVisitorData(visitorInfo* visitorArr, int* size)
{
    char visitorIC[BUFFER_SIZE], delVis;
    do {
        printf("\n\n\t Enter [Visitor IC] to delete: ");
        scanf("%s", &visitorIC); rewind(stdin);
        // check if search term exists in array
        if (strcmp(findVisitorRecord(visitorArr, *size, visitorIC).icNum, "-1") == 0)
        {
            system("cls");
            printf("\n\n\t       .-------------------------------.\n");
            printf("\t       |      Unknown IC number !      |\n");
            printf("\t       '-------------------------------'\n");
            printf("\n\t _____________________________________________\n\n");
            printf("\n\t Please enter again ->   ");
            scanf("%s", &visitorIC);
            rewind(stdin);
        }
        printf("\n\t _________________________________________________\n");
        printf("\n\n\t Sure to DELETE this visitor record ? ( Y or N ) ->    ");
        scanf("%c", &delVis);
        rewind(stdin);
        while (toupper(delVis) != 'Y' && toupper(delVis) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Sure to DELETE this visitor record ? ( Y or N ) ->   ");
            scanf("%c", &delVis);
            rewind(stdin);
        }
        if (toupper(delVis) == 'Y')
        {

            for (int i = 0; i < *size; i++)
                if (strcmp(visitorArr[i].icNum, visitorIC) == 0)
                    for (; i + 1 < *size; i++)
                        visitorArr[i] = visitorArr[i + 1];

            // update size 
            (*size)--;

            system("cls");
            printf("\n\n\t          .-----------------------------.\n");
            printf("\t          |   Delete successful ! ! !   |\n");
            printf("\t          '-----------------------------'\n");
            printf("\n\t _________________________________________________\n\n");
        }

        printf("\n\t Delete more visitor record ??? ( Y or N ) :   ");
        scanf("%c", &delVis);
        rewind(stdin);
        while (toupper(delVis) != 'Y' && toupper(delVis) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Delete more visditor record ??? ( Y or N ) : ");
            scanf("%c", &delVis);
            rewind(stdin);
        }
        system("cls");


    } while (toupper(visitorIC) == 'Y');

    system("cls");
}

visitorInfo* readVisitorData(int* size)
{
    FILE* fp;
    fp = fopen("./Files/Visitor.txt", "r");

    if (fp == NULL)
    {
        fp = fopen("./Files/Visitor.txt", "w");
        fclose(fp);
        *size = 0;
        visitorInfo* ok = malloc(10 * sizeof(visitorInfo)); // allocate extra 10 slots for new data
        return ok;
    }

    // get num of lines/num of data
    char temp[BUFFER_SIZE];
    while (fgets(temp, sizeof(temp), fp) != NULL)
    {
        (*size)++;
    };

    // allocate space
    visitorInfo* visitorArr = (visitorInfo*)malloc((10 + *size) * sizeof(visitorInfo)); // allocate extra 10 slots for new data
    rewind(fp);

    // read data into variables 
    int i = 0, a, b, c;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%c|%d:%d:%d|%d:%d:%d|%f|%d|%d|%d|\n", &visitorArr[i].icNum, &visitorArr[i].visitorName, &visitorArr[i].phoneNo, &visitorArr[i].gender, &visitorArr[i].visitDate.year, &visitorArr[i].visitDate.month, &visitorArr[i].visitDate.day, &visitorArr[i].visitTime.hour, &visitorArr[i].visitTime.minit, &visitorArr[i].visitTime.second, &visitorArr[i].temp, &visitorArr[i].staffID, &visitorArr[i].visitID, &visitorArr[i].category) != EOF)
    {
        i++;
    }

    fclose(fp);

    return visitorArr;
}

void writeVisitorData(visitorInfo* visitorArr, int size)
{
    FILE* fp;
    fp = fopen("./Files/visitor.txt", "w");

    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%s|%s|%s|%c|%d:%d:%d|%d:%d:%d|%f|%d|%d|%d|\n", visitorArr[i].icNum, visitorArr[i].visitorName, visitorArr[i].phoneNo, visitorArr[i].gender, visitorArr[i].visitDate.year, visitorArr[i].visitDate.month, visitorArr[i].visitDate.day, visitorArr[i].visitTime.hour, visitorArr[i].visitTime.minit, visitorArr[i].visitTime.second, visitorArr[i].temp, visitorArr[i].staffID, visitorArr[i].visitID, visitorArr[i].category);
    }

    fclose(fp);
}

void visitor(visitorPass visPass, venuePass venPass, vnePass vnePass, staffPass staffPass, vneMetaData* md)
{
    int usrInput = 0;

    do {
        printf("\n\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t     !         Visitor Menu        !\n");
        printf("\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
        printf("\t\t\t.---------------------------------------.\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [1]  Visitor login               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [2]  Search record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [3]  Modify record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [4]  Show all records            |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [5]  Delete records              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [6]  Back to Main Menu           |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t'---------------------------------------'\n");
        printf("\n\t\t\t Please enter your option :  ");
        scanf("%d", &usrInput);

        if (usrInput == 1) {
            system("cls");
            visitorLogin(visPass, vnePass, md);
        }
        else if (usrInput == 2) {
            system("cls");
            searchVisitorRecord(visPass.visitorArr, *(visPass.size), venPass, vnePass, staffPass);
        }
        else if (usrInput == 3) {
            system("cls");
            modifyVisitorRecord(visPass.visitorArr, *(visPass.size));
        }
        else if (usrInput == 4) {
            system("cls");
            showVisitorRecord(visPass.visitorArr, *(visPass.size), venPass, vnePass, staffPass);
        }
        else if (usrInput == 5) {
            system("cls");
            deleteVisitorData(visPass.visitorArr, visPass.size);
        }
        else if (usrInput == 6)
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
        else {
            system("cls");
            printf("\n\n\t\t======================================================\n\n");
            printf("\t\tInvalid choice! Please enter the NUMBER shown in menu.\n\n");
            printf("\t\t======================================================\n\n\n\n");
            system("pause"); system("cls");
        }

    } while (usrInput != 6);
}


