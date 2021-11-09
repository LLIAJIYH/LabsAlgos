#include <iostream>
using namespace std;

class Student{
public:
	int stud;
	void setStud(int s){
		stud = s;
	}
	void Reverse(){
		int stud2 = stud;
		for(int i = 0; i < 10; i++){
				int x = stud2%10;
				cout << x;
				stud2 /= 10;
		}
		cout << endl;
	}
	void Max(){
		int max = 0;
		int stud2 = stud;
		for(int i = 0; i < 10; i++){
			int x = stud2%10;
			if (x > max) max = x;
			stud2 /= 10;
		}
		cout << max << endl;
	}
	void Min(){
		int min = 9;
		int stud2 = stud;
		for(int i = 0; i < 10; i++){
			int x = stud2%10;
			if (x < min) min = x;
			stud2 /= 10;
		}
		cout << min << endl;
	}
};

int main(){
	int stud;
	cin >> stud;
	Student student1;
	student1.setStud(stud);
	student1.Reverse();
	student1.Max();
	student1.Min();
}
