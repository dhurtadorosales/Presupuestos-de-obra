/* getdate example */ 

#include <dos.h>
#include <stdio.h>

void llameme(void);   /* Función invocada desde main.   */

struct date d;
int main(void)
{
	llameme();
	printf("The current year is: %d\n", d.da_year);
	printf("The current day is: %d\n", d.da_day);
	printf("The current month is: %d\n", d.da_mon);
	return 0;
}


void llameme(void)
{


	getdate(&d);
	printf("The current year is: %d\n", d.da_year);
	printf("The current day is: %d\n", d.da_day);
	printf("The current month is: %d\n", d.da_mon);
}

