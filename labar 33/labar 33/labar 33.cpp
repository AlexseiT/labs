#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void FillInc(int a[], int n) //Ð·Ð°Ð¿Ð¾Ð»Ð½ÐµÐ½Ð¸Ðµ Ð¼Ð°ÑÑÐ¸Ð²Ð° Ð²Ð¾Ð·Ñ€Ð°ÑÑ‚Ð°ÑŽÑ‰Ð¸Ð¼Ð¸ Ñ‡Ð¸ÑÐ»Ð°Ð¼Ð¸
{
    for (int i = 1; i <= n; i++)
        a[i] = i;
    return;
}

void FillDec(int a[], int n) //Ð·Ð°Ð¿Ð¾Ð»Ð½ÐµÐ½Ð¸Ðµ Ð¼Ð°ÑÑÐ¸Ð²Ð° ÑƒÐ±Ñ‹Ð²Ð°ÑŽÑ‰Ð¸Ð¼Ð¸ Ñ‡Ð¸ÑÐ»Ð°Ð¼Ð¸
{
    for (int j = n, i = 1; i <= n; j--, i++)
        a[i] = j;
    return;
}

//void FillRand(int a[], int n) //Ð·Ð°Ð¿Ð¾Ð»Ð½ÐµÐ½Ð¸Ðµ Ð¼Ð°ÑÑÐ¸Ð²Ð° Ñ€Ð°Ð½Ð´Ð¾Ð¼Ð½Ñ‹Ð¼Ð¸ Ñ‡Ð¸ÑÐ»Ð°Ð¼Ð¸
//{
//	int b,c;
//	cout <<"Random from... \n";
//	cin >>b;
//	cout <<"to...\n";
//	cin >>c;
//	for (int i=1; i<=n; i++){
//	    a[i]=b+rand()%(c-b+1);
//  }
//}

void FillRand(int a[], int n)
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
        a[i] = rand() % n;
    return;
}


int CheckSum(int a[], int n) //Ð¿Ð¾Ð´ÑÑ‡Ñ‘Ñ‚ ÐºÐ¾Ð½Ñ‚Ñ€Ð¾Ð»ÑŒÐ½Ð¾Ð¹ ÑÑƒÐ¼Ð¼Ñ‹ ÑÐ»ÐµÐ¼ÐµÐ½Ñ‚Ð¾Ð² Ð¼Ð°ÑÑÐ¸Ð²Ð°
{
    int Sum = 0;
    for (int i = 1; i <= n; i++)
        Sum += a[i];
    cout << "Control summa = " << Sum << endl;
    return Sum;

}

int RunNumber(int a[], int n) //Ð¿Ð¾Ð´ÑÑ‡Ñ‘Ñ‚ ÑÐµÑ€Ð¸Ð¹ Ð² Ð¼Ð°ÑÑÐ¸Ð²Ðµ
{
    int Number = 1;
    for (int i = 1; i <= n - 1; i++) {
        if (a[i] > a[i + 1])
            Number += 1;
    }
    cout << "Number Series = " << Number << endl;
    return Number;
}

void PrintMas(int a[], int n) //Ð²Ñ‹Ð²Ð¾Ð´ Ð½Ð° ÑÐºÑ€Ð°Ð½ ÑÐ»ÐµÐ¼ÐµÐ½Ñ‚Ð¾Ð² Ð¼Ð°ÑÑÐ¸Ð²Ð°
{
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;
    return;
}

void BubbleSort(int a[], int n)
{
    int k, C = 0, M = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = n; j >= i + 1; j--) {
            C++;
            if (a[j] < a[j - 1]) {
                k = a[j];
                a[j] = a[j - 1];
                a[j - 1] = k;
                M += 3;
            }
        }
    }


    cout << C + M << "     ";



}

int main()
{
    int n;

    cout << "N       " << "Inc       " << "Dec       " << "Rand       " << "theor       " << endl;
    for (n = 100; n <= 500; n += 100) {
        int a[n];
        int Ct = ((n * n) - n) / 2;
        int Mt = 3 * Ct;
        cout << n << "    ";
        FillInc(a, n);
        BubbleSort(a, n);

        FillDec(a, n);
        BubbleSort(a, n);

        FillRand(a, n);
        BubbleSort(a, n);

        cout << Ct + Mt << "     ";
        cout << endl;
    }


}
