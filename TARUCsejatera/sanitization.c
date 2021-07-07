#include "sanitization.h"

void showSanRecord(sanitizationInfo* sanArr, int size, venuePass pass)
{
    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }
    int num = 0;
    while (num < size)
    {
        printSanitizationInfo(sanArr[num], findRecord(pass.venArr, *(pass.size), sanArr[num].venueID));

        num++;
    }

    system("pause");
    system("cls");
}

void printSanitizationInfo(sanitizationInfo san, venueInfo venueTemp)
{
    printf("\n\n\t .---------------------------------------------------------.");
    printf("\n\t |                                                         |");
    printf("\n\t |  Sanitization Record at - %02d/%02d/%02d                    |", sanDay.day, sanDay.month, sanDay.year);
    printf("\n\t | _______________________________________________________ |");
    printf("\n\t |                                                         |");
    printf("\n\t |  Record ID : %2d                                         |", san.sanRecord);
    printf("\n\t |                                                         |");
    printf("\n\t |  Start Time : %02d:%02d:%02d                                  |", sanStarTime.hour, sanStarTime.minit, sanStarTime.second);
    printf("\n\t |  End Time   : %02d:%02d:%02d                                  |", sanEndTime.hour, sanEndTime.minit, sanEndTime.second);
    printf("\n\t |  Venue ID   : %3d                                       |", san.venueID);
    if (san.venueID == -1)
        printf("\n\t |  Error!!! Venue ID not entered.                         |");
    else
        printf("\n\t |  Venue Name : %-35s       |", venueTemp.venueName);
    printf("\n\t |                                                         |");
    printf("\n\t |  Company name     : %-35s |", san.compName);
    printf("\n\t |  Person in charge : %-35s |", san.contactPerson);
    printf("\n\t |  Gender           : %c                                   |", toupper(san.gender));
    printf("\n\t |                                                         |");
    printf("\n\t '---------------------------------------------------------'\n");
}

void addSanRecord(sanitizationInfo* sanArr, int* index, int* maxSize, sanMetaData* md)
{
    char ans = 'Y';
    sanitizationInfo sanData;
    do
    {
        (md->numAdd)++;
        if (*index == *maxSize) // resize array if needed
        {
            void* temp = realloc(sanArr, (*index + 10) * sizeof(sanitizationInfo));
            if (!temp)
            {
                free(temp);
                temp = NULL;
                printf("\n\t\t\t.------------------------------------------------------------------------------.\n");
                printf("\t\t\t|  Error with adding sanitization record. Please save the data and try again.  |\n");
                printf("\t\t\t.------------------------------------------------------------------------------.");
                return;
            }
            sanArr = temp;
            *maxSize = *index + 10;
        }

        if (*index == 0)   // 
            sanData.sanRecord = 1;
        else
            sanData.sanRecord = sanArr[*index - 1].sanRecord + 1;

        SYSTEMTIME t;
        GetLocalTime(&t);  //get system time & store as the start time of sanitization

        sanData.sanDate.day = t.wDay;
        sanData.sanDate.month = t.wMonth;
        sanData.sanDate.year = t.wYear;
        sanData.starTime.hour = t.wHour;
        sanData.starTime.minit = t.wMinute;
        sanData.starTime.second = t.wSecond;

        printf("\n\n\t TIMES of sanitization (24-hours form)");
        printf("\n\t _____________________________________ ");
        printf("\n\t .--------------.");
        printf("\n\t |   END TIME   |");
        printf("\n\t '--------------'");
        printf("\n\t Hour   (0-23) : ");
        scanf("%d", &sanData.endTime.hour);
        rewind(stdin);
        while (sanData.endTime.hour < 0 || sanData.endTime.hour > 23)
        {
            printf("\n\t      Invalid HOUR. Please enter 0 to 23. ");
            printf("\n\n\t Hour   (0-23) : ");

            scanf("%d", &sanData.endTime.hour);
        }
        printf("\t Minute (0-59) : ");
        scanf("%d", &sanData.endTime.minit);
        rewind(stdin);
        while (sanData.endTime.minit < 0 || sanData.endTime.minit > 59)
        {
            printf("\n\t      Invalid MINUTE. Please enter 0 to 59. ");
            printf("\n\n\t Minute (0-59) : ");
            scanf("%d", &sanData.endTime.minit);
        }
        printf("\t Second (0-59) : ");
        scanf("%d", &sanData.endTime.second);
        rewind(stdin);
        while (sanData.endTime.second < 0 || sanData.endTime.second > 59)
        {
            printf("\n\t      Invalid SECOND. Please enter 0 to 59. ");
            printf("\n\n\t Second (0-59) : ");
            scanf("%d", &sanData.endTime.second);
        }

        printf("\n\n\t Other details ");
        printf("\n\t ________________");
        printf("\n\n\t Venue ID              -> ");
        scanf("%d", &sanData.venueID);
        rewind(stdin);
        printf("\t Sanitize Company name -> ");
        fgets(&sanData.compName, SIZE, stdin);
        rewind(stdin);
        sanData.compName[strcspn(sanData.compName, "\n")] = 0;  //ignore enter, prevent read file error
        printf("\t Person in charge      -> ");
        fgets(&sanData.contactPerson, SIZE, stdin);
        rewind(stdin);
        sanData.contactPerson[strcspn(sanData.contactPerson, "\n")] = 0;
        printf("\t Contact number        -> ");
        scanf("%s", &sanData.contactNo);
        rewind(stdin);
        printf("\t Gender (M or F)       -> ");
        scanf("%c", &sanData.gender);
        rewind(stdin);
        while (toupper(sanData.gender) != 'M' && toupper(sanData.gender) != 'F')
        {
            printf("\n\t      Invalid GENDER. Please enter M for Male, F for female.");
            printf("\n\n\t Gender (M or F)       -> ");
            scanf("%c", &sanData.gender);
            rewind(stdin);
        }

        sanArr[(*index)++] = sanData;  // save useriput into array, add the index (add 1 to the rec no.)

        system("cls");
        printf("\n\n\t          .----------------------------.\n");
        printf("\t          |   Added successful ! ! !   |\n");
        printf("\t          '----------------------------'\n");
        printf("\n\t __________________________________________________\n\n");

        printf("\n\t Add More record ??? (Y or N) ->   ");
        scanf("%c", &ans);
        rewind(stdin);
        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Add More record ??? (Y or N) ->   ");
            scanf("%c", &ans);
            rewind(stdin);
        }
    } while (toupper(ans) == 'Y');
    system("cls");
}

// performs findRecord and displays the result if found 
void searchSanRecord(sanitizationInfo* sanArr, int size, venuePass pass)
{
    int findSanRec; char ans = 'Y';
    do
    {
        printf("\n\n\t Enter sanitization [Record ID] to search: ");
        scanf("%d", &findSanRec);
        rewind(stdin);

        sanitizationInfo temp = findSanRecord(sanArr, size, findSanRec);
        if (temp.sanRecord == -1)
        {
            system("cls");
            printf("\n\n\t    .---------------------------------------------------.\n");
            printf("\t    |   No record found for sanitization record ID.%2d   |\n", findSanRec);
            printf("\t    '---------------------------------------------------'\n\n");
        }
        else
            printSanitizationInfo(temp, findRecord(pass.venArr, *(pass.size), temp.venueID));

        printf("\n\t ___________________________________________________________\n\n");
        printf("\n\t Search for more sanirization record ??? ( Y or N ) ->   ");
        scanf("%c", &ans);
        rewind(stdin);
        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Search for more sanirization record ??? ( Y or N ) ->   ");
            scanf("%c", &ans);
            rewind(stdin);
        }
        system("cls");
    } while (toupper(ans) == 'Y');

    system("cls");
}

// loop through the array and find the record
// returns venueInfo with venueID -1 if not found
sanitizationInfo findSanRecord(sanitizationInfo* sanArr, int size, int findSanRec)
{
    sanitizationInfo temp;
    temp.sanRecord = -1; // value if not found 

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return temp;
    }

    int min = 0, max = size - 1, mid;

    while (min <= max)
    {
        mid = (max + min) / 2;
        if (sanArr[mid].sanRecord == findSanRec)
            return sanArr[mid];

        if (sanArr[mid].sanRecord > findSanRec)
            max = mid - 1;

        if (sanArr[mid].sanRecord < findSanRec)
            min = mid + 1;
    }
    return temp;
}

void modifySanRecord(sanitizationInfo* sanArr, int size, venuePass pass, sanMetaData* md)
{
    int newSanData;
    char ans = 'Y';

    (md->numModify)++;
    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }
    printf("\t  __________________________________________________________________________________\n");
    printf("\t |           |                  |           |                                       |\n");
    printf("\t |    No.    |   Sanitization   |   Venue   |               Name of                 |\n");
    printf("\t |           |    Record ID.    |    ID.    |                Venue                  |\n");
    printf("\t |___________|__________________|___________|_______________________________________|\n");
    for (int num = 0; num < size; num++)
    {
        printf("\t |           |                  |           |                                       |\n");
        printf("\t |    %2d     |        %02d        |    %3d    |       %-30s  |\n", num + 1, sanArr[num].sanRecord, sanArr[num].venueID, findRecord(pass.venArr, *(pass.size), sanArr[num].venueID).venueName);
        printf("\t |___________|__________________|___________|_______________________________________|\n");
    }

    printf("\n\n\t Choose the [No.] you wish to modify ->   ");   //modify based on the number, not sanitize record ID
    scanf("%d", &newSanData);

    while (newSanData > size)
    {
        printf("\n\t\t '``````````````````````````````````````````````````````````````'\n");
        printf("\t\t '       No. not found. Please choose number shown in above.    '\n");
        printf("\t\t '                                                              '\n");
        printf("\t\t ````````````````````````````````````````````````````````````````\n\n");
        printf("\t Choose the [No.] you wish to modify ->   ");
        scanf("%d", &newSanData);
    }

    newSanData--;
    system("cls");

    printf("\n\n\t DATE of sanitization");
    printf("\n\t _____________________");
    printf("\n\n\t Day   (1 - 31)      : ");
    scanf("%d", &sanArr[newSanData].sanDate.day);
    rewind(stdin);
    while (sanArr[newSanData].sanDate.day < 1 || sanArr[newSanData].sanDate.month > 31)
    {
        printf("\n\t      Invalid DAY. Please enter again. ");
        printf("\n\t Day   (1 - 31)      : ");
        scanf("%d", &sanArr[newSanData].sanDate.day);
    }
    printf("\t Month (1 - 12)      : ");
    scanf("%d", &sanArr[newSanData].sanDate.month);
    rewind(stdin);
    while (sanArr[newSanData].sanDate.month < 1 || sanArr[newSanData].sanDate.month > 12)
    {
        printf("\n\t      Invalid MONTH. Please enter again. ");
        printf("\n\n\t Month (1 - 12)      : ");
        scanf("%d", &sanArr[newSanData].sanDate.month);
    }
    printf("\t Year  (1999 - 2021) : ");
    scanf("%d", &sanArr[newSanData].sanDate.year);
    rewind(stdin);
    while (sanArr[newSanData].sanDate.year < 1999 || sanArr[newSanData].sanDate.year > 2021)
    {
        printf("\n\t      Invalid YEAR. Please enter again. ");
        printf("\n\n\t Year  (1999 - 2021) : ");
        scanf("%d", &sanArr[newSanData].sanDate.year);
    }

    printf("\n\n\t TIMES of sanitization");
    printf("\n\t ______________________ ");
    printf("\n\t .--------------.");
    printf("\n\t |  START TIME  |");
    printf("\n\t '--------------'");
    printf("\n\t Hour   (0-23) : ");
    scanf("%d", &sanArr[newSanData].starTime.hour);
    rewind(stdin);
    while (sanArr[newSanData].starTime.hour < 0 || sanArr[newSanData].starTime.hour > 23)
    {
        printf("\n\t      Invalid HOUR. Please enter 0 to 23. ");
        printf("\n\n\t Hour   (0-23) : ");
        scanf("%d", &sanArr[newSanData].starTime.hour);
    }
    printf("\t Minute (0-59) : ");
    scanf("%d", &sanArr[newSanData].starTime.minit);
    rewind(stdin);
    while (sanArr[newSanData].starTime.minit < 0 || sanArr[newSanData].starTime.minit > 59)
    {
        printf("\n\t      Invalid MINUTE. Please enter 0 to 59. ");
        printf("\n\n\t Minute (0-59) : ");
        scanf("%d", &sanArr[newSanData].starTime.minit);
    }
    printf("\t Second (0-59) : ");
    scanf("%d", &sanArr[newSanData].starTime.second);
    rewind(stdin);
    while (sanArr[newSanData].starTime.second < 0 || sanArr[newSanData].starTime.second > 59)
    {
        printf("\n\t      Invalid SECOND. Please enter 0 to 59. ");
        printf("\n\n\t Second (0-59) : ");
        scanf("%d", &sanArr[newSanData].starTime.second);
    }
    printf("\n\t .--------------.");
    printf("\n\t |   END TIME   |");
    printf("\n\t '--------------'");
    printf("\n\t Hour   (0-23) : ");
    scanf("%d", &sanArr[newSanData].endTime.hour);
    rewind(stdin);
    while (sanArr[newSanData].endTime.hour < 0 || sanArr[newSanData].endTime.hour > 23)
    {
        printf("\n\t      Invalid HOUR. Please enter 0 to 23. ");
        printf("\n\n\t Hour   (0-23) : ");
        scanf("%d", &sanArr[newSanData].endTime.hour);
    }
    printf("\t Minute (0-59) : ");
    scanf("%d", &sanArr[newSanData].endTime.minit);
    rewind(stdin);
    while (sanArr[newSanData].endTime.minit < 0 || sanArr[newSanData].endTime.minit > 59)
    {
        printf("\n\t      Invalid MINUTE. Please enter 0 to 59. ");
        printf("\n\n\t Minute (0-59) : ");
        scanf("%d", &sanArr[newSanData].endTime.minit);
    }
    printf("\t Second (0-59) : ");
    scanf("%d", &sanArr[newSanData].endTime.second);
    rewind(stdin);
    while (sanArr[newSanData].endTime.second < 0 || sanArr[newSanData].endTime.second > 59)
    {
        printf("\n\t      Invalid SECOND. Please enter 0 to 59. ");
        printf("\n\n\t Second (0-59) : ");
        scanf("%d", &sanArr[newSanData].endTime.second);
    }
    printf("\n\n\t Other details ");
    printf("\n\t ________________");
    printf("\n\n\t Venue ID              -> ");
    scanf("%d", &sanArr[newSanData].venueID);
    rewind(stdin);
    printf("\t Sanitize Company name -> ");
    fgets(&sanArr[newSanData].compName, SIZE, stdin);
    rewind(stdin);
    sanArr[newSanData].compName[strcspn(sanArr[newSanData].compName, "\n")] = 0;
    printf("\t Person in charge      -> ");
    fgets(&sanArr[newSanData].contactPerson, SIZE, stdin);
    sanArr[newSanData].contactPerson[strcspn(sanArr[newSanData].contactPerson, "\n")] = 0;
    rewind(stdin);
    printf("\t Contact number        -> ");
    scanf("%s", &sanArr[newSanData].contactNo);
    rewind(stdin);
    printf("\t Gender (M or F)       -> ");
    scanf("%c", &sanArr[newSanData].gender);
    rewind(stdin);
    while (toupper(sanArr[newSanData].gender) != 'M' && toupper(sanArr[newSanData].gender) != 'F')
    {
        printf("\n\t      Invalid GENDER. Please enter M for Male, F for female.");
        printf("\n\n\t Gender (M or F)       -> ");
        scanf("%c", &sanArr[newSanData].gender);
        rewind(stdin);
    }

    system("cls");
    printf("\n\n\t\t\t     .---------------------------------------.\n");
    printf("\t\t\t     |   Modify successful ! Data updated.   |\n");
    printf("\t\t\t     '---------------------------------------'\n");
    printf("\n\t\t\t _________________________________________________\n\n\n\n");
    system("pause");
    system("cls");
}

void deleteSanData(sanitizationInfo* sanArr, int* size, sanMetaData* md)
{
    int sanRecNo; char ans;
    do
    {
        printf("\n\n\t Enter sanitization [Record ID] to delete: ");     // based on ID delete the data
        scanf("%d", &sanRecNo);
        rewind(stdin);

        while (sanRecNo > *size)
        {
            system("cls");
            printf("\n\n\t       .-------------------------------.\n");
            printf("\t       |      Unknown Record ID !      |\n");
            printf("\t       '-------------------------------'\n");
            printf("\n\t _____________________________________________\n\n");
            printf("\n\t Please enter again ->   ");
            scanf("%d", &sanRecNo);
            rewind(stdin);
        }
        printf("\n\t _________________________________________________\n");
        printf("\n\n\t Sure to DELETE this sanitization record ? ( Y or N ) ->    ");
        scanf("%c", &ans);
        rewind(stdin);
        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Sure to DELETE this sanitization record ? ( Y or N ) ->   ");
            scanf("%c", &ans);
            rewind(stdin);
        }
        if (toupper(ans) == 'Y')
        {
            for (int i = sanRecNo - 1; i + 1 < *size; i++)
            {
                sanArr[i] = sanArr[i + 1];
            }
            (*size)--;
            (md->numDelete)++;

            system("cls");
            printf("\n\n\t          .-----------------------------.\n");
            printf("\t          |   Delete successful ! ! !   |\n");
            printf("\t          '-----------------------------'\n");
            printf("\n\t _________________________________________________\n\n");
        }

        printf("\n\t Delete more sanitization record ??? ( Y or N ) ->   ");
        scanf("%c", &ans);
        rewind(stdin);
        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No.");
            printf("\n\n\t Delete more sanitization record ??? ( Y or N ) ->  ");
            scanf("%c", &ans);
            rewind(stdin);
        }
        system("cls");

    } while (toupper(ans) == 'Y');


    printf("\n\n\n");
    system("cls");
}

sanitizationInfo* readSanData(int* size)
{
    FILE* readSan;
    readSan = fopen("./Files/San.txt", "r");

    if (readSan == NULL)   //if no such file, write
    {
        readSan = fopen("./Files/San.txt", "w");
        fclose(readSan);
        *size = 0;
        sanitizationInfo* ok = malloc(10 * sizeof(sanitizationInfo)); // allocate extra 10 slots for new data
        return ok;
    }
    int sanCount = 0;
    char sanRec[SIZE];
    while (fgets(sanRec, sizeof(sanRec), readSan) != NULL)
    {
        sanCount++;
    }
    *size = sanCount;
    sanitizationInfo* sanArr = malloc((10 + sanCount) * sizeof(sanitizationInfo)); // allocate extra 10 slots for new data
    rewind(readSan);

    int s = 0;
    while (fscanf(readSan, "%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%d|%[^|]|%[^|]|%[^|]|%c|\n",
        &sanArr[s].sanRecord, &sanArr[s].sanDate.day, &sanArr[s].sanDate.month, &sanArr[s].sanDate.year,
        &sanArr[s].starTime.hour, &sanArr[s].starTime.minit, &sanArr[s].starTime.second,
        &sanArr[s].endTime.hour, &sanArr[s].endTime.minit, &sanArr[s].endTime.second,
        &sanArr[s].venueID, &sanArr[s].compName, &sanArr[s].contactPerson, &sanArr[s].contactNo, &sanArr[s].gender) != EOF)
    {
        s++;
    }

    fclose(readSan);
    return sanArr;
}

void writeSanData(sanitizationInfo* sanArr, int size)
{
    FILE* writeSan;
    writeSan = fopen("./Files/San.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(writeSan, "%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%d|%s|%s|%s|%c|\n", sanArr[i].sanRecord, sanArr[i].sanDate.day, sanArr[i].sanDate.month, sanArr[i].sanDate.year, sanArr[i].starTime.hour, sanArr[i].starTime.minit, sanArr[i].starTime.second, sanArr[i].endTime.hour, sanArr[i].endTime.minit, sanArr[i].endTime.second, sanArr[i].venueID, sanArr[i].compName, sanArr[i].contactPerson, sanArr[i].contactNo, toupper(sanArr[i].gender));
    }
    fclose(writeSan);
}

void reportSan(sanMetaData* md)
{
    printf("\n\n\t\t\t _____________________________________________________\n");
    printf("\t\t\t|                                             |       |\n");
    printf("\t\t\t|   Number of sanitization records added      |  %2d   |\n", (md->numAdd));
    printf("\t\t\t|_____________________________________________|_______|\n");
    printf("\t\t\t|                                             |       |\n");
    printf("\t\t\t|   Number of sanitization records modified   |  %2d   |\n", (md->numModify));
    printf("\t\t\t|_____________________________________________|_______|\n");
    printf("\t\t\t|                                             |       |\n");
    printf("\t\t\t|   Number of sanitization records deleted    |  %2d   |\n", (md->numDelete));
    printf("\t\t\t|_____________________________________________|_______|\n");
    system("pause");
    system("cls");
}

void sanitization(sanitizationInfo* sanArr, int* size, int* maxSize, venuePass venPass, sanMetaData* md)
{
    int choice = 0, notDigit = 0;

    do
    {
        printf("\n\t\t\t      +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t      !      Sanitization Menu      !\n");
        printf("\t\t\t      +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
        printf("\t\t\t.-----------------------------------------.\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [1]  Show all records            |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [2]  Add new record              |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [3]  Search records              |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [4]  Modify record               |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [5]  Delete Record               |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [6]  Report actions done         |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|        [7]  Back to Main Menu           |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t|                                         |\n");
        printf("\t\t\t'-----------------------------------------'\n");
        printf("\n\t\t\t Please enter a number ->  ");
        scanf("%d", &choice);
        rewind(stdin);

        switch (choice)
        {
        case 1: system("cls");
            showSanRecord(sanArr, *(size), venPass); break;
        case 2: system("cls");
            addSanRecord(sanArr, size, maxSize, md); break;
        case 3: system("cls");
            searchSanRecord(sanArr, *(size), venPass); break;
        case 4: system("cls");
            modifySanRecord(sanArr, *(size), venPass, md); break;
        case 5: system("cls");
            deleteSanData(sanArr, (size), md); break;
        case 6: system("cls");
            reportSan(md); break;
        case 7: printf("\n\n\n"); system("pause"); system("cls");
            printf("\n\n\t\t_____________________________________\n\n");
            printf("\t\t      Returning to main menu...\n");
            printf("\t\t_____________________________________\n\n\n\n\n");
            system("pause"); system("cls"); return;
        default:
            system("cls");
            printf("\n\n\t\t======================================================\n\n");
            printf("\t\tInvalid choice! Please enter the NUMBER shown in menu.\n\n");
            printf("\t\t======================================================\n\n\n\n");
            system("pause"); system("cls");
        }
    } while (choice != 7);

}