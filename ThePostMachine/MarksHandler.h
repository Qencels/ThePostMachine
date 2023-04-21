#pragma once
#include "Enums.h"
#include <vector>

namespace postMachine {
	namespace marksHandler {

		class EndlessBelt {

			private:

				static EndlessBelt* p_instance;

				EndlessBelt();
				EndlessBelt(const EndlessBelt& obj);

				static std::vector<long long int> positions; // marks positions
				static long long int car_pos; // carriage position

				//for delMark;
				static void swap(long long int& firstE, long long int& secondE); 

			public:

				static long long int find(long long int elem);
				static void clearValues();

				static void setMark(long long int pos);
				static void delMark(long long int pos);

				static void setCarriage(long long int pos);

				static std::vector<long long int>& getPositions();
				static long long int getCarPos();

				static EndlessBelt* getInstance();

		};

	}
}
