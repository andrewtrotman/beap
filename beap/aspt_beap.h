/*
	ASPT_BEAP.H
	-----------
	see: https://pdf.sciencedirectassets.com/272574/1-s2.0-S0022000000X01043/1-s2.0-0022000080900379/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjEHMaCXVzLWVhc3QtMSJHMEUCIQDliCWRlWsdRlJzHrOJlYUKk%2B9Ltk4aEp0yUvsHjVR1kAIgbEDQ4ClLwEM0rlGc365TxqYZheprFGRnFY88FIvUaRwqvQMI%2FP%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARADGgwwNTkwMDM1NDY4NjUiDOpAeCnUnpQAfS2uLSqRA4Jv%2BvA76o5AWo7usKU6j1e3VSRmKAPZlgfkDyYQI99WmUXuOC57gy9SvwXVFILaDBkKDeqUY6OxQLpQxp0CgpijtTZgCfEC3f%2FWx4Loz2wujt8YB6CU1fvtLG8xzxzfAgYN0NzuJnF8RMDtAilX7JBC0SeG8Wx9leBwY98W59L8DXMuNI%2BKyOhNNSYgA2946AdplJZUwqksu5qURQrp7bSiGp%2F%2FWMzO9Up14cuwoUgK6X3eGE8%2BEepOsJiHfh7LEAfhAkSvlxojwzEoruijKdoI4TwjiFc%2BP%2B5NkBXV2OT%2BA4I1xOsVB3Dm6Ngd5G16dcADW%2BAL9UjLCf80RMgjHvC3rJxzmQ8mG7G%2FcROBgmcCJFrcqRx5meYiIQ34joUCAtfXhIjxxyrI2CtKwmOON6TOXOPW4enZsXkrDoQ6Pnc7H7tIMSf5gZifJOrtxmaXC%2FB6T8SkZJyEgSFIAmse0gPSlt15WVAhbEUKAkbCGp72fruPfsEEbfjlFdzp7B9fQi2UVcZ0%2FwvSkpRLPde0%2F752MOqv5fcFOusBC1dnzJeA65Jcr%2Fo1cMjTaO3FtG10q%2F%2FulB7tsxSFxVOpT1G1xeNlziXjevYGarSs39d0AXwCGhjL5LW08jiNVodr%2FoiCk4%2BPuK0U%2BzDFqo5bmloh6khchY63aRrG5Q3TQrTGdnjyWJxoX6qghoCXpUCqR0WgZ103zknHYE8VrTgDfXKy7qLNzfpqu3qkbdqXB6Pn9RMuGhSyZZiyvI0%2F%2FIuQeXYkCO2822mHp0vRl15XRk5D7FB8B4wFGK3ZKf6A013iJnNXfiTFc%2BEgcrU%2FTGHUsa0F1sGPZe76i9kReoFAw7ZAHQk9dVqYKw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20200629T032942Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYRYQE4VN3%2F20200629%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=178fdf2c8848e325b3900fc2513413cd2ed23bcfeb0d6891d8a5f1f3ed3425ed&hash=e777b46a59ee56aabb1e498e4dfd071c896d447f116d87e9b6847cbbdb94f140&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=0022000080900379&tid=spdf-9cb23011-e1e3-4914-a399-16f5225eeb21&sid=73ae443e4644b54cfa186f068b7536868cfagxrqa&type=client
*/
#include <iostream>
#include <algorithm>

namespace JASS
	{
	template <typename TYPE>
	class bleap
		{
		template <typename T>
		friend std::ostream &operator<<(std::ostream &into, const bleap<T> &object);

		private:
			TYPE *array;				///< the array that is the beap
			int64_t elements;			///< elements in the beap
			int64_t height;				///< height of the beap

		public:
			/*
				BEAP::BEAP()
				------------
				min beap (the lowest value is at array[0]
			*/
			bleap(TYPE *array, int64_t elements):
				array(array),
				elements(elements),
				height(get_height(elements))
				{
				std::sort(array, array + elements);
				}

			/*
				BEAP::GET_HEIGHT()
				------------------
				return the row number given the index (both count from 0) (so get_height(0) == 0, get_height(1) == 1, get_height(2) == 1)
			*/
			int64_t get_height(int64_t element) const
				{
				return ceil((sqrt(8 * element + 2) - 1) / 2) - 1;
				}

			/*
				BEAP::GET_FIRST()
				-----------------
				both count from  0 (so get_first(0) == 0), get_first(1) == 1);
			*/
			int64_t get_first(int64_t height) const
				{
				return height * (height + 1) / 2;
				}

			/*
				BEAP::GET_LAST()
				----------------
				both count from  0 (so get_last(0) == 0), get_first(1) == 2);
			*/
			int64_t get_last(int64_t height) const
				{
				return (height + 1) * (height + 2) / 2 - 1;
				}
			/*
				BEAP::REPLACE()
				---------------
				return -1 on not found, or the location of new_key after it has been added
			*/
			int64_t replace(TYPE old_key, TYPE new_key)
				{
				int64_t location = find(old_key);
				if (location < 0)
					{
std::cout << old_key << " Not found\n";
std::cout << *this << "\n";

					return -1;
					}

				array[location] = new_key;
//				if (new_key < old_key)
//					return beap_up(location);
//				else
					return beap_down(location);
				}
				
			/*
				BEAP::ISBEAP()
				--------------
				return true if a beap else return false
			*/
			bool isbeap(void)
				{
				int64_t end_of_row = 0;
				for (int64_t current_height = 0; current_height < height; current_height++)
					{
					end_of_row += get_last(current_height + 1);
					for (int64_t current_location = get_first(current_height); current_location <= get_last(current_height); current_location++)
						{
						int64_t child1 = current_location + current_height + 1;
						int64_t child2 = std::min(current_location + current_height + 2, elements - 1);

						if (child1 >= elements)
							return true;

						if (array[current_location] > array[child1] || array[current_location] > array[child2])
							return false;
						}
					}
				return true;
				}

			/*
				BEAP::FIND()
				------------
				return -ve on not found, or the index into array[] on found.
			*/
			int64_t find(TYPE key)
				{
				/*
					Start in the bottom right corner of the beap
				*/
				int64_t current_height = height;
				int64_t current_location = get_first(height);
				int64_t end_of_row = get_last(height);

//std::cout << " start:[h:" << current_height << ","<< current_location << "=" << array[current_location] << "]\n";
				do
					{
					if (key < array[current_location])
						{
						current_location -= current_height;
						current_height--;
						end_of_row -= current_height + 2;
						if (current_location < 0)
							return -1;
//std::cout << "    up:[h:" << current_height << ","<< current_location << "=" << array[current_location] << "]\n";
						}
					else if (key > array[current_location])
						{
						if (current_height == height || current_location + current_height + 2 >= elements)
							{
							current_location++;
							if (current_location > end_of_row)
								return -1;
//std::cout << "across:[h:" << current_height << "," << current_location << "=" << array[current_location] << "]\n";
							}
						else
							{
							current_location += current_height + 2;
							current_height++;
							end_of_row += current_height + 1;
							if (current_location > end_of_row)
								return -1;
//std::cout << "down :[h:" << current_height << ","<< current_location << "=" << array[current_location] << "]\n";
							}
						}
					else	// not greater and not less than (so must be equal to)
						return current_location;
					}
				while (1);

				return -1;
				}

			/*
				BEAP::BEAP_DOWN()
				-----------------
				push down the beap (towards the leaves)
			*/
			int64_t beap_down(int64_t current_location)
				{
				int64_t current_height = get_height(current_location);
				int64_t end_of_row = get_last(current_height);

				do
					{
					end_of_row += current_height + 2;
					int64_t child1 = current_location + current_height + 1;
					int64_t child2 = std::min(current_location + current_height + 2, end_of_row);

					if (child1 >= elements)
						return current_location;		// we're on the the row before a partial bottom row
					else if (array[current_location] > array[child1])
						{
						std::swap(array[current_location], array[child1]);
						current_location = child1;
						}
					else if (array[current_location] > array[child2])
						{
						std::swap(array[current_location], array[child1]);
						current_location = child2;
						}
					else
						return current_location;

					current_height++;
					}
				while (1);

				return -1;
				}

			/*
				BEAP::UNITTEST()
				----------------
			*/
			void unittest(void) const
				{
				assert(get_height(0) == 0);
				assert(get_first(0) == 0);
				assert(get_last(0) == 0);

				assert(get_height(3) == 2);
				assert(get_height(5) == 2);
				assert(get_first(2) == 3);
				assert(get_last(2) == 5);

				assert(get_height(406) == 28);
				assert(get_height(434) == 28);
				assert(get_first(28) == 406);
				assert(get_last(28) == 434);

				puts("unittest::PASS");
				}
		};

	/*
		OPERATOR<<()
		------------
	*/
	template <typename TYPE>
	static std::ostream &operator<<(std::ostream &stream, const bleap<TYPE> &object)
		{
		std::cout << "height :" << object.height << "\n";
		for (int64_t current_height = 0; current_height <= object.height; current_height++)
			{
			stream.width(2);
			stream << current_height << ":";
			for (int64_t element = object.get_first(current_height); element <= object.get_last(current_height); element++)
				{
				stream.width(2);
				if (element < object.elements)
					stream << object.array[element] << " ";
				}
			stream << "\n";
			}
		return stream;
		}
	}
