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
char cls_str[3000];
bool cls_init = false;
void getcls() {
	cls_init = true;
	int x = 0;
	for (int i = 0; i < 36; ++i) {
		for (int j = 0; j < 60; ++j) cls_str[x++] = ' ';
		cls_str[x++] = '\n';
	}
}
void cls() {
	if (!cls_init) getcls();
	jump(0, 0);
	puts(cls_str);
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
		freopen("CON", "r", stdin);
		for (int i = 0; i < nM; ++i) best[i] = -1;
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
		freopen("CON", "r", stdin); 
	}
	int get_g(int x, int y) {
		return x < 0 or x >= nx or y < 0 or y >= ny ? -1 : g[x][y];
	}
	int get_tobj(int x, int y) {
		return tobj[get_g(x, y) + aux];
	}
	pair<int, int> exfind(int x, int y) {
		return get_tobj(x, y) == 3 ? exfind(a[x][y].first, a[x][y].second) : make_pair(x, y); 
	}
	int real_tobj(int x, int y) {
		auto p = exfind(x, y);
		return get_tobj(p.first, p.second);
	}
	void print_obj(int x) {
		col(0, cobj[x + aux]);
		cout << sobj[x + aux];
	}
	void reduct(int x, int y) {
		g[x][y] = f[x][y];
	}
	bool block_side(int x, int y) {
		auto t = real_tobj(x, y);
		return t == 2 or t == 5 or t == 7 or t == 4;
	}
	bool bot_side(int x,int y){
		int t=get_tobj(x,y);
		return t==2||t==3||t==4||t==5||t==6;
	}
	bool bot_side_b(int x,int y){
		int t=get_tobj(x,y);
		return t==2||t==4||t==5||t==6||(t==3&&get_g(x,y)!=-23);
	}
	int score;
	bool win;
	int X, Y, object;
	int cnt_up, aut_up, lst, fall_cnt;
	bool falin, bouncin, bot_rinit;
	double tlst, tup, tfall, speed;
	void place(int x, int y) {
		X = x;
		Y = y;
	}
	int print_R0, print_R1, print_x, print_y, print_g[29][29];
	void print() {
		g[X][Y] = cnt_up <= 1 ? object : object + 50;
		if (!~print_x) {
			print_x = X;
			print_y = Y;
		}
		if (X < print_x - print_R1 or X > print_x + print_R1) print_x = X;
		if (Y < print_y - print_R1 or Y > print_y + print_R1) print_y = Y;
		for (int i = -print_R0; i <= print_R0; ++i) for (int j = -print_R0; j <= print_R0; ++j) {
			if (get_g(print_x + i, print_y + j) == print_g[i + print_R0][j + print_R0]) continue;
			jump((j + print_R0) * 2, (i + print_R0));
			print_obj(get_g(print_x + i, print_y + j));
			print_g[i + print_R0][j + print_R0] = get_g(print_x + i, print_y + j);
		}
	}
	void moveto(int x, int y) {
		reduct(X, Y);
		if (get_tobj(x, y) == 3) {
			speed = 0.2;
			fall_cnt = 0;
			falin = false;
			bot_rinit=1;
		} 
		tie(x, y) = exfind(x, y);
		place(x, y);
		int t = get_tobj(X, Y);
		if (t == 6 and score >= a[X][Y].first) win = true;
		print();
	}
	void botkill() {
		moveto(a[X][Y].first,a[X][Y].second),bot_rinit=1;
	}
	void init(int x, int y) {
		place(x, y);
		aut_up = lst = fall_cnt = 0;
		falin = bouncin = false;
		cnt_up = 1;
		tlst = tup = tfall = getTs() - 0.3;
		speed = 0.2;
	}
	void move_up() {
		if (cnt_up >= 2) return;
		if (block_side(X - 1, Y)) {
			if (real_tobj(X - 1, Y) == 4) {
				falin = true;
				fall_cnt = (aut_up + 1) / 2;
				speed = 0.5 / (2.5 + fall_cnt);
			}
			aut_up = 0;
			return;
		}
		cnt_up += 1;
		speed = 0.2;
		fall_cnt = 0;
		falin = false;
		if (getTs() - tlst > 0.3) lst = 0;
		tup = getTs();
		if (!block_side(X - 1, Y + lst)) moveto(X - 1, Y + lst);
		else {
			if (real_tobj(X - 1, Y + lst) == 4) {
				lst = -lst;
				tlst = getTs(); 
				aut_up += (aut_up + 1) / 2;
				tup = getTs();
			}
			moveto(X - 1, Y);
		}
		aut_up += 1;
		bouncin = false;
	}
	void auto_up() {
		if (getTs() - tup < 0.2)
			return;
		if (block_side(X - 1, Y)) { 
			if (real_tobj(X - 1, Y) == 4) {
				falin = true;
				fall_cnt = (aut_up + 1) / 2;
				speed = 0.5 / (2.5 + fall_cnt);
			}
			aut_up = 0;
			return;
		}
		if (!block_side(X - 1, Y + lst)) moveto(X - 1, Y + lst);
		else {
			auto p = exfind(X - 1, Y + lst);
			if (real_tobj(X - 1, Y + lst) == 5) {
				reduct(p.first, p.second);
				score += 1;
			}
			else if (real_tobj(X - 1, Y + lst) == 4) {
				lst = -lst;
				tlst = getTs(); 
				aut_up += (aut_up + 1) / 2;
				tup = getTs();
			}
			moveto(X - 1, Y);
		}
		aut_up -= 1;
		bouncin = false;
	}
	void left() {
		lst = -1;
		if (cnt_up) return;
		tlst = getTs();
		if (block_side(X, Y - 1) or !block_side(X + 1, Y)) return;
		moveto(X, Y - 1);
	}
	void right() {
		lst = +1;
		if (cnt_up) return;
		tlst = getTs();
		if (block_side(X, Y + 1) or !block_side(X + 1, Y)) return;
		moveto(X, Y + 1);
	}
	void free() {
		auto T = getTs();
		if (block_side(X + 1, Y) and !bouncin) {
			if (cnt_up) {
				cnt_up = 0;
				print();
			}
			if (falin) {
				if (real_tobj(X + 1, Y) == 4 and fall_cnt and !block_side(X - 1, Y)) {
					if (cnt_up != 1) {
						cnt_up = 1;
						print();
					}
					bouncin = true;
					if (T - tlst > 0.3) lst = 0;
					aut_up = (fall_cnt + 1) / 2;
					tup = T;
				}
				speed = 0.2;
				fall_cnt = 0;
				falin = false;
			}
		}
		else if (!aut_up and T - tfall > speed and !bouncin) {
			tfall = T;
			if (!falin) {
				falin = true;
				if (!cnt_up) cnt_up += 1;
			}
			else {
				fall_cnt += 1;
				speed = 0.5 / (2.5 + fall_cnt);
				moveto(X + 1, Y);
			}
		}
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
	int print_mode() {
		cls();
		jump(0, 0);
		col(0, 11);
		cout << "\n ¡ô select mode ¡ô        [W] [S] [¡ü] [¡ý] [K]\n\n";
		for (int i = 0; i < nM; ++i) {
			col(0, i == m ? 14 : 15);
			cout << "   " << name[i] << '\n';
		}
		col(0, 11);
		cout << "\n ¡ô select skin ¡ô        [A] [D] [¡û] [¡ú]\n\n";
		col(0, cobj[object + aux]);
		cout << "   ¡ñ\n";
		col(0, 11);
		cout << "\n ¡ô select map size ¡ô    [Q] [E]\n\n";
		col(0, 14);
		cout << "   " << print_R0 << '\n';
		col(0, 11);
		cout << "\n ¡ô select map range ¡ô   [Z] [C]\n\n";
		col(0, 14);
		cout << "   " << print_R1 << '\n';
		for (; (ch = getch()); ) {
			towasd();
			if (ch == ' ') return 0;
			if (ch == 'k') return 1;
			if (ch == 'w') {
				if (!m) continue;
				jump(3, 3 + m);
				col(0, 15);
				cout << name[m--];
				jump(3, 3 + m);
				col(0, 14);
				cout << name[m];
			}
			else if (ch == 's') {
				if (m + 1 >= nM) continue;
				jump(3, 3 + m);
				col(0, 15);
				cout << name[m++];
				jump(3, 3 + m);
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
				jump(3, 6 + nM);
				col(0, cobj[object + aux]);
				cout << "¡ñ";
			}
			else if (ch == 'q' or ch == 'e') {
				if (ch == 'q' and print_R0 > max(3, print_R1)) print_R0 -= 1;
				if (ch == 'e' and print_R0 < 14) print_R0 += 1;
				jump(3, 10 + nM);
				col(0, 14);
				cout << print_R0 << "   "; 
			}
			else if (ch == 'z' or ch == 'c') {
				if (ch == 'z' and print_R1 > 0) print_R1 -= 1;
				if (ch == 'c' and print_R1 < print_R0) print_R1 += 1;
				jump(3, 14 + nM);
				col(0, 14);
				cout << print_R1 << "   "; 
			}
		}
	}
	const int maxD=10,inf=1e9,maxCnum=maxD*maxD+(maxD+1)*(maxD+1);
	const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
	struct node{
		int x,y;
		node(int _x=0,int _y=0){x=_x,y=_y;}
		node(pair<int,int>_x){x=_x.first,y=_x.second;}
		int dis(node o){
			return abs(x-o.x)+abs(y-o.y);
		}
		friend bool operator==(node x,node y){
			return x.x==y.x&&x.y==y.y;
		}
		friend bool operator!=(node x,node y){
			return x.x!=y.x||x.y!=y.y;
		}
		friend node operator+(node x,node y){
			return node(x.x+y.x,x.y+y.y);
		}
		bool valid(){
			return x>=0&&x<nx&&y>=0&&y<ny;
		}
	};
	int id(int x,int y){
		return x*ny+y;
	}
	int id(node x){
		return id(x.x,x.y);
	}
	node id(int x){
		return node(x/ny,x%ny);
	}
	struct botfish_d{
		int d,cnum,que[xn*xn],nid[xn*xn],idx;
		node rnid[maxCnum];
		double lwk;
		void bfs(int s,int*dis,int d){
			node sn=rnid[s];
			int l=0,r=-1;
			dis[s]=0,que[++r]=s;
			while(l<=r){
				int u=que[l++];
				node un=rnid[u];
				for(int i=0;i<4;i++){
					node vn=un+node(dx[i],dy[i]);
					if(!vn.valid()||sn.dis(vn)>d||bot_side_b(vn.x,vn.y))continue;
					int v=nid[id(vn)];
					if(dis[v]==inf)dis[v]=dis[u]+1,que[++r]=v;
				}
			}
		}
		int dis[maxCnum];
		void init(int _d){
			d=_d,cnum=d*d+(d+1)*(d+1);
		}
		void work(){
			idx=0;
			for(int i=X-d;i<=X+d;i++)
				for(int j=Y-d;j<=Y+d;j++){
					if(node(X,Y).dis(node(i,j))>d)continue;
					rnid[idx]=node(i,j);
					if(node(i,j).valid())nid[id(i,j)]=idx;
					idx++;
				}
			assert(idx==cnum);
			for(int i=0;i<cnum;i++)
				dis[i]=inf;
			bfs(nid[id(X,Y)],dis,d);
		}
	}bf_d;
	struct botfish{
		int x,y,d;
		botfish(int _x,int _y){
			x=_x,y=_y,d=maxD;
		}
		int nid(int _x,int _y){
			_x-=X,_y-=Y;
			int td=bf_d.d;
			if(_x<=0)return (td+_x)*(td+_x)+(_y-(-d-_x));
			_x=-_x,_y=-_y;
			return bf_d.cnum-1-nid(_x+X,_y+Y);
		}
		int dis1(int _x,int _y){
			return bf_d.dis[nid(_x,_y)];
		}
		int dis1(node _x){
			return dis1(_x.x,_x.y);
		}
		int dis1(){
			return dis1(x,y);
		}
		int dis2(int _x,int _y){
			return node(X,Y).dis(node(_x,_y));
		}
		int dis2(node _x){
			return dis2(_x.x,_x.y);
		}
		int dis2(){
			return dis2(x,y);
		}
		void move(node to){
			g[to.x][to.y]=g[x][y];
			a[to.x][to.y]=a[x][y];
			g[x][y]=f[x][y];
			x=to.x,y=to.y;
			if(node(x,y)==node(X,Y))botkill();
		}
		bool work1(){
			node now=node(x,y),to=now;
			for(int i=0;i<4;i++){
				node v=now+node(dx[i],dy[i]);
				if(!v.valid()||dis2(v)>d||bot_side(v.x,v.y))continue;
				if(dis1(v)<dis1(to))to=v;
			}
			if(to!=now)return move(to),1;
			return 0;
		}
		bool work2(){
			node now=node(x,y),to=now;
			for(int i=0;i<4;i++){
				node v=now+node(dx[i],dy[i]);
				if(!v.valid()||bot_side(v.x,v.y))continue;
				if(dis2(v)<dis2(to))to=v;
			}
			if(to!=now)return move(to),1;
			return 0;
		}
		bool work(){
			jump(0,31);
			if(dis2()<=d&&dis1()!=inf)return work1();
			return work2();
		}
	};
	vector<botfish>jelly,jelly_tmp;
	void bot_init(){
		bf_d.init(maxD);
		bf_d.lwk=getTs();
	}
	void bot_clear(){
		jelly.clear();
		jelly_tmp.clear();
	}
	void bot_reinit(){
		for(int i=0,sz=jelly.size();i<sz;i++){
			int x=jelly[i].x,y=jelly[i].y;
			reduct(x,y);
		}
		jelly=jelly_tmp;
		for(int i=0,sz=jelly.size();i<sz;i++){
			int x=jelly[i].x,y=jelly[i].y;
			g[x][y]=-23;
		}
		bf_d.lwk=getTs();
		print();
		bot_rinit=0;
	}
	void bot_work(){
		if((getTs()-bf_d.lwk)*1000<740)return;
		bf_d.work(),bf_d.lwk=getTs();
		vector<int>del,mq;
		for(int i=0,sz=jelly.size();i<sz;i++)
			mq.push_back(i);
		while(1){
			del.clear();
			for(auto i:mq)
				if(jelly[i].work())del.push_back(i);
			vector<int>tmp;
			int x=0,sz=mq.size();
			for(auto i:del){
				while(mq[x]!=i)tmp.push_back(mq[x++]);
				x++;
			}
			while(x<sz)tmp.push_back(mq[x++]);
			mq=tmp;
			if(del.empty())break;
			bf_d.work();
		}
		print();
	}
	string levelin(int x) {
		stringstream s;
		s << "level" << x << ".in";
		return s.str();
	}
	bool skip0, skip1;
	void init_map() {
		bot_clear();
		score = 0;
		win = false;
		freopen(levelin(m).c_str(), "r", stdin);
		cin >> nx >> ny;
		for (int i = 0; i < nx; ++i) for (int j = 0; j < ny; ++j) {
			cin >> g[i][j];
			f[i][j] = get_tobj(i, j) == 5 or get_tobj(i, j) == 1 ? 0 : g[i][j];
			if (get_tobj(i, j) == 3) cin >> a[i][j].first >> a[i][j].second;
			else if (get_tobj(i, j) == 1) init(i, j);
			else if (get_tobj(i, j) == 6) cin >> a[i][j].first;
		}
		for(int i=0;i<nx;i++)
			for(int j=0;j<ny;j++)
				if(g[i][j]==-23)jelly.push_back(botfish(i,j)),f[i][j]=0;
		jelly_tmp=jelly;
		cls();
		print_x = print_y = -1;
		memset(print_g, 0, sizeof print_g);
		print();
		freopen("CON", "r", stdin);
		bot_init();
	}
	void load_level() {
		init_map();
		auto T = getTs();
		col(0, 15);
		jump(0, 29 + 1);
		cout << "time : 0.000";
		if (best[m] >= 0) {
			jump(0, 29 + 3);
			cout << "best : " << best[m];
		}
		jump(20, 29 + 1);
		cout << "score : 0";
		col(0, 14);
		jump(20, 29 + 3);
		cout << "[S] : ";
		for (; !win; ) {
			if (kbhit()) {
				ch = getch();
				towasd();
				if (ch == 27) return;
				if (ch == 'r') return skip1 = true, void();
				if (ch == 'w') W();
				else if (ch == 'a') A();
				else if (ch == 'd') D();
				else if (ch == 's') {
					col(0, 14);
					jump(26, 29 + 3);
					cout << getTs() - T;
				}
			}
			free();
			bot_work();
			if(bot_rinit) bot_reinit();
			col(0, 15);
			jump(7, 29 + 1);
			cout << getTs() - T;
			jump(28, 29 + 1);
			cout << score;
		}
		if (win) {
			jump((Y - print_y + print_R0) * 2, X - print_x + print_R0);
			col(0, cobj[object + aux]);
			cout << "¢Ù";
			double useT = getTs() - T;
			if (best[m] < 0 or useT < best[m]) {
				jump(7, 29 + 1);
				cout << useT;
				if (best[m] >= 0) {
					jump(6, 29 + 4);
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
		jump(0, 29 + 5);
		col(0, 15);
		printf("input any key to continue.");
		while (true) if (kbhit()) {
			ch = getch();
			towasd();
			if (ch == 'r') skip1 = true;
			return;
		}
	}
	string rankin(int x) {
		stringstream s;
		s << "rank" << x << ".in";
		return s.str();
	}
	string githublink(int x) {
		stringstream s;
		s << "start https://ballspeedrun.github.io/#" << x;
		return s.str();
	}
	void load_rank() {
		freopen(rankin(m).c_str(), "r", stdin);
		int nr;
		cin >> nr;
		cls();
		jump(0, 0);
		col(0, 11);
		cout << "\n ¡ô ranking ¡ô            [O]\n\n";
		string s;
		getline(cin, s);
		for (int i = 0; i < nr; ++i) {
			getline(cin, s);
			col(0, i == 0 ? 14 : i == 1 ? 15 : i == 2 ? 6 : 8);
			cout << "   " << s << '\n';
		}
		freopen("CON", "r", stdin);
		s = githublink(m);
		while (true) if (kbhit()) {
			ch = getch();
			towasd();
			if (ch == 27) return;
			if (ch == 'o') system(s.c_str());
		}
	}
	void run() {
		if (skip0 or !print_mode()) load_level();
		else load_rank();
	}
	void work() {
		init_obj();
		init_modes();
		m = 0;
		object = 1;
		skip0 = skip1 = false;
		print_R0 = 14;
		print_R1 = 0;
		for (; true; ) {
			skip0 = skip1;
			skip1 = false;
			run();
		}
	}
};
void play() {
	cls();
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
	system("mode con cols=60 lines=40");
	play();
	return 0;
}
