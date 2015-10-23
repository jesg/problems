
#include <iostream>
#include <vector>

void combinations(const unsigned int, const std::vector<int>&, const std::vector<std::vector<int>>&);
void add_next(const unsigned int, const std::vector<int>&, const std::vector<int>&, const std::vector<std::vector<int>>&);

void combinations(const unsigned int dimension, const std::vector<int> &input, const std::vector<std::vector<int>> &output)
{
	std::vector<int> current_output;
	add_next(dimension, input, current_output, output);
}

void add_next(const unsigned int dimension, const std::vector<int>& input, const std::vector<int>& current_output, const std::vector<std::vector<int>>& output)
{
	if(dimension == 0) {
		output.push_back(current_output);
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

		std::vector<std::vector<int>> output;
		combinations(3, input, output);
    for (unsigned int i = 0; i < output.size(); ++i) {
        for (unsigned int j = 0; j < dimension; ++j) {
            std::cout << output[i][j];
        }
        std::cout << std::endl;
    }

	return 0;
}
