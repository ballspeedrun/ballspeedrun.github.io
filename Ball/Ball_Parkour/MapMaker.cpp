#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define N(a) int((a).size())
#define V(a) (a).begin(), (a).end()
using namespace std;
using LS = long long;
using IU = unsigned int;
using LU = unsigned long long;
mt19937 rng(__builtin_ia32_rdtsc());
void col(int c1, int c2) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c1 * 16 + c2);
}
void HideCursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}
COORD coord;
void jump(int x, int y) {
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
char cls_str[6000];
bool cls_init = false;
void getcls() {
	cls_init = true;
	int x = 0;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 30; ++j) cls_str[x++] = ' ';
		cls_str[x++] = '\n';
	}
}
void cls() {
	if (!cls_init) getcls();
	jump(0, 0);
	puts(cls_str);
	jump(0, 0);
}
double getTs() {
	return double(clock()) / CLOCKS_PER_SEC;
}
int ch;
void towasd() {
	if (ch == 224 or ch == -32) {
		ch = getch();
		if (ch == 72) ch = 'w';
		else if (ch == 80) ch = 's';
		else if (ch == 75) ch = 'a';
		else if (ch == 77) ch = 'd';
	}
	else if (isupper(ch)) ch += 'a' - 'A';
}
namespace project_2 {
	constexpr int xn = 200;
	int nx, ny, g[xn][xn];
	pair<int, int> a[xn][xn];
	constexpr int xobj = 200, aux = 100;
	int cobj[xobj], tobj[xobj];
	string sobj[xobj];
	vector<int> objs;
	void insert_obj(int id, int c, string s, int t) {
		cobj[id + aux] = c;
		sobj[id + aux] = s;
		tobj[id + aux] = t;
		if ((t != 1 or id == 1) and id != -100) objs.push_back(id);
	}
	void init_obj() {
		insert_obj(-100, 7, "□", -1);
		freopen("objects.in", "r", stdin);
		int nobj;
		cin >> nobj;
		string s;
		getline(cin, s);
		for (int i = 0; i < nobj; ++i) {
			int id, c, t;
			cin >> id >> c >> t;
			getline(cin, s);
			getline(cin, s);
			insert_obj(id, c, s, t);
		}
		freopen("CON.in", "r", stdin); 
		sort(V(objs));
	}
	int get_g(int x, int y) {
		if (x < 0 or x >= nx or y < 0 or y >= ny) return -100;
		return g[x][y];
	}
	int X, Y, cur;
	void print() {
		cls();
		jump(0, 0);
		for (int i = -7; i <= 7; ++i) {			
			for (int j = -7; j <= 7; ++j) {
				if (i or j) col(0, cobj[get_g(X + i, Y + j) + aux]);
				else col(8, cobj[get_g(X + i, Y + j) + aux]);
				cout << sobj[get_g(X + i, Y + j) + aux];
			}
			cout << '\n';
		}
	}
	void work() {
		init_obj();
		cls();
		col(0, 15);
		cout << "imput [nx] [ny]: ";
		cin >> nx >> ny;
		X = Y = cur = 0;
		print();
		while (true) if (kbhit()) {
			ch = getch();
			towasd();
			if (ch == 27) break;
			bool move = false;
			if (ch == 'w') {
				if (X > 0) {
					--X;
					move = true;
				}
			}
			if (ch == 's') {
				if (X + 1 < nx) {
					++X;
					move = true;
				}
			}
			if (ch == 'a') {
				if (Y > 0) {
					--Y;
					move = true;
				}
			}
			if (ch == 'd') {
				if (Y + 1 < ny) {
					++Y;
					move = true;
				}
			}
			if (move) {
				print();
				cur = lower_bound(V(objs), g[X][Y]) - objs.begin();
			}
			if (ch == 'q') {
				(cur += N(objs) - 1) %= N(objs);
				assert(0 <= cur and cur < N(objs)); 
				g[X][Y] = objs[cur];
				jump(14, 7);
				col(8, cobj[g[X][Y] + aux]);
				cout << sobj[g[X][Y] + aux];
			}
			if (ch == 'e') {
				(cur += 1) %= N(objs);
				assert(0 <= cur and cur < N(objs));
				g[X][Y] = objs[cur];
				jump(14, 7);
				col(8, cobj[g[X][Y] + aux]);
				cout << sobj[g[X][Y] + aux];
			}
		}
		cls();
		freopen("map.out", "w", stdout);
		cout << nx << ' ' << ny << '\n';
		for (int i = 0; i < nx; ++i) {
			for (int j = 0; j < ny; ++j) {
				int t = tobj[g[i][j] + aux];
				cout << g[i][j] << '\t';
				if (t == 6 or t == 3) cout << a[i][j].first;
				cout << '\t';
				if (t == 3) cout << a[i][j].second;
				cout << '\t';
			}
			cout << '\n';
		}
		freopen("CON.out", "w", stdout);
		jump(0, 0);
		cout << "map saved successfully! go check [map.out].\n\n";
		cout << "P.S. you need to set the infos about tp gates or stars yourself.\n\n";
	}
};
void play() {
	jump(4, 1);
	col(0, 11);
	cout << " ◆ Ball Mapmaker ◆\n\n";
	col(0, 12);
	puts("●");
	col(0, 7);
	puts("■■■■■■■■■■■■■■■\n");
	col(0, 15);
	puts("input any key to start.");
	clock_t tim = clock(), now = clock();
	double sk = double(now - tim) / CLOCKS_PER_SEC;
	int ago1 = 6, ago2 = 0;
	while (true) {
		if (kbhit()) {
			ch = getch();
			break;
		}
		now = clock();
		if (double(now - tim) / CLOCKS_PER_SEC - sk >= 0.15) {
			jump(ago1 % 30, 3);
			col(0, 12);
			printf("  ");
			ago1 += 2;
			jump(ago1 % 30, 3);
			printf("●");
			jump(ago2 % 30, 3);
			col(0, 10);
			printf("  ");
			ago2 += 2;
			jump(ago2 % 30, 3);
			printf("●");
			sk = double(now - tim) / CLOCKS_PER_SEC;
		}
	}
	project_2::work();
}
int main() {
	cout << fixed << setprecision(3);
	HideCursor();
	system("title Ball Mapmaker");
	system("mode con cols=60 lines=36");
	play();
	return 0;
}
