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

std::vector<std::vector<int>> matrixResult1;
std::vector<std::vector<int>> matrixResult2;

std::vector<std::thread> thread_pool;

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
	
	/*std::cout << "Matrix A:" << std::endl;
	for (size_t i = 0; i < countRows; ++i)
	{
		for (size_t j = 0; j < countCols; ++j)
		{
			std::cout << matrixA[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Matrix B:" << std::endl;
	for (size_t i = 0; i < countRows; ++i)
	{
		for (size_t j = 0; j < countCols; ++j)
		{
			std::cout << matrixB[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/
}

void multMatrix(std::vector<int> row_, std::vector<std::vector<int>>& matrixRes_)
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
	matrixRes_.push_back(multedRow);
}

void multWithoutThreads()
{
	for (size_t i = 0; i < countRows; ++i)
	{
		multMatrix(matrixA[i], matrixResult1);
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

void multInThreads()
{
	for (size_t i = 0; i < countRows; ++i)
	{
		thread_pool.push_back(std::thread(multMatrix, matrixA[i], std::ref(matrixResult2)));
		thread_pool[i].join();
	}
}

int main()
{
	initMatrix();
	
	time_t timeStart = time(NULL);
	multWithoutThreads();
	time_t timeEnd = time(NULL);
	std::cout << "Running time the 'multWithoutThreads' func is " << timeEnd - timeStart << " seconds" << std::endl;
	//printMatrixResult();

	timeStart = time(NULL);
	multInThreads();
	timeEnd = time(NULL);
	std::cout << "Running time the 'multInThreads' func is " << timeEnd - timeStart << " seconds" << std::endl;
	//printMatrixResult();

}