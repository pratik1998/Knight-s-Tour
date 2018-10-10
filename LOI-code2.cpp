//============================================================================
// Name        : LOI-code2.cpp
// Author      : Tapan Modi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define MAXN 1000
#define MAXM 1000

static const unsigned int Grid6_6[6][6][2] =
{
    {{4,5}, {5,6}, {4,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {0,3}, {3,5}, {0,6}, {0,7}},
    {{2,5}, {1,4}, {0,1}, {3,4}, {2,5}, {1,6}},
    {{2,5}, {5,6}, {4,7}, {0,2}, {1,5}, {0,6}},
    {{3,4}, {1,4}, {4,7}, {4,7}, {0,2}, {1,7}},
    {{2,3}, {1,3}, {1,0}, {3,0}, {0,2}, {0,1}}
};

static const unsigned int Grid6_8[6][8][2] =
{
    {{4,5}, {4,6}, {4,7}, {4,7}, {4,6}, {4,6}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {6,0}, {0,4}, {0,3}, {0,3}, {0,5}, {0,7}},
    {{2,5}, {1,4}, {0,5}, {2,5}, {2,5}, {0,3}, {2,5}, {1,6}},
    {{2,5}, {2,6}, {6,7}, {0,6}, {6,7}, {5,6}, {5,7}, {1,6}},
    {{3,4}, {1,4}, {3,7}, {1,4}, {1,3}, {1,4}, {2,7}, {1,7}},
    {{2,3}, {1,2}, {0,2}, {0,2}, {2,3}, {0,3}, {1,2}, {0,1}}
};

static const unsigned int Grid8_8[8][8][2] =
{
    {{4,5}, {5,6}, {5,7}, {4,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,5}, {3,6}, {0,3}, {3,6}, {3,6}, {0,3}, {5,6}, {0,7}},
    {{2,5}, {1,6}, {1,7}, {1,5}, {4,5}, {1,3}, {2,5}, {1,6}},
    {{2,3}, {1,5}, {2,5}, {2,4}, {6,7}, {2,4}, {0,5}, {1,6}},
    {{2,5}, {1,6}, {3,7}, {4,5}, {1,6}, {0,1}, {2,5}, {0,1}},
    {{3,5}, {5,6}, {1,4}, {1,2}, {4,5}, {0,5}, {2,5}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {2,7}, {0,1}, {4,7}, {0,7}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,3}, {1,3}, {1,2}, {0,1}}
};

static const unsigned int Grid8_10[8][10][2] =
{
    {{4,5}, {4,6}, {4,7}, {4,7}, {4,7}, {6,7}, {4,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {0,3}, {0,3}, {0,3}, {0,3}, {0,3}, {3,4}, {0,5}, {0,6}},
    {{2,4}, {1,6}, {0,6}, {6,7}, {2,4}, {4,6}, {5,7}, {5,6}, {2,5}, {0,1}},
    {{2,5}, {3,5}, {0,5}, {4,6}, {3,5}, {5,7}, {0,4}, {0,7}, {2,5}, {1,7}},
    {{2,5}, {2,6}, {2,7}, {3,5}, {2,4}, {0,3}, {2,7}, {1,3}, {0,1}, {1,6}},
    {{3,5}, {1,6}, {1,2}, {1,6}, {3,5}, {1,7}, {0,1}, {4,5}, {5,7}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {3,7}, {1,4}, {4,7}, {3,7}, {4,7}, {2,7}, {0,7}},
    {{2,3}, {1,3}, {0,2}, {0,3}, {0,3}, {1,3}, {0,3}, {0,3}, {1,2}, {0,1}}
};

static const unsigned int Grid10_10[10][10][2] =
{
    {{4,5}, {4,6}, {5,7}, {4,6}, {4,7}, {6,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {4,6}, {0,3}, {0,3}, {3,5}, {0,3}, {0,3}, {3,4}, {5,6}, {6,0}},
    {{2,4}, {1,6}, {0,2}, {0,1}, {2,4}, {6,7}, {5,6}, {1,6}, {2,5}, {0,1}},
    {{2,4}, {5,6}, {0,6}, {3,5}, {4,5}, {1,4}, {0,4}, {2,6}, {2,5}, {1,6}},
    {{2,5}, {4,5}, {0,7}, {4,5}, {2,6}, {2,5}, {0,2}, {0,1}, {0,6}, {1,6}},
    {{2,3}, {2,6}, {1,7}, {0,5}, {1,7}, {0,1}, {2,6}, {6,7}, {2,6}, {1,7}},
    {{3,5}, {1,6}, {1,3}, {2,7}, {1,5}, {3,7}, {1,7}, {2,3}, {2,5}, {6,7}},
    {{2,5}, {3,6}, {5,6}, {3,7}, {1,3}, {2,7}, {2,6}, {2,3}, {5,6}, {6,7}},
    {{2,4}, {1,3}, {4,7}, {3,4}, {4,7}, {1,7}, {4,7}, {3,4}, {2,7}, {1,7}},
    {{2,3}, {1,2}, {0,3}, {1,3}, {0,3}, {0,2}, {0,3}, {2,3}, {0,2}, {0,1}}
};

static const unsigned int Grid10_12[10][12][2] =
{
    {{4,5}, {4,6}, {6,7}, {4,7}, {5,6}, {4,7}, {5,7}, {4,7}, {4,6}, {4,7}, {5,6}, {6,7}},
    {{3,5}, {3,6}, {0,7}, {0,3}, {3,6}, {0,3}, {6,7}, {0,3}, {5,6}, {0,3}, {0,5}, {0,6}},
    {{2,3}, {1,2}, {6,7}, {2,6}, {3,4}, {1,7}, {5,6}, {1,2}, {5,7}, {2,4}, {2,5}, {1,6}},
    {{2,3}, {1,6}, {4,5}, {2,3}, {4,7}, {2,7}, {0,3}, {2,7}, {5,7}, {1,6}, {2,5}, {0,1}},
    {{4,5}, {2,6}, {2,3}, {3,5}, {0,4}, {2,3}, {0,3}, {1,7}, {4,6}, {1,7}, {2,5}, {1,6}},
    {{2,4}, {4,5}, {0,7}, {1,6}, {4,6}, {3,6}, {0,7}, {3,6}, {2,5}, {1,6}, {0,7}, {1,6}},
    {{2,3}, {1,6}, {0,7}, {0,5}, {1,3}, {4,6}, {0,7}, {2,4}, {3,7}, {4,5}, {2,5}, {1,6}},
    {{3,5}, {5,6}, {1,2}, {2,7}, {2,3}, {5,6}, {2,3}, {0,5}, {2,7}, {0,1}, {2,5}, {0,6}},
    {{2,4}, {3,4}, {4,7}, {4,7}, {1,2}, {4,7}, {3,4}, {4,7}, {4,7}, {4,7}, {1,2}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,2}, {0,3}, {1,3}, {0,3}, {0,1}, {0,3}, {0,2}, {0,1}}
};

static const int offsetDirArr[8][2] =
{{-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2, 1}, {1, 2}, {-1,2}, {-2,1}};

bool vis[MAXN][MAXM];
int trace[MAXN][MAXM];
pair<int,int> dim[MAXN][MAXN];
map<pair<int,int>,pair<int,int>> mpp;

void solveSubSystem(int n,int m,int offset_x, int offset_y) {
	int x = 0, y = 0;
	int i = 0;
	while(1)
	{
		trace[x + offset_x][y + offset_y] = ++i;
		vis[x + offset_x][y + offset_y] = true;
		dim[x+offset_x][y+offset_y].F = n;
		dim[x+offset_x][y+offset_y].S = m;
		const unsigned int *p = (n==6 && m==6) ? Grid6_6[x][y] :
								(n=8 && m==8) ? Grid8_8[x][y]: Grid10_10[x][y];
		const int *dir1 = offsetDirArr[(int)p[0]];
		const int *dir2 = offsetDirArr[(int)p[1]];
		if(!vis[x + offset_x + dir1[1]][y + offset_y + dir1[0]]){
			x = x + dir1[1];
			y = y + dir1[0];
		}
		else if(!vis[x + offset_x + dir2[1]][y + offset_y + dir2[0]]){
			x = x + dir2[1];
			y = y + dir2[0];
		}
		else{
			printf("Tour Completed\n");
			break;
		}
	}
}

void solve(int n, int m, int offset_x, int offset_y) {
	if(n < 12 || m < 12) {
		solveSubSystem(n,m,offset_x, offset_y);
		return;
	}
	int halve_x = n / 2;
	int halve_y = m / 2;
//	cout << halve_x << " " << halve_y << endl;
	pair<int,int> q1 = {halve_x - 1 + offset_x, halve_y - 1 + offset_y};
	pair<int,int> q2 = {halve_x + offset_x, halve_y - 1 + offset_y};
	pair<int,int> q3 = {halve_x - 1 + offset_x, halve_y + offset_y};
	pair<int,int> q4 = {halve_x + offset_x, halve_y + offset_y};
//	cout << q1.F << " " << q1.S << endl;
//	cout << q2.F << " " << q2.S << endl;
//	cout << q3.F << " " << q3.S << endl;
//	cout << q4.F << " " << q4.S << endl;
//	cout << endl;
	mpp[mp(q1.F - 1, q1.S)] = mp(q3.F - 2, q3.S + 1);
	mpp[q3] = mp(q4.F, q4.S + 2);
	mpp[mp(q4.F + 1, q4.S)] = mp(q2.F + 2, q2.S - 1);
	mpp[q2] = mp(q1.F, q1.S - 2);
//	cout << mpp[q2].F << "**" << mpp[q2].S  << " " << q1.F << "  " << q1.S<< endl;
	solve(halve_x, halve_y, offset_x, offset_y);
	solve(halve_x, halve_y, halve_x + offset_x, offset_y);
	solve(halve_x, halve_y, offset_x, halve_y + offset_y);
	solve(halve_x, halve_y, halve_x + offset_x, halve_y + offset_y);
}

void knightTour()
{
	int x=0,y=0;
	while(vis[x][y])
	{
		vis[x][y] = false;

	}
}

int main() {

	int x = 0, y = 0;
//	cin >> x >> y;
	int n;
    cin>>n;
	solve(n, n, 0, 0);
	for(auto it : mpp){
		cout << it.F.F << " " << it.F.S << " -> " << it.S.F << " " << it.S.S << " " << x++ << endl;
	}
	/*int i = 0;
	int offset_x = 0, offset_y = 0;

	int denom;
	if(!(n % 6)) denom = 6;
	else if(!(n % 8)) denom = 8;
	else if(!(n % 10)) denom = 10;
	cout << denom << endl;
	bool f = 0;
	while(1) {
		offset_x = (x / denom) * denom;
		offset_y = (y / denom) * denom;
		trace[x][y] = ++i;
		vis[x][y] = true;
		cout << x << " " << y << endl;
		const unsigned int *p = (denom == 6) ? Grid6_6[x - offset_x][y - offset_y]:
								(denom == 8) ? Grid8_8[x - offset_x][y - offset_y]:
								Grid10_10[x - offset_x][y - offset_y];

		const int *dir1 = offsetDirArr[(int)p[0]];
		const int *dir2 = offsetDirArr[(int)p[1]];
		if(mpp.count(mp(x, y))){

			int tx = mpp[mp(x, y)].F;
			int ty = mpp[mp(x, y)].S;
			f = 1;
			x = tx;
			y = ty;
//			cout << x << " ++ " << y << endl;
		}
		else if(!f){
			if(!vis[x + dir1[1]][y + dir1[0]]){
						x = x + dir1[1];
						y = y + dir1[0];
			}
			else if(!vis[x + dir2[1]][y + dir2[0]]){
				x = x + dir2[1];
				y = y + dir2[0];

			}
			else{
				printf("Tour Completed\n");
				break;
			}
		}
		else{
			if(!vis[x + dir1[1]][y + dir1[0]] && !mpp.count(mp(x + dir1[1], y + dir1[0]))){
				x = x + dir1[1];
				y = y + dir1[0];
				f = 0;
			}
			else if(!vis[x + dir2[1]][y + dir2[0]] && !mpp.count(mp(x + dir2[1], y + dir2[0]))){
				x = x + dir2[1];
				y = y + dir2[0];
				f = 0;
			}
			else{
				printf("Tour Completed\n");
				break;
			}
		}

	}*/
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << trace[i][j] << "\t";
		cout << endl;
	}
	return 0;
}