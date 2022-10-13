#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define R(i, a, b) for (auto i = (a); i < (b); ++i)
#define L(i, a, b) for (auto i = (b) - 1; i >= (a); --i)
#define N(a) int((a).size())
#define V(a) (a).begin(), (a).end()
#define B(a, n) (a), (a) + (n)
#define spc << ' '
#define ntr << '\n'
using namespace std;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
mt19937 rng(__builtin_ia32_rdtsc());
u32 xorshift(u32 x) {
	x ^= x << 17;
	x ^= x >> 7;
	x ^= x << 13;
	return x;
}
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
	R(i, 0, 50) {
		R(j, 0, 100) cls_str[x++] = ' ';
		cls_str[x++] = '\n';
	}
}
void cls() {
	if (!cls_init) getcls();
	jump(0, 0);
	puts(cls_str);
	jump(0, 0);
}
struct point {
	int x, y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};
double getTs() {
	return double(clock()) / CLOCKS_PER_SEC;
}
namespace project_0 {
	constexpr int xn = 50;
	constexpr int xplayer = 9;
	int nx, ny, g[xn][xn], f[xn][xn], m;
	point tp[xn][xn];
	int nM;
	struct mode_t {
		string name, bot, team, reset_score;
		int trk_cnt[xplayer];
	} M[50];
	void init_modes() {
		nM = 11; 
		M[0].name = "City";
		M[1].name = "Cyberpunk";
		M[2].name = "Go To 2050";
		M[3].name = "Beach";
		M[4].name = "Hello Bots";
		M[5].name = "0.125";
		M[6].name = "Sunken Treasure";
		M[7].name = "For Real Ball Run";
		M[8].name = "Hello Magic";
		M[9].name = "San defacto RY";
		M[10].name = "Ole Sky";
		R(i, 0, nM) {
			M[i].bot = M[i].team = "";
			M[i].reset_score = "1"; 
			R(j, 1, xplayer) M[i].trk_cnt[j] = 0;
		} 
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
		for (int i = 1; i <= 8; ++i) mod_50[i] = mod_50[i + 50] = i;
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
		insert_obj(-40, 14, "¨ˆ ", 5); // sand
		insert_obj(40, 14, "¡ï", 6); // crown
		insert_obj(-30, 14, "¡õ", 7);
		insert_obj(-31, 6, "¡õ", 7); // tricky square
	}
	int t_obj(int x, int y) {
		return tobj[g[x][y] + aux];
	}
	point exfind(int x, int y) {
		return t_obj(x, y) == 3 ? exfind(tp[x][y].x, tp[x][y].y) : point{x, y}; 
	}
	int real_obj(int x, int y) {
		auto p = exfind(x, y);
		return t_obj(p.x, p.y);
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
	int sand_score() {
		int x = 0;
		while (rng() & 1) x += 1;
		return x;
	}
	int np, score[xplayer][50], team[xplayer];
	bool alive[xplayer];
	vector<int> dord, member[xplayer];
	int team_print_place[xplayer], tsc[xplayer][50];
	string player_name[xplayer] = {"", "A", "B", "C", "D", "E", "F", "G", "H", };
	void add_score(int i, int x);
	struct player_t {
		int X, Y, object;
		int cnt_up, aut_up, lst;
		vector<int> trk;
		bool falin;
		double tlst, tup, tfall, speed, ttrk;
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
				moveto(tp[X][Y].x, tp[X][Y].y);
				return;
			} else if (t == 1) {
				alive[mod_50[g[X][Y]]] = false;
				dord.push_back(mod_50[g[X][Y]]);
				add_score(object, 10);
			} else if (t == 4) {
				alive[object] = false;
				dord.push_back(object);
				return;
			} else if (t == 6) {
				vector<int> s;
				R(i, 1, np + 1) if (i != object and alive[i] and team[i] != team[object]) s.push_back(i);
				shuffle(V(s), rng);
				for (int i : s) {
					alive[i] = false;
					dord.push_back(i);
				}
				R(i, 1, nx + 1) R(j, 1, ny + 1) if (t_obj(i, j) == 1 and !alive[mod_50[g[i][j]]]) reduct(i, j);
				add_score(object, N(s) * 10 + 100);
				return;
			}
			print();
		}
		void init(int x, int y) {
			place(x, y);
			g[x][y] = object;
			cnt_up = aut_up = lst = falin = 0;
			trk.clear();
			tlst = tup = tfall = getTs() - 0.3;
			ttrk = -0.6;
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
				if (t_obj(p.x, p.y) == 5) {
					reduct(p.x, p.y);
					add_score(object, sand_score());
				} else if (t_obj(p.x, p.y) == 7) {
					trk.push_back(g[p.x][p.y]);
					reduct(p.x, p.y);
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
		void put_square(int x, int y) {
			if (!N(trk) or block_side(x, y)) return;
			change(x, y, trk.back());
			trk.pop_back();
		}
		void free() {
			auto p = exfind(X + 1, Y);
			if (block_top(X + 1, Y) or (t_obj(p.x, p.y) == 1 and team[g[p.x][p.y]] == team[object])) {
				speed = 0.2;
				falin = false;
				cnt_up = 0;
				print();
			} else if (!aut_up)
				fall();
			if (aut_up)
				auto_up();
		}
		void W() {
			move_up();
		}
		void A() {
			if ((getTs() - ttrk) <= 0.5) put_square(X, Y - 1), ttrk = -0.6;
			else left();
		}
		void D() {
			if ((getTs() - ttrk) <= 0.5) put_square(X, Y + 1), ttrk = -0.6;
			else right(); 
		}
		void S() {
			if ((getTs() - ttrk) <= 0.5) put_square(X + 1, Y), ttrk = -0.6;
			else ttrk = getTs();
		}
		bool sta() {
			if (aut_up)	return 0;
			if (getTs() - tlst < 0.31) return 0;
			auto p = exfind(X + 1, Y);
			if (block_top(X + 1, Y) or (t_obj(p.x, p.y) == 1 and team[g[p.x][p.y]] == team[object])) return 0;
			return 1;
		}
	} player[xplayer];
	int rad(int x, int y) {
		return rng() % (y - x + 1) + x;
	}
	struct node {
		int x, y;
		node(int X = 0, int Y = 0) {
			x = X, y = Y;
		}
		bool operator == (const node &o) const {
			return x == o.x and y == o.y;
		}
		bool operator != (const node &o) const {
			return x != o.x or y != o.y;
		}
	} cant, ept;
	bool is_bot[xplayer];
	struct FYY_bot {
		vector<int> actq;
		int pid, dis[35 * 35][35 * 35];
		int chw, cha, chd, inf = 1e9;
		clock_t lad, lmo;
		bool lsta;
		player_t *A, *B;
		vector<int> e[35 * 35];
		node p[14][35 * 35];
		int id(int x, int y) {
			return x * (ny + 2) + y;
		}
		int id(node x) {
			return id(x.x, x.y);
		}
		bool cd(int s) {
			if (s != cha && s != chd)
				return 0;
			return ((double)(clock() - lad)) / CLOCKS_PER_SEC < 0.2;
		}
		int to(char s) {
			if (s == 'w')
				return chw;
			if (s == 'a')
				return cha;
			if (s == 'd')
				return chd;
			return 0;
		}
		bool cd(char s) {
			return cd(to(s));
		}
		bool cd(const string &s) {
			for (auto i : s) {
				int x = to(i);
				if (cd(x)) return 1;
			}
			return 0;
		}
		void clearcd() {
			lad = -1000000;
		}
		void cdc() {
			wcd = np * 10;
			if (!rad(0, 16) or !alive[B->object]) {
				vector<int> al;
				R(i, 1, np + 1) if (i != pid and alive[i] and team[A->object] != team[i]) al.push_back(i);
				if(al.empty()) return;
				int x = rad(0, N(al) - 1);
				B = &player[al[x]];
			}
		}
		void push(const string&s) {
			if (cd(s))
				return;
			cdc();
			for (auto i : s)
				actq.push_back(to(i));
		}
		void push_rev(const string&s){
			if (cd(s))
				return;
			cdc();
			for (int i = ((int)s.size()) - 1; i >= 0; i--)
				actq.push_back(to(s[i]));
		}
		void push(int s){
			if (cd(s))
				return;
			cdc();
			actq.push_back(s);
		}
		void push(char s){
			push(to(s));
		}
		const string acq[14] = {"a", "d", "w", "ww", "aw", "dw", "wa", "wd", "wwa", "wwd", "awaw", "dwdw", "awdw", "dwaw"};
		const vector<node> ps[14] = {
			{node(0, -1)}, //a0
			{node(0, 1)}, //d1
			{node( - 1, 0), node( - 2, 0)}, //w2
			{node( - 1, 0), node( - 2, 0), node( - 3, 0), node( - 4, 0)}, //ww3
			{node(0, -1), ept, node( - 1, -2), ept, node( - 2, -3)}, //aw4
			{node(0, 1), ept, node( - 1, 2), ept, node( - 2, 3)}, //dw5
			{node( - 1, 0), ept, node( - 2, -1)}, //wa6
			{node( - 1, 0), ept, node( - 2, 1)}, //wd7
			{node( - 1, 0), node( - 2, 0), ept, node( - 3, -1), ept, node( - 4, -2)}, //wwa8
			{node( - 1, 0), node( - 2, 0), ept, node( - 3, 1), ept, node( - 4, 2)}, //wwd9
			{node(0, -1), ept, node( - 1, -2), ept, node( - 2, -3), ept, node( - 3, -4), ept, node( - 4, -5)}, //awaw10
			{node(0, 1), ept, node( - 1, 2), ept, node( - 2, 3), ept, node( - 3, 4), ept, node( - 4, 5)}, //dwdw11
			//		{node(0,-1),ept,node(-1,-2),ept,node(-2,-1),ept,node(-3,0),ept,node(-4,1)},//awdw12
			//		{node(0,1),ept,node(-1,2),ept,node(-2,1),ept,node(-3,0),ept,node(-4,-1)}//dwaw13
		}, pf[14] = {
			{node(0, -1)}, //a0
			{node(0, 1)}, //d1
			{node( - 1, 0), node( - 2, 0)}, //w2
			{node( - 1, 0), node( - 2, 0), node( - 3, 0), node( - 4, 0)}, //ww3
			{node(0, -1), node( - 1, -1), node( - 1, -2), node( - 2, -2), node( - 2, -3)}, //aw4
			{node(0, 1), node( - 1, 1), node( - 1, 2), node( - 2, 2), node( - 2, 3)}, //dw5
			{node( - 1, 0), node( - 2, 0), node( - 2, -1)}, //wa6
			{node( - 1, 0), node( - 2, 0), node( - 2, 1)}, //wd7
			{node( - 1, 0), node( - 2, 0), node( - 3, 0), node( - 3, -1), node( - 4, -1), node( - 4, -2)}, //wwa8
			{node( - 1, 0), node( - 2, 0), node( - 3, 0), node( - 3, 1), node( - 4, 1), node( - 4, 2)}, //wwd9
			{node(0, -1), node( - 1, -1), node( - 1, -2), node( - 2, -2), node( - 2, -3), node( - 3, -3), node( - 3, -4), node( - 4, -4), node( - 4, -5)}, //awaw10
			{node(0, 1), node( - 1, 1), node( - 1, 2), node( - 2, 2), node( - 2, 3), node( - 3, 3), node( - 3, 4), node( - 4, 4), node( - 4, 5)}, //dwdw11
			//		{node(0,-1),node(-1,-1),node(-1,-2),node(-2,-2),node(-2,-1),node(-3,-1),node(-3,0),node(-4,0),node(-4,1)},//awdw12
			//		{node(0,1),node(-1,1),node(-1,2),node(-2,2),node(-2,1),node(-3,1),node(-3,0),node(-4,0),node(-4,-1)}//dwaw13
		};
		node gets(node x) {
			for (int i = x.x; i <= nx + 1; i++) {
				if (t_obj(i, x.y) == 4)
					return cant;
				if (block_top(i, x.y))
					return node(i - 1, x.y);
			}
			assert(0);
			return cant;
		}
		node getp(){
			node x = node(B->X, B->Y);
			for (int i = x.x; i <= nx + 1; i++) {
				if (t_obj(i, x.y) == 4)
					return cant;
				if (block_top(i, x.y))
					return node(i - 1, x.y);
			}
			assert(0);
			return cant;
		}
		node get(node x, int id){
			int sz = ps[id].size();
			assert(sz == (int)pf[id].size());
			if (id == 10 && !block_side(A->X, A->Y - 1) && !block_top(A->X + 1, A->Y - 1))
				return get(x, 4);
			if (id == 11 && !block_side(A->X, A->Y + 1) && !block_top(A->X + 1, A->Y + 1))
				return get(x, 5);
			node lx = x;
			for (int k = 0; k < sz; k++) {
				int i = ps[id][k].x, j = ps[id][k].y;
				if (node(i, j) != ept && t_obj(x.x + i, x.y + j) == 4)
					return cant;
				i = pf[id][k].x, j = pf[id][k].y;
				if (lx.x == x.x + i && abs(lx.y - (x.y + j)) == 1 && block_side(x.x + i, x.y + j))
					x.y += lx.y - (x.y + j);
				if (block_side(x.x + i, x.y + j))
					return gets(lx);
				lx = node(x.x + i, x.y + j);
			}
			return gets(lx);
		}
		int mdis(node x, node y){
			return abs(x.x - y.x) + abs(x.y - y.y);
		}
		bool willd(){
			for (int i = 1; i <= np; i++)
				if (i != pid && (player[i].X == A->X - 1 || player[i].X == A->X - 2) && player[i].Y == A->Y)
					return 1;
			return 0;
		}
		const int urun[6] = {0, 1, 4, 5, 10, 11};
		bool fl;
		int flim, wcd;
		void work() {
			if (wcd)
				return wcd--, void();
			if (!alive[pid])
				return;
			if (!alive[B->object]) cdc();
			bool nsta = A->sta();
			if (nsta && !lsta)
				lmo = clock();
			lsta = nsta;
			if (actq.size() == flim)
				fl = 0;
			if (!actq.empty())
				return;
			if (willd() && block_side(A->X + 1, A->Y) && !fl) {
				clearcd();
				vector<int>can;
				for (int i = 0; i < 6; i++) {
					node x = get(node(A->X, A->Y), urun[i]);
					if (x != cant && x != node(A->X, A->Y))
						can.push_back(urun[i]);
				}
				if (can.empty()) {
					int x = rad(2, 5);
					int flim = actq.size();
					push_rev(acq[urun[x]]), fl = 1;
				}
				else{
					int x = rad(0, ((int)can.size()) - 1);
					int flim = actq.size();
					push_rev(acq[can[x]]), fl = 1;
				}
				return;
			}
			if (!nsta)
				return;
			vector<int>can;
			node mp = node(A->X, A->Y), ep = getp();
			if (ep == cant)
				return;
			if (dis[id(mp)][id(B->X, B->Y)] <= 1 && rad(0, 2)) {
				for (int i = 0; i < 12; i++) {
					node x = get(mp, i);
					if (x == node(B->X, B->Y))
						can.push_back(i);
				}
				if (!can.empty()) {
					int x = rad(0, ((int)can.size()) - 1);
					push(acq[can[x]]);
					reverse(actq.begin(), actq.end());
					return;
				}
			}
			for (int i = 0; i < 12; i++) {
				node x = get(mp, i);
				if (x == cant || (x == ep && ep != node(B->X, B->Y)))
					continue;
				if (dis[id(x)][id(ep)] <= rad(1, 2))
					can.push_back(i);
				else if (dis[id(x)][id(ep)] < dis[id(mp)][id(ep)])
					can.push_back(i);
			}
			if (can.empty())
				for (int i = 0; i < 12; i++) {
					node x = get(mp, i);
					if (x == cant || (x == ep && ep != node(B->X, B->Y)))
						continue;
					if (dis[id(x)][id(ep)] <= 3)
						can.push_back(i);
					else if (mdis(id(x), id(ep)) <= rad(7, 15))
						can.push_back(i);
					else if (dis[id(x)][id(ep)] <= dis[id(mp)][id(ep)])
						can.push_back(i);
					else if (mdis(id(x), id(ep)) < mdis(id(mp), id(ep)))
						can.push_back(i);
				}
			if (can.empty())
				for (int i = 0; i < 12; i++) {
					node x = get(mp, i);
					if (x == cant || (x == ep && ep != node(B->X, B->Y)))
						continue;
					if (mdis(id(x), id(ep)) < mdis(id(mp), id(ep)) + 5)
						can.push_back(i);
				}
			if (can.empty())
				return;
			int x = rad(0, ((int)can.size()) - 1);
			if ((can[x] == 2 || can[x] == 3) && rad(0, 3))
				return;
			push(acq[can[x]]);
			reverse(actq.begin(), actq.end());
		}
		void clear(){
			for (int i = 0; i < 35 * 35; i++)
				e[i].clear();
			for (int i = 0; i < 35 * 35; i++)
				for (int j = 0; j < 35 * 35; j++)
					dis[i][j] = inf;
			fl = 0, wcd = 0;
		}
		int que[35 * 35];
		void bfs(int s, int * dis) {
			int l = 0, r = -1;
			dis[s] = 0, que[++r] = s;
			while (l <= r) {
				int u = que[l++];
				for (auto i : e[u])
					if (dis[i] == inf)
						dis[i] = dis[u] + 1, que[++r] = i;
			}
		}
		void init(int _pid){
			pid = _pid;
			actq.clear();
			cant = node( - 1, -1);
			ept = node(0, 0);
			chw = 1001 + pid * 4;
			cha = 1002 + pid * 4;
			chd = 1003 + pid * 4;
			for (int i = 1; i <= np; i++)
				if (pid == i)
					A = &player[i];
			vector<int> al;
			R(i, 1, np + 1) if (i != pid and alive[i] and team[A->object] != team[i]) al.push_back(i);
			B = &player[al[rad(0, N(al) - 1)]];
			clear();
			for (int i = 1; i <= nx; i++)
				for (int j = 1; j <= ny; j++)
					for (int k = 0; k < 12; k++) {
						p[k][id(i, j)] = get(node(i, j), k);
						if (p[k][id(i, j)] != cant)
							e[id(i, j)].push_back(id(p[k][id(i, j)]));
					}
			for (int i = 1; i <= nx; i++)
				for (int j = 1; j <= ny; j++)
					bfs(id(i, j), dis[id(i, j)]);
			lad = clock();
		}
	} bot[xplayer];
	string signs[2] = {"¡Ñ", "¨’"};
	int te[xn * xn];
	int fr(int u) {
		return u == te[u] ? u : te[u] = fr(te[u]);
	}
	bool valid() {
		static int id[xn][xn];
		R(i, 0, nx + 2) R(j, 0, ny + 2) {
			auto t = t_obj(i, j);
			id[i][j] = t == 2 or t == 4 or t == 5 or t == 7 ? -1 : 0;
		}
		R(i, 1, nx + 1) R(j, 1, ny + 1) {
			if (!~id[i - 1][j] and ~id[i][j] and !~id[i + 1][j]) return false;
			if (!~id[i - 1][j] and ~id[i][j] and ~id[i + 1][j] and !~id[i + 2][j]) return false;
		}
		int nid = 0;
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (~id[i][j])
			id[i][j] = nid++;
		iota(B(te, nid), 0);
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (~id[i][j]) {
			if (i + 1 <= nx and ~id[i + 1][j])
				te[fr(id[i][j])] = fr(id[i + 1][j]);
			if (j + 1 <= ny and ~id[i][j + 1])
				te[fr(id[i][j])] = fr(id[i][j + 1]);
		}
		R(i, 0, nid) if (fr(i) != fr(0))
			return false;
		return true;
	}
	bool isplace(int x, int y) {
		if (x < 1 or x > nx or y < 1 or y > ny or g[x][y] != 0) return false;
		g[x][y] = -1;
		auto res = valid();
		g[x][y] = 0;
		return res;
	}
	vector<point> spawns;
	void make_sz(int x, int y) {
		nx = x;
		ny = y;
		R(i, 1, nx + 1) R(j, 1, ny + 1) f[i][j] = g[i][j] = 0;
		R(i, 0, nx + 2) f[i][0] = f[i][ny + 1] = g[i][0] = g[i][ny + 1] = -1;
		R(i, 1, ny + 1) f[0][i] = f[nx + 1][i] = g[0][i] = g[nx + 1][i] = f[nx][i] = g[nx][i] = -1;
		spawns.clear();
	}
	void make_0() {
		make_sz(24, 24);
		for (double t = 10; t >= 3; t *= 0.99) {
			if (rng() % 8 > 0)
				continue;
			int x = t * 1.2, y = t;
			int mx = rng() % x, my = rng() % y;
			int ax = rng() % (nx - 1) + 2, ay = rng() % ny + 1;
			if (!isplace(ax, ay))
				continue;
			f[ax][ay] = g[ax][ay] = -14;
			R(i, 0, y) if (i != mx and isplace(ax, ay + (i - my))) {
				f[ax][ay + (i - my)] = g[ax][ay + (i - my)] = -1;
				if (isplace(ax + 1, ay + (i - my)) and rng() % 10 < ax / 2)
					f[ax + 1][ay + (i - my)] = g[ax + 1][ay + (i - my)] = -21;
			}
			R(i, 0, x) if (i != my and isplace(ax + (i - mx), ay))
				f[ax + (i - mx)][ay] = g[ax + (i - mx)][ay] = -1;
		}
		double now = 0.6;
		L(i, 1, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (x < now * 0.2)
					f[i][j] = g[i][j] = -1;
				else if (x < now * 0.4)
					f[i][j] = g[i][j] = -14;
				else if (x < now * 0.6)
					f[i][j] = g[i][j] = -15;
			}
			now *= 0.9;
		}
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_1() {
		make_sz(30, 30);
		for (double t = 10; t >= 3; t *= 0.995) {
			if (rng() % 8 > 0)
				continue;
			int x = t * 1.2, y = t;
			int mx = rng() % x, my = rng() % y;
			int ax = rng() % (nx - 1) + 2, ay = rng() % ny + 1;
			if (!isplace(ax, ay))
				continue;
			f[ax][ay] = g[ax][ay] = -14;
			R(i, 0, y) if (i != mx and isplace(ax, ay + (i - my))) {
				f[ax][ay + (i - my)] = g[ax][ay + (i - my)] = -1;
				if (isplace(ax + 1, ay + (i - my)) and rng() % 10 < ax / 3)
					f[ax + 1][ay + (i - my)] = g[ax + 1][ay + (i - my)] = -21;
			}
			R(i, 0, x) if (i != my and isplace(ax + (i - mx), ay))
				f[ax + (i - mx)][ay] = g[ax + (i - mx)][ay] = -1;
		}
		double now = 0.6;
		L(i, 1, nx + 1) {
			R(j, 1, ny + 1) {
				auto x = double(rng() % 10000000) / 10000000;
				if (isplace(i, j) and x < now * 0.5)
					f[i][j] = g[i][j] = -11;
				else if (!f[i][j]) {
					if (x < now * 0.4)
						f[i][j] = 23;
					else if (x < now * 0.5)
						f[i][j] = 22;
					else if (x < now * 0.7)
						f[i][j] = 21;
					else if (x < now)
						f[i][j] = 20;
					if (!g[i][j] and f[i][j])
						g[i][j] = f[i][j];
				}
			}
			now *= 0.9;
		}
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_2() {
		make_sz(30, 30);
		for (double t = 10; t >= 3; t *= 0.995) {
			if (rng() % 8 > 0)
				continue;
			int x = t * 1.2, y = t;
			int mx = rng() % x, my = rng() % y;
			int ax = rng() % (nx - 1) + 2, ay = rng() % ny + 1;
			if (!isplace(ax, ay))
				continue;
			f[ax][ay] = g[ax][ay] = -15;
			R(i, 0, y) if (i != mx and isplace(ax, ay + (i - my))) {
				f[ax][ay + (i - my)] = g[ax][ay + (i - my)] = -15;
				if (isplace(ax + 1, ay + (i - my)) and rng() % 10 < ax / 3)
					f[ax + 1][ay + (i - my)] = g[ax + 1][ay + (i - my)] = -21;
			}
			R(i, 0, x) if (i != my and isplace(ax + (i - mx), ay))
				f[ax + (i - mx)][ay] = g[ax + (i - mx)][ay] = -15;
		}
		double now = 0.6;
		L(i, 1, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (x < now * 0.5)
					f[i][j] = g[i][j] = -15;
			}
			now *= 0.9;
		}
		vector<point> s;
		static bool ok[50][50];
		R(i, 0, 32) R(j, 0, 32) ok[i][j] = false;
		R(i, 1, nx - 1) R(j, 1, ny + 1) if (t_obj(i, j) == 2 and t_obj(i + 1, j) != 2 and t_obj(i + 2, j) == 0) {
			s.emplace_back(i + 1, j);
			ok[i + 1][j] = true;
		}
		shuffle(V(s), rng);
		if (N(s) >= 2) {
			int x_xor = s[0].x ^ s[1].x;
			int y_xor = s[0].y ^ s[1].y;
			for (auto p : s)
				if (ok[x_xor ^ p.x][y_xor ^ p.y]) {
				f[p.x][p.y] = f[x_xor ^ p.x][y_xor ^ p.y] = g[p.x][p.y] = g[x_xor ^ p.x][y_xor ^ p.y] = 30;
				tp[p.x][p.y] = {(x_xor ^ p.x) + 1, y_xor ^ p.y};
				tp[x_xor ^ p.x][y_xor ^ p.y] = {p.x + 1, p.y};
				ok[p.x][p.y] = ok[x_xor ^ p.x][y_xor ^ p.y] = false;
			}
		}
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_3() {
		make_sz(30, 20);
		auto get_barrier = [&]() {
			return rng() % 3 < 2 ? -1 : -14;
		};
		f[5][1] = g[5][1] = get_barrier();
		f[5][ny] = g[5][ny] = get_barrier();
		double now = 0.6;
		L(i, 6, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (x < now * 0.9)
					f[i][j] = g[i][j] = get_barrier();
			}
			now *= 0.9;
		}
		now = 0.2;
		L(i, 6, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (t_obj(i + 1, j) == 2 and x < now * .8)
					f[i][j] = g[i][j] = -2;
				else if (x < now)
					f[i][j] = g[i][j] = -22;
			}
			now *= 0.9;
		}
		for (double t = 20; t >= 3; t *= 0.995) {
			if (rng() % 4 > 0)
				continue;
			int l = t, ax = rng() % (nx - l - 5) + 6, ay = rng() % ny + 1;
			R(x, ax, ax + l) {
				if (isplace(x, ay))
					g[x][ay] = -40;
				vector<int> adj;
				R(i, -1, 2) if (1 <= ay + i and ay + i <= ny)
					adj.push_back(i);
				ay += adj[rng() % N(adj)];
			}
		}
		L(i, 1, 6) R(j, 1, ny + 1) if (isplace(i, j) and (i == 5 or t_obj(i + 1, j) == 2)) {
			int x = rng() % 10;
			if (x < 6)
				f[i][j] = g[i][j] = get_barrier();
		}
		int a = 0, b = 50, c = 100, d = 300;
		L(i, 6, nx + 1) R(j, 1, ny + 1) if (!f[i][j]) {
			int x = rng() % (a + b + c + d);
			if (x < a)
				f[i][j] = 23;
			else if (x < a + b)
				f[i][j] = 22;
			else if (x < a + b + c)
				f[i][j] = 21;
			else
				f[i][j] = 20;
			if (!g[i][j])
				g[i][j] = f[i][j];
			a += 10, b += 8, c += 6;
		}
		R(i, 1, 6) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_4() {
		make_sz(30, 30);
		vector<point> s;
		R(i, 1, nx) R(j, 1, ny + 1) s.emplace_back(i, j);
		shuffle(V(s), rng);
		for (auto p : s) if (isplace(p.x, p.y)) f[p.x][p.y] = g[p.x][p.y] = -15;
		s.clear();
		R(i, nx - 3, nx) R(j, 1, ny + 1) if (t_obj(i, j) == 0) s.emplace_back(i, j);
		if (N(s)) {
			int i, j, k = rng() % N(s);
			i = s[k].x, j = s[k].y;
			f[i][j] = g[i][j] = 40;
		}
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_5() {
		make_sz(30, 30);
		for (double t = 10; t >= 3; t *= 0.995) {
			if (rng() % 8 > 0)
				continue;
			int x = t * 1.2, y = t;
			int mx = rng() % x, my = rng() % y;
			int ax = rng() % (nx - 1) + 2, ay = rng() % ny + 1;
			if (!isplace(ax, ay))
				continue;
			f[ax][ay] = g[ax][ay] = -15;
			R(i, 0, y) if (i != mx and isplace(ax, ay + (i - my))) {
				f[ax][ay + (i - my)] = g[ax][ay + (i - my)] = -15;
				if (isplace(ax + 1, ay + (i - my)) and rng() % 10 < ax / 3)
					f[ax + 1][ay + (i - my)] = g[ax + 1][ay + (i - my)] = -21;
			}
			R(i, 0, x) if (i != my and isplace(ax + (i - mx), ay))
				f[ax + (i - mx)][ay] = g[ax + (i - mx)][ay] = -15;
		}
		double now = 0.6;
		L(i, 1, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (x < now * 0.5) f[i][j] = g[i][j] = -15;
			}
			now *= 0.9;
		}
		R(i, 1, nx + 1) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_6() {
		make_sz(30, 30);
		auto get_barrier = [&]() {
			return rng() % 3 < 2 ? -1 : -14;
		};
		f[5][1] = g[5][1] = get_barrier();
		f[5][ny] = g[5][ny] = get_barrier();
		double now = 0.6;
		L(i, 6, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (x < now * 0.9)
					f[i][j] = g[i][j] = get_barrier();
			}
			now *= 0.9;
		}
		now = 0.2;
		L(i, 6, nx + 1) {
			R(j, 1, ny + 1) if (isplace(i, j)) {
				auto x = double(rng() % 10000000) / 10000000;
				if (t_obj(i + 1, j) == 2 and x < now * .8)
					f[i][j] = g[i][j] = -2;
				else if (x < now)
					f[i][j] = g[i][j] = -22;
			}
			now *= 0.9;
		}
		for (double t = 20; t >= 3; t *= 0.995) {
			if (rng() % 3 > 0)
				continue;
			int l = t, ax = rng() % (nx - l - 5) + 6, ay = rng() % ny + 1;
			R(x, ax, ax + l) {
				if (isplace(x, ay))
					g[x][ay] = -40;
				vector<int> adj;
				R(i, -1, 2) if (1 <= ay + i and ay + i <= ny)
					adj.push_back(i);
				ay += adj[rng() % N(adj)];
			}
		}
		L(i, 1, 6) R(j, 1, ny + 1) if (isplace(i, j) and (i == 5 or t_obj(i + 1, j) == 2)) {
			int x = rng() % 10;
			if (x < 6) f[i][j] = g[i][j] = get_barrier();
		}
		int a = 0, b = 50, c = 100, d = 300;
		L(i, 6, nx + 1) R(j, 1, ny + 1) if (!f[i][j]) {
			int x = rng() % (a + b + c + d);
			if (x < a)
				f[i][j] = 23;
			else if (x < a + b)
				f[i][j] = 22;
			else if (x < a + b + c)
				f[i][j] = 21;
			else
				f[i][j] = 20;
			if (!g[i][j])
				g[i][j] = f[i][j];
			a += 10, b += 8, c += 6;
		}
		vector<point> s;
		R(i, nx - 3, nx) R(j, 1, ny + 1) if (t_obj(i, j) == 0) s.emplace_back(i, j);
		if (N(s)) {
			int i, j, k = rng() % N(s);
			i = s[k].x, j = s[k].y;
			f[i][j] = g[i][j] = 40;
		}
		R(i, 1, 6) R(j, 1, ny + 1) if (t_obj(i, j) == 0 and t_obj(i + 1, j) == 2) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
		assert(valid());
	}
	void make_7() {
		make_sz(9, 4);
		f[1][4] = g[1][4] = 40;
		f[8][1] = g[8][1] = -1;
		f[3][4] = g[3][4] = -1;
		R(i, 3, 9) f[i][3] = g[i][3] = -1;
		spawns.emplace_back(8, 2);
		spawns.emplace_back(8, 4);
	}
	void make_8() { // Hello Magic
		make_sz(30, 30);
		vector<int> len(31, 0);
		len[3] = len[28] = 4;
		R(i, 4, 28) if (i % 5 == 3) len[i] = rng() % 7 + 6;
		R(i, 1, nx + 1) if (i % 5 == 3) {
			L(j, ny - len[i], ny) f[j][i] = g[j][i] = -1;
			g[ny - len[i] - 1][i] = rng() & 1 ? -30 : -31;
		}
		spawns.emplace_back(29, 1);
		spawns.emplace_back(29, 30);
	}
	void make_9() {
		make_sz(20, 30);
		R(i, 13, 20) if (i != 17) R(j, 15, 17) f[i][j] = g[i][j] = -1;
		R(j, 15, 17) g[17][j] = -40;
		team[1] = team[2] = team[3] = team[4] = 1, is_bot[2] = is_bot[3] = is_bot[4] = true;
		team[5] = team[6] = team[7] = team[8] = 2, is_bot[5] = is_bot[6] = is_bot[7] = is_bot[8] = true;
		spawns.emplace_back(1, 1);
		spawns.emplace_back(1, 3);
		spawns.emplace_back(1, 5);
		spawns.emplace_back(1, 7);
		spawns.emplace_back(1, 24);
		spawns.emplace_back(1, 26);
		spawns.emplace_back(1, 28);
		spawns.emplace_back(1, 30);
	}
	void make_10() {
		make_sz(30, 28);
		auto get_barrier = [&]() {
			int x = rng() % 10;
			return x < 1 ? -14 : x < 3 ? -15 : -1;
		};
		for (int i = 1; i <= nx; ++i) f[i][1] = g[i][1] = f[i][ny] = g[i][ny] = get_barrier();
		for (int j = 2; j <= nx - 1; ++j) g[1][j] = -1;
		for (int j = 2; j <= ny - 1; ++j) if (j != 3 and j != 26) {
			bool ok = false;
			int cnt = 0;
			while (!ok) {
				int i = rng() % 28 + 2;
				if (isplace(i, j)) {
					f[i][j] = g[i][j] = get_barrier();
					ok = true;
				}
				if (++cnt >= 30) break; 
			}
		}
		for (int i = 2; i <= 29; ++i) for (int j = 5; j <= 24; ++j) if (isplace(i, j) and (rng() % 15 == 0)) f[i][j] = g[i][j] = get_barrier();
		for (double t = 15; t >= 1; t *= 0.99) {
			if (rng() % 6 > 0) continue;
			int x = t, ax = rng() % (29 - x) + 2, ay = rng() % 20 + 5;
			vector<int> tmp(x);
			for (int i = 0; i < x; ++i) {
				tmp[i] = g[ax + i][ay];
				g[ax + i][ay] = -1;
			}
			if (valid()) {
				for (int i = 0; i < x; ++i) {
					if (!f[ax + i][ay]) g[ax + i][ay] = -40;
					else g[ax + i][ay] = tmp[i];
				}
			} else for (int i = 0; i < x; ++i) g[ax + i][ay] = tmp[i];
		}
		for (int j = 2; j <= nx - 1; ++j) {
			f[1][j] = g[1][j] = f[nx][j] = g[nx][j] = 30;
			tp[1][j] = {nx - 1, j};
			tp[nx][j] = {2, j};
		}
		int t = rng() & 1;
		for (int i = 2; i <= nx - 1; ++i) {
			if ((i & 1) == t) f[i][3] = g[i][3] = -15;
			else f[i][ny - 2] = g[i][ny - 2] = -15;
		}
		for (int i = 1; i <= nx; ++i) for (int j = 1; j <= ny; ++j) if (t_obj(i, j) == 0 and block_top(i + 1, j)) spawns.emplace_back(i, j);
		shuffle(V(spawns), rng);
	}
	vector<function<void(void)>> makes = {make_0, make_1, make_2, make_3, make_4, make_5, make_6, make_7, make_8, make_9, make_10};
	int ch;
	void towasd() {
		if (ch == 224 or ch == -32) {
			ch = getch();
			if (ch == 72)
				ch = 'w';
			else if (ch == 80)
				ch = 's';
			else if (ch == 75)
				ch = 'a';
			else if (ch == 77)
				ch = 'd';
		} else if (isupper(ch))
			ch += 'a' - 'A';
	}
	void print_mode() {
		cls();
		col(0, 11);
		cout << " ¡ô select mode ¡ô" ntr ntr;
		R(i, 0, nM) {
			col(0, i == m ? 14 : 15);
			cout << "  " << M[i].name ntr;
		}
		for (; (ch = getch()); ) {
			towasd();
			if (ch == ' ') return;
			if (ch == 'w') {
				if (!m) continue;
				jump(2, 2 + m);
				col(0, 15);
				cout << M[m--].name;
				jump(2, 2 + m);
				col(0, 14);
				cout << M[m].name;
			} else if (ch == 's') {
				if (m + 1 >= nM) continue;
				jump(2, 2 + m);
				col(0, 15);
				cout << M[m++].name;
				jump(2, 2 + m);
				col(0, 14);
				cout << M[m].name;
			}
		}
	}
	int kbhit_ch() {
		for (int i = 1; i <= np; i++) {
			if (!is_bot[i])
				continue;
			if (!bot[i].actq.empty() && (double)(clock() - bot[i].lmo) / CLOCKS_PER_SEC > 0.03) {
				int rch = bot[i].actq.back();
				bot[i].actq.pop_back();
				if (rch == bot[i].cha || rch == bot[i].chd)
					bot[i].lad = clock();
				bot[i].lmo = clock();
				return rch;
			}
		}
		if (kbhit()) return getch();
		return 0;
	}
	bool get_settings_esc;
	void get_settings() {
		auto bug = [&](const string &s) {
			jump(0, 8);
			col(0, 15);
			cout << s;
		};
		cls();
		jump(0, 0);
		col(0, 11);
		cout << " ¡ô settings ¡ô";
		int cur = 0;
		jump(0, 2);
		col(0, 14);
		cout << " be bot  : [";
		R(i, 0, N(M[m].bot)) {
			col(0, cobj[(i + 1) + aux]);
			cout << M[m].bot[i];
		} 
		col(0, 14);
		cout << "]";
		jump(0, 4);
		col(0, 15);
		cout << " team id : [";
		R(i, 0, N(M[m].team)) {
			col(0, cobj[(i + 1) + aux]);
			cout << M[m].team[i];
		}
		col(0, 15);
		cout << "]";
		jump(0, 6);
		col(0, 15);
		cout << " reset   : [" << M[m].reset_score << "]";
		for (; (ch = getch()); ) {
			bug(string(36, ' '));
			towasd();
			if (ch == 27) {
				get_settings_esc = true;
				return;
			}
			if (ch == ' ') {
				if (N(M[m].bot) != N(M[m].team)) bug("player number error.");
				else if (N(M[m].bot) < 2) bug("player number unaccepted.");
				else if (N(M[m].reset_score) != 1) bug("reset limit error");
				else return;
			}
			if (ch == 's' and cur == 0) {
				cur = 1;
				jump(0, 2);
				col(0, 15);
				cout << " be bot  : [";
				jump(12 + N(M[m].bot), 2);
				cout << "]";
				jump(0, 4);
				col(0, 14);
				cout << " team id : [";
				jump(12 + N(M[m].team), 4);
				cout << "]";
			} else if (ch == 'w' and cur == 1) {
				cur = 0;
				jump(0, 2);
				col(0, 14);
				cout << " be bot  : [";
				jump(12 + N(M[m].bot), 2);
				cout << "]";
				jump(0, 4);
				col(0, 15);
				cout << " team id : [";
				jump(12 + N(M[m].team), 4);
				cout << "]";
			} else if (ch == 's' and cur == 1) {
				cur = 2;
				jump(0, 4);
				col(0, 15);
				cout << " team id : [";
				jump(12 + N(M[m].team), 4);
				cout << "]";
				jump(0, 6);
				col(0, 14);
				cout << " reset   : [";
				jump(12 + N(M[m].reset_score), 6);
				cout << "]";
			} else if (ch == 'w' and cur == 2) {
				cur = 1;
				jump(0, 4);
				col(0, 14);
				cout << " team id : [";
				jump(12 + N(M[m].team), 4);
				cout << "]";
				jump(0, 6);
				col(0, 15);
				cout << " reset   : [";
				jump(12 + N(M[m].reset_score), 6);
				cout << "]";
			}
			if (isdigit(ch)) {
				if (cur == 0 and (ch == '0' or ch == '1')) {
					if (N(M[m].bot) + 1 <= min(xplayer - 1, N(spawns))) {
						M[m].bot.push_back(ch);
						jump(11 + N(M[m].bot), 2);
						col(0, cobj[N(M[m].bot) + aux]);
						cout << char(ch);
						col(0, 14);
						cout << "]";
					} else bug("player limit error.");
				} else if (cur == 1 and ch >= '1' and ch <= '8') {
					if (N(M[m].team) + 1 <= min(xplayer - 1, N(spawns))) {
						M[m].team.push_back(ch);
						jump(11 + N(M[m].team), 4);
						col(0, cobj[N(M[m].team) + aux]);
						cout << char(ch);
						col(0, 14);
						cout << "]";
					} else bug("player limit error.");
				} else if (cur == 2 and (ch == '0' or ch == '1')) {
					if (N(M[m].reset_score) == 0) {
						M[m].reset_score.push_back(ch);
						jump(11 + N(M[m].reset_score), 6);
						col(0, 15);
						cout << char(ch);
						col(0, 14);
						cout << "]";
					} else bug("reset limit error.");
				}
				else bug("digit error.");
			}
			if (ch == 8) {
				if (cur == 0) {
					if (N(M[m].bot)) {
						M[m].bot.pop_back();
						jump(12 + N(M[m].bot), 2);
						col(0, 14);
						cout << "] ";
					} else bug("player limit error.");
				} else if (cur == 1) {
					if (N(M[m].team)) {
						M[m].team.pop_back();
						jump(12 + N(M[m].team), 4);
						col(0, 14);
						cout << "] ";
					} else bug("player limit error.");
				} else if (cur == 2) {
					if (N(M[m].reset_score)) {
						M[m].reset_score.pop_back();
						jump(12 + N(M[m].reset_score), 6);
						col(0, 14);
						cout << "] ";
					} else bug("reset limit error.");
				}
			}
		}
	}
	void add_score(int i, int x) {
		score[i][m] += x;
		tsc[team[i]][m] += x;
		jump(ny * 2 + N(player_name[i]) + 8, i);
		col(0, cobj[i + aux]);
		cout << setfill('0') << setw(5) << score[i][m];
		if (N(member[team[i]]) > 1) {
			jump(team_print_place[team[i]], nx + 3);
			col(0, 15);
			cout << setfill('0') << setw(5) << tsc[team[i]][m];
		}
	}
	int chw[xplayer], cha[xplayer], chd[xplayer], chs[xplayer];
	vector<int> bots, humans;
	void init_players() {
		np = N(M[m].bot);
		dord.clear();
		R(i, 1, xplayer) member[i].clear();
		if (M[m].reset_score == "1") {
			memset(score, 0, sizeof score);
			memset(tsc, 0, sizeof tsc);
		}
		bots.clear();
		humans.clear();
		R(i, 1, np + 1) {
			alive[i] = true;
			if ((is_bot[i] = M[m].bot[i - 1] == '1')) bots.push_back(i);
			else humans.push_back(i);
			team[i] = M[m].team[i - 1] - '0';
			member[team[i]].push_back(i);	
			player[i].init(spawns[i - 1].x, spawns[i - 1].y);
			chw[i] = 1001 + i * 4, cha[i] = 1002 + i * 4, chd[i] = 1003 + i * 4, chs[i] = 1004 + i * 4;
		}
		for (int i : bots) bot[i].init(i);
	}
	void init_map() {
		cls();
		R(i, 1, nx + 1) R(j, 1, ny + 1) print(i, j);
		jump(0, nx + 1);
		col(0, 15);
		cout << "specimens : ";
		R(i, 1, np + 1) {
			jump(ny * 2 + 2, i);
			col(0, cobj[i + aux]);
			cout << signs[is_bot[i]] << " " << player_name[i] << " : " << setfill('0') << setw(5) << score[i][m];
		}
		jump(0, nx + 3);
		int now = 0;
		R(i, 1, xplayer) if (N(member[i]) > 1) {
			col(0, 15);
			cout << "[", now += 1;
			R(l, 0, N(member[i])) {
				int j = member[i][l];
				col(0, cobj[j + aux]);
				cout << signs[is_bot[j]], now += 2;
				if (l != N(member[i]) - 1) cout << " ", now += 1;
			}
			col(0, 15);
			cout << "] : ", now += 4;
			team_print_place[i] = now;
			cout << setfill('0') << setw(5) << tsc[i][m] << "  ", now += 7; 
		}
	}
	void run() {
		print_mode();
		makes[m]();
		get_settings_esc = false;
		get_settings();
		if (get_settings_esc) return;
		init_players();
		init_map();
		Sleep(1000);
		for (; kbhit(); ) ch = getch();
		auto check = [&]() {
			int lst = -1;
			R(i, 1, np + 1) if (alive[i]) {
				if (!~lst) lst = team[i];
				else if (lst != team[i]) return true;
			}
			return false;
		};
		for (int lst = N(dord); check(); ) {
			R(i, 1, np + 1) if (is_bot[i]) bot[i].work();
			if ((ch = kbhit_ch())) {
				if (isupper(ch)) ch += 'a' - 'A';
				if (ch == 27) return;
				if (N(humans) >= 1) {
					if (ch == 'w') ch = chw[humans[0]];
					if (ch == 'a') ch = cha[humans[0]];
					if (ch == 'd') ch = chd[humans[0]];
					if (ch == 's') ch = chs[humans[0]];
				}
				if (N(humans) >= 2) if (ch == 224 or ch == -32) {
					ch = getch();
					if (ch == 72) ch = chw[humans[1]];
					if (ch == 75) ch = cha[humans[1]];
					if (ch == 77) ch = chd[humans[1]];
					if (ch == 80) ch = chs[humans[1]];
				}
				if (N(humans) >= 3) {
					if (ch == 'u') ch = chw[humans[2]];
					if (ch == 'h') ch = cha[humans[2]];
					if (ch == 'k') ch = chd[humans[2]];
					if (ch == 'j') ch = chs[humans[2]];
				}
				R(i, 1, np + 1)	if ((ch == chw[i] or ch == cha[i] or ch == chd[i] or ch == chs[i]) and alive[i]) {
					if (ch == chw[i]) player[i].W();
					else if (ch == cha[i]) player[i].A();
					else if (ch == chd[i]) player[i].D();
					else if (ch == chs[i]) player[i].S();
				}
			}
			R(i, 1, np + 1) if (alive[i]) player[i].free();
			for (; lst < N(dord); ++lst) {
				jump(12 + lst * 4, nx + 1);
				print_obj(dord[lst]);
			}
		}
		R(i, 1, np + 1) if (alive[i]) {
			jump_g(player[i].X, player[i].Y);
			col(0, cobj[i + aux]);
			cout << "¢Ù";
			add_score(i, 10);
		}
		Sleep(500);
		for (; kbhit(); ) ch = getch();
		jump(0, nx + 5);
		col(0, 15);
		printf("input any key to continue.");
		for (; true; )
			if (kbhit()) {
			ch = getch();
			break;
		}
	}
	void work() {
		init_obj();
		init_modes();
		m = 0;
		R(i, 1, xplayer) player[i].object = i;
		memset(score, 0, sizeof score);
		memset(tsc, 0, sizeof tsc);
		for (; true; ) run();
	}
};
int ch;
void towasd() {
	if (ch == 224 or ch == -32) {
		ch = getch();
		if (ch == 72)
			ch = 'w';
		else if (ch == 80)
			ch = 's';
		else if (ch == 75)
			ch = 'a';
		else if (ch == 77)
			ch = 'd';
	} else if (isupper(ch))
		ch += 'a' - 'A';
}
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
	for (; true; ) {
		if (kbhit()) {
			ch = getch();
			towasd();
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
	project_0::work();
}
int main() {
	HideCursor();
	system("title Ball Fight");
	system("mode con cols=100 lines=60");
	play();
	return 0;
}
