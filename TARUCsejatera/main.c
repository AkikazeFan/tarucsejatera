#pragma once
#include <stdio.h>
#include <sys/stat.h>
#include "venue.h"
#include "staff.h"
#include "sanitization.h"
#include "visitor.h"
#include "visitnexit.h"

void splashScreen()
{
    // end init //
    printf("\n\t.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.\n");
    printf("\t!\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t!\n");
    printf("\t.\t                                ______                                      _____          _____                                . \n");
    printf("\t!\tRRRRRRRRRRRRRRRRRRRRR\\         /      \\             /RRRRRRRRRRRRRR        |    |\\        |    |\\       RRRRRRRRRRRRRR          !\n");
    printf("\t.\tRRRRRRRRRRRRRRRRRRRRR \\       /   __   \\           / RRRRRRRRRRRRRRRR      |    ||        |    ||     /RRRRRRRRRRRRRRRRR        .\n");
    printf("\t!\t\\______RRRRRR  ______\\|      /   /  \\   \\          | RRRRR      RRRRRR     |    ||        |    ||    /RRRRRR       RRRRRR       !\n");
    printf("\t.\t       RRRRRR |             /   /    \\   \\         | RRRRR      RRRRRR     |    ||        |    ||   | RRRRRR       RRRRRR       .\n");
    printf("\t!\t       RRRRRR |            /   /______\\   \\        | RRRRRRRRRRRRRRRR      |    ||        |    ||   | RRRRRR                    !\n");
    printf("\t.\t       RRRRRR |           /                \\       | RRRRRRRRRRRRRRR       |    ||        |    ||   | RRRRRR                    .\n");
    printf("\t!\t       RRRRRR |          /                  \\      | RRRRRRR  RRRRRR       |    ||        |    ||   | RRRRRR                    !\n");
    printf("\t.\t       RRRRRR |         /     __________     \\     | RRRRRRR\\  RRRRRR      |    ||        |    ||   | RRRRRR       RRRRRR       .\n");
    printf("\t!\t       RRRRRR |        /     / ________ \\     \\    | RRRRRRR \\  RRRRRR     |    \\|________/    ||   | RRRRRR      RRRRRR        !\n");
    printf("\t.\t       RRRRRR |       /     / /        \\ \\     \\   | RRRRRRR  \\  RRRRRR    \\                   ||   |  RRRRRRRRRRRRRRRR         .\n");
    printf("\t!\t       RRRRRR |      /_____/ /          \\ \\_____\\  | RRRRRRR   \\  RRRRRR    \\_________________/ |    \\  RRRRRRRRRRRRRR          !\n");
    printf("\t.\t       \\_____\\|      \\_____\\/            \\/_____/  |/_____/     \\/_____/     \\________________\\/      \\/____________/           .\n");
    printf("\t!\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t!\n");
    printf("\t.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t.\n");
    printf("\t!\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t!\n");
    printf("\t.\t        ________    ________         __    ________    __      __    __________    ________    _______      ________            .\n");
    printf("\t!\t      /|   _____| /|   _____|      /|  | /|   __   | /|  |   /|  | /|___    ___| /|   _____| /|   __  \\   /|   __   |           !\n");
    printf("\t.\t      ||  |____/  ||  |____/       ||  | ||  |_/|  | ||  |   ||  | |/__/|  |__/  ||  |____/  ||  |_/|  |  ||  |_/|  |           .\n");
    printf("\t!\t      ||  |_____  ||  |___         ||  | ||  |_|/  | ||  |___||  |     ||  |     ||  |___    ||  |_|/  /  ||  |_|/  |           !\n");
    printf("\t.\t      |/_____   | ||   ___|    __  ||  | ||   __   | ||   ____   |     ||  |     ||   ___|   ||   __   \\  ||   __   |           .\n");
    printf("\t!\t        _____|  | ||  |_____  /| |_||  | ||  |_/|  | ||  |___/|  |     ||  |     ||  |_____  ||  |__/|  | ||  |_/|  |           !\n");
    printf("\t.\t      /|________| ||________| ||_______| ||__| ||__| ||__|   ||__|     ||__|     ||________| ||__|  ||__| ||__| ||__|           .\n");
    printf("\t!\t      |_________/ |/________/ |/_______/ |/__/ |/__/ |/__/   /___/     |/__/     |/________/ |/__/  |/__/ |/__/ |/__/           !\n");
    printf("\t.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t.\n");
    printf("\t!\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t!\n");
    printf("\t.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.\n\n\n\n\n\n");
    system("pause");
    system("cls");
}

void main()
{
    // init //

    // creates a Files folder if doesn't exist
    mkdir(".\/Files\/");

    int initValueZero = 0;

    int vneSize = 0;
    visitExitInfo* vneArr = readVisitExitData(&vneSize);
    int maxVNESize = vneSize + 10;

    int visitorSize = 0;
    visitorInfo* visitorArr = readVisitorData(&visitorSize);
    //int maxVisitorSize = visitorSize + 10;
    int maxVisitorSize = visitorSize;

    int venueSize = 0;
    venueInfo* venueArr = readData(&venueSize);
    int maxVenueSize = venueSize + 10;

    int staffSize = 0;
    staffInfo* staffArr = readStaffData(&staffSize);
    int maxStaffSize = staffSize + 10;

    int sanSize = 0;
    sanitizationInfo* sanArr = readSanData(&sanSize);
    int maxSanSize = sanSize + 10;

    // for linking of data
    venuePass venPass = { venueArr, &venueSize, &maxVenueSize };
    vnePass vnePass = { vneArr, &vneSize, &maxVNESize };
    visitorPass visPass = { visitorArr, &visitorSize, &maxVisitorSize };
    staffPass staffPass = { staffArr, &staffSize, &maxStaffSize };

    // for meta data
    sanMetaData sanMD = { 0, 0, 0 };
    vneMetaData vneMD = { 0, 0, 0 };
    venueMetaData venueMD = { 0, 0, 0 };
    staffMetaData staffMD = { 0, 0, 0 };

    splashScreen();

    int usrInput = 0;
    do
    {
        printf("\n\n");
        printf("\t\t\t               ___________\n\t\t\t\t      /           \\\n");
        printf("\t\t\t\t     /  Main Menu  \\      \n");
        printf("\t\t\t ___________/_______________\\___________\n");
        printf("\t\t\t|   | \t\t\t\t\t|\n");
        printf("\t\t\t| 1 | \tVenue module                    |\n\t\t\t|___|___________________________________|\n");
        printf("\t\t\t|   | \t\t\t\t\t|\n");
        printf("\t\t\t| 2 | \tVisitors module                 |\n\t\t\t|___|___________________________________|\n");
        printf("\t\t\t|   | \t\t\t\t\t|\n");
        printf("\t\t\t| 3 | \tVisits & exits module           |\n\t\t\t|___|___________________________________|\n");
        printf("\t\t\t|   | \t\t\t\t\t|\n");
        printf("\t\t\t| 4 | \tStaffs module                   |\n\t\t\t|___|___________________________________|\n");
        printf("\t\t\t|   | \t\t\t\t\t|\n");
        printf("\t\t\t| 5 | \tSanitization module             |\n\t\t\t|___|___________________________________|\n");
        printf("\t\t\t|   | \t\t\t\t\t|\n");
        printf("\t\t\t| 6 | \tSave and exit                   |\n\t\t\t|___|___________________________________|\n");
        printf("\n\t\t\t Enter your choice: ");
        scanf("%d", &usrInput);
        rewind(stdin);

        if (usrInput == 1)
        {
            system("cls");
            venue(venPass, &venueMD);
        }
        else if (usrInput == 2)
        {
            system("cls");
            visitor(visPass, venPass, vnePass, staffPass, &vneMD);
        }
        else if (usrInput == 3)
        {
            system("cls");
            visitnexit(vnePass, venPass, &vneMD);
        }
        else if (usrInput == 4)
        {
            system("cls");
            staff(staffArr, &staffSize, &maxStaffSize, &staffMD);
        }
        else if (usrInput == 5)
        {
            system("cls");
            sanitization(sanArr, &sanSize, &maxSanSize, venPass, &sanMD);
        }
        else if (usrInput == 6)
        {
            // save data to file 
            writeData(venueArr, venueSize);
            writeStaffData(staffArr, staffSize);
            writeSanData(sanArr, sanSize);
            writeVisitorData(visitorArr, visitorSize);
            writeVisitExitData(vneArr, vneSize);

            // free memory 
            free(vneArr);
            vneArr = NULL;

            free(venueArr);
            venueArr = NULL;

            free(staffArr);
            staffArr = NULL;

            free(visitorArr);
            visitorArr = NULL;

            free(sanArr);
            sanArr = NULL;

            exit(0);
        }
        else
            printf("\t\t\t Invalid choice !!!  ");

    } while (usrInput != 6);
}
