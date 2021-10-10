/**
 * @file RefMandelCalculator.cc
 * @author Vojtech Mrazek (mrazek@fit.vutbr.cz)
 * @brief Naive implementation
 * @date 2021-09-24
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "RefMandelCalculator.h"

RefMandelCalculator::RefMandelCalculator(unsigned matrixBaseSize, unsigned limit) : BaseMandelCalculator(matrixBaseSize, limit, "RefMandelCalculator")
{
	data = (int *)(malloc(height * width * sizeof(int)));
}

RefMandelCalculator::~RefMandelCalculator()
{
	free(data);
	data = NULL;
}

template <typename T>
static inline int mandelbrot(T real, T imag, int limit)
{
	T zReal = real;
	T zImag = imag;

	for (int i = 0; i < limit; ++i)
	{
		T r2 = zReal * zReal;
		T i2 = zImag * zImag;

		std::cout << (r2 + i2) << " " << !!((r2 + i2) > 4.f) << "\t";
		break;

		if (r2 + i2 > 4.0f)
			return i;

		zImag = 2.0f * zReal * zImag + imag;
		zReal = r2 - i2 + real;
	}

	return limit;
}

int *RefMandelCalculator::calculateMandelbrot()
{
	int *pdata = data;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float x = x_start + j * dx; // current real value
			float y = y_start + i * dy; // current imaginary value

			int value = mandelbrot(x, y, limit);

			
			*(pdata++) = value;
		}

		std::cout << std::endl;
	}
	/*
	for (int i = 0; i < height; i++) {
		std::cout << std::dec << i << ":\t";

		for (int j = 0; j < width; j++)
			std::cout << std::dec << data[i * width + j] << " ";

		std::cout << std::endl;
	}
	*/
	return data;
}