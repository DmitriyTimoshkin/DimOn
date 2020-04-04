#include <stdio.h> 
#include <time.h>
#include <cstddef>
#include <utility>
#include <iostream>
#include <list>
#include <chrono>
#include<vector>
using namespace std;

template<typename T>
void selection_sort(T A, const size_t N)
{
	for (size_t idx_i = 0; idx_i < N - 1; idx_i++)
	{
		size_t min_idx = idx_i;

		for (size_t idx_j = idx_i + 1; idx_j < N; idx_j++)
		{
			if (A[idx_j] < A[min_idx])
			{
				min_idx = idx_j;
			}
		}

		if (min_idx != idx_i)
		{
			std::swap(A[idx_i], A[min_idx]);
		}
	}
}
template <typename T>
void bubble_sort(T A,const size_t N)
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 2; j++)
		{
			if (A[j] > A[j + 1])
			{
				auto b = A[j];
				A[j] = A[j + 1];
				A[j + 1] = b;
			}
		}
	}
}
template<typename T>
void shell_sort(T array[], int length) 
{
	int h = 1;
	while (h < length / 3) 
	{
		h = 3 * h + 1;
	}
	while (h >= 1) 
	{
		for (int i = h; i < length; i++) 
		{
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) 
			{
				std::swap(array[j], array[j - h]);
			}
		}
		h = h / 3;
	}
}
template<typename T>
void quick_Sort(T A[], const size_t N) 
{
	int i = 0, j = N - 1; 
	auto mid = A[N / 2];
	do 
	{
		while (A[i] < mid)
			++i;
		while (A[j] > mid)
			--j;
		if (i <= j) 
		{
			std::swap(A[i], A[j]);
			++i;
			--j;
		}
	} 
	while (i <= j);
	if (j > 0)
		quick_Sort(A, j + 1);
	if (i < N)
		quick_Sort(A + i, N - i);
}

template <typename T>
void merge_Sort(std::vector<T>& v) 
{
	auto begin = std::chrono::steady_clock::now();

	// Данные:
	// s - Флаг перессылки (s = true - перессылка из области ОСНОВНОГО массива в область ДОБАВОЧНОГО МАССИВА, s = false - наоборот)
	// f - Флаг выхода из сортировки
	// N - Размер массива
	// i,j - начало и конец основного массива
	// k,l - начало и конец вспомогательного массива
	// d - Шаг, с которым ходит k (в зависимости от того, куда идет k)
	// ИСПОЛЬЗУЕТСЯ ВСПОМОГАТЕЛЬНЫЙ И ОСНОВНОЙ МАССИВ

	/*=================================
			Начальная установка
	=================================*/
	bool s = true;
	bool f;
	const int N = static_cast<int>(v.size());

	// Расширяем массив (добавляем дополнительный к основному)
	v.resize(static_cast<size_t>(N) * 2);


	int i, j, k, l, d;
	do {
		// ОСНОВНОЙ МАССИВ В НАЧАЛЕ
		if (s) {
			i = 0;
			j = N - 1;
			k = N;
			l = 2 * N - 1;
		}
		// ОСНОВНОЙ МАССИВ В КОНЦЕ
		else {
			k = 0;
			l = N - 1;
			i = N;
			j = 2 * N - 1;
		}

		d = 1; f = false;

		while (1) {

			// Если удобнее идти слева (массив же сортируется в порядке возрастания)
			if (v[i] <= v[j]) {
				// Если индексы совпали (последний элемент в доп массиве не заполнен)
				if (i == j)
				{
					// Заполняем последний элемент
					v[k] = v[i];
					// Меняем ОСНОВНОЙ массив на ВСПОМОГАТЕЛЬНЫЙ
					if (s)
						s = false;
					else
						s = true;
					break;
				}
				// Рассматриваем серии слева
				v[k] = v[i];
				k += d;
				++i;
				if (v[static_cast<size_t>(i) - 1] <= v[i]) continue;

				// Рассматриваем серии справа
				do {
					v[k] = v[j];
					k += d;
					--j;
				} while (v[static_cast<size_t>(j) + 1] <= v[j]);
			}
			// Если удобнее идти справа
			else {
				// Рассматриваем серии справа
				v[k] = v[j];
				k += d;
				--j;
				if (v[static_cast<size_t>(j) + 1] <= v[j]) continue;

				// Рассматриваем серии слева
				do {
					v[k] = v[i];
					k += d;
					++i;
				} while (v[static_cast<size_t>(i) - 1] <= v[i]);
			}
			f = true;
			// Меняем шаг
			d = d * (-1);
			std::swap(k, l);
		}
	} while (f);
	// Если отсортирован дополнительный массив (справа от основного), то пересылаем его в основной (слева)
	if (!s) {
		for (auto i = 0; i < N; ++i)
		{
			v[i] = v[static_cast<size_t>(i) + N];
		}
	}
	// Правая часть больше не нужна
	v.resize(N);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "The time: " << elapsed_ms.count() << " ms\n";
}




int main()
{
	int flag = 0;
	size_t size;
	do
	{
		srand(time(0));
		cout << "Enter size of array:";
		cin >> size;
		int* A = new int[size];
		int* B = new int[size];
		int* C = new int[size];
		int* D = new int[size];
		int* E = new int[size];
		for (int i = 0; i < size; i++)
		{
			A[i] = rand() % 20;
		}
		memcpy(B, A, sizeof(int) * size);
		memcpy(C, A, sizeof(int) * size);
		memcpy(D, A, sizeof(int) * size);
		memcpy(E, A, sizeof(int) * size);
		auto begi = std::chrono::steady_clock::now();
		selection_sort(A, size);
		auto en = std::chrono::steady_clock::now();
		auto elapsed_m = std::chrono::duration_cast<std::chrono::nanoseconds>(en - begi);
		std::cout << "The time: " << elapsed_m.count() << " ms\n";
		auto beg = std::chrono::steady_clock::now();
		bubble_sort(B, size);
		auto e = std::chrono::steady_clock::now();
		auto elapsed_ = std::chrono::duration_cast<std::chrono::nanoseconds>(e - beg);
		std::cout << "The time: " << elapsed_.count() << " ms\n";
		shell_sort(C,size);
		auto begin = std::chrono::steady_clock::now();
		quick_Sort(D, size);
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		std::cout << "The time: " << elapsed_ms.count() << " ms\n";
		//merge_Sort()
		cout << "\nDo you want to continue experement? 1-Y,0-N";
		cin >> flag;
	} while (flag==1);
}