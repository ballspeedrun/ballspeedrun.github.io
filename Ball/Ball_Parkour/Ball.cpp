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
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 100; ++j) cls_str[x++] = ' ';
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
namespace project_1 {
	constexpr int xn = 200, xm = 100;
	int nx, ny, g[xn][xn], f[xn][xn];
	pair<int, int> a[xn][xn];
	int nM, m;
	string name[xm];
	double best[xm];
	void init_modes() {
		freopen("modes.in", "r", stdin);
		cin >> nM;
		getline(cin, name[0]);
		for (int i = 0; i < nM; ++i) getline(cin, name[i]);
		freopen("CON.in", "r", stdin);
		for (int i = 0; i < nM; ++i) best[i] = -1;
	}
	void jump_g(int x, int y) {
		jump(y % 30 * 2, x % 30);
	}
	constexpr int xobj = 200, aux = 100;
	int cobj[xobj], tobj[xobj], mod_50[100];
	string sobj[xobj];
	vector<int> objs;
	void insert_obj(int id, int c, string s, int t) {
		cobj[id + aux] = c;
		sobj[id + aux] = s;
		tobj[id + aux] = t;
		objs.push_back(id);
	}
	void init_obj() {
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
	}
	int t_obj(int x, int y) {
		return tobj[g[x][y] + aux];
	}
	pair<int, int> exfind(int x, int y) {
		return t_obj(x, y) == 3 ? exfind(a[x][y].first, a[x][y].second) : make_pair(x, y); 
	}
	int real_obj(int x, int y) {
		auto p = exfind(x, y);
		return t_obj(p.first, p.second);
	}
	void print_obj(int x) {
		col(0, cobj[x + aux]);
		cout << sobj[x + aux];
	}
	void print(int x, int y) {
		jump_g(x, y);
		print_obj(g[x][y]);
	}
	void reduct(int x, int y) {
		g[x][y] = f[x][y];
		print(x, y);
	}
	bool block_side(int x, int y) {
		auto t = real_obj(x, y);
		return t == 1 or t == 2 or t == 5 or t == 7;
	}
	bool block_top(int x, int y) {
		auto t = real_obj(x, y);
		return t == 2 or t == 5 or t == 7;
	}
	int score;
	bool alive, win;
	int X, Y, object;
	int cnt_up, aut_up, lst;
	bool falin;
	double tlst, tup, tfall, speed;
	void place(int x, int y) {
		X = x;
		Y = y;
	}
	int zone_x, zone_y;
	void print() {
		g[X][Y] = cnt_up <= 1 ? object : object + 50;
		if (X / 30 == zone_x and Y / 30 == zone_y) print(X, Y);
		else {
			int _x = X / 30, _y = Y / 30;
			for (int i = 0; i < 30; ++i) for (int j = 0; j < 30; ++j) if (g[_x * 30 + i][_y * 30 + j] != g[zone_x * 30 + i][zone_y * 30 + j]) print(_x * 30 + i, _y * 30 + j);
			zone_x = _x;
			zone_y = _y;
		}
	}
	void leave() {
		reduct(X, Y);
	}
	void moveto(int x, int y) {
		leave();
		place(x, y);
		int t = t_obj(X, Y);
		if (t == 3) {
			moveto(a[X][Y].first, a[X][Y].second);
			return;
		} else if (t == 4) {
			alive = false;
			return;
		} else if (t == 6 and score >= a[X][Y].first) {
			win = true;
			return;
		}
		print();
	}
	void init(int x, int y) {
		place(x, y);
		g[X][Y] = object;
		cnt_up = aut_up = lst = falin = 0;
		tlst = tup = tfall = getTs() - 0.3;
		speed = 0.2;
	}
	void move_up() {
		if (cnt_up >= 2)
			return;
		if (block_side(X - 1, Y))
			return;
		tup = getTs();
		if (tup - tlst > 0.3)
			lst = 0;
		cnt_up += 1;
		aut_up += 1;
		if (!block_side(X - 1, Y + lst)) moveto(X - 1, Y + lst);
		else moveto(X - 1, Y);
	}
	void auto_up() {
		if (getTs() - tup < 0.2)
			return;
		aut_up -= 1;
		if (block_side(X - 1, Y))
			return;
		if (!block_side(X - 1, Y + lst))
			moveto(X - 1, Y + lst);
		else {
			auto p = exfind(X - 1, Y + lst);
			if (t_obj(p.first, p.second) == 5) {
				reduct(p.first, p.second);
				score += 1;
			}
			moveto(X - 1, Y);
		}
	}
	void fall() {
		auto T = getTs();
		if (T - tfall < speed)
			return;
		tfall = T;
		if (!falin) {
			falin = true;
			if (!cnt_up)
				cnt_up += 1;
			return;
		}
		speed = 0.5 / (0.5 / speed + 1);
		moveto(X + 1, Y);
	}
	void left() {
		lst = -1;
		if (cnt_up)
			return;
		tlst = getTs();
		if (block_side(X, Y - 1))
			return;
		moveto(X, Y - 1);
	}
	void right() {
		lst = +1;
		if (cnt_up)
			return;
		tlst = getTs();
		if (block_side(X, Y + 1))
			return;
		moveto(X, Y + 1);
	}
	void free() {
		auto p = exfind(X + 1, Y);
		if (block_top(X + 1, Y)) {
			speed = 0.2;
			falin = false;
			if (cnt_up) {
				cnt_up = 0;
				print();
			} 
		} else if (!aut_up) fall();
		if (aut_up) auto_up();
	}
	void W() {
		move_up();
	}
	void A() {
		left();
	}
	void D() {
		right(); 
	}
	void S() {
	}
	void print_mode() {
		cls();
		col(0, 11);
		cout << " ¡ô select mode ¡ô\n\n";
		for (int i = 0; i < nM; ++i) {
			col(0, i == m ? 14 : 15);
			cout << "   " << name[i] << '\n';
		}
		col(0, 11);
		cout << "\n ¡ô select skin ¡ô\n\n";
		col(0, cobj[object + aux]);
		cout << "   ¡ñ\n";
		for (; (ch = getch()); ) {
			towasd();
			if (ch == ' ') return;
			if (ch == 'w') {
				if (!m) continue;
				jump(3, 2 + m);
				col(0, 15);
				cout << name[m--];
				jump(3, 2 + m);
				col(0, 14);
				cout << name[m];
			}
			else if (ch == 's') {
				if (m + 1 >= nM) continue;
				jump(3, 2 + m);
				col(0, 15);
				cout << name[m++];
				jump(3, 2 + m);
				col(0, 14);
				cout << name[m];
			}
			else if (ch == 'a' or ch == 'd') {
				if (ch == 'a') {
					object -= 1;
					if (!object) object = 8;
				}
				else if (ch == 'd') {
					object += 1;
					if (object == 9) object = 1;
				}
				jump(3, 5 + nM);
				col(0, cobj[object + aux]);
				cout << "¡ñ";
			}
		}
	}
	void FI(int x) {
		string s = "level", y;
		stringstream ss;
		ss << x;
		ss >> y;
		s = s + y;
		s = s + ".in";
		freopen(s.c_str(), "r", stdin);
	}
	void init_map() {
		score = 0;
		win = false;
		alive = true;
		FI(m);
		cin >> nx >> ny;
		int sx = 0, sy = 0, _nx = nx, _ny = ny;
		_nx = ((nx + 1) / 30 + 1) * 30;
		sx = (_nx - nx) / 2;
		_ny = ((ny + 1) / 30 + 1) * 30;
		sy = (_ny - ny) / 2;
		for (int i = sx; i < sx + nx; ++i) for (int j = sy; j < sy + ny; ++j) {
			cin >> g[i][j];
			f[i][j] = t_obj(i, j) == 5 or t_obj(i, j) == 1 ? 0 : g[i][j];
			if (t_obj(i, j) == 3) cin >> a[i][j].first >> a[i][j].second;
			else if (t_obj(i, j) == 1) init(i, j);
			else if (t_obj(i, j) == 6) cin >> a[i][j].first;
		}
		for (int i = 0; i < _nx; ++i) for (int j = 0; j < _ny; ++j) if (!(sx <= i and i < sx + nx) or !(sy <= j and j < sy + ny)) f[i][j] = g[i][j] = -1; 
		nx = _nx;
		ny = _ny;
		cls();
		zone_x = X / 30;
		zone_y = Y / 30;
		for (int i = 0; i < 30; ++i) for (int j = 0; j < 30; ++j) print(zone_x * 30 + i, zone_y * 30 + j);
		freopen("CON.in", "r", stdin);
	}
	bool skip0, skip1;
	void run() {
		if (!skip0) print_mode();
		init_map();
		auto T = getTs();
		jump(0, 30 + 1);
		col(0, 15);
		cout << "time : 0.000";
		if (best[m] >= 0) {
			jump(0, 30 + 3);
			cout << "best : " << best[m];
		}
		for (; alive and !win; ) {
			if (kbhit()) {
				ch = getch();
				towasd();
				if (ch == 27) return;
				if (ch == 'r') return skip1 = true, void();
				if (ch == 'w') W();
				else if (ch == 'a') A();
				else if (ch == 's') S();
				else if (ch == 'd') D();
			}
			free();
			jump(7, 30 + 1);
			col(0, 15);
			cout << getTs() - T;
		}
		if (win) {
			jump_g(X, Y);
			col(0, cobj[object + aux]);
			cout << "¢Ù";
			double useT = getTs() - T;
			if (best[m] < 0 or useT < best[m]) {
				jump(7, 30 + 1);
				cout << useT;
				if (best[m] >= 0) {
					jump(6, 30 + 4);
					cout << "-" << best[m] - useT;
					best[m] = useT;
				}
				else best[m] = useT;
			}
		}
		Sleep(500);
		for (; kbhit(); ) {
			ch = getch();
			towasd();
			if (ch == 'r') return skip1 = true, void(); 
		}
		jump(0, 30 + 5);
		col(0, 15);
		printf("input any key to continue.");
		while (true) if (kbhit()) {
			ch = getch();
			towasd();
			if (ch == 'r') skip1 = true;
			return;
		}
	}
	void work() {
		init_obj();
		init_modes();
		m = 0;
		object = 1;
		skip0 = skip1 = false;
		for (; true; ) {
			skip0 = skip1;
			skip1 = false;
			run();
		}
	}
};
void play() {
	jump(5, 1);
	col(0, 11);
	cout << " ¡ô Ball Parkour ¡ô\n\n";
	col(0, 12);
	puts("¡ñ");
	col(0, 7);
	puts("¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö¡ö\n");
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
			printf("¡ñ");
			jump(ago2 % 30, 3);
			col(0, 10);
			printf("  ");
			ago2 += 2;
			jump(ago2 % 30, 3);
			printf("¡ñ");
			sk = double(now - tim) / CLOCKS_PER_SEC;
		}
	}
	project_1::work();
}
int main() {
	cout << fixed << setprecision(3);
	HideCursor();
	system("title Ball Parkour");
	system("mode con cols=60 lines=36");
	play();
	return 0;
}

