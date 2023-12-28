#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

double D1(); // Диаметр меньшего шкива
int material(); // Материал ремня
int material_p(); //Материал покрытия ремня
double Dmin_δ(); //Отношение диаметра шкива к толщине ремня
double δ(int mat, double D1); //Толщина ремня
double F(); //Определение окружной силы
double gamma(int mat, double D1, double δ);
double gammaF(int mat, double D1, double δ, double gamma, int mat_p);
double C0(double mat);
double C1();
double C2(int mat);
double C3();
double b(double F, double δ, double gammaF);


int material() {
    int mat;
    wcout << L"Выберите материал ремня: " << endl;
    wcout << L"1. Тканевый прорезиненный" << endl;
    wcout << L"2. Синтетический капроновый" << endl;
    cin >> mat;
    if ((mat > 2) || (mat < 1)) { wcout << L"Такого варианта нет"; }
    return mat;
}

int material_p() {
    int mat_p;
    wcout << L"Выберите покрытие ремня: " << endl;
    wcout << L"1. Из полиамида С6 в соединении с каучуком СКН-40" << endl;
    wcout << L"2. Из наиритового латекса" << endl;
    cin >> mat_p;
    if ((mat_p > 2) || (mat_p < 1)) { wcout << L"Такого варианта нет"; }
    return mat_p;
}

double D1() {
    double D1;
    cout << "Введите димаетр меньшего шкива (D1): "; //Диаметр меньшего шкива
    cin >> D1;
    return D1;
}

double F() {
    double N, v;
    wcout << L"Введите мощность(N): ";
    cin >> N;
    wcout << L"Введите скорость(v): ";
    cin >> v;
    double N_v = N / v;
    double F = pow(10, 3) * N_v;
    return F;
}

double δ(int mat, double D1) {
    double Dmin_δ;
    int div;
    wcout << L"Выберите отношение диаметра меньшего шкива к толщине ремня (Dmin/delta): " << endl;
    wcout << L"1. Допускаемое" << endl;
    wcout << L"2. Рекомендуемое" << endl;
    cin >> div;
    if (mat == 1) {
        if (div == 1) { Dmin_δ = 30; }
        else if (div == 2) { Dmin_δ = 40; }
        else { wcout << L"Такого варианта нет"; }
    }
    if (mat == 2) {
        if (div == 1) { Dmin_δ = 60; }
        else if (div == 2) { Dmin_δ = 125; }
        else { wcout << L"Такого варианта нет"; }
    }

    double δ = D1 / Dmin_δ;
    return δ;
}

double gamma(int mat, double D1, double δ) {

    int G, E;
    double gamma;
    while (true) {
        wcout << L"Выберите тип натяжения ремня" << endl;
        wcout << L"1. Постоянное" << endl;
        wcout << L"2. Периодическое" << endl;
        wcout << L"3. Переменное" << endl;
        cin >> G;
        //cout << mat << endl;

        if (mat == 1) {
            wcout << L"Выберите тип межосевого расстояния" << endl;
            wcout << L"1. Малое" << endl;
            wcout << L"2. Достаточное" << endl;
            wcout << L"3. Регулируемое" << endl;
            wcout << L"4. Автоматически регулируемое" << endl;
            cin >> E;
            if ((G == 1) && (E == 1)) { gamma = 1.6; break; }
            if ((G == 1) && (E == 2)) { gamma = 1.8; break; }
            if ((G == 2) && (E == 3)) { gamma = 1.8; break; }
            if ((G == 1) && (E == 4)) { gamma = 2.0; break; }
            if ((G == 3) && (E == 4)) { gamma = 2.4; break; }
            else { wcout << L"Невозможно подобрать подходящее значение, выберите другие параметры" << endl; }
        }

        if (mat == 2) {
            //cout << D1/δ << endl;
            if ((G == 2) && (D1 / δ <= 80)) { gamma = 4.0; break; }
            if ((G == 2) && (D1 / δ <= 80)) { gamma = 4.5; break; }
            if ((G == 2) && (D1 / δ <= 80)) { gamma = 5.0; break; }
            if ((G == 1) && (D1 / δ > 80)) { gamma = 7.5; break; }
            if ((G == 3) && (D1 / δ > 100)) { gamma = 10.0; break; }
            else { wcout << L"Невозможно подобрать значение, выберите другие параметры" << endl; }
        }
    }
    return gamma;

}

double gammaF(int mat, double D1, double δ, double gamma, int mat_p) {
    double A, W, gammaF0;
    if (mat == 1) {
        if (gamma == 1.6) {
            A = 2.3;
            W = 9.0;
        }
        if (gamma == 1.8) {
            A = 2.5;
            W = 10.0;
        }
        if (gamma == 2.0) {
            A = 2.7;
            W = 11.0;
        }
        if (gamma == 2.4) {
            A = 3.05;
            W = 13.5;
        }
    }
    if (mat == 2) {
        if (mat_p == 1) {
            if (gamma == 4.0) {
                A = 5.75;
                W = 176;
            }
            if (gamma == 5.0) {
                A = 7.0;
                W = 220;
            }
            if (gamma == 7.5) {
                A = 9.6;
                W = 330;
            }
            if (gamma == 10.0) {
                A = 11.6;
                W = 440;
            }
        }
        if (mat_p == 2) {
            if (gamma == 4.0) {
                A = 6.55;
                W = 124;
            }
            if (gamma == 5.0) {
                A = 8.0;
                W = 156;
            }
            if (gamma == 7.5) {
                A = 11.4;
                W = 233;
            }
            if (gamma == 10.0) {
                A = 14.3;
                W = 311;
            }
        }
    }
    gammaF0 = A - (W * δ / D1);
    return (gammaF0 * C0(mat) * C1() * C2(mat) * C3());
}

double C0(double mat) {
    double c0 = 1.0;
    int L;
    while (true) {
        if (mat == 1) {
            wcout << L"Укажите угол наклона оси передачи к горизонту (От 0 до 90)" << endl;
            cin >> L;
            if ((L >= 0) && (L <= 60)) { c0 = 1.0; break; }
            if ((L > 60) && (L <= 80)) { c0 = 0.9; break; }
            if (L == 90) { c0 = 0.8; break; }
            else { wcout << L"Вы ввели неккоректное значение" << endl; }

        }
        if (mat == 2) { c0 = 1.0; break; }
    }
    return c0;
}

double C1() {
    double c1;
    int L;
    while (true) {
        wcout << L"Введите угол обхвата на меньшем шкиве (От 110 до 180)" << endl;
        cin >> L;
        if (L == 110) { c1 = 0.79; break; }
        if (L == 120) { c1 = 0.82; break; }
        if (L == 130) { c1 = 0.85; break; }
        if (L == 140) { c1 = 0.88; break; }
        if (L == 150) { c1 = 0.91; break; }
        if (L == 160) { c1 = 0.94; break; }
        if (L == 170) { c1 = 0.97; break; }
        if (L == 180) { c1 = 1.0; break; }
        wcout << L"Вы ввели неправильный промежуток" << endl;
    }
    return c1;
}

double C2(int mat) {
    int v;
    double c2;
    if (mat == 1) {
        wcout << L"Введите скорость (от 5 до 30 с шагом 5): ";
        cin >> v;
        switch (v)
        {
        case 5:
            c2 = 1.03;
            break;
        case 10:
            c2 = 1.0;
            break;
        case 15:
            c2 = 0.95;
            break;
        case 20:
            c2 = 0.88;
            break;
        case 25:
            c2 = 0.79;
            break;
        case 30:
            c2 = 0.68;
            break;
        default:
            wcout << L"Вы ввели неподходящую скорость" << endl;
            break;
        }
    }
    if (mat == 2) {
        wcout << L"Введите скорость (от 5 до 40 с шагом 5 или 50 или 70): ";
        cin >> v;
        switch (v)
        {
        case 5:
            c2 = 1.01;
            break;
        case 10:
            c2 = 1.00;
            break;
        case 15:
            c2 = 0.99;
            break;
        case 20:
            c2 = 0.97;
            break;
        case 25:
            c2 = 0.95;
            break;
        case 30:
            c2 = 0.92;
            break;
        case 35:
            c2 = 0.89;
            break;
        case 40:
            c2 = 0.85;
            break;
        case 50:
            c2 = 0.76;
            break;
        case 70:
            c2 = 0.52;
            break;
        default:
            wcout << L"Вы ввели неподходящую скорость" << endl;
            break;
        }
    }
    return c2;
}

double C3() {
    double c3;
    int en_type;
    wcout << L"Выберите тип двигателя" << endl;
    wcout << L"1. Электродвигатель постоянного тока" << endl;
    wcout << L"2. Электродвигатель переменного тока" << endl;
    cin >> en_type;

    // int load_type;
    // wcout << L"Выберите характер нагрузки" << endl;
    // wcout << L"1. Спокойная. Пусковая нагрузка до 120%" << endl;
    // wcout << L"2. Умеренные колебания нагрузки. Пусковая нагрузка до 150%" << endl;
    // wcout << L"3. Значительные колебания нагрузки. Пусковая нагрзка до 200%" << endl;
    // wcout << L"4. Весьма неравномерная и ударная нагрузка. Пусковая нагрузка до 300%" << endl;
    // cin >> load_type;

    int veh_type;
    wcout << L"Выберите тип машины" << endl;
    wcout << L"1. Ленточные транспортеры" << endl;
    wcout << L"2. Пластинчатые транспортеры" << endl;
    wcout << L"3. Реверсивные приводы" << endl;
    wcout << L"4. Подъёмники" << endl;
    cin >> veh_type;

    if (en_type == 1) {
        if (veh_type == 1) {
            c3 = 1.0;
        }
        if (veh_type == 2) {
            c3 = 0.9;
        }
        if (veh_type == 3) {
            c3 = 0.8;
        }
        if (veh_type == 4) {
            c3 = 0.7;
        }
    }
    if (en_type == 2) {
        if (veh_type == 1) {
            c3 = 0.9;
        }
        if (veh_type == 2) {
            c3 = 0.8;
        }
        if (veh_type == 3) {
            c3 = 0.7;
        }
        if (veh_type == 4) {
            c3 = 0.6;
        }
    }

    return c3;
}

double b(double F, double δ, double gammaF) {
    return (F / (δ * gammaF));
}







int main() {
    setlocale(LC_ALL, "Russian");
    while (true) {
        double DD1 = D1();
        int mat = material();
        double delta = δ(mat, DD1);
        double FF = F();
        double gamm = gamma(mat, DD1, delta);
        double gammF = gammaF(mat, DD1, delta, gamm, material_p());
        double bb = b(FF, delta, gammF);

        wcout << L"Ваши введенные значения" << endl;
        cout << "---------------------------" << endl;
        wcout << L"Диаметр меньшего шкива:  " << DD1 << endl;
        cout << "---------------------------" << endl;
        wcout << L"Материал ремня: ";
        if (mat == 1) { wcout << L"Тканевый прорезиненный" << endl; }
        if (mat == 2) { wcout << L"Синтетический капроновый" << endl; }
        cout << "---------------------------" << endl;
        wcout << L"Толщина ремня: " << delta << endl;
        cout << "---------------------------" << endl;
        wcout << L"Окружная сила: " << FF << endl;
        cout << "---------------------------" << endl;
        wcout << L"Начальное напряжение ремня: " << gamm << endl;
        cout << "---------------------------" << endl;
        wcout << L"Допускаемое полезное напряжение: " << gammF << endl;
        cout << "---------------------------" << endl;
        double flag;
        wcout << L"Всё верно?" << endl;
        wcout << L"1. Да" << endl;
        wcout << L"2. Нет (Ввести заного)" << endl;
        cin >> flag;
        if (flag == 1) {
            wcout << L"Сечение ремня равно: " << bb;
            break;
        }
    }
    double X;
    cin >> X;
}