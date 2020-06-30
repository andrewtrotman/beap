#include <vector>
#include <random>
#include <numeric>
#include <iostream>

#include "beap.h"
#include "aspt_beap.h"

/*
	SHUFFLE()
	---------
*/
void shuffle(std::vector<int> &sequence, JASS::bleap<int> &my_beap)
	{
	for (int x = 0; x < sequence.size() * 10; x++)
		{
		size_t location = rand() % sequence.size();
		my_beap.replace(sequence[location], sequence[location] + 100);
		if (!my_beap.isbeap())
			{
			std::cout << "BROKEN\n";
			exit(1);
			}
		}
	std::cout << "shuffle ";
	}

/*
	FIND()
	------
*/
void find(std::vector<int> &sequence, JASS::bleap<int> &my_beap)
	{
	int64_t found = 0;
	for (int x = 0; x < sequence.size(); x++)
		if (my_beap.find(sequence[x] >= 0))
			found++;

	if (found != sequence.size())
		{
		std::cout << "NOT FOUND\n";
		exit(1);
		}

	std::cout << "Found:" << found;
	}


/*
	MAIN()
	------
*/
int main()
	{
	/*
		Populate an array with the shuffled sequence 0..instance.size()
	*/
	std::vector<int> sequence(100);
	std::iota(sequence.begin(), sequence.end(), 0);
	std::random_device random_number_generator;
//	std::shuffle(sequence.begin(), sequence.end(), std::knuth_b(random_number_generator()));
	std::shuffle(sequence.begin(), sequence.end(), std::knuth_b(1));

	JASS::bleap<int> my_beap(sequence.data(), sequence.size());
	my_beap.unittest();

//	std::cout << "\n" << my_beap;
	std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";

	find(sequence, my_beap);
	for (int x = 0; x < 1000; x++)
		{
//		my_beap.noise();
		shuffle(sequence, my_beap);
		find(sequence, my_beap);
//		std::cout << "\n" << my_beap;
		std::cout << (my_beap.isbeap() ? " BEAP" : " NOTBEAP") << "\n";
		}

	return 0;
	}
