// Тестовое задание для поступающих в школу разработки Heads x Hands

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <iomanip>
#include <cmath>

using namespace std;


//	Алгоритм бинарного поиска
bool binarySearch(unsigned short *arr, unsigned short l_bound, unsigned short r_bound, unsigned short key) {
	bool elem_is_founded = true;
	unsigned short mid_bound = 0;
	while (true) {
		mid_bound = (int)((l_bound + r_bound) / 2);
		if (key < arr[mid_bound]) r_bound = mid_bound - 1;
		else if (key > arr[mid_bound]) l_bound = mid_bound + 1;
		else return elem_is_founded;
		if (l_bound > r_bound) {
			elem_is_founded = false;
			return elem_is_founded;
		}
	}
}


template <typename T1>
//	Алгоритм сортировки вставками
void insertionSort(T1 *arr, unsigned short size, bool is_direct_order) {
	T1 x;
	short i, prev_elem_ind;
	//	Сортировка по возрастанию
	if (is_direct_order == true) {
		for (i = 0; i < size; i++) {
			x = arr[i];
			prev_elem_ind = i - 1;
			while (prev_elem_ind >= 0 && arr[prev_elem_ind] > x) {
				arr[prev_elem_ind + 1] = arr[prev_elem_ind];
				arr[prev_elem_ind] = x;
				prev_elem_ind--;
			}
		}
	}
	// Сортировка по убыванию
	else {
		for (i = 0; i < size; i++) {
			x = arr[i];
			prev_elem_ind = i - 1;
			while (prev_elem_ind >= 0 && arr[prev_elem_ind] < x) {
				arr[prev_elem_ind + 1] = arr[prev_elem_ind];
				arr[prev_elem_ind] = x;
				prev_elem_ind--;
			}
		}
	}
}


template <typename T2>
//	Алгоритм быстрой сортировки
void quickSort(T2 *arr, unsigned short l_bound, unsigned short r_bound, bool is_direct_order) {
	//	Сортировка по возрастанию
	if (is_direct_order == true) {
		unsigned short l_b_holded = l_bound;
		unsigned short r_b_holded = r_bound;
		T2 pivot_elem = arr[l_bound];
		while (l_bound < r_bound) {
			while ((arr[r_bound] >= pivot_elem) && (l_bound < r_bound)) r_bound--;
			if (l_bound != r_bound) {
				arr[l_bound] = arr[r_bound];
				l_bound++;
			}
			while ((arr[l_bound] <= pivot_elem) && (l_bound < r_bound)) l_bound++;
			if (l_bound != r_bound) {
				arr[r_bound] = arr[l_bound];
				r_bound--;
			}
		}
		arr[l_bound] = pivot_elem;
		unsigned short p_bound = l_bound;
		l_bound = l_b_holded;
		r_bound = r_b_holded;
		if (l_bound < p_bound) quickSort(arr, l_bound, p_bound - 1, is_direct_order);
		if (r_bound > p_bound) quickSort(arr, p_bound + 1, r_bound, is_direct_order);
	}
	// Сортировка по убыванию
	else {
		unsigned short l_b_holded = l_bound;
		unsigned short r_b_holded = r_bound;
		T2 pivot_elem = arr[l_bound];
		while (l_bound < r_bound) {
			while ((arr[r_bound] <= pivot_elem) && (l_bound < r_bound)) r_bound--;
			if (l_bound != r_bound) {
				arr[l_bound] = arr[r_bound];
				l_bound++;
			}
			while ((arr[l_bound] >= pivot_elem) && (l_bound < r_bound)) l_bound++;
			if (l_bound != r_bound) {
				arr[r_bound] = arr[l_bound];
				r_bound--;
			}
		}
		arr[l_bound] = pivot_elem;
		unsigned short p_bound = l_bound;
		l_bound = l_b_holded;
		r_bound = r_b_holded;
		if (l_bound < p_bound) quickSort(arr, l_bound, p_bound - 1, is_direct_order);
		if (r_bound > p_bound) quickSort(arr, p_bound + 1, r_bound, is_direct_order);
	}
}


//	Функция добавления очередного размера в массив размеров массивов (работает через quick sort)
void addIntoSizeArrayQuickSort(unsigned short &size, unsigned short *arr_used_sizes, unsigned short &n, unsigned short &size_limit) {
	bool elem_is_founded = binarySearch(arr_used_sizes, 0, n - 1, size);
	if (elem_is_founded == true) {
		while (elem_is_founded) {
			size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			while (size == 0) {
				size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			}
			elem_is_founded = binarySearch(arr_used_sizes, 0, n - 1, size);
		}
	}
	if (elem_is_founded == false) {
		arr_used_sizes[0] = size;
		quickSort(arr_used_sizes, 0, n - 1, true);
	}
}


//	Функция добавления очередного размера в массив размеров массивов (работает через insertion sort)
void addIntoSizeArrayInsertionSort(unsigned short &size, unsigned short *arr_used_sizes, unsigned short &n, unsigned short &size_limit) {
	bool elem_is_founded = binarySearch(arr_used_sizes, 0, n - 1, size);
	if (elem_is_founded == true) {
		while (elem_is_founded) {
			size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			while (size == 0) {
				size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			}
			elem_is_founded = binarySearch(arr_used_sizes, 0, n - 1, size);
		}
	}
	if (elem_is_founded == false) {
		arr_used_sizes[0] = size;
		insertionSort(arr_used_sizes, n, true);
	}
}


//	Функция, генерирующая случайные массивы
double** generateRandomArrays(unsigned short n, bool show_result, unsigned short size_limit) {
	double **arr;
	unsigned short *arr_used_sizes_sorted, *arr_used_sizes_in_order;
	arr = new double*[n];

	//	Отсортированный по возрастанию массив размеров (для облегчения проверки на повторение)
	arr_used_sizes_sorted = new unsigned short[n];
	//	Массив размеров в порядке добавления (нужно для сортировки массивов случайных чисел)
	arr_used_sizes_in_order = new unsigned short[n];
	for (unsigned short i = 0; i < n; i++) {
		arr_used_sizes_sorted[i] = 0;
		arr_used_sizes_in_order[i] = 0;
	}

	//	Если число массивов в массиве больше 3000, то используем сортировку вставками, чтобы избежать переполнения стека
	if (n>3000) {
		for (unsigned short i = 0; i < n; i++) {
			unsigned short size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			while (size == 0) {
				size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			}

			//	Добавление в массив размеров + сортировка
			addIntoSizeArrayInsertionSort(size, arr_used_sizes_sorted, n, size_limit);
			arr[i] = new double[size];
			arr_used_sizes_in_order[i] = size;

			//	Заполнение массивов в основном массиве случайными вещественными числами
			for (unsigned short j = 0; j < size; j++) {
				arr[i][j] = (double)rand() + (double)rand() / RAND_MAX;
			}
		}

		//	Сортировка внутри массивов
		for (unsigned short i = 0; i < n; i++) {
			// Считаем, что нумерация массивов начинается с 1 (т.е. 'нулевой' массив - нечётный)
			if (i % 2 == 0) {
				insertionSort(arr[i], arr_used_sizes_in_order[i], false);
			}
			else {
				insertionSort(arr[i], arr_used_sizes_in_order[i], true);
			}
		}
	}
	//	Иначе используем быструю сортировку
	else {
		for (unsigned short i = 0; i < n; i++) {
			unsigned short size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			while (size == 0) {
				size = (unsigned short)(rand() * (1.0 / ((double)(RAND_MAX)+1.0)) * size_limit + 1);
			}

			//	Добавление в массив размеров + сортировка
			addIntoSizeArrayQuickSort(size, arr_used_sizes_sorted, n, size_limit);
			arr[i] = new double[size];
			arr_used_sizes_in_order[i] = size;

			//	Заполнение массивов в основном массиве случайными вещественными числами
			for (unsigned short j = 0; j < size; j++) {
				arr[i][j] = (double)rand() + (double)rand() / RAND_MAX;
			}
		}

		//	Сортировка внутри массивов
		for (unsigned short i = 0; i < n; i++) {
			// Считаем, что нумерация массивов начинается с 1 (т.е. 'нулевой' массив - нечётный)
			if (i % 2 == 0) {
				quickSort(arr[i], 0, arr_used_sizes_in_order[i] - 1, false);
			}
			else {
				quickSort(arr[i], 0, arr_used_sizes_in_order[i] - 1, true);
			}
		}
	}

	//	Вывод результата в файл
	ofstream res_file("result.txt", ios::out);
	if (res_file.is_open()) {
		for (unsigned short i = 0; i < n; i++) {
			for (unsigned short j = 0; j < arr_used_sizes_in_order[i]; j++) {
				res_file.width(15);
				res_file << std::fixed << std::setprecision(6) << arr[i][j];
			}
			res_file << endl << endl;
		}
	}
	else {
		cout << "File can't be opened!" << endl;
	}
	res_file.close();

	//	Вывод результата на экран консоли
	if (show_result == true) {
		for (unsigned short i = 0; i < n; i++) {
			for (unsigned short j = 0; j < arr_used_sizes_in_order[i]; j++) {
				printf("%15.6f", arr[i][j]);
			}
			cout << endl << endl;
		}
	}

	//	Очистка памяти
	delete[] arr_used_sizes_sorted, arr_used_sizes_in_order;
	return arr;
}

int main() {
	double eps = 1.e-18;
	float n;
	unsigned short int_part;
	double **result_arr;
	bool do_size_limit;
	char h;	//вспомогательная переменная

	srand((unsigned)time(NULL));
	cout << "Enter natural number n (we recommend you try n less than 3000, otherwise program will work slowly...): ";
	cin >> n;
	int_part = (int)n;
	while ((n <= 0) || (n > RAND_MAX) || (abs(n-int_part)>eps)) {
		cout << "n must be natural number less than 32767, please, try again..." << endl;
		cout << "Enter natural number n: ";
		cin >> n;
		int_part = (int)n;
	}

	cout << "Do you want to limit possible size of arrays? Type 'y' (yes) or 'n' (no)."<<endl;
	cin >> h;
	if (h == 'y') {
		do_size_limit = true;
	}
	else if (h == 'n') {
		do_size_limit = false;
	}
	else {
		while (h != 'y' && h != 'n') {

			cout << "Something goes wrong with your answer... Try again, write words in specified format." << endl << "Do you want to limit possible size of arrays? Type 'y' (yes) or 'n' (no)." << endl;
			cin >> h;
			if (h == 'y') {
				do_size_limit = true;
			}
			else if (h == 'n') {
				do_size_limit = false;
			}
		}
	}
	unsigned short size_limit;
	if (do_size_limit == true) {
		
		cout << "Enter size limit (natural number less than 32767 and equal or more than n): ";
		cin >> size_limit;
		int_part = (int)size_limit;

		while ((size_limit <= 0) || (size_limit > RAND_MAX) || (size_limit < n) || (abs(size_limit-int_part)>eps)) {
			cout << "Size limit must be natural number less than 32767 and equal or more than n, please, try again..." << endl;
			cout << "Enter size limit (natural number less than 32767 and equal or more than n): ";
			cin >> size_limit;
			int_part = (int)size_limit;
		}
	}
	else {
		size_limit = RAND_MAX;
	}

	char show_result;
	cout << "Do you want to see result of program's working in console? Type 'y' (yes) or 'n' (no)." << endl;
	cin >> show_result;
	if (show_result == 'y') {
		result_arr = generateRandomArrays(n, true, size_limit);
		delete[] result_arr;
	}
	else if (show_result == 'n') {
		result_arr = generateRandomArrays(n, false, size_limit);
		delete[] result_arr;
	}
	else {
		while (show_result != 'y' && show_result != 'n') {
			cout << "Something goes wrong with your answer... Try again, write words in specified format." << endl <<"Do you want to see result of program's working in console? Type 'y' (yes) or 'n' (no)." << endl;
			cin >> show_result;
			if (show_result == 'y') {
				result_arr = generateRandomArrays(n, true, size_limit);
				delete[] result_arr;
			}
			else if (show_result == 'n') {
				result_arr = generateRandomArrays(n, false, size_limit);
				delete[] result_arr;
			}
		}
	}
}