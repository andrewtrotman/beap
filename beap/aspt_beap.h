/*
	ASPT_BEAP.H
	-----------
	see: https://pdf.sciencedirectassets.com/272574/1-s2.0-S0022000000X01043/1-s2.0-0022000080900379/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjEHMaCXVzLWVhc3QtMSJHMEUCIQDliCWRlWsdRlJzHrOJlYUKk%2B9Ltk4aEp0yUvsHjVR1kAIgbEDQ4ClLwEM0rlGc365TxqYZheprFGRnFY88FIvUaRwqvQMI%2FP%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARADGgwwNTkwMDM1NDY4NjUiDOpAeCnUnpQAfS2uLSqRA4Jv%2BvA76o5AWo7usKU6j1e3VSRmKAPZlgfkDyYQI99WmUXuOC57gy9SvwXVFILaDBkKDeqUY6OxQLpQxp0CgpijtTZgCfEC3f%2FWx4Loz2wujt8YB6CU1fvtLG8xzxzfAgYN0NzuJnF8RMDtAilX7JBC0SeG8Wx9leBwY98W59L8DXMuNI%2BKyOhNNSYgA2946AdplJZUwqksu5qURQrp7bSiGp%2F%2FWMzO9Up14cuwoUgK6X3eGE8%2BEepOsJiHfh7LEAfhAkSvlxojwzEoruijKdoI4TwjiFc%2BP%2B5NkBXV2OT%2BA4I1xOsVB3Dm6Ngd5G16dcADW%2BAL9UjLCf80RMgjHvC3rJxzmQ8mG7G%2FcROBgmcCJFrcqRx5meYiIQ34joUCAtfXhIjxxyrI2CtKwmOON6TOXOPW4enZsXkrDoQ6Pnc7H7tIMSf5gZifJOrtxmaXC%2FB6T8SkZJyEgSFIAmse0gPSlt15WVAhbEUKAkbCGp72fruPfsEEbfjlFdzp7B9fQi2UVcZ0%2FwvSkpRLPde0%2F752MOqv5fcFOusBC1dnzJeA65Jcr%2Fo1cMjTaO3FtG10q%2F%2FulB7tsxSFxVOpT1G1xeNlziXjevYGarSs39d0AXwCGhjL5LW08jiNVodr%2FoiCk4%2BPuK0U%2BzDFqo5bmloh6khchY63aRrG5Q3TQrTGdnjyWJxoX6qghoCXpUCqR0WgZ103zknHYE8VrTgDfXKy7qLNzfpqu3qkbdqXB6Pn9RMuGhSyZZiyvI0%2F%2FIuQeXYkCO2822mHp0vRl15XRk5D7FB8B4wFGK3ZKf6A013iJnNXfiTFc%2BEgcrU%2FTGHUsa0F1sGPZe76i9kReoFAw7ZAHQk9dVqYKw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20200629T032942Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYRYQE4VN3%2F20200629%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=178fdf2c8848e325b3900fc2513413cd2ed23bcfeb0d6891d8a5f1f3ed3425ed&hash=e777b46a59ee56aabb1e498e4dfd071c896d447f116d87e9b6847cbbdb94f140&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=0022000080900379&tid=spdf-9cb23011-e1e3-4914-a399-16f5225eeb21&sid=73ae443e4644b54cfa186f068b7536868cfagxrqa&type=client
*/
#include <iostream>
#include <algorithm>

namespace JASS
	{
	/*
		CLASS BEAP
		----------
	*/
	/*!
		@brief Bi-parental heap over a fixed length array (min-beap)
	*/
	template <typename TYPE>
	class beap
		{
		template <typename T>
		friend std::ostream &operator<<(std::ostream &into, const beap<T> &object);

		private:
			TYPE *array;					///< the array that is the beap
			int64_t elements;				///< elements in the beap
			int64_t height;				///< height of the beap

		public:

			/*
				BEAP::BEAP()
				------------
				min beap (the lowest value is at array[0]
			*/
			/*!
				@brief Constructor of min-beap (array[0] is the smallest element and values increase as you go down the tree).
				@param array [in] The array to use as the beap.  This is assumed to be pre-populated, full, and out of order
				@param elements [in] The number of elements in the array (and therefore the beap) to use
			*/
			beap(TYPE *array, int64_t elements):
				array(array),
				elements(elements),
				height(get_height(elements))
				{
				std::sort(array, array + elements);
				}

			/*
				BEAP::GET_HEIGHT()
				------------------
			*/
			/*!
				@brief Return the row number of the element array[element].  Counting from 0, so get_height(0) == 0, get_height(1) == 1, get_height(2) == 1, etc.
				@param element [in] The index into the array (counting from 0).
				@return The row of the tree that holds array[element].
			*/
			int64_t get_height(int64_t element) const
				{
				return ceil((sqrt(8 * element + 2) - 1) / 2) - 1;
				}

			/*
				BEAP::GET_FIRST()
				-----------------
			*/
			/*!
				@brief Return the first element of the row at the row given by height.  Both count from  0 (so get_first(0) == 0), get_first(1) == 1).
				@param height [in] The row number.
				@return The index into array[] of the first element of the row given by height.
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
			/*!
				@brief Return the last element of the row at the row given by height.  Both count from  0 ((so get_last(0) == 0), get_first(1) == 2))
				@param height [in] The row number.
				@return The index into array[] of the last element of the row given by height
			*/
			int64_t get_last(int64_t height) const
				{
				return (height + 1) * (height + 2) / 2 - 1;
				}
			/*
				BEAP::REPLACE()
				---------------
			*/
			/*!
				@brief Find and instance of old_key, replace it with new_key, and reshuffle the beap to maintain the beap property
				@param old_key [in] The old key (the one to find)
				@param new_key [in] The new key (an instance old_key is replaced by new_key).
				@return -1 if old_key cannot be found, or the index into array of the new location of new_key
			*/
			int64_t replace(const TYPE &old_key, const TYPE &new_key)
				{
				/*
					Find the old key
				*/
				int64_t location = find(old_key);
				if (location < 0)
					return -1;

				/*
					Rebuild the beap.
					Note that "array[location] = new_key" must happen after the  compare as old_key might be a reference to array[location]
				*/
				if (new_key < old_key)
					{
					array[location] = new_key;
					return beap_up(location);
					}
				else
					{
					array[location] = new_key;
					return beap_down(location);
					}
				}
				
			/*
				BEAP::ISBEAP()
				--------------
				return true if a beap else return false
			*/
			/*!
				@brief Check the beap to make sure it is, indeed, a beap.
				@return true if array[] is a beap, false otherwise.
			*/
			bool isbeap(void) const
				{
				int64_t end_of_row = 0;
				for (int64_t current_height = 0; current_height < height; current_height++)
					{
					end_of_row += get_last(current_height + 1);
					size_t end_of_current_row = get_last(current_height);
					for (int64_t current_location = get_first(current_height); current_location <= end_of_current_row; current_location++)
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
			/*!
				@brief Find an instance of key in the beap and return its index into array[].
				@param key [in] The key to look for.
				@return The index into array[] of an instance of key, or -1 if key cannot be found in the beap.
			*/
			int64_t find(const TYPE &key) const
				{
				/*
					Start in the bottom right corner of the beap
				*/
				int64_t current_height = height;
				int64_t current_location = get_first(height);
				int64_t end_of_row = get_last(height);

				do
					{
					if (key < array[current_location])
						{
						/*
							If key is less then the current location them move up one level of the beap
						*/
						current_location -= current_height;
						current_height--;
						end_of_row -= current_height + 2;
						if (current_location < 0)
							return -1;
						}
					else if (key > array[current_location])
						{
						/*
							If key is greater then either go down (if we can) or accoss (if we're on the bottom row)
						*/
						if (current_height == height || current_location + current_height + 2 >= elements)
							{
							/*
								Can't go down so go across
							*/
							current_location++;
							if (current_location > end_of_row)
								return -1;
							if (current_location >= elements)
								{
								/*
									In this case we can't go across because we're on the bottom row and have a partially full row that we're at the edge of, so
									the next largest value might be up and to the right (i.e. the bottom row of the previous full row).  In other words, the
									full row above are the leaves and we need to go across a leaf, but that leaf isn't on the bottom ro because bottom row isn't full.
								*/
								current_location -= current_height;
								current_height--;
								end_of_row -= current_height + 2;
								// in this case we went accross, but we went past the end of the array so we now need to go up
								}
							}
						else
							{
							/*
								Go down because we can.
							*/
							current_location += current_height + 2;
							current_height++;
							end_of_row += current_height + 1;
							if (current_location > end_of_row)
								return -1;
							}
						}
					else
						{
						/*
							Not less than and not greater than so we've found the key in the beap
						*/
						return current_location;
						}
					}
				while (1);

				return -1;
				}

			/*
				BEAP::BEAP_DOWN()
				-----------------
			*/
			/*!
				@brief Re-shuffle the beap from current_location towards the leaves.
				@param current_location [in] The locaiton to reshuffle from.
				@return The new location in array[] of the element that was at current_location.
			*/
			int64_t beap_down(int64_t current_location)
				{
				int64_t current_height = get_height(current_location);

				do
					{
					int64_t child1 = current_location + current_height + 1;
					int64_t child2 = current_location + current_height + 2;

					if (child1 >= elements)
						{
						/*
							On the second to last row, but the last row in incomplete, so we can't move down, so we're in the right place.
						*/
						return current_location;
						}
					else if (array[current_location] > array[child1])
						{
						/*
							Move down, swap with the largest child.
						*/
						if (child2 >= elements)
							{
							/*
								On the second to last row, but the last row in incomplete, so we can't move down, so we're in the right place.
							*/
							std::swap(array[current_location], array[child1]);
							return child1;
							}

						/*
							Swap with the smallest child
						*/
						if (array[child1] <= array[child2])
							{
							std::swap(array[current_location], array[child1]);
							current_location = child1;
							}
						else
							{
							std::swap(array[current_location], array[child2]);
							current_location = child2;
							}
						}
					else if (child2 < elements && array[current_location] > array[child2])
						{
						/*
							We're between child 1 and child 2
						*/
						std::swap(array[current_location], array[child2]);
						current_location = child2;
						}
					else
						{
						/*
							We're in the correct place
						*/
						return current_location;
						}

					current_height++;
					}
				while (1);

				return -1;		// cannot happen
				}

			/*
				BEAP::BEAP_UP()
				---------------
			*/
			/*!
				@brief Re-shuffle the beap from current_location towards the root.
				@param current_location [in] The locaiton to reshuffle from.
				@return The new location in array[] of the element that was at current_location.
			*/
			int64_t beap_up(int64_t current_location)
				{
				int64_t current_height = get_height(current_location);
				int64_t end_of_row = get_last(current_height);

				do
					{
					int64_t start_of_row = end_of_row - current_height;

					/*
						If we're at and edge then we only need to do a linear search, special handeling is done in left_push() and right_push()
					*/
					if (current_location == start_of_row)
						return left_push(current_location, current_height);
					else if (current_location == end_of_row)
						return right_push(current_location, current_height);
					else
						{
						/*
							We're in the middle of the tree
						*/
						int64_t parent1 = current_location - current_height - 1;
						int64_t parent2 = current_location - current_height;

						if (current_location <= 0)
							{
							/*
								We're at the root of the beap
							*/
							return 0;
							}
						else if (array[current_location] < array[parent1])
							{
							/*
								We need to shuffle up towards the root, so swap with the largest parent.
							*/
							if (array[parent1] >= array[parent2])
								{
								std::swap(array[current_location], array[parent1]);
								current_location = parent1;
								}
							else
								{
								std::swap(array[current_location], array[parent2]);
								current_location = parent2;
								}
							}
						else if (array[current_location] < array[parent2])
							{
							/*
								We're between each parent so swap with the largest parent.
							*/
							std::swap(array[current_location], array[parent2]);
							current_location = parent2;
							}
						else
							{
							/*
								Not smaller than either partnt so in the right place.
							*/
							return current_location;
							}
						}

					current_height--;
					end_of_row -= current_height + 2;
					}
				while (1);

				return -1;
				}

			/*
				BEAP::LEFT_PUSH()
				-----------------
				return the new location of the key in the array.
			*/
			/*!
				@brief Re-shuffle the beap from current_location towards the root, where current_location is on the left hand edge of the tree.
				@param current_location [in] The locaiton to reshuffle from.
				@param current_height [in] The row number of current_location.
				@return The new location in array[] of the element that was at current_location.
			*/
			int64_t left_push(int64_t current_location, int64_t current_height)
				{
				int64_t parent = current_location - current_height;

				while (current_height > 0 && array[current_location] <= array[parent])
					{
					std::swap(array[current_location], array[parent]);
					current_height--;
					current_location = parent;
					parent -= current_height;
					}
				return current_location;
				}

			/*
				BEAP::RIGHT_PUSH()
				------------------
				return the new location of the key in the array.
			*/
			/*!
				@brief Re-shuffle the beap from current_location towards the root, where current_location is on the right hand edge of the tree.
				@param current_location [in] The locaiton to reshuffle from.
				@param current_height [in] The row number of current_location.
				@return The new location in array[] of the element that was at current_location.
			*/
			int64_t right_push(int64_t current_location, int64_t current_height)
				{
				int64_t parent = current_location - current_height - 1;
				while (current_height > 0 && array[current_location] <= array[parent])
					{
					std::swap(array[current_location], array[parent]);
					current_height--;
					current_location = parent;
					parent -= current_height + 1;
					}
				return current_location;
				}


			/*
				BEAP::UNITTEST()
				----------------
			*/
			/*!
				@brief Unit test this class
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
	static std::ostream &operator<<(std::ostream &stream, const beap<TYPE> &object)
		{
		std::cout << "height :" << object.height << "\n";
		for (int64_t current_height = 0; current_height <= object.height; current_height++)
			{
			stream.width(3);
			stream << current_height << ":";
			for (int64_t element = object.get_first(current_height); element <= object.get_last(current_height); element++)
				{
				stream.width(3);
				if (element < object.elements)
					stream << object.array[element] << " ";
				}
			stream << "\n";
			}
		return stream;
		}
	}
