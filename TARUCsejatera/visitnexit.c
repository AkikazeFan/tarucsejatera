#include "visitnexit.h"

void printVisitExitInfo(visitExitInfo vne, venueInfo venueTemp)
{
    printf("\n\n\t .---------------------------------------------------------.\n");
    printf("\t |                                                         |\n");
    printf("\t |   Visit date : %02d/%02d/%02d    Visit time : %02d:%02d:%02d      |\n", vneEnterDate.day, vneEnterDate.month, vneEnterDate.year, vneEnterTime.hour, vneEnterTime.minit, vneEnterTime.second);
    printf("\t |   Exit date  : %02d/%02d/%02d    Exit time  : %02d:%02d:%02d      |\n", vneExitDate.day, vneExitDate.month, vneExitDate.year, vneExitTime.hour, vneExitTime.minit, vneExitTime.second);
    printf("\t |                                                         |\n");
    printf("\t |   Venue ID   : %3d                                      |\n", vne.venueID);
    if (vne.venueID == -1)
        printf("\t |  Warning: Venue record not entered.                         |\n");
    else
        printf("\t |   Venue Name : %-25s                |\n", venueTemp.venueName);
    printf("\t |                                                         |\n");
    printf("\t |   Visitor IC  : %-12s                            |\n", vne.visitorIC);
    printf("\t |   Temperature : %02.2f                                   |\n", vne.temp);
    printf("\t |   Reason of visit  : %-15s                    |\n", vne.visitReason);
    printf("\t |   Health condition : %-17s                  |\n", vne.healthCon);
    printf("\t |   Number of person with visitor :%2d                     |\n", vne.noPerson);
    printf("\t |                                                         |\n");
    printf("\t '---------------------------------------------------------'\n\n\n");

}

// adds a new visit/exit record
// returns the visit/exit ID
int addVisitExitRecord(vnePass* vnePass, char* visitorIC, int temperature, vneMetaData* md)
{
    (md->numAdd)++;

    if (*vnePass->size == *vnePass->maxSize) // resize array if needed
    {
        void* temp = realloc(vnePass->vneArr, (*vnePass->size + 10) * sizeof(visitExitInfo));
        if (!temp)
        {
            free(temp);
            temp = NULL;
            printf("\n\t\t\t.------------------------------------------------------------------------------.\n");
            printf("\t\t\t|  Error with adding visit & exit record. Please save the data and try again.  |\n");
            printf("\t\t\t.------------------------------------------------------------------------------.");
            return;
        }
        vnePass->vneArr = temp;
        *vnePass->maxSize = *vnePass->size + 10;
    }

    char ans = 'Y';
    visitExitInfo vneData;

    if (*vnePass->size == 0)
        vneData.vneRecord = 1;
    else
        vneData.vneRecord = vnePass->vneArr[*vnePass->size - 1].vneRecord + 1;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    vneData.enterDate.day = tm.tm_mday;
    vneData.enterDate.month = tm.tm_mon + 1;
    vneData.enterDate.year = tm.tm_year + 1900;
    vneData.enterTime.hour = tm.tm_hour;
    vneData.enterTime.minit = tm.tm_min;
    vneData.enterTime.second = tm.tm_sec;

    printf("\n\t ENTER year  of exit  (1-31) : ");
    scanf("%d", &vneData.exitDate.year); rewind(stdin);
    while (vneData.exitDate.year < 0 || vneData.exitDate.year > 2021)
    {
        printf("\n\t      IMPROPER year. Re-enter year of exit  : ");
        scanf("%d", &vneData.exitDate.year); rewind(stdin);
    }
    printf("\t ENTER month  of exit (1-31) : ");
    scanf("%d", &vneData.exitDate.month); rewind(stdin);
    while (vneData.exitDate.month < 1 || vneData.exitDate.month > 12)
    {
        printf("\n\t      IMPROPER month. Re-enter month of exit  : ");
        scanf("%d", &vneData.exitDate.month); rewind(stdin);
    }
    printf("\t ENTER date  of exit  (1-31) : ");
    scanf("%d", &vneData.exitDate.day); rewind(stdin);
    while (vneData.exitDate.day < 1 || vneData.exitDate.day > 31)
    {
        printf("\n\t      IMPROPER date. Re-enter date of exit : ");
        scanf("%d", &vneData.exitDate.day); rewind(stdin);
    }
    printf("\n\t ________________________________________________");


    printf("\n\n\t ENTER time of exit in hour    (0-23) : ");
    scanf("%d", &vneData.exitTime.hour); rewind(stdin);

    while (vneData.exitTime.hour < 1 && vneData.exitTime.hour > 23)
    {
        printf("\n\t      IMPROPER hour. Re-enter time of exit in hour : ");
        scanf("%d", &vneData.exitTime.hour); rewind(stdin);
    }

    printf("\t ENTER time of exit in minutes (0-59) : ");
    scanf("%d", &vneData.exitTime.minit); rewind(stdin);

    while (vneData.exitTime.minit < 1 && vneData.exitTime.minit > 59)
    {
        printf("\n\t      IMPROPER minutes. Re-enter time of exit in minutes : ");
        scanf("%d", &vneData.exitTime.minit); rewind(stdin);
    }


    printf("\t ENTER time of exit in seconds (0-59) : ");
    scanf("%d", &vneData.exitTime.second); rewind(stdin);

    while (vneData.exitTime.second < 1 && vneData.exitTime.second > 59)
    {
        printf("\n\t      IMPROPER seconds. Re-enter time of exit in seconds : ");
        scanf("%d", &vneData.exitTime.second); rewind(stdin);
    }
    printf("\n\t ________________________________________________");

    vneData.temp = temperature;
    strcpy(vneData.visitorIC, visitorIC);

    printf("\n\n\t ENTER your reason of visit  : ");
    fgets(&vneData.visitReason, BUFFER_SIZE, stdin); rewind(stdin);
    vneData.visitReason[strcspn(vneData.visitReason, "\n")] = 0;

    printf("\t ENTER your health condition : ");
    fgets(&vneData.healthCon, BUFFER_SIZE, stdin); rewind(stdin);
    vneData.healthCon[strcspn(vneData.healthCon, "\n")] = 0;

    printf("\t ENTER the number of person you visited with : ");
    scanf("%d", &vneData.noPerson); rewind(stdin);

    while (vneData.noPerson < 0)
    {
        printf("\n\t      IMPROPER number. Re-enter the number of person you visited with : ");
        scanf("%d", &vneData.noPerson); rewind(stdin);
    }
    printf("\n\t ________________________________________________");

    printf("\n\n\t ENTER the venue ID : ");
    scanf("%d", &vneData.venueID); rewind(stdin);

    vnePass->vneArr[(*vnePass->size)++] = vneData;

    return vneData.vneRecord;
    system("pause");
    system("cls");
}

void showVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass)
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
        printVisitExitInfo(vneArr[index], findRecord(pass.venArr, *(pass.size), vneArr[index].venueID));

        index++;
    }
    system("pause");
    system("cls");
}

// loop through the array and find the record
// returns visitExitInfo with vneRecord -1 if not found
visitExitInfo findVisitExitRecord(visitExitInfo* vneArr, int size, int findVnERec)
{
    visitExitInfo temp;
    temp.vneRecord = -1; // value if not found  (not sure is visitor or venue)

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
        if (vneArr[mid].vneRecord == findVnERec)
            return vneArr[mid];

        if (vneArr[mid].vneRecord > findVnERec)
            max = mid - 1;

        if (vneArr[mid].vneRecord < findVnERec)
            min = mid + 1;
    }
    return temp;
}

// performs findRecord and displays the result if found 
void searchVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass)
{
    int findVnERec;
    char yesNo;
    do
    {
        printf("\n\n\t   Enter [Record ID] to search: ");
        scanf("%d", &findVnERec); rewind(stdin);

        visitExitInfo temp = findVisitExitRecord(vneArr, size, findVnERec);

        if (temp.vneRecord == -1)
        {
            system("cls");
            printf("\n\n\t    .---------------------------------------------------.\n");
            printf("\t    |   No record found for visit & exit record no.%2d   |\n", findVnERec);
            printf("\t    '---------------------------------------------------'\n\n");
        }
        else
            printVisitExitInfo(temp, findRecord(pass.venArr, *(pass.size), temp.venueID));

        printf("\n\t ___________________________________________________________\n\n");
        printf("\n\t Search for more exit & vist record ? ( Y or N ) :  ");
        scanf("%c", &yesNo);
        rewind(stdin);
        while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N')
        {
            printf("\n\t      Invalid input. Please enter Y for Yes, N for No :  ");
            scanf("%c", &yesNo);
            rewind(stdin);
        }
        system("cls");
    } while (toupper(yesNo) == 'Y');

    system("cls");
}

void modifyVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass, vneMetaData* md)
{
    (md->numModify)++;
    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }
    int usrInput, yesNo = 'Y';

    printf("\t  __________________________________________________________________________________\n");
    printf("\t |           |                  |           |                                       |\n");
    printf("\t |    No.    |   Visit & Exit   |   Venue   |               Name of                 |\n");
    printf("\t |           |    Record ID.    |    ID.    |                Venue                  |\n");
    printf("\t |___________|__________________|___________|_______________________________________|\n");
    for (int index = 0; index < size; index++)
    {
        printf("\t |           |                  |           |                                       |\n");
        printf("\t |    %2d     |        %02d        |    %3d    |       %-30s  |\n", index + 1, vneArr[index].vneRecord, vneArr[index].venueID, findRecord(pass.venArr, *(pass.size), vneArr[index].venueID).venueName);
        printf("\t |___________|__________________|___________|_______________________________________|\n");
    }

    printf("\n\t Select [No.] to modify :  ");
    scanf("%d", &usrInput);
    rewind(stdin);

    while (usrInput > size)
    {
        printf("\n\t\t '``````````````````````````````````````````````````````````````'\n");
        printf("\t\t '       No. not found. Please choose number shown in above.    '\n");
        printf("\t\t '                                                              '\n");
        printf("\t\t ````````````````````````````````````````````````````````````````\n\n");
        printf("\t Select record number to modify : ");
        scanf("%d", &usrInput);
        rewind(stdin);
    }

    usrInput--;
    system("cls");
    printf("\n\n\t ENTER year of visit (e.g. 2021) : ");
    scanf("%d", &vneArr[usrInput].enterDate.year);
    rewind(stdin);

    while (vneArr[usrInput].enterDate.year < 0 || vneArr[usrInput].enterDate.year > 2021)
    {
        printf("\n\t      IMPROPER YEAR. Re-enter year of visit : ");
        scanf("%d", &vneArr[usrInput].enterDate.year);
        rewind(stdin);
    }


    printf("\t ENTER month of visit (1-12) : ");
    scanf("%d", &vneArr[usrInput].enterDate.month);
    rewind(stdin);

    while (vneArr[usrInput].enterDate.month < 1 || vneArr[usrInput].enterDate.month > 12)
    {
        printf("\n\t      IMPROPER MONTH. Re-enter month of visit : ");
        scanf("%d", &vneArr[usrInput].enterDate.month);
        rewind(stdin);
    }


    printf("\t ENTER date of visit (1-31) : ");
    scanf("%d", &vneArr[usrInput].enterDate.day);
    rewind(stdin);

    while (vneArr[usrInput].enterDate.day < 1 || vneArr[usrInput].enterDate.day > 31)
    {
        printf("\n      IMPROPER date. Re-enter date of visit : ");
        scanf("%d", &vneArr[usrInput].enterDate.day);
        rewind(stdin);
    }
    printf("\n\t ________________________________________________");


    printf("\n\n\t ENTER time of visit in hour (0-23) : ");
    scanf("%d", &vneArr[usrInput].enterTime.hour);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.hour < 0 || vneArr[usrInput].enterTime.hour > 23)
    {
        printf("\n\t      IMPROPER hour. Re-enter time of visit in hour : ");
        scanf("%d", &vneArr[usrInput].enterTime.hour);
        rewind(stdin);
    }


    printf("\t ENTER time of visit in minutes (0-59) : ");
    scanf("%d", &vneArr[usrInput].enterTime.minit);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.minit < 0 || vneArr[usrInput].enterTime.minit > 59)
    {
        printf("\n\t      IMPROPER minutes. Re-enter time of visit in minutes : ");
        scanf("%d", &vneArr[usrInput].enterTime.minit);
        rewind(stdin);
    }


    printf("\t ENTER time of visit in seconds (0-59) : ");
    scanf("%d", &vneArr[usrInput].enterTime.second);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.second < 0 || vneArr[usrInput].enterTime.second > 59)
    {
        printf("\n\t      IMPROPER second. Re-enter time of visit in seconds : ");
        scanf("%d", &vneArr[usrInput].enterTime.second);
        rewind(stdin);
    }
    printf("\n\t ________________________________________________");

    printf("\n\n\t ENTER year of exit : ");
    scanf("%d", &vneArr[usrInput].exitDate.year);
    rewind(stdin);

    while (vneArr[usrInput].exitDate.year < 0 || vneArr[usrInput].exitDate.year > 2021)
    {
        printf("\n\t      IMPROPER year. Re-enter year of exit  : ");
        scanf("%d", &vneArr[usrInput].exitDate.year);
        rewind(stdin);
    }


    printf("\t ENTER month of exit  (1-12) : ");
    scanf("%d", &vneArr[usrInput].exitDate.month);
    rewind(stdin);

    while (vneArr[usrInput].exitDate.month < 1 || vneArr[usrInput].exitDate.month > 12)
    {
        printf("\n\t      IMPROPER month. Re-enter month of exit  : ");
        scanf("%d", &vneArr[usrInput].exitDate.month);
        rewind(stdin);
    }


    printf("\t ENTER date of exit (1-31) : ");
    scanf("%d", &vneArr[usrInput].exitDate.day);
    rewind(stdin);

    while (vneArr[usrInput].exitDate.day < 1 || vneArr[usrInput].exitDate.day > 31)
    {
        printf("\n\t      IMPROPER date. Re-enter date of exit : ");
        scanf("%d", &vneArr[usrInput].exitDate.day);
        rewind(stdin);
    }
    printf("\n\t ________________________________________________");

    printf("\n\n\t ENTER time of exit in hour (0-23) : ");
    scanf("%d", &vneArr[usrInput].exitTime.hour);
    rewind(stdin);

    while (vneArr[usrInput].exitTime.hour < 0 || vneArr[usrInput].exitTime.hour > 23)
    {
        printf("\n\t      IMPROPER hour. Re-enter time of exit in hour : ");
        scanf("%d", &vneArr[usrInput].exitTime.hour);
        rewind(stdin);
    }


    printf("\t ENTER time of exit in minutes (0-59) : ");
    scanf("%d", &vneArr[usrInput].exitTime.minit);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.minit < 0 || vneArr[usrInput].enterTime.minit > 59)
    {
        printf("\n\t      IMPROPER minutes. Re-enter time of exit in minutes : ");
        scanf("%d", &vneArr[usrInput].exitTime.minit);
        rewind(stdin);
    }


    printf("\t ENTER time of exit in seconds (0-59) : ");
    scanf("%d", &vneArr[usrInput].exitTime.second);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.second < 0 || vneArr[usrInput].enterTime.second > 59)
    {
        printf("\n\t      IMPROPER seconds. Re-enter time of exit in seconds : ");
        scanf("%d", &vneArr[usrInput].exitTime.second);
        rewind(stdin);
    }
    printf("\n\t ________________________________________________");

    printf("\n\n\t ENTER visitor IC : ");
    scanf("%s", &vneArr[usrInput].visitorIC);
    rewind(stdin);

    printf("\t ENTER your temperature : ");
    scanf("%f", &vneArr[usrInput].temp);
    rewind(stdin);

    while (vneArr[usrInput].temp < 0)
    {
        printf("\n\t      IMPROPER temperature. Re-enter temperature : ");
        scanf("%f", &vneArr[usrInput].temp);
        rewind(stdin);
    }

    printf("\t ENTER your reason of visit : ");
    fgets(&vneArr[usrInput].visitReason, BUFFER_SIZE, stdin); rewind(stdin);
    vneArr[usrInput].visitReason[strcspn(vneArr[usrInput].visitReason, "\n")] = 0;


    printf("\t ENTER your health condition : ");
    fgets(&vneArr[usrInput].healthCon, BUFFER_SIZE, stdin); rewind(stdin);
    vneArr[usrInput].healthCon[strcspn(vneArr[usrInput].healthCon, "\n")] = 0;

    printf("\t ENTER the number of person you visited with : ");
    scanf("%d", &vneArr[usrInput].noPerson); rewind(stdin);
    while (vneArr[usrInput].noPerson < 0)
    {
        printf("\n\t      IMPROPER number. Re-enter the number of person you visited with : ");
        scanf("%d", &vneArr[usrInput].noPerson);  rewind(stdin);
    }

    system("cls");
    printf("\n\n\t\t\t     .---------------------------------------.\n");
    printf("\t\t\t     |   Modify successful ! Data updated.   |\n");
    printf("\t\t\t     '---------------------------------------'\n");
    printf("\n\t\t\t _________________________________________________\n\n\n\n");
    system("pause");
    system("cls");
}

visitExitInfo* readVisitExitData(int* size)
{
    FILE* fp;
    fp = fopen("./Files/Vne.txt", "r");

    if (fp == NULL) {
        fp = fopen("./Files/Vne.txt", "w");
        fclose(fp);
        *size = 0;
        visitExitInfo* ok = malloc(10 * sizeof(visitExitInfo)); // allocate extra 10 slots for new data
        return ok;
    }

    int count = 0;
    char temp[BUFFER_SIZE];
    while (fgets(temp, sizeof(temp), fp) != NULL)   //temporary hold data
    {
        count++;
    };
    *size = count;
    visitExitInfo* vneArr = malloc((10 + count) * sizeof(visitExitInfo)); // allocate extra 10 slots for new data
    rewind(fp);
    int i = 0;
    while (fscanf(fp, "%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%[^|]|%d|%f|%[^|]|%[^|]|%d\n", &vneArr[i].vneRecord, &vneArr[i].enterDate.year, &vneArr[i].enterDate.month, &vneArr[i].enterDate.day, &vneArr[i].enterTime.hour, &vneArr[i].enterTime.minit, &vneArr[i].enterTime.second, &vneArr[i].exitDate.year, &vneArr[i].exitDate.month, &vneArr[i].exitDate.day, &vneArr[i].exitTime.hour, &vneArr[i].exitTime.minit, &vneArr[i].exitTime.second, &vneArr[i].visitorIC, &vneArr[i].venueID, &vneArr[i].temp, &vneArr[i].visitReason, &vneArr[i].healthCon, &vneArr[i].noPerson) != EOF)
    {
        i++;
    }
    fclose(fp);
    return vneArr;
}

void writeVisitExitData(visitExitInfo* vneArr, int size)
{
    FILE* fp;
    fp = fopen("./Files/Vne.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%s|%d|%f|%s|%s|%d\n",
            vneArr[i].vneRecord, vneArr[i].enterDate.year, vneArr[i].enterDate.month, vneArr[i].enterDate.day,
            vneArr[i].enterTime.hour, vneArr[i].enterTime.minit, vneArr[i].enterTime.second,
            vneArr[i].exitDate.year, vneArr[i].exitDate.month, vneArr[i].exitDate.day,
            vneArr[i].exitTime.hour, vneArr[i].exitTime.minit, vneArr[i].exitTime.second,
            vneArr[i].visitorIC, vneArr[i].venueID, vneArr[i].temp, vneArr[i].visitReason,
            vneArr[i].healthCon, vneArr[i].noPerson);
    }
    fclose(fp);
}

void deleteVisitExitData(visitExitInfo* vneArr, int* size, vneMetaData* md) //(not sure what to del)
{
    int vneRecord; char yesNo;
    do {

        printf("\n\n\t ENTER visit & exit [Record no.] to delete: ");
        scanf("%d", &vneRecord); rewind(stdin);
        while (vneRecord > *size)
        {
            system("cls");
            printf("\n\n\t       .--------------------------------.\n");
            printf("\t       |      Unknown record no. !      |\n");
            printf("\t       '--------------------------------'\n");
            printf("\n\t _____________________________________________\n\n");
            printf("\n\t Please enter again :  ");
            scanf("%d", &vneRecord); rewind(stdin);
        }
        printf("\n\t _________________________________________________\n");
        printf("\n\n\t Do you want to DELETE this visit & exit record ? ( Y or N ) :  ");
        scanf("%c", &yesNo);
        rewind(stdin);
        while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N')
        {
            printf("\n\t      IMPROPER input. Please enter Y or N :  ");
            scanf("%c", &yesNo);
            rewind(stdin);
        }
        if (toupper(yesNo) == 'Y')
        {
            for (int i = vneRecord - 1; i + 1 < *size; i++)
            {
                vneArr[i] = vneArr[i + 1];
            }
            (*size)--;
            (md->numDelete)++;

            system("cls");
            printf("\n\n\t          .-----------------------------.\n");
            printf("\t          |   Delete successful ! ! !   |\n");
            printf("\t          '-----------------------------'\n");
            printf("\n\t _________________________________________________\n\n");
        }
        printf("\n\t Do you want to delete more visit & exit record ? ( Y or N ) :  ");
        scanf("%c", &yesNo);
        rewind(stdin);
        while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N')
        {
            printf("\n\t      IMPROPER input. Please enter Y or N :  ");
            scanf("%c", &yesNo);
            rewind(stdin);
        }
        system("cls");

    } while (toupper(yesNo) == 'Y');

    printf("\n\n\n");
    system("pause");
    system("cls");

}

void reportVne(vneMetaData* md)
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

    system("pause");
    system("cls");
}

void visitnexit(vnePass vnePass, venuePass venPass, vneMetaData* md)
{
    int option = 0;

    do {
        printf("\n\n\n");
        printf("\n\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t     !     Visits & Exits Menu     !\n");
        printf("\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
        printf("\t\t\t.---------------------------------------.\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [1]  Search records              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [2]  Modify record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [3]  Show all records            |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [4]  Delete record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [5]  Report actions done         |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [6]  Return to Main Menu         |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t'---------------------------------------'\n");
        printf("\n\t\t\t Enter your choice :  ");
        scanf("%d", &option);

        if (option == 1)
        {
            system("cls");
            searchVisitExitRecord(vnePass.vneArr, *(vnePass.size), venPass);
        }
        else if (option == 2)
        {
            system("cls");
            modifyVisitExitRecord(vnePass.vneArr, *(vnePass.size), venPass, md);
        }
        else if (option == 3)
        {
            system("cls");
            showVisitExitRecord(vnePass.vneArr, *(vnePass.size), venPass);
        }
        else if (option == 4)
        {
            system("cls");
            deleteVisitExitData(vnePass.vneArr, vnePass.size, md);
        }
        else if (option == 5)
        {
            system("cls");
            reportVne(md);
        }
        else if (option == 6)
        {
            printf("\n\n\n");
            system("pause");
            system("cls");
            printf("\n\n\t\t_____________________________________\n\n");
            printf("\t\t      Returning to main menu...\n");
            printf("\t\t_____________________________________\n\n\n\n\n");
            system("pause");
            system("cls");
            return;
        }
        else
        {
            system("cls");
            printf("\n\n\t\t==============================================================\n\n");
            printf("\t\t    Invalid choice! Please enter the NUMBER shown in menu.    \n\n");
            printf("\t\t==============================================================\n\n\n\n");
            system("pause");
            system("cls");
        }
    } while (option != 7);
}