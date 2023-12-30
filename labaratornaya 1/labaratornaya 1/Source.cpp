
#include <stdio.h>
#include <math.h> 
    int main(int argc, char * argv[])
    {
        float a, b, alpha, gip, S, pi = 3.14159265 ;

        printf("Enter:\n");
        scanf_s("%f %f", &gip, &alpha);

        alpha = alpha / 180 * pi; 

        a = gip * sin(alpha);

        b = gip * cos(alpha);

        S = a * b / 2;

        printf("\n a = %6.3f\n b = %6.3f\n gip = %6.3f\n alpha = %6.3f\n S = %6.3f\n ", a, b, gip, alpha, S);

        return 0;
    }
