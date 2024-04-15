#pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <time.h>
#include <functional>

size_t countRows = 2000;
size_t countCols = 2000;
int randomSize = 10;

std::vector<std::vector<int>> matrixA;
std::vector<std::vector<int>> matrixB;

std::vector<std::vector<int>> matrixResult1(countCols);
std::vector<std::vector<int>> matrixResult2(countCols);

void initMatrix()
{
	std::srand(time(NULL));
	for (size_t i = 0; i < countRows; ++i)
	{
		std::vector<int> randomVectorA(countCols, 0);
		std::vector<int> randomVectorB(countCols, 0);
		for (size_t j = 0; j < countRows; ++j)
		{
			randomVectorA[j] = 1 + rand() % randomSize;
			randomVectorB[j] = 1 + rand() % randomSize;
		}
		matrixA.push_back(randomVectorA);
		matrixB.push_back(randomVectorB);
	}
}

void multMatrix(std::vector<int> row_, std::vector<std::vector<int>>& matrixRes_, int index_)
{
	std::vector<int> multedRow(countCols, 0);
	for (size_t i = 0; i < countRows; ++i)
	{
		int sum = 0;
		for (size_t j = 0; j < countCols; ++j)
		{
			sum += row_[j] * matrixB[j][i];
		}
		multedRow[i] = sum;
	}
	matrixRes_[index_] = multedRow;
}

void multWithoutThreads()
{
	for (size_t i = 0; i < countRows; ++i)
	{
		multMatrix(matrixA[i], matrixResult1, i);
	}
}

void printMatrix(const std::vector<std::vector<int>>& matrixToPrint_, const std::string message_ = "")
{
	std::cout << message_ << std::endl;
	for (size_t i = 0; i < countRows; ++i)
	{
		for (size_t j = 0; j < countCols; ++j)
		{
			std::cout << matrixToPrint_[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void multingThread(int indexRow, int countRows)
{
	int diff = matrixResult2.size() - indexRow;
	if (diff < countRows)
		countRows = diff;
	for (int i = 0; i < countRows; i++)
	{
		multMatrix(matrixA[indexRow + i], matrixResult2, indexRow + i);
	}
}

void multInThreads()
{
	int multSize = sqrt(countRows);
	int countThreads = countRows / multSize + 1;
	std::vector<std::thread> thread_pool(countThreads);
	for (size_t i = 0; i < countThreads; ++i)
	{
		thread_pool[i] = (std::thread(multingThread, i*multSize, multSize));
	}

	for (size_t i = 0; i < countThreads; ++i)
	{
		thread_pool[i].join();
	}

}

int main()
{
	initMatrix();

	time_t timeStart = time(NULL);
	//multWithoutThreads();
	time_t timeEnd = time(NULL);
	std::cout << "Running time the 'multWithoutThreads' func is " << double(timeEnd - timeStart) << " seconds" << std::endl;
	//printMatrix(matrixResult1, std::string("Matrix Result 1: "));

	timeStart = time(NULL);
	multInThreads();
	timeEnd = time(NULL);
	std::cout << "Running time the 'multInThreads' func is " << double(timeEnd - timeStart) << " seconds" << std::endl;
	//printMatrix(matrixResult2, std::string("Matrix Result 2: "));

}
