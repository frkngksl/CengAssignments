#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cassert>
#include "the3.h"


void printVector(std::vector<int>& array){

    std::cout << "size: " << array.size() << std::endl;
    for (unsigned i = 0; i < array.size(); ++i){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}




bool TestTask2()
{
  int n=6;
  int arr1[] = {0,0,0,3,0,2};
  int arr2[] = {0,0,3,0,2,0};
  int arr3[] = {0,3,0,0,0,0};
  int arr4[] = {3,0,0,0,0,4};
  int arr5[] = {0,2,0,0,0,0};
  int arr6[] = {2,0,0,4,0,0};
  int* edgeList1[] = {arr1,arr2,arr3,arr4,arr5,arr6};
  int ** edgeList = edgeList1;
  double scores[n];
  double *scores1 = scores;
    // time variables
  clock_t begin;
  clock_t end;
  double duration;
  int expectedTime = 500;
  int true_answer = 2;
  int solution = -1;

    // generate solution
  if ((begin = clock ()) == -1)
      std::cerr << "clock err" << std::endl;

  solution =Important(n, edgeList, scores1);


  if ((end = clock ()) == -1)
      std::cerr << "clock err" << std::endl;

  duration = ((double)end-begin) / CLOCKS_PER_SEC * 1000000;

  cout << "Elapsed time  " << duration << " vs " << expectedTime << " microsecs" << std::endl;

  for(int i=0;i<n;i++){
      cout << i <<". eleman " << scores[i] << endl;
  }
  return (solution == true_answer);
}



bool TestTask1()
{
  int n=5;
  int arr1[] = {0, 0, 2, 5, 3};
  int arr2[] = {0,0,0,2,3};
  int arr3[] = {2,0,0,1,0};
  int arr4[] = {5,2,1,0,4};
  int arr5[] = {3,3,0,4,0};
  int* edgeList1[] = {arr1,arr2,arr3,arr4,arr5};
  int ** edgeList = edgeList1;
  double scores[n] = {0};
  double *scores1 = scores;
    // time variables
  clock_t begin;
  clock_t end;
  double duration;
  int expectedTime = 500;
  int true_answer = 1;
  int solution = -1;

    // generate solution
  if ((begin = clock ()) == -1)
      std::cerr << "clock err" << std::endl;

  solution = Important(n, edgeList, scores1);


  if ((end = clock ()) == -1)
      std::cerr << "clock err" << std::endl;

  duration = ((double)end-begin) / CLOCKS_PER_SEC * 1000000;

  cout << "Elapsed time  " << duration << " vs " << expectedTime << " microsecs" << std::endl;

  for(int i=0;i<n;i++){
      cout << i << ". eleman " << scores[i] << endl;
  }
  return (solution == true_answer);
}





int main()
{
    srandom(time(0));       // no need to initialize second time

  if (TestTask1())
    std::cout << "PASSED TASK 1" << std::endl << std::endl;
  else
    std::cout << "FAILED TASK 1" << std::endl << std::endl;
  if (TestTask2())
    std::cout << "PASSED TASK 2" << std::endl << std::endl;
  else
    std::cout << "FAILED TASK 2" << std::endl << std::endl;

  return 0;
}
