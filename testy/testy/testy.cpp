#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdio.h>
#define N 4

class complex {
public:
    double real;
    double im;
    complex() {
        this->real = 0;
        this->im = 0;
    }
    complex(double real, double im) : real(real), im(im) {

    }
    complex operator + (complex c2) {
        return complex(this->real + c2.real, this->im + c2.im);
    }
    complex operator * (complex c2) {
        complex result;
        result.real = this->real * c2.real - this->im * c2.im;
        result.im = this->real * c2.im + this->im * c2.real;
        return result;
    }
    complex operator - (complex c2) {
        return complex(this->real - c2.real, this->im - c2.im);
    }
    void operator = (complex c2) {
        this->real = c2.real;
        this->im = c2.im;
    }
    void operator += (complex c2) {
        this->real += c2.real;
        this->im += c2.im;
    }
    void operator /= (double n) {
        this->real /= n;
        this->im /= n;
    }
    void print() {
        printf("%f", this->real);
        if (this->im >= 0) printf(" + ");
        else printf(" - ");
        printf("%fi\n", abs(this->im));
    }
};

complex exp(complex z) {
    complex result;
    result.real = exp(z.real) * cos(z.im);
    result.im = exp(z.real) * sin(z.im);
    return result;
}

complex* DFT(complex input[], int& op) {
    complex* output = new complex[N];
    for (int k = 0; k < N; k++) {//(x+iy)*(cos-i*sin); re=x*cos+y*sin; im=-x*sin+y*cos
        output[k].real = output[k].im = 0;
        for (int n = 0; n < N; n++) {
            complex tmp;
            tmp.im = -2 * M_PI * k * n / N;
            op += 3;
            output[k] += exp(tmp) * input[n];
            op += 2;
        }
        output[k] /= N;
    }
    return output;
}

complex* reverse_DFT(complex input[], int& op) {
    complex* output = new complex[N];
    for (int k = 0; k < N; k++) {//(x+iy)*(cos+i*sin); re=x*cos-y*sin; im=x*sin+y*cos
        output[k].real = output[k].im = 0;
        for (int n = 0; n < N; n++) {
            complex tmp;
            tmp.im = 2 * M_PI * k * n / N;
            op += 3;
            output[k] += exp(tmp) * input[n];
            op += 2;
        }
    }
    return output;
}

void divide(int n, int& p1, int& p2) {
    for (p1 = (int)floor(sqrt(n)); p1 > 0; p1--) {
        p2 = n / p1;
        if (p1 * p2 == n) return;
    }
}

int to_one_dim(int k, int j, int p) {
    return k * p + j;
}

complex* HFT(complex input[], int& op) {
    int p1, p2;
    divide(N, p1, p2);
    printf("p1 = %d\np2 = %d\n", p1, p2);
    complex* A1 = new complex[N];
    complex* A2 = new complex[N];
    for (int j2 = 0; j2 < p2; j2++) {
        for (int k1 = 0; k1 < p1; k1++) {
            int n = k1 + p1 * j2;
            for (int j1 = 0; j1 < p1; j1++) {
                complex tmp;
                tmp.im = -2 * M_PI * j1 * k1 / p1;
                op += 3;
                A1[n] += input[j2 + p2 * j1] * exp(tmp);
                op += 2;
            }
            A1[n] /= p1;
        }
    }
    for (int k2 = 0; k2 < p2; k2++) {
        for (int k1 = 0; k1 < p1; k1++) {
            int n = k1 + p1 * k2;
            for (int j2 = 0; j2 < p2; j2++) {
                complex tmp;
                tmp.im = -2 * M_PI * (j2 * (n)) / N;
                op += 3;
                A2[n] += A1[k1 + p1 * j2] * exp(tmp);
                op += 2;
            }
            A2[n] /= p2;
        }
    }
    delete[] A1;
    return A2;
}

complex* reverse_HFT(complex input[], int& op) {
    int p1, p2;
    divide(N, p1, p2);
    printf("p1 = %d\np2 = %d\n", p1, p2);
    complex* A1 = new complex[N];
    complex* A2 = new complex[N];
    for (int j2 = 0; j2 < p2; j2++) {
        for (int k1 = 0; k1 < p1; k1++) {
            int n = k1 + p1 * j2;
            for (int j1 = 0; j1 < p1; j1++) {
                complex tmp;
                tmp.im = 2 * M_PI * j1 * k1 / p1;
                op += 3;
                A1[n] += input[j2 + p2 * j1] * exp(tmp);
                op += 2;
            }
        }
    }
    for (int k2 = 0; k2 < p2; k2++) {
        for (int k1 = 0; k1 < p1; k1++) {
            int n = k1 + p1 * k2;
            for (int j2 = 0; j2 < p2; j2++) {
                complex tmp;
                tmp.im = 2 * M_PI * (j2 * (k1 + p1 * k2)) / N;
                op += 3;
                A2[n] += A1[k1 + p1 * j2] * exp(tmp);
                op += 2;
            }
        }
    }
    delete[] A1;
    return A2;
}

complex* FFT_recursive(complex input[], int n, int& op) {
    if (n == 1) {
        return input;
    }
    complex* even = new complex[n / 2];
    complex* odd = new complex[n / 2];
    complex* output = new complex[n];
    for (int i = 0; i < n / 2; i++) {
        even[i] = input[2 * i];
        odd[i] = input[2 * i + 1];
    }
    even = FFT_recursive(even, n / 2, op);
    odd = FFT_recursive(odd, n / 2, op);
    for (int i = 0; i < n / 2; i++) {
        complex tmp = odd[i] * exp(complex(0, -2 * M_PI * i / n));
        op += 3;
        output[i] = even[i] + tmp;
        op++;
        output[i + n / 2] = even[i] - tmp;
        op++;
    }
    delete[] even, odd;
    return output;
}

complex* FFT(complex input[], int& op) {
    int r = (int)floor(log2(N));
    if (pow(2, r) != N) return NULL;
    complex* output = FFT_recursive(input, N, op);
    for (int i = 0; i < N; i++) {
        output[i] /= N;
    }
    return output;
}

/*complex* reverse_FFT_recursive(complex input[], int n, int& op) {
    if (n == 1) {
        return input;
    }
    complex* even = new complex[n / 2];
    complex* odd = new complex[n / 2];
    complex* output = new complex[n];
    for (int i = 0; i < n / 2; i++) {
        even[i] = input[2 * i];
        odd[i] = input[2 * i + 1];
    }
    even = FFT_recursive(even, n / 2, op);
    odd = FFT_recursive(odd, n / 2, op);
    for (int i = 0; i < n / 2; i++) {
        complex tmp = odd[i] * exp(complex(0, 2 * M_PI * i / n));
        op += 3;
        output[i] = even[i] + tmp;
        op++;
        output[i + n / 2] = even[i] - tmp;
        op++;
    }
    delete[] even, odd;
    return output;
}*/

complex* reverse_FFT(complex input[], int& op) {
    int r = (int)floor(log2(N));
    if (pow(2, r) != N) return NULL;
    for (int i = 0; i < N; i++) {
        input[i].im = -input[i].im;
    }
    complex* output = FFT_recursive(input, N, op);
    for (int i = 0; i < N; i++) {
        output[i].im = -output[i].im;
    }
    return output;
}

int main()
{
    complex* input = new complex[N];
    int op = 0;
    for (int i = 0; i < N; i++) {
        input[i].im = 0;
        input[i].real = i+1;
    }
    /*input[0].real = 1;
    input[1].real = 0;
    input[2].real = 1;
    input[3].real = 0;
    input[4].real = 1;*/
    for (int i = 0; i < N; i++) {
        printf("input[%d] = ", i+1);
        input[i].print();
    }
    printf("\nDFT:\n");
    complex* output = DFT(input, op);
    for (int i = 0; i < N; i++) {
        printf("output[%d] = ", i);
        output[i].print();
    }
    printf("Operations: %d\n", op);
    op = 0;
    delete[] input;
    printf("\nReverse DFT:\n");
    input = reverse_DFT(output, op);
    for (int i = 0; i < N; i++) {
        printf("input[%d] = ", i);
        input[i].print();
    }
    printf("Operations: %d\n", op);
    op = 0;
    printf("-------------------------------------------\n");
    delete[] output;
    printf("\nHFT:\n");
    output = HFT(input, op);
    for (int i = 0; i < N; i++) {
        printf("output[%d] = ", i);
        output[i].print();
    }
    printf("Operations: %d\n", op);
    op = 0;
    delete[] input;
    printf("\nReverse HFT:\n");
    input = reverse_HFT(output, op);
    for (int i = 0; i < N; i++) {
        printf("input[%d] = ", i);
        input[i].print();
    }
    printf("Operations: %d\n", op);
    op = 0;
    printf("-------------------------------------------\n");
    delete[] output;
    output = FFT(input, op);
    if (output) {
        printf("\nFFT:\n");
        for (int i = 0; i < N; i++) {
            printf("output[%d] = ", i);
            output[i].print();
        }
        printf("Operations: %d\n", op);
        op = 0;
        delete[] input;
        printf("\nReverse FFT:\n");
        input = reverse_FFT(output, op);
        for (int i = 0; i < N; i++) {
            printf("input[%d] = ", i);
            input[i].print();
        }
        printf("Operations: %d\n", op);
        delete[] output;
    }
    delete[] input;
}