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
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ������ � ���������" << endl;
        cout << " [2] - ���� ������ �� �����" << endl;
        cout << " [3] - ���������� �� ������ ������" << endl;
        cout << " [4] - ���������� �� ��������� �������" << endl;
        cout << " [5] - ���� ���������� ��� ����� �� ����" << endl;
        cout << " [6] - ���� ���������� ��� ������ ����� �������� �������" << endl;
        cout << " [7] - ���������� ������" << endl;
        cout << " [8] - ��������� ������" << endl;
        cout << " [9] - ����������� ������" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
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
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(Tovar*& tovary, int& n) {
    cout << "������ ������� ������: ";
    cin >> n;

    delete[] tovary;
    tovary = new Tovar[n];

    for (int i = 0; i < n; ++i) {
        cout << "����� � " << i + 1 << ":" << endl;
        cout << "����� ������: "; cin >> tovary[i].nazva;
        cout << "������� ������ �� ������� ������: "; cin >> tovary[i].vartis;
        cout << "ʳ������ ������: "; cin >> tovary[i].kilkist;
        cout << "������� ����������(�������� �� � ��): "; cin >> tovary[i].odun_vum;
    }
}

void Print(const Tovar* tovary, int n) {
    cout << "=========================================================="
        << endl;
    cout << "| � | ����� ������ | ������� | ʳ������ | ������� ���. |"
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
    cout << "������ ����� ������: "; cin >> nazva;

    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (tovary[i].nazva == nazva) {
            cout << "����� ��������:" << endl;
            Print(&tovary[i], 1);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "������ ������ ���� � ����������" << endl;
    }
}

void SearchTovarByRange(const Tovar* tovary, int n) {
    double minPrice, maxPrice;
    cout << "������ ������� ������� ������ (�������� �� ����������� ����): ";
    cin >> minPrice >> maxPrice;

    cout << "������ � ������� � ������� [" << minPrice << ", " << maxPrice << "]:" << endl;
    for (int i = 0; i < n; ++i) {
        double totalValue = tovary[i].vartis * tovary[i].kilkist;
        if (totalValue >= minPrice && totalValue <= maxPrice) {
            Print(&tovary[i], 1);
        }
    }
}

void EditTovar(Tovar* tovary, int n) {
    int index;
    cout << "������ ����� ������, ���� ������� ������������: "; cin >> index;
    index--;

    if (index >= 0 && index < n) {
        cout << "����� ������: "; cin >> tovary[index].nazva;
        cout << "������� ������ �� ������� ������: "; cin >> tovary[index].vartis;
        cout << "ʳ������ ������: "; cin >> tovary[index].kilkist;
        cout << "������� ����������(�������� �� � ��): "; cin >> tovary[index].odun_vum;
    }
    else {
        cout << "����������� ����� ������" << endl;
    }
}

void RemoveTovar(Tovar*& tovary, int& n) {
    int index;
    cout << "������ ����� ������, ���� ������� ��������: "; cin >> index;
    index--;

    if (index >= 0 && index < n) {
        for (int i = index; i < n - 1; ++i) {
            tovary[i] = tovary[i + 1];
        }
        --n;
        cout << "����� ������ ��������" << endl;
    }
    else {
        cout << "����������� ����� ������" << endl;
    }
}