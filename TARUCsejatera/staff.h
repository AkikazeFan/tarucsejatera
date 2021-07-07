#pragma once
#include <stdio.h>
#include <stdlib.h>   ////mikeal binary file 
#pragma warning (disable:4996)
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#define BUFFER_SIZE 256 //declare size, standardised the string size, prevent mistake(ex:10 typo 100)

typedef struct
{
	int staffID;
	char staffName[BUFFER_SIZE];
	char position[BUFFER_SIZE];
	char faculty[BUFFER_SIZE];
	char password[BUFFER_SIZE];
	char phoneNo[BUFFER_SIZE];
	char gender;
	char loginName[BUFFER_SIZE];
}staffInfo;

typedef struct
{
	staffInfo* staffArr;
	int* size;
	int* maxSize;
}staffPass;

typedef struct
{
	int numAdd;
	int numModify;
	int numDelete;
} staffMetaData;

void printStaffInfo(staffInfo staff);
void addStaffRecord(staffInfo* staffArr, int* index, int* maxSize, staffMetaData* md);
void showStaffRecord(staffInfo* staffArr, int size);
staffInfo findStaffRecord(staffInfo* staffArr, int size, int searchID);
void searchStaffRecord(staffInfo* staffArr, int size);
void modifyStaffRecord(staffInfo* staffArr, int size, staffMetaData* md);
staffInfo* readStaffData(int* size);
void writeStaffData(staffInfo* staffArr, int size);
void deleteStaffData(staffInfo* staffArr, int* size, staffMetaData* md);
void reportStaff(staffMetaData* md);
void staff(staffInfo* staffArr, int* size, int* maxSize, staffMetaData* md);