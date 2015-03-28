/*
 Copyright 2015. All rights reserved
 Author: Teh Rong Jiunn
 version: 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>

#define ASIZE 255	//ASCII code size
#define DATA_SIZE 4096000	//4MB
#define YES 1

using namespace std;

typedef struct{
	char* text;
	char* pattern;
	int* shifts;
	int* results;
}stringSearchData;

void stringSearch(int n, int m, stringSearchData host){	
	int i = 0;;
	
	while(i <= n - m){ 
		int k = m - 1;
		while (host.pattern[k] == host.text[i + k]){
			k -= 1;
			if (k < 0){
				host.results[i] = YES;
				break;
			}
		}
		i += host.shifts[host.text[i + m - 1]];		
	}

	return;
}

char* readfile(const char* filename) {

	string line;
	unsigned int i = 0;
	char* data = (char*)malloc(DATA_SIZE * sizeof(char));
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			if (i < 1) strcpy(data, line.c_str());
			else strcat(data, line.c_str());
			i++;
		}
		myfile.close();
	}
	else printf("Unable to open file!\n");
	
	return data;
}

void displayResults(int n, int  results[]) {
	int noMatch = 0;
	int total = 0;
	for (int i = 0; i < n; i++){
		if (results[i] == YES){
			//printf("Found match at %d.\n", i);
			total += 1;
		}
		else noMatch++;
	}
	if (noMatch == n) printf("No match found.\n");
	else printf("Total occurrence: %d\n",total);
}

int main() {
	stringSearchData host;
	char fileName[1000];
	int n = 0; // length of host text
	int m = 0; // length of host pattern
	clock_t begin, end;
	double time;
	
    //
    // Read in the text file
    //
	printf("Text file: ");
	scanf("%s",fileName);
    host.text = readfile(fileName);
	n = strlen(host.text);

	//
	// Input the pattern to be matched
	//
	printf("Pattern: ");
	scanf("%s",fileName);
    host.pattern = fileName;    
    m = strlen(host.pattern);
	
    //
    // Initialize the shift index
    //
    host.shifts = (int*) malloc( ASIZE * sizeof(int) );
    for( int i = 0; i < ASIZE; i++ )
        host.shifts[i] = m;
	
	//
	// Compute shift table
	//
	for (int i = 0; i <= m - 2; i++)
		host.shifts[host.pattern[i]] = m - 1 - i;

	//
	// Perform the string search
	//
	host.results = (int*)malloc(n * sizeof(int));
	begin = clock();
	stringSearch(n, m, host);
	end = clock();
	time = ((double)(end - begin) * 1000.00 )/ CLOCKS_PER_SEC;
	printf("Time taken: %f ms\n", time);
	displayResults(n, host.results);

	//
	// Free allocated memory
	//
	free(host.text);
	free(host.results);
	
	return 0;
}
