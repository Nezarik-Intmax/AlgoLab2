#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#define N 60
using namespace std;

int hashFunction(int a){
    int b = a % 1000;
    return b;
}

int main(){
    setlocale(0, "");
    srand(time(NULL));
    int a[N];
    printf("Начальный массив:");
    for(int i = 0; i < N; i++){
        bool stop = false;
        while(!stop){
            stop = true;
            a[i] = rand() % 9000 + 1000;
            for(int j = 0; j < i; j++){
                if(a[i] == a[j]){
                    stop = false;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < N; i++){
        if(i % 10 == 0) cout << endl;
        cout << a[i] << "  ";
    }
    printf("\nКонечный массив:\n ");
    const int t = N * 1.5;
    int b[t];
    float stepC = 0;
    for(int i = 0; i < t; i++)b[i] = 0;
    for(int i = 0; i < N; i++, stepC++){
        int ind = hashFunction(a[i]) % t;
        for(; b[ind] != 0; ind++, stepC++)
            if(ind > t) ind %= t;
        b[ind] = a[i];
    }
    for(int i = 0; i < t; i++){
        //if(i % 10 == 0) cout << endl << setfill('-') << setw(10 * (2 + 3 + 4 + 3)) << "-\n";
        if(i % 10 == 0) cout << endl << endl;
        cout << setfill(' ') << setw(2) << i << " - " << setfill(' ') << setw(4) << b[i] << "  ";
    }

    cout << "\n\nКоэффициент заполнения: " << setprecision(3) << (double)N / t;
    cout << "\nКоэффициент средних шагов: " << setprecision(3) << stepC / N;
    cout << endl << endl << endl;
}