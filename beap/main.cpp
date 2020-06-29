#include <vector>
#include <random>
#include <numeric>
#include <iostream>

#include "beap.h"
#include "aspt_beap.h"

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

#ifdef NEVER
	Data_structures::Beap<int> beap;

	for (int i = 0; i < sequence.size(); i++)
		beap.push(sequence[i]);

	std::cout << beap << std::endl;

	std::cout << "Find:" << std::endl;
	for ( int i = 0; i < sequence.size(); ++i )
		if ( beap.find( i ) )
			std::cout << i << " ";

	std::cout << std::endl << std::endl;

	std::cout << "Count:" << std::endl;
	int c = 0;
	for ( int i = 0; i < sequence.size(); ++i )
		{
		c += beap.count( i );
		if ( beap.count( i ) )
			std::cout << i << "(" << beap.count( i ) << ") ";
		}

	std::cout << "Items counted:  " << c << std::endl << std::endl;
	std::cout << std::endl << std::endl;
#else
	JASS::bleap<int> my_beap(sequence.data(), sequence.size());
	my_beap.unittest();
	std::cout << "\n" << my_beap;
#endif
	return 0;
	}
