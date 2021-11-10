#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
public:
	vector<vector<int>> arr;
	int n;
	
	void setLen(int N){
		n = N;
		arr.resize(N);
		for(int i = 0; i<N; i++){
			arr[i].resize(N);
			for(int j = 0; j<N; j++){
				arr[i][j] = j+1;
				
			}
			rotate(arr[i].begin(), arr[i].begin() + i, arr[i].end());
		}
	}
	
	void print(){
		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++){
					cout << arr[i][j] << " "; 
			}
			cout << endl;
		}
	}
};

int main(){
	int n;
	cin >> n;
	Matrix matrix;
	matrix.setLen(n);
	matrix.print(); 
}
