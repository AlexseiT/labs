#include <stdio.h>

struct gagaga 
{
	int a;
	float toto;
	char sobaka;
};


int main() {
    
	struct gagaga darova;
	darova.a = 1;
	darova.toto = 30.5;
	darova.sobaka = 'A';

	struct gagaga LOL;
	LOL.a=2;
	LOL.toto=17.8;
	LOL.sobaka='B';

	printf_s("%d\n",darova.a );
	printf_s("%d\n",LOL.a);
	return 0;
}