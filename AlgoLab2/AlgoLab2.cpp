#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#define N 60
const int t = N * 1.5;
using namespace std;
void randInput(int *arr){
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        bool stop = false;
        while(!stop){
            stop = true;
            arr[i] = rand() % 9000 + 1000;
            for(int j = 0; j < i; j++){
                if(arr[i] == arr[j]){
                    stop = false;
                    break;
                }
            }
        }
    }
}
void handInput(int *arr){
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}
int hashFunction(int a){
    int b = a % 1000;
    return b;
}
void hashGenerate(const int *input, int *output, float &steps){
    for(int i = 0; i < t; i++) output[i] = 0;
    for(int i = 0; i < N; i++, steps++){
        int ind = hashFunction(input[i]) % t;
        for(; output[ind] != 0; ind++, steps++)
            if(ind > t) ind %= t;
        output[ind] = input[i];
    }
}
void show(int *arr, int size = N){
    for(int i = 0; i < size; i++){
        if(i % 10 == 0) cout << endl << endl;
        cout << setfill(' ') << setw(2) << i << " - " << setfill(' ') << setw(4) << arr[i] << "  ";
    }
}
int findElem(int *arr, int elem){
    int ind = hashFunction(elem) % t;
    int i = 0;
    for(; arr[ind] != elem; ind++, i++){
        if(ind > t) ind %= t;
        if(i>100)break;
    }if(i<=100){
        cout << "Элемент " << elem << " находится в ячейке " << ind;
        return ind;
    }else{
        cout << "Элемент " << elem << " не найден ";
        return -1;
    }
}
void addElem(int* arr, int elem, float &steps){
    int ind = hashFunction(elem) % t;
    steps = 0;
    for(; arr[ind] != 0; ind++, steps++){
        if(ind > t) ind %= t;
        if(steps > 100)break;
    }if(steps<=100){
        arr[ind] = elem;
        cout << "Элемент " << elem << " добавлен в ячейку " << ind;
    } else cout << "Элемент " << elem << " не добавлен";
}
void delElem(int* arr, int elem){
    int ind = findElem(arr, elem);
    if(ind != -1){
        arr[ind] = 0;
        cout << "Элемент " << elem << " удален";
    } else cout << "Элемент " << elem << " не найден";
}

int main(){
    setlocale(0, "");
    int a[N];
    int b[t];
    float stepC = 0;
    int choice = 0;
    int x = 0;
    int check = 0;
    cout << "Выберите способ ввода:\n1)Рандомный;\n2)Ручной. ";
    do{
        cin >> choice;
    } while(choice != 1 && choice != 2);
    switch(choice){
        case 1: randInput(a); break;
        case 2: handInput(a); break;
    }
    printf("Начальный массив:");
    show(a);
    printf("\nКонечный массив:\n ");
    hashGenerate(a, b, stepC);
    show(b, t);
    do{
        cout << endl << "Выберите действие:\n1) Проверить, имеется ли такой элемент в таблице;\n2) Удалить элемент;\n3) Заменить элемент;\n4) Вывести хеш-таблицу;\n Нажмите 0 для выхода.\n";
        do{
            cin >> choice;
        } while(choice < 0 && choice > 4);
        switch(choice){
        case 1:
            cout << endl << "Введите элемент для проверки(число должно быть двухзначное): ";
            cin >> x;
            check = findElem(b, x);
            if(check==-1)
                addElem(b, x, stepC);
            break;
        case 2:
            cout << endl << "Введите элемент, который хотите удалить: ";
            cin >> x;
            delElem(b, x);
            break;
        case 3:
            cout << endl << "Введите элемент, который хотите заменить: ";
            cin >> x;
            delElem(b, x);
            cout << endl << "Введите элемент, на который хотите заменить: ";
            cin >> x;
            addElem(b, x, stepC);
            break;
        case 4:
            show(b);
            break;
        default: break;
        }

    } while(choice != 0);

    float n = 0;
    for(int i = 0; i < t; i++){
        if(b[i] != 0)
            n++;
    }

    cout << "\n\nКоэффициент заполнения: " << setprecision(3) << (double)n / t;
    cout << "\nКоэффициент средних шагов: " << setprecision(3) << stepC / N;
}