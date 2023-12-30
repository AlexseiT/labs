#include <stdio.h>
#include <math.h> 
int main()
{
    float x, y = 2, t, z = 4, c, s,k;

    c = 1 + y * y;
    t = 5 / c;

    k = t - z;
    s = 3 * sinh(k);
    x = 2 * y + s;




    printf("\n x = %6.3f ", x);

    return 0;
}