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
	string name[xm] = {"FirstRun", "2nd Run", "Vine Lover", "Tree", "Beyond The Brick", "R U Sure"};
	double best[xm];
	void init_modes() {
		nM = 6;
		for (int i = 0; i < nM; ++i) best[i] = -1;
	}
	void jump_g(int x, int y) {
		jump(y * 2 - 2, x - 1);
	}
	constexpr int xobj = 200, aux = 100;
	int cobj[xobj], tobj[xobj], mod_50[100];
	string sobj[xobj];
	void insert_obj(int id, int c, string s, int t) {
		cobj[id + aux] = c;
		sobj[id + aux] = s;
		tobj[id + aux] = t;
	}
	void init_obj() {
		insert_obj(20, 1, "¡ö", 0);
		insert_obj(21, 9, "¡ö", 0);
		insert_obj(22, 3, "¡ö", 0);
		insert_obj(23, 11, "¡ö", 0);
		insert_obj(24, 8, "¡ö", 0);
		insert_obj(0, 0, "  ", 0); // backgrounds
		insert_obj(1, 12, "¡ñ", 1);
		insert_obj(2, 10, "¡ñ", 1);
		insert_obj(3, 5, "¡ñ", 1);
		insert_obj(4, 8, "¡ñ", 1); 
		insert_obj(5, 9, "¡ñ", 1);
		insert_obj(6, 11, "¡ñ", 1); 
		insert_obj(7, 4, "¡ñ", 1);
		insert_obj(8, 2, "¡ñ", 1);
		insert_obj(51, 12, "¡ô", 1);
		insert_obj(52, 10, "¡ô", 1);
		insert_obj(53, 5, "¡ô", 1);
		insert_obj(54, 8, "¡ô", 1); 
		insert_obj(55, 9, "¡ô", 1);
		insert_obj(56, 11, "¡ô", 1); 
		insert_obj(57, 4, "¡ô", 1);
		insert_obj(58, 2, "¡ô", 1); // player
		insert_obj(-1, 7, "¡ö", 2);
		insert_obj(-11, 11, "¡ö", 2);
		insert_obj(-14, 14, "¡ö", 2);
		insert_obj(-15, 15, "¡ö", 2);// barrier
		insert_obj(30, 13, "¡ö", 3); // teleport
		insert_obj(-2, 6, "¡ø", 4);
		insert_obj(-3, 6, "¨‹", 4);
		insert_obj(-20, 15, "¡ø", 4);
		insert_obj(-21, 15, "¨‹", 4);
		insert_obj(-22, 13, "¡è", 4); // spike
		insert_obj(-40, 14, "¨ˆ ", 5);
		insert_obj(-41, 2, "¨ˆ ", 5); // sand
		insert_obj(40, 14, "¡ï", 6); // crown
		insert_obj(-30, 14, "¡õ", 7);
		insert_obj(-31, 6, "¡õ", 7); // tricky square
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
	void change(int x, int y, int z) {
		g[x][y] = z;
		print(x, y);
	}
	void reduct(int x, int y) {
		change(x, y, f[x][y]);
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
	struct player_t {
		int X, Y, object;
		int cnt_up, aut_up, lst;
		bool falin;
		double tlst, tup, tfall, speed;
		void place(int x, int y) {
			X = x;
			Y = y;
		}
		void print() {
			change(X, Y, cnt_up <= 1 ? object : object + 50);
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
			g[x][y] = object;
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
	} player;
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
		col(0, cobj[player.object + aux]);
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
					player.object -= 1;
					if (!player.object) player.object = 8;
				}
				else if (ch == 'd') {
					player.object += 1;
					if (player.object == 9) player.object = 1;
				}
				jump(3, 5 + nM);
				col(0, cobj[player.object + aux]);
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
		_nx = ((nx - 1) / 30 + 1) * 30;
		sx = (_nx - nx) / 2;
		_ny = ((ny - 1) / 30 + 1) * 30;
		sy = (_ny - ny) / 2;
		for (int i = sx + 1; i <= sx + nx; ++i) for (int j = sy + 1; j <= sy + ny; ++j) {
			cin >> g[i][j];
			f[i][j] = t_obj(i, j) == 5 or t_obj(i, j) == 1 ? 0 : g[i][j];
			if (t_obj(i, j) == 3) cin >> a[i][j].first >> a[i][j].second;
			else if (t_obj(i, j) == 1) player.init(i, j);
			else if (t_obj(i, j) == 6) cin >> a[i][j].first;
		}
		for (int i = 0; i <= _nx + 1; ++i) for (int j = 0; j <= _ny + 1; ++j) if (!(sx + 1 <= i and i <= sx + nx) or !(sy + 1 <= j and j <= sy + ny)) f[i][j] = g[i][j] = -1; 
		nx = _nx;
		ny = _ny;
		cls();
		for (int i = 1; i <= nx; ++i) for (int j = 1; j <= ny; ++j) print(i, j);
		freopen("CON.in", "r", stdin);
	}
	void run() {
		print_mode();
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
				if (ch == 'w') player.W();
				else if (ch == 'a') player.A();
				else if (ch == 's') player.S();
				else if (ch == 'd') player.D();
			}
			player.free();
			jump(7, 30 + 1);
			col(0, 15);
			cout << getTs() - T;
		}
		if (win) {
			jump_g(player.X, player.Y);
			col(0, cobj[player.object + aux]);
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
		for (; kbhit(); ) ch = getch();
		jump(0, 30 + 5);
		col(0, 15);
		printf("input any key to continue.");
		while (true) if (kbhit()) {
			ch = getch();
			break;
		}
	}
	void work() {
		init_obj();
		init_modes();
		m = 0;
		player.object = 1;
		for (; true; ) run();
	}
};
void play() {
	jump(9, 1);
	col(0, 15);
	puts("<Ball Fight>\n");
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

