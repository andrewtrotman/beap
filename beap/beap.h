#ifndef CA_UWATERLOO_ALUMNI_DWHARDER_BEAP
#define CA_UWATERLOO_ALUMNI_DWHARDER_BEAP

#include <cassert>
#include <iostream>

// Author:  Douglas Wilhelm Harder
// Copyright (c) 2009 by Douglas Wilhelm Harder.  All rights reserved.
// Under construction....

namespace Data_structures {
	/****************************************************
	 * ************************************************ *
	 * *               Bi-parental Heap               * *
	 * ************************************************ *
	 ****************************************************/

	/****************************************************
	 * Bi-parental Heap (Beap)
	 *   class Beap<Type>
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-21
	 *
	 *  The concept of a bi-parental heap was first
	 *  described by Ian Munro and Hendra Suwanda.
	 *  Most operations are O(sqrt(n)) and consequently,
	 *  this class has been modified to ensure that
	 *  the unused memory is also O(sqrt(n)).
	 *
	 *  To Do: implement bool find( Type const & ) const
	 *                   void erase( Type const & )
	 ****************************************************/

	template <typename Type>
	class Beap {
		public:
			Beap( int = 3 );
			~Beap();
			Beap( Beap const & );
			Beap &operator=( Beap const & );

			bool empty() const;
			int size() const;
			int capacity() const;
			int height() const;
			Type top() const;
			Type back() const;
			bool find( Type const & ) const;
			int count( Type const & ) const;

			void push( Type const & );
			void erase( Type const & );
			void pop();
			void clear();

		private:
			int heap_height;
			int heap_size;
			int initial_capacity;
			int heap_capacity;
			Type *array;

			void left_push( Type const &, int, int );
			void right_push( Type const &, int, int );

			void increase_capacity();
			void decrease_capacity();

			static int first( int );
			static int last( int );

		template <typename T>
		friend std::ostream &operator<<( std::ostream &, const Beap<T> & );
	};

	/****************************************************
	 * ************************************************ *
	 * *         Bi-parental Heap Definitions         * *
	 * ************************************************ *
	 ****************************************************/

	/*
	 * Beap Constructor
	 *   Beap<Type> :: Beap( int h = 3 )
	 *
	 *  The argument is the default height of the allocated heap.
	 *  A heap is empty if the heap size is zero.
	 *  O(1)
	 */

	template <typename Type>
	Beap<Type>::Beap( int h ):
	heap_height( std::max( 0, h ) ),
	heap_size( 0 ),
	initial_capacity( (height() + 1)*(height() + 2)/2 ),
	heap_capacity( initial_capacity ),
	array( new Type[capacity()] ) {
		// Empty constructor
	}

	/*
	 * Beap Desstructor
	 *   Beap<Type> :: ~Beap()
	 *
	 *  Delete the memory allocated for the array.
	 *  O(1)
	 */

	template <typename Type>
	Beap<Type>::~Beap() {
		delete [] array;
	}

	/*
	 * Beap Copy Constructor
	 *   Beap<Type> :: Beap( int h = 3 )
	 *
	 *  Just use the assignment operator.
	 *  O(n)
	 */

	template <typename Type>
	Beap<Type>::Beap( Beap const &beap ):
	heap_height( 0 ),
	heap_size( 0 ),
	initial_capacity( 0 ),
	heap_capacity( 0 ),
	array( 0 ) {
		*this = beap;
	}

	/*
	 * Assignment Operator
	 *   Beap<Type> &Beap<Type> :: operator=( Beap const & )
	 *
	 *  Just use the assignment operator.
	 *  O(n)
	 */

	template <typename Type>
	Beap<Type> &Beap<Type>::operator=( Beap const &rhs ) {
		if ( this == &rhs ) {
			return *this;
		}

		if ( capacity() != rhs.capacity() ) {
			delete [] array;
			array = new Type[rhs.capacity()];
		}

		for ( int i = 0; i < rhs.size(); ++i ) {
			array[i] = rhs.array[i];
		}

		heap_height = rhs.heap_height;
		heap_size = rhs.heap_size;
		initial_capacity = rhs.initial_capacity;
		heap_capacity = rhs.heap_capacity;
	}

	/*
	 * Heap Empty Query
	 *   bool Beap<Type> :: empty() const
	 *
	 *  A heap is empty if the heap size is zero.
	 *  O(1)
	 */

	template <typename Type>
	bool Beap<Type>::empty() const {
		return heap_size == 0;
	}

	/*
	 * Heap Size
	 *   int Beap<Type> :: size() const
	 *
	 *  The number of objects is stored in the
	 *  member variable 'heap_size'.
	 *  O(1)
	 */

	template <typename Type>
	int Beap<Type>::size() const {
		return heap_size;
	}

	/*
	 * Heap Capacity
	 *   int Beap<Type> :: capacity() const
	 *
	 *  The size of the array is stored in the
	 *  member variable 'heap_capacity'.
	 *  O(1)
	 */

	template <typename Type>
	int Beap<Type>::capacity() const {
		return heap_capacity;
	}

	/*
	 * Heap Height
	 *   int Beap<Type> :: height() const
	 *
	 *  The height of the heap is stored in the
	 *  member variable 'heap_capacity'.
	 *  O(1)
	 */

	template <typename Type>
	int Beap<Type>::height() const {
		return heap_height;
	}

	/*
	 * Top of the Heap
	 *   Type Beap<Type> :: top() const
	 *
	 *  The object at the top of the heap stored
	 *  in array[0].
	 *  O(1)
	 */

	template <typename Type>
	Type Beap<Type>::top() const {
		if ( empty() ) {
			return Type();
		}

		return array[0];
	}

	/*
	 * Back of the Heap
	 *   Type Beap<Type> :: back() const
	 *
	 *  The object at the back of the heap.
	 *  O(sqrt(n))
	 */

	template <typename Type>
	Type Beap<Type>::back() const {
		if ( empty() ) {
			return Type();
		}

		Type max = array[size() - height() - 2];

		for ( int i = size() - height() - 1; i < size(); ++i ) {
			if ( array[i] > max ) {
				max = array[i];
			}
		}

		return max;
	}

	/*
	 * Find an Type in the Heap
	 *   bool Beap<Type> :: find( Type const &obj ) const
	 *
	 *  Determine if the argument is in the heap.
	 *  Starting at the bottom left corner, continue moving:
	 *    - Up and to the right if obj < what is stored there, and
	 *    - Down and to the right if obj > what is stored there.
	 *
	 *  In the last case, if we are on the bottom row, we have
	 *  to move across or even across and up and to the right.
	 *  O(sqrt(n))
	 */

	template <typename Type>
	bool Beap<Type>::find( Type const &obj ) const {
		if ( empty() ) {
			return false;
		}

		// Starting at the bottom left,
		//   If the object is less than

		int h = height();
		int posn = h*(h + 1)/2;

		while ( true ) {
			if ( array[posn] < obj ) {
				// Move down and to the right
				//
				//           x
				//         x   x
				//      < a  x   x
				//     x   *   x   x
				//   x   x   x   x   x

				if ( posn == (height() + 1)*(height() + 2)/2 - 1 ) {
					return false;
				}

				if ( posn == height()*(height() + 1)/2 - 1 && size() != (height() + 1)*(height() + 2)/2 ) {
					return false;
				}

				if ( posn + h + 2 < size() ) {
					// Move down to the right
					posn += h + 2;
					++h;
				} else {
					// Move across to the right
					++posn;

					// Move up to the right
					if ( posn == size() ) {
						posn -= h;
						--h;
					}
				}
			} else if ( array[posn] > obj ) {
				// Move down and to the right
				//
				//           x
				//         *   x
				//      > a  x   x
				//     x   x   x   x
				//   x   x   x   x   x

				if ( posn == (h + 1)*(h + 2)/2 - 1 ) {
					return false;
				} else {
					posn -= h;
					--h;
				}
			} else {
				return true;
			}
		}
	}

	/*
	 * Cont the number of occurances of Type in the Heap
	 *   int Beap<Type> :: count( Type const &obj ) const
	 *
	 *  Determine the number of occurances of the object in the heap.
	 *  Starting at the bottom left corner, continue moving:
	 *    - Up and to the right if obj < what is stored there, and
	 *    - Down and to the right if obj > what is stored there.
	 *
	 *  In the last case, if we are on the bottom row, we have
	 *  to move across or even across and up and to the right.
	 *  O(sqrt(n))
	 */

	template <typename Type>
	int Beap<Type>::count( Type const &obj ) const {
		if ( empty() ) {
			return 0;
		}

		// Starting at the bottom left,
		//   If the object is less than

		int object_count = 0;
		int h = height();
		int posn = h*(h + 1)/2;

		while ( true ) {
			if ( obj >= array[posn] ) {
				if ( obj == array[posn] ) {
					int pt = posn;
					int ht = h;

					while ( obj == array[pt] ) {
						++object_count;

						if ( pt == (ht + 1)*(ht + 2)/2 - 1 ) {
							break;
						}

						pt -= ht;
						--ht;
					}
				}

				if ( posn == (height() + 1)*(height() + 2)/2 - 1 ) {
					break;
				}

				if ( posn == height()*(height() + 1)/2 - 1 && size() != (height() + 1)*(height() + 2)/2 ) {
					break;
				}

				if ( posn + h + 2 < size() ) {
					// Move down to the right
					posn += h + 2;
					++h;
				} else {
					// Move across to the right
					++posn;

					// Move up to the right
					if ( posn == size() ) {
						posn -= h;
						--h;
					}
				}
			} else if ( obj < array[posn] ) {
				if ( posn == (h + 1)*(h + 2)/2 - 1 ) {
					break;
				} else {
					posn -= h;
					--h;
				}
			}
		}

		return object_count;
	}

	/*
	 * Heap Push
	 *   void Beap<Type> :: push( Type const & )
	 *
	 *  Push a new object onto the heap by assuming it
	 *  is located in the next available location in the
	 *  array and percolating it up the heap by swapping
	 *  it with that parent which is both larger than
	 *  it and largest.
	 *  O(sqrt(n))
	 */

	template <typename Type>
	void Beap<Type>::push( Type const &obj ) {
		// If the heap is empty, just place the object
		// in the first location and reutrn.

		if ( empty() ) {
			array[0] = obj;
			heap_size = 1;
			heap_height = 0;

			return;
		}

		// Update the heap size and, if necessary,
		// the heap height and capacity.

		int posn = heap_size;

		if ( posn == first( height() + 1 ) ) {
			++heap_height;

			if ( size() == capacity() ) {
				increase_capacity();
			}
		}

		++heap_size;

		// Initially assume that the new object goes into
		// the next available location in the array
		// and move up the heap determining which is the
		// largest between the newly-inserted object
		// and its two parents.

		for ( int h = heap_height; h >= 2; --h ) {
			if ( posn == first( h ) ) {
				return left_push( obj, posn, h );
			} else if ( posn == last( h ) ) {
				return right_push( obj, posn, h );
			} else {
				// Percolate up the centre
				//
				//           x
				//         x   x
				//       x   x   x
				//     x   *   *   x
				//   x   x   *   x   x
				//
				// Swap with the largest parent if larger;
				// otherwise, store the object and return.

				int left_parent  = posn - h - 1;
				int right_parent = posn - h;

				if ( obj < array[left_parent] && array[left_parent] > array[right_parent] ) {
					array[posn] = array[left_parent];
					posn = left_parent;
				} else if ( obj < array[right_parent] ) {
					array[posn] = array[right_parent];
					posn = right_parent;
				} else {
					array[posn] = obj;
					return;
				}
			}
		}

		if ( obj < array[0] ) {
			array[posn] = array[0];
			array[0] = obj;
		} else {
			array[posn] = obj;
		}
	}

	/*
	 * Percolate up the left edge of the heap
	 *   void Beap<Type> :: push_left( obj, posn, height )
	 *
	 *  Percolate up the left edge
	 *
	 *           *
	 *         *   x
	 *       *   x   x
	 *     *   x   x   x
	 *   *   x   x   x   x   <- height
	 *
	 *  Swap if the parent is greater;
	 *  otherwise, store the object and return.
	 *  O(sqrt(n))
	 */

	template <typename Type>
	void Beap<Type>::left_push( Type const &obj, int posn, int height ) {
		assert( posn == first( height ) );

		for ( int h = height; h >= 1; --h ) {
			int parent = posn - h;

			if ( obj < array[parent] ) {
				array[posn] = array[parent];
				posn = parent;
			} else {
				array[posn] = obj;
				return;
			}
		}

		array[posn] = obj;
	}

	/*
	 * Percolate up the right edge of the heap
	 *   void Beap<Type> :: push_right( obj, posn, height )
	 *
	 *  Percolate up the right edge
	 *
	 *           *
	 *         x   *
	 *       x   x   *
	 *     x   x   x   *
	 *   x   x   x   x   *   <- height
	 *
	 *  Swap if the parent is greater;
	 *  otherwise, store the object and return.
	 *  O(sqrt(n))
	 */

	template <typename Type>
	void Beap<Type>::right_push( Type const &obj, int posn, int height ) {
		assert( posn == last( height ) );

		for ( int h = height; h >= 1; --h ) {
			int parent = posn - h - 1;

			if ( obj < array[parent] ) {
				array[posn] = array[parent];
				posn = parent;
			} else {
				array[posn] = obj;
				return;
			}
		}

		array[posn] = obj;
	}

	template <typename Type>
	void Beap<Type>::pop() {
		// If empty, simply return.

		if ( empty() ) {
			return;
		}

		// If the heap size is one, just reset the appropriate
		// member variables.

		if ( size() == 1 ) {
			heap_size = 0;
			heap_height = -1;
			return;
		}

		// Shrink the height of the heap if necessary.

		--heap_size;

		if ( heap_size == first( height() ) ) {
			--heap_height;

			if ( (height() + 3)*(height() + 4)/2 == capacity() && capacity() > initial_capacity ) {
				decrease_capacity();
			}
		}

		// Assume the last object (array[posn]) fits in the
		// root and percolate down until it fits.

		int posn = 0;

		for ( int h = 0; h < height() - 1; ++h ) {
			int left  = posn + h + 1;
			int right = posn + h + 2;

			if (
				array[left] < array[right] &&
				array[left] < array[size()]
			) {
				array[posn] = array[left];
				posn = left;
			} else if ( array[right] < array[size()] ) {
				array[posn] = array[right];
				posn = right;
			} else {
				array[posn] = array[size()];
				return;
			}
		}

		// We must be careful with the last row, as there are
		// three possible cases:
		//   Both children are in the heap,
		//   Only the left child is in the heap,  or
		//   Neither child is in the heap.

		int left  = posn + height();
		int right = left + 1;

		if ( right < size() ) {
			if (
				array[right] < array[left] &&
				array[right] < array[size()]
			) {
				array[posn] = array[right];
				array[right] = array[size()];
				return;
			}
		}

		if ( left < size() ) {
			if ( array[left]  < array[size()] ) {
				array[posn] = array[left];
				array[left] = array[size()];
				return;
			}
		}

		array[posn] = array[size()];
	}

	/*
	 * Clear the Beap
	 *   void Beap<Type> :: clear()
	 *
	 *  Add another row to the heap and copy all objects over.
	 *  O(1)
	 */

	template <typename Type>
	void Beap<Type>::clear() {
		heap_size = 0;
		heap_height = -1;
	}

	/****************************************************
	 * ************************************************ *
	 * *     Private Bi-parental Heap Definitions     * *
	 * ************************************************ *
	 ****************************************************/

	/*
	 * Increase the Heap Capacity
	 *   void Beap<Type> :: increase_capacity()
	 *
	 *  Add another row to the heap and copy all objects over.
	 *  The maximum unused space is O(sqrt(n)), and
	 *  the amortized copies per push is O(sqrt(n)).
	 *  As insertion is already O(sqrt(n)), this makes no difference.
	 *  O(n)
	 */

	template <typename Type>
	void Beap<Type>::increase_capacity() {
		int new_capacity = (height() + 2)*(height() + 3)/2;
		Type *new_array = new Type[new_capacity];

		for ( int i = 0; i < size(); ++i ) {
			new_array[i] = array[i];
		}

		delete [] array;
		heap_capacity = new_capacity;
		array = new_array;
	}

	/*
	 * Decrease the Heap Capacity
	 *   void Beap<Type> :: decrease_capacity()
	 *
	 *  Remove a row from the heap and copy all objects over.
	 *  The maximum unused space is O(sqrt(n)), and
	 *  the amortized copies per pop is O(sqrt(n)).
	 *  As pop is already O(sqrt(n)), this makes no difference.
	 */

	template <typename Type>
	void Beap<Type>::decrease_capacity() {
		int new_capacity = (height() + 2)*(height() + 3)/2;
		Type *new_array = new Type[new_capacity];

		for ( int i = 0; i <= size(); ++i ) {
			new_array[i] = array[i];
		}

		delete [] array;
		heap_capacity = new_capacity;
		array = new_array;
	}

	/*
	 * First Entry of a Row of the Heap
	 *   static int Beap<Type> :: first( int h )
	 *
	 *  Returns the location that the first entry of the
	 *  array for height h.
	 */

	template <typename Type>
	int Beap<Type>::first( int h ) {
		return h*(h + 1)/2;
	}

	/*
	 * Last Entry of a Row of the Heap
	 *   static int Beap<Type> :: last( int h )
	 *
	 *  Returns the location that the last entry of the
	 *  array for height h.
	 */

	template <typename Type>
	int Beap<Type>::last( int h ) {
		return (h + 1)*(h + 2)/2 - 1;
	}

	/****************************************************
	 * ************************************************ *
	 * *                   Friends                    * *
	 * ************************************************ *
	 ****************************************************/

	/*********************************************************************
	 * out << beap;
	 *
	 *  Print the bi-parental heap in the following format:
	 *
         *    Size:     15
         *    Capacity: 21
         *    Height:   4
         *    Empty:    0
         *    Top:      0
         *
         *            0
         *            3       1
         *            8       5       2
         *            10      9       7       4
         *            13      11      14      12      6
	 *
	 *********************************************************************/

	template <typename Type>
	std::ostream &operator<<( std::ostream &out, const Beap<Type> &beap ) {
		out << "Size:     " << beap.size() << std::endl;
		out << "Capacity: " << beap.capacity() << std::endl;
		out << "Height:   " << beap.height() << std::endl;
		out << "Empty:    " << beap.empty() << std::endl;
		out << "Top:      " << beap.top() << std::endl << std::endl;

		if ( beap.empty() ) {
			return out;
		}

		int i = 0;

		for ( int j = 1; true; ++j ) {
			for ( int k = 0; k < j; ++k ) {
				out << '\t' << beap.array[i];
				++i;

				if ( i == beap.size() ) {
					out << std::endl;
					return out;
				}
			}

			out << std::endl;
		}
	}
}

#endif
