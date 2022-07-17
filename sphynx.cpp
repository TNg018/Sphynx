/* Console Question Game 
*  You encounter a sphynx and are asked three questions. 
*  Answer correctly and you may pass.
*  Riddles from: https://parade.com/947956/parade/riddles/
*/

/* To do:
*	Create 2d array of questions and answers, then shuffle 
* 	Ignore a/an/the/'s/your/punctuation' from input
* 	Make riddles private or part of the sphynx constructor class
*/

#include <iostream>
#include <cstring>		// std::string	
#include <unistd.h> 		// sleep(int) for Linux or Windows.h for Windows 
#include <algorithm>   		// std::shuffle
#include <array>		// std::array
#include <random>		// std::default_random_engine
#include <chrono>		// std::chrono::system_clocl

int NUM_RIDDLES = 10;
int NUM_ATTEMPTS = 3;
double TIME  = 1;

class Sphynx
{
public: 
	Sphynx();
	void play();
	std::string riddles[10] = { "What question can you never answer yes to?", "What is full of holes but still holds water?", "What can't talk but can reply when spoken to?", "What goes up but never comes down?", "What can you keep after giving to someone?", "I have branches, but no fruit, trunk or leaves. What am I?", "The more of this there is, the less you see. What is it?", "What gets bigger when more is taken away?", "Where does today come before yesterday?", "What goes up and down but doesn't move?"}; 
	std::string ranswers[10] = {"are you asleep", "a sponge", "an echo", "your age", "your word", "a bank", "darkness", "a hole", "the dictionary", "a staircase"}; 
	std::array<int,10> shuf {0,1,2,3,4,5,6,7,8,9};
private:
	void introduction();
	void shuffle_questions();
	int get_question(int index);
	std::string get_response();
	bool answer(int index, std::string input);
};

int main(){
	Sphynx game;
	game.play();
	return 0;
}

/* Constructor.                                                                                                              
* Should initialize riddles, ranswers                                                                                 
*/
Sphynx::Sphynx(){}

void Sphynx::introduction()
{
	std::puts("You are at the entrance of a dark cave.");
	sleep(TIME);
	std::puts("As you approach, a Sphynx emerges and blocks the entrance.");
	sleep(TIME);
	std::puts("'I WILL ASK YOU THREE QUESTIONS,' says the Sphynx.");
	sleep(TIME);
	std::puts("'IF YOU ANSWER CORRECTLY, YOU MAY PASS. OTHERWISE YOU SHALL PERISH.'");
	sleep(TIME);
}

/*                                                                                                                           
 * Shuffle an array the same size as NUM_RIDDLES so questions are not always output in the same order and without repeats
 * Only the first three indeces will be used to output three questions maximum                                                        
 */
void Sphynx::shuffle_questions()
{
   unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
   shuffle (shuf.begin(), shuf.end(), std::default_random_engine(num));
}

/*                                                                                                                           
 * Get a question from riddles to ask the user                                                           
 */
int Sphynx::get_question(int index)
{
	std::string riddle;
	riddle = riddles[index];
	std::cout << riddle << std::endl;
	return index;
}

/*                                                                                                                           
 * Get answer from user and convert to all lowercase                                                            
 */
std::string Sphynx::get_response() 
{
	std::string response;
	getline(std::cin, response);
	std::transform( response.begin(), response.end(), response.begin(), ::tolower );
	return response;
}

/*                                                                                                                           
 * Checks if user input matches the string at the index of the answers                                                           
 */
bool Sphynx::answer(int index, std::string input)
{
	bool matched = false;
	std::string answer;
	answer = ranswers[index];
	//std::cout << answer << std::endl;
	int c = input.compare(answer);
	if (c == 0) {
		matched = true;
	} 
	return matched;
	
}

/*                                                                                                                           
 * Runs the game in a loop that continues until the game is over.                                                            
 */
void Sphynx::play()
{
	srand(time(NULL));
	std::string repeat;
	int guessed = 0;
	system("clear");
	introduction();
	// if three guesses are correct, allow to pass. Else, end game if incorrect.
	int attempt = 0;
	
	shuffle_questions();
	while (attempt < NUM_ATTEMPTS) { 
		std::cout << "\nQuestion number " << attempt + 1 << std::endl;
		
		int shuffled_index = shuf[attempt];
		int q = get_question(shuffled_index);
		std::string r = get_response();

		if (answer(q, r)) {
			std::cout << "You are correct!" << std::endl;
			guessed++;
		} else {
			break;
		}
		attempt++;
	}
	
	if (guessed == NUM_ATTEMPTS) {
		std::cout << "You correctly answered all of the questions." << std::endl;
		sleep(TIME);
		std::cout << "You may pass." << std::endl;
	} else {
		std::cout << "You answered incorrectly." << std::endl;
		sleep(TIME);
		std::cout << "\nThe Sphynx gobbles you up." << std::endl;
	}	

}	
