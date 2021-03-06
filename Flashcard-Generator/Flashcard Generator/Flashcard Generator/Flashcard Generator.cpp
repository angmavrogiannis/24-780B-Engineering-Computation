/*
   _____                _____   Angelos Mavrogiannis
  |     | _____        |     |  Carnegie Mellon University
  |  3  ||     | _____ |  2  |
  |  x  ||  5  ||     ||  x  |
  |  7  ||  x  ||  4  ||  6  |
  |_____||  2  ||  x  ||_____|  Digital (text-only) version of
		 |_____||  9  |         multiplication flash cards. Program
				|_____|         assures non-repeating questions while
								keeping track of time and score.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int swapArray(int *flashcardArray, int i, int randomIndex)
{
	int temp;
	temp = flashcardArray[i]; //classic swapping method
	flashcardArray[i] = flashcardArray[randomIndex];
	flashcardArray[randomIndex] = temp;
	return 0;
}

int shuffleArray(int *flashcardArray, int arraySize)
{
	int randomIndex, i;
	srand(time(NULL)); //make random number generator more random by giving a seed
	for (i = 0; i < arraySize; i++) {
		randomIndex = rand() % arraySize; //generate random number between 0 and the array elements
		swapArray(flashcardArray, i, randomIndex);
	}
	return 0;
}

int main(void)
{
	int numberOfFlashcards, i, flashcardArray[144], arraySize, maxNumber;
	int answer, correctAnswer, startTime, endTime, elapsedTime, numberOfCorrectAnswers = 0;
	char answer10or12; //this will specify if the user wants to include 11s and 12s or not
	float correctPercentage;
	printf("24-780-B Eng Computation Problem Set 2-2\nMultiplication Flash Cards\n");
	printf("\nPress ENTER when ready:\n");
	getchar(); //wait for the user to press enter
	printf("Do you want to include 11 and 12 in your flashcards? [Y/N]\n");
	scanf("%c", &answer10or12);
	if (answer10or12 == 'Y' || answer10or12 == 'y')
	{
		arraySize = 144;
		maxNumber = 12;
	}
	else //normally it should be else if input=N or input=n but let's keep it that way to avoid
	{    //any issues if the user presses a random key
		arraySize = 100;
		maxNumber = 10;
	}
	printf("How many flashcards do you want to work on?\n");
	scanf("%d", &numberOfFlashcards);
	if (maxNumber == 12) //check if the user entered a valid number of flashcards
	{
		while (numberOfFlashcards < 1 || numberOfFlashcards > 144) {
			printf("The number of cards must be between 1 and 144.\nEnter a valid number of flashcards:");
			scanf("%d", &numberOfFlashcards);
		}
	}
	else
	{
		while (numberOfFlashcards < 1 || numberOfFlashcards > 100) {
			printf("The number of cards must be between 1 and 100\nEnter a valid number of flashcards\n");
			scanf("%d", &numberOfFlashcards);
		}
	}
	for (i = 0; i < arraySize; i++) { //fill flashcardArray with consecutive integers starting from 0
		flashcardArray[i] = i;
	}
	shuffleArray(flashcardArray, arraySize); //shuffle the array containing the flashcard combinations
	startTime = time(NULL); //get current time/starting time
	for (i = 0; i < numberOfFlashcards; i++) {
		correctAnswer = (flashcardArray[i] / maxNumber + 1) * (flashcardArray[i] % maxNumber + 1); //integer division gives us the first digit minus 1
		printf("\n%d x %d :", flashcardArray[i] / maxNumber + 1, flashcardArray[i] % maxNumber + 1); //and modular division gives us the second one minus 1
		scanf("%d", &answer); //when we add +1 to each digit, we get the actual flashcard digits
		if (answer != correctAnswer) {
			printf("Incorrect! The correct answer is %d\n", correctAnswer);
		}
		else
		{
			numberOfCorrectAnswers++;
		}
	}
	endTime = time(NULL); //get current time/ending time
	elapsedTime = endTime - startTime; //calculate elapsed time (difference between starting and ending time
	printf("\nYou answered %d problems in %d seconds.\n", numberOfFlashcards, elapsedTime);
	correctPercentage = float(numberOfCorrectAnswers) / float(numberOfFlashcards) * 100;
	printf("You answered %d problems correctly %.f%%.", numberOfCorrectAnswers, correctPercentage);
	return 0;
}