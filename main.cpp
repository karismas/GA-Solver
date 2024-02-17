#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

class DNA
{
	// contains array of letters towards desired task.
public:

	vector<char> createDNA(int USER_PHRASE_SIZE)
	{
		vector<char>* newGenes = new vector<char>;

		for (int i = 0; i < USER_PHRASE_SIZE; i++)
		{
			int randomizer = rand() % 94;
			int randomLetter = ('!' - 1) + randomizer;
			newGenes->push_back(char(randomLetter));
		}

		return *newGenes;
		delete newGenes;
	}

	vector<vector<char>> crossGenes(vector<char> firstGeneSet, vector<char> secondGeneSet)
	{
		int geneSplit = 0;

		while (geneSplit == 0 || geneSplit == firstGeneSet.size())
		{
			geneSplit = rand() % firstGeneSet.size();
		}

		vector<char> firstChildGeneSet;
		vector<char> secondChildGeneSet;

		firstChildGeneSet.insert(firstChildGeneSet.end(), firstGeneSet.begin(), firstGeneSet.begin() + geneSplit);
		firstChildGeneSet.insert(firstChildGeneSet.end(), secondGeneSet.begin() + geneSplit, secondGeneSet.end());

		secondChildGeneSet.insert(secondChildGeneSet.end(), secondGeneSet.begin(), secondGeneSet.begin() + geneSplit);
		secondChildGeneSet.insert(secondChildGeneSet.end(), firstGeneSet.begin() + geneSplit, firstGeneSet.end());

		return{ firstChildGeneSet, secondChildGeneSet };
	}


};

class Organism
{
	// contains DNA.
	// contains fitness level based on the closeness of completion of the task.
public:


	Organism(vector<char> inputGOAL)
	{
		GOAL = inputGOAL;
	}

	void createOrganism(int USER_PHRASE_SIZE)
	{
		DNA* newDNA = new DNA;
		Genes = newDNA->createDNA(USER_PHRASE_SIZE);
		delete newDNA;
		calculateFitness();
	}

	void calculateFitness()
	{
		for (int i = 0; i < Genes.size(); i++)
		{
			organismFitness += abs((int)Genes[i] - (int)GOAL[i]);
		}
	}

	int getFitness()
	{
		return organismFitness;
	}

	vector<Organism> breedWith(Organism secondParent)
	{
		Organism firstChild(GOAL);
		Organism secondChild(GOAL);

		vector<vector<char>> childGeneSets = DNAController.crossGenes(this->Genes, secondParent.Genes);
		firstChild.Genes = childGeneSets[0];
		secondChild.Genes = childGeneSets[1];

		return{ firstChild, secondChild };

	}

	vector<char> Genes;
	DNA DNAController;
	int organismFitness = 0;
	vector<char> GOAL;
};

class Population
{
	// contains certain amount of organisms.
public:

	Population(vector<char> inputGOAL) : mostFitOrganism(GOAL)
	{
		GOAL = inputGOAL;
	}

	void createPopulation(int POPULATION_SIZE, int USER_PHRASE_SIZE)
	{
		for (int i = 0; i < POPULATION_SIZE; i++)
		{
			Organism* newOrganism = new Organism(GOAL);
			newOrganism->createOrganism(USER_PHRASE_SIZE);
			Organisms.push_back(*newOrganism);
		}

		calculateMostFitOrganism();
	}

	void calculateMostFitOrganism()
	{
		int highestFitness;

		for (int i = 0; i < Organisms.size(); i++)
		{
			if (i == 0)
			{
				highestFitness = Organisms[0].getFitness();
				mostFitOrganism = Organisms[0];
			}

			else
			{
				if (highestFitness > Organisms[i].getFitness())
				{
					highestFitness = Organisms[i].getFitness();
					mostFitOrganism = Organisms[i];
				}
			}
		}
	}

	Organism getMostFitOrganism()
	{
		return mostFitOrganism;
	}

	Population breedPopulation(Population inputPopulation)
	{
		Population newPopulation(GOAL);
		Organism firstParent(GOAL);
		Organism secondParent(GOAL);
		vector<Organism> children;

		while (inputPopulation.Organisms.size() != 0)
		{

			inputPopulation.calculateMostFitOrganism();
			firstParent = inputPopulation.getMostFitOrganism();

			for (int i = 0; i < inputPopulation.Organisms.size(); i++)
			{
				if (firstParent.Genes == inputPopulation.Organisms[i].Genes)
				{
					inputPopulation.Organisms.erase(inputPopulation.Organisms.begin() + i);
					break;
				}
			}

			inputPopulation.calculateMostFitOrganism();
			secondParent = inputPopulation.getMostFitOrganism();

			for (int j = 0; j < inputPopulation.Organisms.size(); j++)
			{
				if (secondParent.Genes == inputPopulation.Organisms[j].Genes)
				{
					inputPopulation.Organisms.erase(inputPopulation.Organisms.begin() + j);
					break;
				}
			}

			children = firstParent.breedWith(secondParent);
			children[0].calculateFitness();
			children[1].calculateFitness();


			newPopulation.Organisms.push_back(children[0]);
			newPopulation.Organisms.push_back(children[1]);
		}

		return newPopulation;
	}

	vector<char> GOAL;
	vector<Organism> Organisms;
	Organism mostFitOrganism;
};

bool checkIfValid(string input)
{
	return input.find_first_not_of("0123456789") == string::npos;
}

void beginAlgorithm(string USER_PHRASE, int POPULATION_SIZE, int GENERATIONS, string PRINTMETHOD)
{
	int start = 1;
	vector<char> GOAL;

	for (int i = 0; i < USER_PHRASE.size(); i++)
	{
		GOAL.push_back(USER_PHRASE[i]);
	}

	Population Population(GOAL);
	Population.createPopulation(POPULATION_SIZE, USER_PHRASE.size());
	Organism BESTORGANISM = Population.getMostFitOrganism();

	if (PRINTMETHOD == "a")
	{
		cout << endl << "Generation 1: " << endl << endl;

		for (int i = 0; i < POPULATION_SIZE; i++)
		{
			for (int j = 0; j < USER_PHRASE.size(); j++)
			{
				cout << Population.Organisms[i].Genes[j];
			}

			cout << ": " << Population.Organisms[i].getFitness();
			cout << endl;
		}

		while (start != GENERATIONS && Population.getMostFitOrganism().getFitness() != 0)
		{
			Population = Population.breedPopulation(Population);
			Population.calculateMostFitOrganism();

			start++;

			if (Population.getMostFitOrganism().getFitness() < BESTORGANISM.getFitness())
			{
				BESTORGANISM = Population.getMostFitOrganism();
			}

			cout << endl << "Generation " << start << ": " << endl << endl;

			for (int i = 0; i < POPULATION_SIZE; i++)
			{
				for (int j = 0; j < USER_PHRASE.size(); j++)
				{
					cout << Population.Organisms[i].Genes[j];
				}

				cout << ": " << Population.Organisms[i].getFitness();
				cout << endl;
			}
		}
	}

	if (PRINTMETHOD == "b")
	{
		cout << endl << "Generation 1: " << endl << endl;

		Organism mostFitOrganism = Population.getMostFitOrganism();
		cout << "Most fit organism: ";

		for (int i = 0; i < mostFitOrganism.Genes.size(); i++)
		{
			cout << mostFitOrganism.Genes[i];
		}

		cout << endl << "With a fitness score of: " << mostFitOrganism.getFitness() << endl;

		while (start != GENERATIONS && mostFitOrganism.getFitness() != 0)
		{
			start++;

			Population = Population.breedPopulation(Population);
			Population.calculateMostFitOrganism();

			mostFitOrganism = Population.getMostFitOrganism();

			if (mostFitOrganism.getFitness() < BESTORGANISM.getFitness())
			{
				BESTORGANISM = Population.getMostFitOrganism();
			}

			cout << endl << "Generation " << start << ": " << endl << endl;

			cout << "Most fit organism: ";

			for (int i = 0; i < mostFitOrganism.Genes.size(); i++)
			{
				cout << mostFitOrganism.Genes[i];
			}

			cout << endl << "With a fitness score of: " << mostFitOrganism.getFitness() << endl;
		}
	}

	if (Population.getMostFitOrganism().getFitness() == 0)
	{
		cout << endl << endl << "--------------------------------------------------" << endl;
		cout << endl << "The genetic algorithm reached its goal." << endl;
		cout << endl << "Generation reached: " << start << endl;
		cout << "Most fit organism: ";

		for (int i = 0; i < Population.getMostFitOrganism().Genes.size(); i++)
		{
			cout << Population.getMostFitOrganism().Genes[i];
		}

		cout << endl << "With a fitness score of: 0" << endl;
		cout << endl << "--------------------------------------------------" << endl;
	}

	else if (Population.getMostFitOrganism().getFitness() != 0)
	{
		cout << endl << endl << "--------------------------------------------------" << endl;
		cout << endl << "All generations finished." << endl;
		cout << endl << "Generation reached: " << start << endl;
		cout << "Most fit organism: ";

		for (int i = 0; i < BESTORGANISM.Genes.size(); i++)
		{
			cout << BESTORGANISM.Genes[i];
		}

		cout << endl << "With a fitness score of: " << BESTORGANISM.getFitness() << endl;
		cout << endl << "--------------------------------------------------" << endl;
	}
}

void intro()
{

	string USER_PHRASE;
	string POPULATION_SIZE;
	string GENERATIONS;
	string PRINTMETHOD;

	cout << endl << "What phrase would you like the algorithm to guess?" << endl;
	cout << endl << "> ";
	getline(cin, USER_PHRASE);

	cout << endl << "How many organisms would you like in the population? (must be an even number)" << endl;
	cout << endl << "> ";
	getline(cin, POPULATION_SIZE);

	if (stoi(POPULATION_SIZE) % 2 != 0)
	{
		cout << endl << "Your input contained an uneven number. Restarting." << endl;
		intro();
	}

	if (!checkIfValid(POPULATION_SIZE))
	{
		cout << endl << "Your input contained characters that were not numbers. Restarting." << endl;
		intro();
	}

	cout << endl << "How many generations would you like to run?" << endl;
	cout << endl << "> ";
	getline(cin, GENERATIONS);

	if (!checkIfValid(GENERATIONS))
	{
		cout << endl << "Your input contained characters that were not numbers. Restarting." << endl;
		intro();
	}

	cout << endl << "Would you like to print: " << endl << endl;
	cout << "(a) All organisms for every generation. " << endl;
	cout << "(b) Only the best organism for every generation." << endl;
	cout << "Choose (a/b)." << endl;
	cout << endl << "> ";
	getline(cin, PRINTMETHOD);

	if (PRINTMETHOD != "a" && PRINTMETHOD != "b")
	{
		cout << endl << "Your input contained characters that were not included in the choices. Restarting." << endl;
		intro();
	}

	cout << endl << "Starting." << endl;

	beginAlgorithm(USER_PHRASE, stoi(POPULATION_SIZE), stoi(GENERATIONS), PRINTMETHOD);

}

int main()
{
	/*

	Simple task to solve for the population.
	Make a population of organisms.
	Make individual organisms.
	Make DNA (genes only) for those organisms.

	*/

	srand(time(NULL));
	cout << endl << "Welcome to the Genetic Algorithm phrase guesser!" << endl;

	intro();

}
