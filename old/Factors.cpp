#include <iostream>

int main()
{                        					// main
	const int min = 1;
	const int max = 100;
	int count = min, x, y;
	vector<int> factors {};
	vector<int> primes {};
	while (count <= max)
	{                       				//count while
		x = 1;
		while (x <= count) {				//x while
			y = 1;
			while (y <= count) {			//y while
				if (x * y == count && x <= y) {	//if open
					factors.push_back(x);
					if (x != y) factors.push_back(y);
				}                    		//close if
				y++;
			}                    			//close y while
			x++;
		}                     				//close x while
		cout << "factors of " << count << ": ";
		for(auto f : factors) {
			cout << f << ", ";
		}
		cout << endl;
		if (factors.size() == 2) primes.push_back(count);
		factors.clear();
		count++;
	}                      					//close count while
	cout << "primes (from " << min << " to " << max << "): ";
	for(auto p : primes) {
		cout << p << ", ";
	}
	cout << endl;

	return 0;
}
