#include "MarksHandler.h"

namespace postMachine {
	namespace marksHandler {

		std::vector<long long int> EndlessBelt::positions = { };
		long long int EndlessBelt::car_pos = 0;

		EndlessBelt::EndlessBelt() {}

		EndlessBelt* EndlessBelt::p_instance = nullptr;

		EndlessBelt* EndlessBelt::getInstance() {
			if (p_instance == nullptr) {
				p_instance = new EndlessBelt();
				return p_instance;
			}
			else {
				return p_instance;
			}
		}

		EndlessBelt::EndlessBelt(const EndlessBelt& obj) {}

		long long int EndlessBelt::find(long long int elem) {
			for (size_t i = 0; i < positions.size(); i++) {
				if (positions[i] == elem) return i;
			}
			return -1;
		}

		void EndlessBelt::swap(long long int& firstE, long long int& secondE) {
			long long int temp = firstE;
			firstE = secondE;
			secondE = temp;
		}

		void EndlessBelt::setMark(long long int pos) {
			if (find(pos) == -1) positions.push_back(pos);
		}

		void EndlessBelt::delMark(long long int pos) {
			size_t ind = find(pos);
			if (ind != -1) {
				swap(positions[ind], positions[positions.size()-1]);
				positions.pop_back();
				sortArr();
			}
		}

		void EndlessBelt::setCarriage(long long int pos) {
			car_pos = pos;
		}

		std::vector<long long int>& EndlessBelt::getPositions() {
			sortArr();
			return positions;
		}

		long long int EndlessBelt::getCarPos() {
			return car_pos;
		}

		void EndlessBelt::clearValues(){
			positions.clear();
			car_pos = 0;
		}

		void EndlessBelt::sortArr() {
			std::sort(positions.begin(), positions.end());
		}

	}
}