#pragma once
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include "venue.h"

#define SIZE 130   //declare & standardise the string size, prevent typo & cause error 

#define sanDay san.sanDate       //declare variable name for sanitization date & time as they are not a member of sanitizationInfo, they are member from venue
#define sanStarTime san.starTime
#define sanEndTime san.endTime

typedef struct
{
    date sanDate;   //date & time struct already declare in venue.h, above include the header file
    times starTime;
    times endTime;
    int venueID, sanRecord;
    char compName[SIZE], contactPerson[SIZE], contactNo[SIZE], gender;

} sanitizationInfo;

typedef struct
{
    int numAdd;
    int numModify;
    int numDelete;

} sanMetaData;

void showSanRecord(sanitizationInfo* sanArr, int size, venuePass pass);
void printSanitizationInfo(sanitizationInfo san, venueInfo venueTemp);
void addSanRecord(sanitizationInfo* sanArr, int* index, int* maxSize, sanMetaData* md);
void searchSanRecord(sanitizationInfo* sanArr, int size, venuePass pass);
sanitizationInfo findSanRecord(sanitizationInfo* sanArr, int size, int searchID);
void modifySanRecord(sanitizationInfo* sanArr, int size, venuePass pass, sanMetaData* md);
sanitizationInfo* readSanData(int* size);
void writeSanData(sanitizationInfo* sanArr, int size);
void deleteSanData(sanitizationInfo* sanArr, int* size, sanMetaData* md);
void reportSan(sanMetaData* md);
void sanitization(sanitizationInfo* sanArr, int* size, int* maxSize, venuePass venPass, sanMetaData* md);