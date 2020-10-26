#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


	string monsterAttacks[4]{"Claw Attack", "Fire Breath", "Ground Slam", "Death Screech"};
	string playerAttacks[4]{ "Fire Ball", "Smoke Screen", "Godess Heal", "Sword Slice" };
	string playerName;

	char leaveStats;
	char checkStats;
	char startPlay;

	float playerHealth = 100;
	float monsterHealth = 300;
	
	int movesLeft = 24;

	enum attackPower{FIREBALL = 15, SMOKESCREEN = 3, GODESSHEAL = 25, SWORDSLICE = 25};
	enum monsterPower{CLAWATTACK=20, FIREBREATH=15, GROUNDSLAM = 10, DEATHSCREECH = 5};

	void gamePlay()
	{
		char rollDie;
		cout << "Press 'R' to see what move you should use against your foe!" << endl;
		cin >> rollDie;


		if (rollDie == 'R' || rollDie == 'r')
		{
			srand((time(0)));
			int die = (rand() % 4) + 1;
			cout << die << endl;
			if (die == 1)
			{
				cout << playerName << "Used " << playerAttacks[0] << endl;
				monsterHealth -= attackPower{ FIREBALL };
				cout << "The monster is burnt" << endl;
				--movesLeft;
			}
			else if (die == 2)
			{
				cout << playerName << "Used " << playerAttacks[1] << endl;
				monsterHealth -= attackPower{ SMOKESCREEN };
				cout << "The monster is trying to see where you are" << endl;
				--movesLeft;
			}
			else if (die == 3)
			{
				cout << playerName << "Used " << playerAttacks[2] << endl;
				playerHealth += attackPower{ GODESSHEAL };
				cout << "You feel your health getting a little low, you have healed yourself" << endl;
				--movesLeft;
			}
			else if (die == 4)
			{
				cout << playerName << "Used " << playerAttacks[3] << endl;
				monsterHealth -= attackPower{ SWORDSLICE };
				cout << "You make a deep cut between the monsters scales" << endl;
				--movesLeft;
			}

		}
		else
		{
			cout << "What are you doing press the 'R' button!" << endl;

		}

	}

	void monsterPlay()
	{
		srand((time(0)));
		int monsterMove = (rand() % 4) + 1;
		if (monsterMove == 1) 
		{
			cout << "The monster comes at you with a fierse " << monsterAttacks[0] << "!\n You are bleeding from the attack!" << endl;
			playerHealth -= monsterPower{ CLAWATTACK };
		}
		else if (monsterMove == 2) 
		{
			cout << "The monster attacks you with a fierse " << monsterAttacks[1] << "\nYou smell something burning... IT'S YOU!" << endl;
			playerHealth -= monsterPower{ FIREBREATH };
		}
		else if (monsterMove == 3) 
		{
			cout << "The monster jump high and comes down with a " << monsterAttacks[2] <<'\n' <<" You are as flat as a pancake." << endl;
			playerHealth -= monsterPower{ GROUNDSLAM};
		}
		else if (monsterMove == 4) 
		{
			cout << "The monster opens it's mouth. You prepare for a fire attack, but you get paralized when you get hit by " << monsterAttacks[3] << endl;
			playerHealth -= monsterPower{ DEATHSCREECH };
		}
	}


	void playerStats()
	{
		cout << "Your health " << playerHealth  <<'\n' << "Moves left "<< movesLeft << '\n' <<"Monster health " <<monsterHealth << endl;
		cout << "Do you want to leave stats? (y/n)" << endl;
		cin >> leaveStats;
		if (leaveStats == 'y' || leaveStats == 'Y') 
		{
			gamePlay();
		}
		else if (leaveStats == 'n' || leaveStats == 'N')
		{
			cout << "Okay then, keep on watching then." << endl;
			playerStats();
		}
		else
		{
			cout << "You can only choose y or n!" << endl;
			playerStats();
		}

	}




int main() 
{
	cout << "Welcome to dragon beaters!\n" << "What should I call you?" << endl;
	cin >> playerName;
	cout << "So you are called " << playerName << ". Well guess we have your parents to blame for that." << endl;
	cout << "Press 'P' to play " << playerName << endl;
	cin >> startPlay;
	if (startPlay == 'p' || startPlay == 'P') {
		cout << playerName << " has been sent on a dangerous and perrilous quest to kill a fierse dragon and save a damsel in distress." << endl;
		cout << "And the fate of the world is in your hands etc." << endl;
		cout << "Anyway, you have entered the monsters lair, when all of a sudden the monster greets you with open arms to a movienight." << endl;
		cout << "That fiend! " << playerName << "You have to kill him for he is holding the remote with POTATO CHIPS GREASED FINGERS!!!" << endl;
		cout << "The " << playerName << " and the horrible chips eating monster are locked in battle!" << endl;
		cout << "FIGHT!" << endl;
		for (;;) {
			gamePlay();
			monsterPlay();
			cout << "would you like to check your stats?(y/n)" << endl;
			cin >> checkStats;
			if (checkStats == 'y' || checkStats == 'Y')
			{
				playerStats();
			}
			else if (checkStats == 'n' || checkStats == 'N')
			{
				cout << "Ok let's continue the Battle!" << endl;
				gamePlay();
			}
			else
			{
				cout << "Would you please choose from y/n!" << endl;
			}

			if (monsterHealth == 0)
			{
				cout << "You did it! You have Beaten the beast!" << endl;
				cout << "GAME OVER" << endl;
				exit(0);
			}
			else if (playerHealth == 0)
			{
				cout << "Come back!\n" << "You can't die here you need to keep fighting!" << endl;
				cout << "Without you who is going to save the world?!" << endl;
				cout << "You were never good enough to begin with, with you dead the world shall now perish and it's all your fault." << endl;
				cout << "GAME OVER!" << endl;
				exit(0);
			}
			else if (movesLeft == 0)
			{
				cout << "I can't believe it, are you... SLEEPING DURING A FIGHT?!!" << endl;
				cout << "You ran out of moves" << endl;
				cout << "GAME OVER" << endl;
				exit(0);
			}
		}
	}
	else 
	{
		cout << "You have to press 'P' to play!" << endl;
	}
	
}
