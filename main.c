#define MAX_ROWS 20
#define MAX_COLS 20
#define MAX_PERSONS 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ex. 1
int lowestNumberSquaredMatrix(int numbers[MAX_ROWS][MAX_COLS], int rows, int columns) {
  int lowestNumber = numbers[0][0];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (numbers[i][j] < lowestNumber) {
        lowestNumber = numbers[i][j];
      }
    }
  }
  return lowestNumber;
}

// ex. 2
int medianAdjustedScore(int score1, int score2, int score3) {
  int median = (score1 + score2 + score3) / 3;

  return (score1 + score2 * 2 + score3 * 3 + median) / 7;
}

// ex. 3
void printReversedPyramid(int maxNumber) {
  if (maxNumber % 2 == 0) {
    printf("Error: even number");
    return;
  }
  int discount = 0;
  for (int i = 0; i < (maxNumber + 1) / 2; i++) {
    for (int j = 0; j < maxNumber ; j++) {
      if (i - discount > 0) printf("%d ", j);
      else printf("  ");
      discount += 1;
    }
    printf("\n");
  }
}

// Escreva um programa que leia um arquivo texto com o nome, a idade e a altura de um conjunto de pessoa. Use, como exemplo, os dados a seguir como conteúdo do arquivo a ser lido:
//
// Maria
// 15
// 1.6
// ...
//
// Ao longo da leitura, coloque esses dados em uma um vetor de Structs/Objeto e ordene esse vetor pelo campo da altura. No final, gere um novo arquivo com os dados ordenados.
//
// Encapsule, obrigatoriamente, em funções/métodos:
//
//     (i) a leitura de cada instância de uma pessoa
//     (ii) a ordenação do conjunto de dados
//     (iii) a impressão

typedef struct {
  int age;
  float height;
  char name[100];
} personStruct;

int countFileLines(char *fileName) {
  FILE *fp = fopen(fileName, "r");
  char myString[100];
  int i = 0;
  while(fgets(myString, 100, fp)) {
    i++;
  }
  return i;
}

void textFileIntoStructArray(char *fileName, personStruct persons[MAX_PERSONS]) {
  FILE *fptr = fopen(fileName, "r");

  char myString[100];
  int i = 0;
  int personsCount = 0;
  personStruct person;
  while(fgets(myString, 100, fptr)) {
    if (i % 3 == 0) {
      strcpy(person.name, myString);
    }
    if (i % 3 == 1) {
      int ageNumber = atoi(myString);
      person.age = ageNumber;
    }
    if (i % 3 == 2) {
      float heightNumber = atof(myString);
      person.height = heightNumber;
      persons[personsCount] = person;
      personsCount++;
    }
    i++;
  }

  fclose(fptr);
}

void printPersonsStruct(personStruct persons[MAX_PERSONS], int personsCount) {
  for (int i = 0; i < personsCount; i++) {
    printf("Name: %s", persons[i].name);
    printf("Age: %d\n", persons[i].age);
    printf("Height: %.2fm\n\n", persons[i].height);
  }
}

int compareAge(const void *a, const void *b) {
  personStruct *person1 = (personStruct *)a;
  personStruct *person2 = (personStruct *)b;

  if (person2->height > person1->height) return -1;
  return 1;
}

void createPersonsFile(char *fileName, int personsCount, personStruct persons[MAX_PERSONS]) {
  FILE *fp = fopen(fileName, "w");

  for (int i = 0; i < personsCount; i++) {
    fprintf(fp, "Name: %s", persons[i].name);
    fprintf(fp, "Age: %d\n", persons[i].age);
    fprintf(fp, "Height: %.2fm\n\n", persons[i].height);
  }

  fclose(fp);
}

int main() {

  char fileName[100] = "text.txt";
  char newFileName[100] = "persons_text.txt";

  personStruct persons[MAX_PERSONS];
  int fileLines = countFileLines(fileName);
  int personsCount = fileLines / 3;
  textFileIntoStructArray(fileName, persons);
  qsort(persons, personsCount, sizeof(personStruct), compareAge);
  printPersonsStruct(persons, personsCount);
  createPersonsFile(newFileName, personsCount, persons);

  return 0;
}