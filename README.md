#### Пояснения к коду для тестового задания для поступающих в школу разработки Heads x Hands

##### Задача. На входе функция получает параметр n - натуральное число. Необходимо сгенерировать n-массивов, заполнить их случайными числами, каждый массив имеет случайный размер. Размеры массивов не должны совпадать. Далее необходимо отсортировать массивы. Массивы с четным порядковым номером отсортировать по возрастанию, с нечетным порядковым номером - по убыванию. На выходе функция должна вернуть массив с отсортированными массивами.

##### Доброго времени суток! Данное задание было выполнено на ЯП C++ с использованием среды разработки MS Visual Studio 2017.
##### В рамках данной программы был реализован дополнительный функционал, делающий проверку кода более удобной. При запуске программы пользователь задаёт число n (при этом осуществляется проверка на то, что введено натуральное число, не большее константы C++ RAND_MAX=32767, так как это понадобится для генерации псевдослучайных чисел). Далее пользователь выбирает, хочет ли он ограничить максимально возможный размер для каждого из n массивов (формат ввода ответа указан: "y" - да, "n" - нет). По умолчанию для ввода максимального размера выполняется проверка на натуральность и то, что размер не меньше n. Затем пользователь может выбрать, нужно ли выводить результат работы программы на экран. По умолчанию результат программы выводится в файл "result.txt".
##### Основная логика программы реализована в функции generateRandomArrays(...). Для упрощения понимания кода некоторые его фрагменты вынесены в отдельные функции: binarySearch(...) - алгоритм бинарного поиска, insertionSort(...) - алгоритм сортировки вставками, quickSort(...) - алгоритм быстрой сортировки (так как данный алгоритм является рекурсивным, то было принято решении о создании отдельных функций для вспомогательных алгоритмов). 
##### Один из ключевых моментов программы - выбор алгоритма сортировки в зависимости от введённого n. Путём проведённых тестов было выяснено, что при n>~3000 более быстрый алгоритм quick sort вызывает переполнение стека, поэтому для поддержания работоспособности программы было принято решение использовать в случае n>3000 значительно более медленный, но не использующий рекурсию алгоритм сортировки вставками, а при n<=3000 - рекурсивный алгоритм быстрой сортировки.
##### Также в программе реализованы вспомогательные функции добавления очередного размера в массив размеров массивов addIntoSizeArrayQuickSort(...) и addIntoSizeArrayInsertionSort(...) (работают через quick sort и insertion sort, соответственно), которые вызываются в функции generateRandomArrays(...).
##### Из-за использования встроенной функции rand() для генерации натуральных случайных чисел и константы RAND_MAX=32767 было принято решение использовать для таких переменных тип данных unsigned short.
##### Генерируемый массив из n массивов случайных неповторяющихся размеров имеет тип данных double, так как внутри него генерируются вещественные числа (отдельно генерируется целая часть - случайное натуральное число, отдельно - дробная часть - случайное вещественное число, лежащее на отрезке от 0 до 1, затем целая и дробная части складываются).
##### Так как сортировка применятся к массивам различных типов (double и unsigned short), то были использованы шаблоны.
##### Некоторые другие комментарии приведены в самом коде программы (файл HeadsAndHandsTask2021.cpp).

##### Спасибо за внимание!
