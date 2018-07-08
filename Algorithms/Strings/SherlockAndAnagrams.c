#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
problemsite:
https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem

Input Format

The first line contains an integer q, the number of queries. 
Each of the next q lines contains a string s to analyze.

Constraints

1<=q<=10
2<=|s|<=100
 
String s contains only lowercase letters ∈ ascii[a-z].

Output Format

For each query, return the number of unordered anagrammatic pairs.

sample input:
2
abba
abcd

sample output:
4
0
*/

char* readline();

// Made by xiper
// Last Updata : 2016 / 2 / 02
// test status : √


char* substr(char* s1, int start, int end){
    char* s2 = (char*)malloc(sizeof(char)*(end-start+1));
    int index = 0;
    for(int i=start;i<end;i++){
        s2[index] = s1[i];
        index++;
    }
    s2[index] = '\0';
    return s2;
}

int find(char* s1, char* s2){
    int len = strlen(s1);
    int marklist[len];
    for(int i=0;i<len;i++){
        marklist[i] = 0;
    }
    for(int i=0;i<len;i++){
        char temp = s1[i];
        int find_mark = 0;
        for(int j=0;j<len;j++){
            if(s2[j]==temp&&marklist[j]==0){
                marklist[j] = 1;
                find_mark = 1;
                break;
            }
        }
        if(find_mark!=1){
            return 0;
        }
    }
    return 1;
}

int find_anagrams(char* s1, char* s2){
    int s1len = strlen(s1);
    int s2len = strlen(s2);
    int count = 0;
    for(int i=1;i<s1len-s2len+1;i++){
        char* s3 = substr(s1,i,i+s2len);
        if(find(s3,s2)==1){
            count++;
        }
    }
    return count;
}

int sherlockAndAnagrams(char* s) {
    int count = 0;
    int len = strlen(s);
    for(int i=0;i<len;i++){
        for(int j=i;j<len;j++){
            char* s2 = substr(s,i,j+1);
            char* s1 = substr(s,i,len);
            count += find_anagrams(s1,s2);
        }
    }
    return count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* q_endptr;
    char* q_str = readline();
    int q = strtol(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* s = readline();

        int result = sherlockAndAnagrams(s);

        fprintf(fptr, "%d\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}
