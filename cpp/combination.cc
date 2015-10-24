
#include <iostream>
#include <vector>
#include <forward_list>

void combinations(const unsigned int, const std::vector<int>&, std::forward_list<std::vector<int>>&);
void add_next(const unsigned int, const std::vector<int>&, std::vector<int>&, std::forward_list<std::vector<int>>&);

void combinations(const unsigned int dimension, const std::vector<int>& input, std::forward_list<std::vector<int>>& output)
{
	std::vector<int> current_output;
	add_next(dimension, input, current_output, output);
}

void add_next(const unsigned int dimension, const std::vector<int>& input, std::vector<int>& current_output, std::forward_list<std::vector<int>>& output)
{
	if(dimension == 0) {
		output.push_front(current_output);
	} else {
		for(unsigned int i = 0; i < input.size(); ++i) {
			current_output.push_back(input[i]);
			add_next(dimension - 1, input, current_output, output);
			current_output.pop_back();
		}
	}
}

int main()
{
    const unsigned int dimension = 3;
    std::vector<int> input(4);
    input[0] = 0;
    input[1] = 1;
    input[2] = 2;
    input[3] = 3;

		std::forward_list<std::vector<int>> output;
		combinations(3, input, output);
		for(auto it = output.begin(); it != output.end(); ++it) {
        for (unsigned int j = 0; j < dimension; ++j) {
            std::cout << (*it)[j];
        }
        std::cout << std::endl;
    }

	return 0;
}
