//Name: Angelos Mavrogiannis
//Andrew ID: angelosm
//Date: 11/5/2018
//Course: Engineering Computation _Section B
//Problem Set 10 - Function File(.cpp)

#include "BowlingScoreCalc _angelosm.h"

BowlingScoreCalc::BowlingScoreCalc()
{
}

void BowlingScoreCalc::readScores(const string & input)
{
	char inputCharacters[22];
	if (input.length() < 21) {
		cout << "Too Short." << endl;
		reset();
	}
	else {
		strncpy(inputCharacters, input.c_str(), 21); //make sure only 21 characters are copied from
		for (int i = 0; i < 21; i++) {				//the input string to the character array
			if (inputCharacters[i] >= '0' && inputCharacters[i] <= '9')
				pinsKnockedDown[i] = inputCharacters[i] - '0'; //converting ascii value to integer
			else if (inputCharacters[i] == 'X' || inputCharacters[i] == 'x') //strike
				pinsKnockedDown[i] = 10;
			else if (inputCharacters[i] == '/') //spare
				pinsKnockedDown[i] = 10 - pinsKnockedDown[i - 1];
			else if (inputCharacters[i] == '-' || inputCharacters[i] == ' ') //0 pins knocked down
				pinsKnockedDown[i] = 0;
			else { //unknown character detected
				cout << "Bad Input." << endl;
				reset(); // on error, all values are set to zero
				//exit(EXIT_FAILURE); //program terminates if the input string
			}  //includes any other character other than the approved ones. However I commented that out,
		}     //to run the tests with bowling_tester.cpp. Uncomment for termination if bad data is given.
	}
}

void BowlingScoreCalc::reset()
{
	for (int i = 0; i < 21; i++)
		pinsKnockedDown[i] = 0; //sets all pin counts to zero
}

int BowlingScoreCalc::scoreForFrame(int frameNo)
{
	int score;
	if (frameNo < 1 || frameNo > 10)
		score = - 1; //return -1 for invalid frameNo
	else if (frameNo < 10) {
		if (pinsKnockedDown[2 * frameNo - 2] == 10) { //strike
			score = 10;
			if (pinsKnockedDown[2 * frameNo] == 10 && frameNo < 9) // 2 consequent strikes
				score += 10 + pinsKnockedDown[2 * frameNo + 2];
			else //just one strike, or two strikes if we start from frame 9
				score += pinsKnockedDown[2 * frameNo] + pinsKnockedDown[2 * frameNo + 1];
		}
		else if (pinsKnockedDown[2 * frameNo - 2] + pinsKnockedDown[2 * frameNo - 1] == 10) //spare
			score = 10 + pinsKnockedDown[2 * frameNo];
		else //neither strike nor spare
			score = pinsKnockedDown[2 * frameNo - 2] + pinsKnockedDown[2 * frameNo - 1];
	}
	else {
		if (pinsKnockedDown[2 * frameNo - 2] == 10 || pinsKnockedDown[2 * frameNo - 2] 
			+ pinsKnockedDown[2 * frameNo - 1] == 10) //strike or spare in the 10th frame
			score = pinsKnockedDown[2 * frameNo - 2] + pinsKnockedDown[2 * frameNo - 1] 
			+ pinsKnockedDown[2 * frameNo];
		else //neither strike nor spare in the 10th frame
			score = pinsKnockedDown[2 * frameNo - 2] + pinsKnockedDown[2 * frameNo - 1];
	}
	return score;
}

int BowlingScoreCalc::scoreUpToFrame(int frameNo)
{
	int frameScore = 0, frameLimit = frameNo;
	if (frameNo > 10)
		frameLimit = 10; //returns final score (=score up to 10th frame) for frameNo > 10
	else if (frameNo >= 1) {
		for (int i = 1; i <= frameLimit; i++) {
			frameScore += scoreForFrame(i); //calculate accumulative score for
		}								   //frameNo number of frames
	}							   
	return frameScore; //will return 0 if frameNo < 1, score up to frameNo if frameNo <= 10
}				      //and final score if frameNo > 10 (10th frame is covered by scoreForFrame(10))
