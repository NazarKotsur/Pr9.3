#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

struct Tovar {
    string nazva;
    double vartis;
    int kilkist;
    double odun_vum;
};

void Create(Tovar*& tovary, int& n);
void Print(const Tovar* tovary, int n);
void SortByName(Tovar* tovary, int n);
void SortByTotalValue(Tovar* tovary, int n);
void SearchTovarByName(const Tovar* tovary, int n);
void SearchTovarByRange(const Tovar* tovary, int n);
void EditTovar(Tovar* tovary, int n);
void RemoveTovar(Tovar*& tovary, int& n);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Tovar* tovary = nullptr;
    int n = 0;

    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - Введення товарів з клавіатури" << endl;
        cout << " [2] - Вивід товарів на екран" << endl;
        cout << " [3] - Сортування за назвою товару" << endl;
        cout << " [4] - Сортування за загальною вартістю" << endl;
        cout << " [5] - Вивід інформації про товар по назві" << endl;
        cout << " [6] - Вивід інформації про товари згідно діапазону вартості" << endl;
        cout << " [7] - Добавлення товару" << endl;
        cout << " [8] - Видалення товару" << endl;
        cout << " [9] - Редагування товару" << endl;
        cout << " [0] - Вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(tovary, n);
            break;
        case 2:
            Print(tovary, n);
            break;
        case 3:
            SortByName(tovary, n);
            Print(tovary, n);
            break;
        case 4:
            SortByTotalValue(tovary, n);
            Print(tovary, n);
            break;
        case 5:
            SearchTovarByName(tovary, n);
            break;
        case 6:
            SearchTovarByRange(tovary, n);
            break;
        case 7:
            Create(tovary, n);
            break;
        case 8:
            RemoveTovar(tovary, n);
            break;
        case 9:
            EditTovar(tovary, n);
            break;
        case 0:
            delete[] tovary;
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(Tovar*& tovary, int& n) {
    cout << "Введіть кількість товарів: ";
    cin >> n;

    delete[] tovary;
    tovary = new Tovar[n];

    for (int i = 0; i < n; ++i) {
        cout << "Товар № " << i + 1 << ":" << endl;
        cout << "Назва товару: "; cin >> tovary[i].nazva;
        cout << "Вартість товару за одиницю товару: "; cin >> tovary[i].vartis;
        cout << "Кількість товару: "; cin >> tovary[i].kilkist;
        cout << "Одиниця вимірювання(упаковка по Х кг): "; cin >> tovary[i].odun_vum;
    }
}

void Print(const Tovar* tovary, int n) {
    cout << "=========================================================="
        << endl;
    cout << "| № | Назва товару | Вартість | Кількість | Одиниця вим. |"
        << endl;
    cout << "----------------------------------------------------------"
        << endl;

    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << tovary[i].nazva
            << "| " << setw(8) << right << tovary[i].vartis << " "
            << "| " << setw(9) << left << tovary[i].kilkist << " "
            << "| " << setw(12) << left << tovary[i].odun_vum << " |" << endl;
    }
    cout << "=========================================================="
        << endl;
    cout << endl;
}

void SortByName(Tovar* tovary, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (tovary[j].nazva > tovary[j + 1].nazva) {
                swap(tovary[j], tovary[j + 1]);
            }
        }
    }
}

void SortByTotalValue(Tovar* tovary, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            double totalValue1 = tovary[j].vartis * tovary[j].kilkist;
            double totalValue2 = tovary[j + 1].vartis * tovary[j + 1].kilkist;
            if (totalValue1 > totalValue2) {
                swap(tovary[j], tovary[j + 1]);
            }
        }
    }
}

void SearchTovarByName(const Tovar* tovary, int n) {
    string nazva;
    cout << "Введіть назву товару: "; cin >> nazva;

    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (tovary[i].nazva == nazva) {
            cout << "Товар знайдено:" << endl;
            Print(&tovary[i], 1);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Такого товару немає в асортименті" << endl;
    }
}

void SearchTovarByRange(const Tovar* tovary, int n) {
    double minPrice, maxPrice;
    cout << "Введіть діапазон вартості товару (мінімальна та максимальна ціна): ";
    cin >> minPrice >> maxPrice;

    cout << "Товари з вартістю в діапазоні [" << minPrice << ", " << maxPrice << "]:" << endl;
    for (int i = 0; i < n; ++i) {
        double totalValue = tovary[i].vartis * tovary[i].kilkist;
        if (totalValue >= minPrice && totalValue <= maxPrice) {
            Print(&tovary[i], 1);
        }
    }
}

void EditTovar(Tovar* tovary, int n) {
    int index;
    cout << "Введіть номер товару, який потрібно відредагувати: "; cin >> index;
    index--;

    if (index >= 0 && index < n) {
        cout << "Назва товару: "; cin >> tovary[index].nazva;
        cout << "Вартість товару за одиницю товару: "; cin >> tovary[index].vartis;
        cout << "Кількість товару: "; cin >> tovary[index].kilkist;
        cout << "Одиниця вимірювання(упаковка по Х кг): "; cin >> tovary[index].odun_vum;
    }
    else {
        cout << "Некоректний номер товару" << endl;
    }
}

void RemoveTovar(Tovar*& tovary, int& n) {
    int index;
    cout << "Введіть номер товару, який потрібно видалити: "; cin >> index;
    index--;

    if (index >= 0 && index < n) {
        for (int i = index; i < n - 1; ++i) {
            tovary[i] = tovary[i + 1];
        }
        --n;
        cout << "Товар успішно видалено" << endl;
    }
    else {
        cout << "Некоректний номер товару" << endl;
    }
}