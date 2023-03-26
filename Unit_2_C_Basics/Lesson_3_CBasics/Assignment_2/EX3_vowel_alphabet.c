/*
 ============================================================================
 Name        : EX3_vowel_alphabet.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//AOS
//Assignment 2 EX3_vowel_alphabet
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c ;
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	switch (c){
	case'a':
	case'e':
	case'i':
	case'o':
	case'u':
	case'A':
	case'E':
	case'I':
	case'O':
	case'U':
	{
		printf("%c is a vowel",c);
	}
	break;
	default:
	{
		printf("%c is a consonant",c);
	}
	break;
	}
}
