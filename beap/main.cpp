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
//	int n = -2;
//	std::generate(sequence.begin(), sequence.end(), [&n]{return n += 2;});
	std::random_device random_number_generator;
//	std::shuffle(sequence.begin(), sequence.end(), std::knuth_b(random_number_generator()));
	std::shuffle(sequence.begin(), sequence.end(), std::knuth_b(1));

	JASS::bleap<int> my_beap(sequence.data(), sequence.size());
	my_beap.unittest();


	std::cout << "\n" << my_beap;
	std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";

	/*
		find
	*/
	int found = 0;
	for (int x = 0; x <= sequence[sequence.size() - 1]; x++)
		{
		if (x % 16 == 0)
			std::cout <<  "\n";
		auto location = my_beap.find(x);
		std::cout << "(" << x << ":" << location << ")";
		if (location >= 0)
			found++;
		}
	std::cout << "\n\n";

	std::cout << "Found:" << found << "\n";



#ifndef NEVER

	std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";
	/*
		replace
	*/
	for (int x = 0; x < sequence.size() * 10; x++)
		{
		size_t location = rand() % sequence.size();
		std::cout << "my_beap.replace(" << sequence[location] << ", " << sequence[location] + 100 << ");  //";
		my_beap.replace(sequence[location], sequence[location] + 100);
		std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";
		}

#else

	my_beap.replace(27, 127);  //BEAP

	std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";

	std::cout << "\n" << my_beap;
	my_beap.noise();
	my_beap.replace(37, 137);

	std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";

#endif

	std::cout << "\n" << my_beap;
	std::cout << (my_beap.isbeap() ? "BEAP" : "NOTBEAP") << "\n";




	/*
		find
	*/
	found = 0;
	for (int x = 0; x < sequence.size(); x++)
		{
		if (x % 16 == 0)
			std::cout <<  "\n";
		auto location = my_beap.find(sequence[x]);
		std::cout << "(" << sequence[x] << ":" << location << ")";
		if (location >= 0)
			found++;
		}
	std::cout << "\n\n";

	std::cout << "Found:" << found << "\n";

	my_beap.noise();
	auto location = my_beap.find(1474);
	std::cout << "Location:" << location << "\n";


	return 0;
	}
