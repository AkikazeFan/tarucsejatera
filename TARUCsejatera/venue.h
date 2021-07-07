#pragma once
#include <stdio.h>
#include <stdlib.h>    //wen xian text file
#pragma warning (disable:4996)
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#define BUFFER_SIZE 256 //declare size, standardised the string size, prevent mistake(ex:10 typo 100)
#define xd venue.sanitizationDate

typedef struct
{
    int hour;
    int minit;
    int second;
} times;

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct venueInfo
{
    int venueID;
    char category[BUFFER_SIZE];
    char description[BUFFER_SIZE];
    int maxVisitor;
    int currentVisitor;
    date sanitizationDate;
    char currentEvent[BUFFER_SIZE];
    char venueName[BUFFER_SIZE];
} venueInfo;

typedef struct
{
    venueInfo* venArr;
    int* size;
    int* maxSize;
} venuePass;

typedef struct
{
    int numAdd;
    int numModify;
    int numDelete;
} venueMetaData;

void printVenueInfo(venueInfo venue);
void addRecord(venueInfo* venueArr, int* index, int* maxSize, venueMetaData* md);
void showRecord(venueInfo* venueArr, int size);
venueInfo findRecord(venueInfo* venueArr, int size, int searchID);
void searchRecord(venueInfo* venueArr, int size);
void modifyRecord(venueInfo* venueArr, int size, venueMetaData* md);
venueInfo* readData(int* size);
void writeData(venueInfo* venueArr, int size);
void deleteData(venueInfo* venueArr, int* size, venueMetaData* md);
void reportVenue(venueMetaData* md);
void venue(venuePass venPass, venueMetaData* md);