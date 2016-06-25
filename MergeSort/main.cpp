#include<thread>
#include<iostream>
#include<vector>
#include<list>
#include<chrono>

#define COUNT 1000000

template<typename t>
std::vector<t> Mergesort(std::vector<t> toSort);
template<typename t>
std::vector<t> MergesortMT(std::vector<t> toSort);
int main()
{
	std::vector<int> test ;
	for (int i = 0;i < COUNT;i++)
		test.push_back(rand()+i);
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::vector<int> completeSorted = Mergesort(test);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long double> time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

	std::cout <<"Time to sort in nanoseconds: "<< time_span.count() << std::endl;
	getchar();

}

template<typename t>
void Divide(std::vector<t>& toDivide, std::vector<t>& part1, std::vector<t>& part2)
{
	int partlenght = toDivide.size() / 2;
	for (int i = 0;i < partlenght;i++)
	{
		part1.push_back(toDivide[i]);
	}
	for (int i = partlenght;i < toDivide.size();i++)
	{
		part2.push_back(toDivide[i]);
	}
}

template<typename t>
std::vector<t> Merge(std::vector<t> part1, std::vector<t> part2)
{
	std::vector<t> merged;

	int p2Iter = 0;
	int p1Iter = 0;
	while (p1Iter < part1.size())
	{
		if (p1Iter < part1.size() && p2Iter < part2.size())
		{
			if (part1[p1Iter] < part2[p2Iter])
			{
				merged.push_back(part1[p1Iter]);
				p1Iter++;
			}
			else
			{
				merged.push_back(part2[p2Iter]);
				p2Iter++;
			}
		}
		else
		{
			break;
		}
	}
	while (p1Iter < part1.size())
	{
		merged.push_back(part1[p1Iter]);
		p1Iter++;
	}
	while (p2Iter < part2.size())
	{
		merged.push_back(part2[p2Iter]);
		p2Iter++;
	}

	return merged;
}

template<typename t>
void Sort(std::vector<t>& toSort)
{
	if (toSort.size() > 2)
	{
		std::vector<t> part1;
		std::vector<t> part2;
		Divide(toSort, part1, part2);
		Sort(part1);
		Sort(part2);
		toSort = Merge(part1, part2);
	}
	else if (toSort.size() == 2)
	{
		if (toSort[0] > toSort[1]) {
			int temp = toSort[0];
			toSort[0] = toSort[1];
			toSort[1] = temp;
		}
	}
}

template<typename t>
std::vector<t> Mergesort(std::vector<t> toSort)
{
	if (toSort.size() > 2) {
		
		std::vector<t> part1;
		std::vector<t> part2;
		Divide(toSort, part1, part2);
		Sort(part1);
		Sort(part2);
		return Merge(part1, part2);
	}
	return toSort;
}

template<typename t>
std::vector<t> MergesortMT(std::vector<t> toSort)
{
	if (toSort.size() > 2) {
		std::vector<t> part1;
		std::vector<t> part2;
		Divide(toSort, part1, part2);
		std::thread t1(Sort<t>,part1);
		Sort(part2);
		t1.join();
		return Merge(part1, part2);
	}
	return toSort;
}