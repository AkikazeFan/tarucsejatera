#pragma once
#include <stdio.h>  //aki binary
#include <stdlib.h>  
#pragma warning (disable:4996)
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <time.h>
#include "visitnexit.h"
#include "staff.h"
#define BUFFER_SIZE 256 //declare size, standardised the string size, prevent mistake(ex:10 typo 100)
#define xd_ visitor.visitDate //new add
#define xD_ visitor.visitTime //new add

typedef struct
{
    char icNum[13];
    char visitorName[BUFFER_SIZE];
    char gender;
    int category;
    char phoneNo[BUFFER_SIZE];
    date visitDate;
    times visitTime;
    float temp;
    int staffID;
    int visitID; // last visit and exit id
}visitorInfo;

typedef struct
{
    visitorInfo* visitorArr;
    int* size;
    int* maxSize;
}visitorPass;

void addVisitorRecord(visitorInfo* visitorArr, int* index, int* maxSize);
void printVisitorInfo(visitorInfo visitor, venueInfo venInfo, staffInfo staffInfo);
void showVisitorRecord(visitorInfo* visitorArr, int size, venuePass venPass, vnePass vnePass, staffPass staffPass);
visitorInfo findVisitorRecord(visitorInfo* visitorArr, int size, char* searchID);
void searchVisitorRecord(visitorInfo* visitorArr, int size, venuePass venPass, vnePass vnePass, staffPass staffPass);
void modifyVisitorRecord(visitorInfo* visitorArr, int size);
void visitorLogin(visitorPass visPass, vnePass vnePass, vneMetaData* md);
void deleteVisitorData(visitorInfo* visitorArr, int* size);
visitorInfo* readVisitorData(int* size);
void writeVisitorData(visitorInfo* visitorArr, int size);
void visitor(visitorPass visPass, venuePass venPass, vnePass vnePass, staffPass staffPass, vneMetaData* md);