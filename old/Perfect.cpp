//DANGER WILL ROBINSON!!! DANGER

//David Russell (leader) & Rachel Brockington
//Seha Loo
//CS 220-02
//2-19-98
//Assignment #6
//calculates perfect numbers between 1 & 100


#include<iostream.h>
void Check (int num, int max);

int main()
{
	int min=1;
	int max = 100'000;
	cout<<"These are the perfect numbers between " << min << " & " << max << ":"<<endl;
	//the fist perfect number greater than 8,128 is > 33M
	//the largest known perfect number has > 49K digits
	//https://en.wikipedia.org/wiki/List_of_Mersenne_primes_and_perfect_numbers
	Check(min, max);
	return 0;
}

void Check (int num, int max)
{
	int fact, sum;
	while (num <= max)
	{
		if (num % 10'000 == 0) cerr << "."; //write . out to cerr because it doesn't wait like cout does
		sum = 0;
		for (fact = 1; fact < num; fact++)
		{
			if(num % fact == 0) sum = fact + sum;
		}

		if (sum == num)
		{
			for (fact = 1; fact < num; fact++)
			{
				if (num % fact == 0) sum = fact + sum;
			}
			cout << num << " is a perfect number." << endl;
		}
		num++;
	}
}
