
#include <iostream>
#include <vector>

void product(const std::vector<std::vector<int>*>& vecs, std::vector<std::vector<int>*> *result);
void product(const std::vector<std::vector<int>*>& vecs, std::vector<std::vector<int>*> *result) {
  std::vector<std::vector<int>*>* rslts;
  for (int ii = 0; ii < vecs.size(); ++ii) {
    const std::vector<int>& vec = *vecs[ii];
    if (ii == 0) {
      // vecs=[[1,2],...] ==> rslts=[[1],[2]]
      rslts = new std::vector<std::vector<int>*>;
      for (int jj = 0; jj < vec.size(); ++jj) {
        std::vector<int>* v = new std::vector<int>;
        v->push_back(vec[jj]);
        rslts->push_back(v);
      }
    } else {
      // vecs=[[1,2],[3,4],...] ==> rslts=[[1,3],[1,4],[2,3],[2,4]]
      std::vector<std::vector<int>*>* tmp = new std::vector<std::vector<int>*>;
      for (int jj = 0; jj < vec.size(); ++jj) {  // vec[jj]=3 (first iter jj=0)
        for (std::vector<std::vector<int>*>::const_iterator it = rslts->begin();
             it != rslts->end(); ++it) {
          std::vector<int>* v = new std::vector<int>(**it);       // v=[1]
          v->push_back(vec[jj]);                        // v=[1,3]
          tmp->push_back(v);                            // tmp=[[1,3]]
        }
      }
      for (int kk = 0; kk < rslts->size(); ++kk) {
        delete (*rslts)[kk];
      }
      delete rslts;
      rslts = tmp;
    }
  }
  result->insert(result->end(), rslts->begin(), rslts->end());
  delete rslts;
}

int main()
{
  int myints[] = {1,2,3};
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
  int myints2[] = {4,5};
  std::vector<int> sixth (myints2, myints2 + sizeof(myints2) / sizeof(int) );
	std::vector<std::vector<int>*> output;
	std::vector<std::vector<int>*> input;
	input.push_back(&fifth);
	input.push_back(&sixth);

	product(input, &output);
    for (unsigned int i = 0; i < output.size(); ++i) {
        for (unsigned int j = 0; j < input.size(); ++j) {
            std::cout << (*output[i])[j];
        }
        std::cout << std::endl;
    }
	return 0;
}
