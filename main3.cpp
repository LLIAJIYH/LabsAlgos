#include <iostream>
#include <vector>
using namespace std;


class Game{
	protected:
		vector<vector<int>> Pole; // game pole
		int x, y; // position of player
		int len; // len of matrix
	public:
		void print(){
			cout << endl;
			for(int i = 0; i < len; i++){
				for(int j = 0; j < len; j++){
					cout << Pole[i][j] << " ";
				}
				cout << endl;	
			}
		}
		
		void makeField(int n){
			len = n;
			Pole.resize(n);
			for(int i = 0; i < n; i++){
				Pole[i].resize(n);
			}
			//print();
		}
		
		void resizePole(int n){
			len = n;
			Pole.resize(n);
			for(int i = 0; i < n; i++){
				Pole[i].resize(n);
			}			
		}
		
		void setWalls(){
			for(int i = 0; i < len; i++){
				for(int j = 0; j < len; j++){
					Pole[i][j] = rand()%2;
				}
			}
		}
		
		void setPosition(int _x, int _y){
			x = _x;
			y = _y;
			Pole[x][y] = 2;
		}
		
		void goUp(){
			if(x-1 >= 0 && Pole[x-1][y] != 1){
				Pole[x-1][y] = 2;
				Pole[x][y] = 0;
				x -= 1;
				print();
			}else{
				cout << "can't move to this position" << endl;
			}
		}

		void goDown(){
			if(x+1 <= len-1 && Pole[x+1][y] != 1){
				Pole[x+1][y] = 2;
				Pole[x][y] = 0;
				x += 1;
				print();
			}else{
				cout << "can't move to this position" << endl;
			}
		}
		
		void goLeft(){
			if(y-1 >= 0 && Pole[x][y-1] != 1){
				Pole[x][y-1] = 2;
				Pole[x][y] = 0;
				y -= 1;
				print();
			}else{
				cout << "can't move to this position" << endl;
			}			
		}

		void goRight(){
			if(y+1 <= len-1 && Pole[x][y+1] != 1){
				Pole[x][y+1] = 2;
				Pole[x][y] = 0;
				y += 1;
				print();
			}else{
				cout << "can't move to this position" << endl;
			}			
		}
		
		void startGame(){
			char button = 'w';
			while(button != 'e'){
				cin >> button;
				if(button == 'w') goUp();
				if(button == 'a') goLeft();
				if(button == 's') goDown();
				if(button == 'd') goRight();
			}
		}
};	

int main(){
	Game game;
	int n, x, y;
	cin>>n;
	cin>>x;
	cin>>y;
	game.makeField(n);
	game.setWalls();
	game.setPosition(x, y);
	game.print();
	game.startGame();
}
