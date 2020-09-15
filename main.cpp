#include <iostream>
#include <cstdlib>

using namespace std;

// Верхняя граница диапазона случайных чисел
const int MAX_VAL = 100;

// Точность сравнения чисел с плавающей точкой
const double EPS = 1e-7;

// Функции корректного сравнения чисел с плавающей точкой
inline bool is_less(double a, double b) {
    return a < b - EPS;
}
inline bool is_equal(double a, double b) {
    return b - EPS < a && a < b + EPS;
}
inline bool is_greater(double a, double b) {
    return b + EPS < a;
}

// Функция вывода массива на экран
void print_arr(const int a[], int n);

// Функция определения среднего арифметического
double mean(const int a[], int n);

// Функция заполнения массива y(m)
void fill_y(int x[], int n, int * y[], int& m);

// Функция удаления элемента из массива (без перераспределения памяти)
void del(int a[], int& n, int pos);

// Функция проверки числа на простоту
bool is_prime(int n);


int main() {

    // Заполнение массива x(n)

    cout << "Введите количество элементов: ";

    int n;
    cin >> n;

    int * x = new int[n];

    string ans = "";
    while (ans != "y" && ans != "n") {
        cout << "Заполнить массив случайными числами? (y/n) : ";
        cin >> ans;
    }

    if (ans == "y") {

        // Заполнение случайными числами

        for (int i = 0; i < n; i++)
            x[i] = rand() % MAX_VAL + 1;
    }
    else {

        // Заполнение с клавиатуры

        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = ";
            cin >> x[i];
        }
    }

    cout << "\nМассив x(n) после заполнения:\n";
    print_arr(x, n);


    // Заполнение массива y(m)

    int m;
    int * y;

    fill_y(x, n, &y, m);

    cout << "\nМассив y(m) после заполнения:\n";
    print_arr(y, m);


    // Удаление в x(n) и y(m) всех чисел, не являющихся простыми

    int pos_x = 0;
    while (pos_x < n) {
        if (is_prime(x[pos_x]))
            pos_x++;
        else
            del(x, n, pos_x);
    }

    int pos_y = 0;
    while (pos_y < m) {
        if (is_prime(y[pos_y]))
            pos_y++;
        else
            del(y, m, pos_y);
    }


    // Вывод получившихся массивов на экран

    cout << "\nМассив x(n) после удаления всех чисел, не являющихся простыми:\n";
    print_arr(x, n);

    cout << "\nМассив y(m) после удаления всех чисел, не являющихся простыми:\n";
    print_arr(y, m);


    // Освобождение памяти, выделенной под динамические массивы

    delete[] x;
    delete[] y;


    return 0;
}


void print_arr(const int a[], int n) {
    cout << n << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

void del(int a[], int& n, int pos) {
    for (int i = pos; i < n - 1; i++)
        a[i] = a[i + 1];
    n--;
    return;
}

double mean(const int a[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum / n;
}

void fill_y(int x[], int n, int * y[], int& m) {

    double mean_val = mean(x, n);

    cout << "\nСреденее арифметическое массива x(n):\n";
    cout << mean_val << endl;

    m = 0;
    for (int i = 0; i < n; i++) {
        if (is_greater(x[i], mean_val))
            m++;
    }

    int * tmp = new int[m];

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (is_greater(x[i], mean_val))
            tmp[j++] = x[i];
    }

    *y = tmp;

    return;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}