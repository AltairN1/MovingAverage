#include <iostream>
#include <queue>
#include <chrono>
using namespace std;

void MovingAverage(deque <float> D, int W) {
    if (D.size() >= W && W > 0) {
        deque<float>::iterator it;
        it = D.begin();
        advance(it, W - 1); //перемещаем итератор на Window-1
        float b = 0; //создаём переменную для подсчёта среднего значения в окне
        deque <float> NewD; //контейнер для новой очереди
        for (int i = 1; i < D.size(); i++) {
            for (int j = 1; j <= W; j++) {
                b += *it; //считаем среднее значение в окне
                if (j == W) break; //выходим из цикла, когда дошли до начала окна
                advance(it, -1); //двигаемся итератором к началу окна
            }
            b = b / W; //получаем среднее значение в окне
            NewD.push_back(b); //помещаем среднее значение в новую очередь
            b = 0; //обнуляем переменную подсчёта среднего значения
            if (it < (D.end() - (W))) { //если итератор не достиг разности конца очереди и длины окна, то продолжаем цикл
                advance(it, W);
            }
            else break;
        }
    }
    else if (W) cout << "Ошибка! Размер окна больше количества отсчётов!" << endl;
    else cout << "Ошибка! Размер окна равен нулю!" << endl;
}

void MovingAverage(deque <double> D, int W) { //перегрузка фунции MovingAverage для типа double
    if (D.size() >= W && W > 0) {
        deque<double>::iterator it;
        it = D.begin();
        advance(it, W - 1);
        float b = 0;
        deque <double> NewD;
        for (int i = 1; i < D.size(); i++) {
            for (int j = 1; j <= W; j++) {
                b += *it;
                if (j == W) break;
                advance(it, -1);
            }
            b = b / W;
            NewD.push_back(b);
            b = 0;
            if (it < (D.end() - (W))) {
                advance(it, W);
            }
            else break;
        }
    }
    else if (W) cout << "Ошибка! Размер окна больше количества отсчётов!" << endl;
    else cout << "Ошибка! Размер окна равен нулю!" << endl;
} 

int typecheck() { 
    int a;
    for (;;) {
        cin >> a;
        if (cin.good()) {
            cin.ignore(10, '\n');
            return a;
        }
        else {
            cin.clear();
            cout << "Недопустимый тип данных! Введие n заново:" << endl;
            cin.ignore(10, '\n');
        }
    }
}

int main()
{
    
    setlocale(LC_ALL, "ru");
    deque <float> D_float; //контейнер для float 
    deque <double> D_double; //контейнер для double
    
    int Window, Countdown; //размер окна, количество элементов;
    
    Countdown = typecheck(); //проверка на тип
    Window = typecheck(); //проверка на тип

    for (int i = 1; i <= Countdown; i++) { //помещаем рандомные значения в контейнеры
        D_float.push_back(rand()%100);
        D_double.push_back(rand()%100);
    }
    
    auto Start = chrono::high_resolution_clock::now();

    MovingAverage(D_float, Window); 
    //MovingAverage(D_double, Window);

    auto End = chrono::high_resolution_clock::now();
    chrono::duration<float> Duration = End - Start;

    cout << "Время выполнения: " << Duration.count() << "сек" << endl;

    return 0;
}
