#pragma once
#include <stdio.h>
#include <stdlib.h>   //tingle text file
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)
#include <Windows.h>
#include <time.h>
#include "venue.h"
#define BUFFER_SIZE 256 //declare size, standardised the string size, prevent mistake(ex:10 typo 100)
#define vneEnterDate vne.enterDate //new add
#define vneEnterTime vne.enterTime //new add
#define vneExitDate vne.exitDate //new add
#define vneExitTime vne.exitTime //new add

typedef struct
{
    date enterDate;
    times enterTime;
    date exitDate;
    times exitTime;
    char visitorIC[13];
    int venueID;
    int vneRecord;
    float temp;
    char visitReason[BUFFER_SIZE];
    char healthCon[BUFFER_SIZE];
    int noPerson;
}visitExitInfo;

typedef struct
{
    visitExitInfo* vneArr;
    int* size;
    int* maxSize;
}vnePass;

typedef struct
{
    int numAdd;
    int numModify;
    int numDelete;
} vneMetaData;

void printVisitExitInfo(visitExitInfo vne, venueInfo venueTemp);
int addVisitExitRecord(vnePass* vnePass, char* visitorIC, int temperature, vneMetaData* md);
void showVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass);
visitExitInfo findVisitExitRecord(visitExitInfo* vneArr, int size, int searchID);
void searchVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass);
void modifyVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass, vneMetaData* md);
visitExitInfo* readVisitExitData(int* size);
void writeVisitExitData(visitExitInfo* vneArr, int size);
void deleteVisitExitData(visitExitInfo* vneArr, int* size, vneMetaData* md);
void reportVne(vneMetaData* md);
void visitnexit(vnePass vnePass, venuePass venPass, vneMetaData* md);