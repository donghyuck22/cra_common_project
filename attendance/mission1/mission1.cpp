#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> player;
int player_id_cnt = 0;
string idToName[100];
int attendanceData[100][7];
int points[100];
int grade[100];
int wednesdayCount[100];
int weekendCount[100];

void saveAttendanceOfPlayers(const string& name, const string& dayOfWeek) {
	if (player.count(name) == 0) {
		player_id_cnt++;
		player[name] = player_id_cnt;
		idToName[player_id_cnt] = name;
	}
	int player_id = player[name];

	int dayIndex = 0;
	int addedPoints = 0;

	if (dayOfWeek == "monday") { 
		dayIndex = 0; 
		addedPoints = 1; 
	}
	else if (dayOfWeek == "tuesday") { 
		dayIndex = 1; 
		addedPoints = 1; 
	}
	else if (dayOfWeek == "wednesday") { 
		dayIndex = 2; 
		addedPoints = 3; 
		wednesdayCount[player_id]++;
	}
	else if (dayOfWeek == "thursday") { 
		dayIndex = 3; 
		addedPoints = 1; 
	}
	else if (dayOfWeek == "friday") { 
		dayIndex = 4; 
		addedPoints = 1; 
	}
	else if (dayOfWeek == "saturday") { 
		dayIndex = 5; 
		addedPoints = 2; 
		weekendCount[player_id]++;
	}
	else if (dayOfWeek == "sunday") { 
		dayIndex = 6; 
		addedPoints = 2; 
		weekendCount[player_id]++;
	}

	attendanceData[player_id][dayIndex]++;
	points[player_id] += addedPoints;
}

void inputAttendanceData(const string& filename) {
	ifstream fin(filename);
	string name, dayOfWeek;
	while (fin >> name >> dayOfWeek) {
		saveAttendanceOfPlayers(name, dayOfWeek);
	}
}

void applyBonusesAndGrades() {
	for (int id = 1; id <= player_id_cnt; id++) {
		if (wednesdayCount[id] >= 10) {
			points[id] += 10;
		}
		if (weekendCount[id] >= 10) {
			points[id] += 10;
		}

		if (points[id] >= 50) {
			grade[id] = 1;
		}
		else if (points[id] >= 30) {
			grade[id] = 2;
		}
		else {
			grade[id] = 0;
		}
	}
}

void printResults() {
	for (int id = 1; id <= player_id_cnt; id++) {
		cout << "NAME : " << idToName[id] << ", ";
		cout << "POINT : " << points[id] << ", ";
		cout << "GRADE : ";

		if (grade[id] == 1)      
			cout << "GOLD\n";
		else if (grade[id] == 2) 
			cout << "SILVER\n";
		else                     
			cout << "NORMAL\n";
	}
}

void printRemovedPlayers() {
	cout << "\n";
	cout << "Removed player\n";
	cout << "==============\n";
	for (int id = 1; id <= player_id_cnt; id++) {
		if (grade[id] == 0 && wednesdayCount[id] == 0 && weekendCount[id] == 0) {
			cout << idToName[id] << "\n";
		}
	}
}

int main() {
	//1. 출석 처리 데이터
	inputAttendanceData("attendance_weekday_500.txt");

	//2. 점수 부여 및 등급 지정
	applyBonusesAndGrades();

	// 3. 결과 출력
	printResults();

	// 4. 탈락 후보 출력
	printRemovedPlayers();
}