#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Point {
public:
	int x;
	int y;
	bool visited;
	int distance;
	bool valid;

	Point(int cord_x, int cord_y, bool validity=false, bool v=false, int d=0) {
		x = cord_x;
		y = cord_y;
		visited = v;
		distance = d;
		valid = validity;
	}

	int getX() { return x; }
	int getY() { return y; }
	int walkedLenth() { return distance; }
	bool isVisited() { return visited; }
};

class Labyrinth {
public:
	vector<vector<Point > > board;
	vector<Point> openings;
	int max_walked_length;
	
	Labyrinth(vector< vector < char > > input) {
		for(int i=0; i<input.size(); i++) {
			vector<Point> temp_row;
			for(int j=0; j<input[i].size(); j++) {
				if(input[i][j] == '.') temp_row.push_back(Point(i, j, true));
				else temp_row.push_back(Point(i, j, false));
				if(i == 0 || i == input.size()-1 || j == 0 || j == input[i].size()-1) 
					if(input[i][j] == '.') openings.push_back(Point(i, j, true));
			}
			board.push_back(temp_row);
		}
		max_walked_length = 0;
	}

	vector<Point> findNeighbor(int x, int y) {
		vector<Point> neighbor;
		for (int i=-1; i<2; i++) {
			for(int j=-1; j<2; j++) {
				if(i == 0 && j == 0) continue;
				if(i == j || i+j == 0) continue;
				if(i+x < 0 || i+x >= board.size()) continue;
				if(j+y < 0 || j+y >= board[i].size()) continue;
				if(board[i+x][j+y].valid) neighbor.push_back(board[i+x][j+y]);
			}
		}
		return neighbor;
	}
	
	int pathFinderUtility(int x, int y, vector<Point> temp_path, vector<Point> &max_path) {
		if(!board[x][y].valid) return max_path.size();
		if(board[x][y].visited) return max_path.size();
		temp_path.push_back(board[x][y]);
		if(max_path.size() < temp_path.size()){
			max_path.clear();
			for(int i=0; i<temp_path.size(); i++)
				max_path.push_back(temp_path[i]);
		}
		board[x][y].visited = true;
		vector<Point> neighbors = findNeighbor(x, y);
		for(int i=0; i<neighbors.size(); i++)
			pathFinderUtility(neighbors[i].x, neighbors[i].y, temp_path, max_path);
		board[x][y].visited = false;
		return max_path.size();
	}

	vector<Point> findLongestPath(){
		int max_length = 0;
		vector<Point> max_path;
		vector<Point> temp_path;
		for(int i=0; i<openings.size(); i++)
			int lenght = pathFinderUtility(openings[i].x, openings[i].y,temp_path, max_path);
		max_walked_length = max_path.size();
		return max_path;
	}
	
	void printLayout(){
		cout<<"----------------- LABYRINTH ----------------"<<endl;
		for(int i=0; i<board.size(); i++) {
			for(int j=0; j<board[i].size(); j++) {
				if(board[i][j].valid) cout<<'.';
				else cout<<'#';
			}
			cout<<endl;
		}
		cout<<"--------------------------------------------"<<endl;
		cout<<endl;
	}

};

void readLabyrinth(string input_file_path, vector<vector< char > > &board) {
	char character;
	vector<char> temp;
	ifstream readFile;
	//readFile.open("temp_input.txt");
	readFile.open(input_file_path.c_str());
	cout<<"[INPUT]: Reading from the file: "<<input_file_path<<endl;
	while(!readFile.eof()) {
		readFile.get(character);
		if(character == '\n') {
			if(temp.size() < 1) continue;
			board.push_back(temp);
			temp.clear();
		}
		else temp.push_back(character);
	}
	readFile.close();
	cout<<"[READING]: Reading file completed... Closing Input File"<<endl;
}

void writeLabyrinth(string output_file_path, vector<vector<char > > input, vector<Point> max_path) {
	for(int i=0; i<max_path.size(); i++)
		input[max_path[i].x][max_path[i].y] = '0'+i%10;
	cout<<"[OUTPUT]: Opening file for writing the Results"<<endl;
	ofstream writeFile(output_file_path.c_str());
	writeFile<<max_path.size()<<endl;
	for(int i=0; i<input.size(); i++) {
		for(int j=0; j<input[i].size(); j++)
			writeFile<<input[i][j];
		writeFile<<endl;
	}
	cout<<"[OUTPUT]: Output written successfully int file: "<<output_file_path<<endl;
	writeFile.close();
}

void printResult(vector<Point> max_path, vector<vector<char > > input){
	for(int i=0; i<max_path.size(); i++)
		input[max_path[i].x][max_path[i].y] = ('0'+i%10);
	cout<<"-- -- -- Labyrinth with Max Path possible -- -- --"<<endl;
	cout<<max_path.size()<<endl;
	for(int i=0; i<input.size(); i++) {
		for(int j=0; j<input[i].size(); j++)
			cout<<input[i][j];
		cout<<endl;
	}
	cout<<"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --"<<endl;
}


int main(int argc, char *argv[]) {
	vector<vector<char > > input;
	readLabyrinth(argv[1], input);
	Labyrinth labyrinth(input);
	labyrinth.printLayout();
	vector<Point> max_path = labyrinth.findLongestPath();
	writeLabyrinth(argv[2], input, max_path);
	printResult(max_path, input);
	return 0;
}
