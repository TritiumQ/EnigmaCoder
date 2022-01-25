#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int rotor[10][36] =
{
{20,2,17,10,15,32,29,25,18,14,5,12,31,35,19,34,3,7,0,21,22,24,11,6,28,33,26,1,8,9,4,27,13,16,30,23},
{5,26,21,3,13,6,19,12,0,8,31,18,35,28,4,24,22,11,34,15,33,23,27,32,2,30,7,25,16,20,29,1,9,17,14,10},
{28,10,34,9,25,24,32,2,23,8,21,33,4,13,15,30,14,6,27,20,0,3,19,12,16,7,5,18,35,31,26,11,22,1,29,17},
{19,26,24,30,16,33,5,22,3,17,31,35,9,15,27,34,4,29,14,8,0,6,21,7,28,18,10,11,2,13,23,32,1,25,20,12},
{33,21,27,24,31,13,20,7,34,23,6,26,19,30,22,14,9,10,16,0,5,17,8,35,4,32,18,11,29,3,28,25,2,15,1,12},
{13,9,25,19,14,15,1,20,30,5,2,31,33,4,16,34,17,24,12,27,0,10,26,35,22,6,28,3,29,32,7,21,8,11,23,18},
{15,30,35,24,29,17,27,4,12,22,14,33,6,32,28,21,26,5,10,19,2,8,7,25,31,20,11,3,16,34,9,23,0,1,13,18},
{15,9,23,29,25,34,8,33,10,28,22,31,16,18,12,4,17,3,19,26,21,7,20,0,11,2,14,24,6,32,5,30,27,13,35,1},
{25,23,18,7,8,12,33,29,20,35,13,16,3,17,22,24,4,5,19,10,26,9,32,30,11,15,27,34,0,2,31,21,6,1,28,14},
{7,19,9,30,21,33,18,24,17,31,32,0,8,10,26,13,3,16,34,25,1,29,27,4,14,22,28,12,11,15,23,5,2,35,20,6}
};

const char alnum[37] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };//基础字母数字表
int IN(char ch)//返回字母数字对应的下标
{
	for (int i = 0; i < 36; i++) {
		if (alnum[i] == ch) return i;
	}
	return -1;
}
char OUT(int idx)//返回下标对应的字母数字
{
	if (idx < 0 || idx >= 36) return '?';
	else return alnum[idx];
}

const int Re_Idx[36] = { 18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
int reflect(int i)
{
	return Re_Idx[i];
}

class Rotor {
public:
	int link[36], rlink[36];//记录转盘的替换规则
	int type;//记录转盘类型
	int state;//记录转盘状态
	int count;//记录转盘使用次数
	//int round;//记录已转过的圈数

	void init(int ti, int ri, int si)//转盘初始化
	{
		count = 0;
		type = ti;
		state = si;
		for (int i = 0; i < 36; i++) {
			link[i] = rotor[ri][i];
		}
		for (int i = 0; i < 36; i++) {
			rlink[link[i]] = i;
		}
	}

	void Rotor_Set()
	{
		count++;
		if (type == 1) {//一号转盘每加密一个字母，转盘转一格
			state++;
		}
		else if (type == 2) {//一号每转一圈二号转一格
			if (count == 36) {
				count = 0;
				state++;
			}
		}
		else if (type == 3) {//二号每转一圈三号转一格
			if (count == 36 * 36) {
				count = 0;
				state++;
			}
		}
		//else if
		if (state == 36) state = 0;
	}

	int handler(int num)//下标处理器，正向
	{
		int tmp = abs(num + state)%36; // 通过state的偏移量模拟转轮转动
		//if (tmp >= 36) tmp %= 36;
		return (link[tmp] - state + 36) % 36;
	}

	int handler_back(int num)//反向
	{
		int tmp = abs(num + state)%36;
		//if (tmp >= 36) tmp %= 36;
		tmp = (rlink[tmp] - state + 36) % 36;
		Rotor_Set();
		return tmp;
	}
};

class EgnimaCoder {
private:
	Rotor rot1, rot2, rot3;
	int r[3], s[3];

	bool read1()
	{
		string t;
		int tmp;
		for (int i = 0; i < 3; i++) {
			while (1) {
				cout << "选择转子" << i + 1 << "型号" << "(输入0~9) : ";
				cin >> t;
				tmp = t[0] - '0';
				if (t.length() == 1 && tmp>=0 && tmp<=9 && t[0] >='0' && t[0] <= '9') {
					r[i] = tmp%36;
					break;
				}
				cout << "格式错误!请重新输入\n";
			}
		}
		for (int i = 0; i < 3; i++) {
			while (1) {
				cout << "设置转子" << i + 1 << "状态(输入0~35) : ";
				cin >> t;
				if (t.length() == 1) {
					if (t[0] >= '0' && t[0] <= '9') {
						tmp = t[0] - '0';
						s[i] = tmp;
						break;
					}
				}
				else if (t.length() == 2) {
					if (t[0] >= '0' && t[0] <= '9' && t[1] >= '0' && t[1] <= '9') {
						tmp = (t[0] - '0') * 10 + t[1] - '0';
						if (tmp >= 0 && tmp <= 35) {
							s[i] = tmp;
							break;
						}
					}
				}
				cout << "格式错误!请重新输入\n";
			}
		}
		cout << endl << "本次加密的密钥:";
		for (int i : r) cout << i;
		for (int i : s) cout << setfill('0') << setw(2) << i;
		cout << endl;
		return true;
	}

	bool read2()
	{
		string password;
		cout << "请输入密码（九位阿拉伯数字）：\n";
		while (1) {
			cin >> password;
			if (password.length() != 9) cout << "密码格式错误，请重新输入:\n";
			else break;
		}
		//密码格式：000 00 00 00
		int t;
		for (int i = 0; i < 3; i++) {
			t = password[i] - '0';
			if (t < 0 || t>9) {
				t = abs(t) % 10;
			}
			r[i] = t;
		}
		for (int i = 0; i < 3; i++) {
			t = (password[2 * i + 3] - '0') * 10 + (password[2 * i + 4] - '0');
			if (t < 0 || t>35) {
				t = abs(t) % 36;
			}
		}
		return true;
	}
public:
	string encode(string str)
	{
		if (read1()) {
			rot1.init(1, r[0], s[0]);
			rot2.init(2, r[1], s[1]);
			rot3.init(3, r[2], s[2]);
			string tmp = "";
			for (char ch : str) {
				int ti; char tc;
				if (ch >= 'a' && ch <= 'z') {
					ch -= 32;
				}
				if (IN(ch) == -1) {
					tmp += '?';
				}
				else {
					ti = rot3.handler(rot2.handler(rot1.handler(IN(ch))));
					ti = reflect(ti);
					ti = rot1.handler_back(rot2.handler_back(rot3.handler_back(ti)));
					tc = OUT(ti);
					tmp += tc;
				}
			}
			return tmp;
		}
		else return "ERROR";
	}
	string decode(string str)
	{
		if (read2()) {
			rot1.init(1, r[0], s[0]);
			rot2.init(2, r[1], s[1]);
			rot3.init(3, r[2], s[2]);
			string tmp;
			for (char ch : str) {
				int ti; char tc;
				if (IN(ch) == -1) {
					tmp += '?';
				}
				else {
					ti = rot3.handler(rot2.handler(rot1.handler(IN(ch))));
					ti = reflect(ti);
					ti = rot1.handler_back(rot2.handler_back(rot3.handler_back(ti)));
					tc = OUT(ti);
					tmp += tc;
				}
			}
			return tmp;
		}
		else return "ERROR";
	}
};

int main()
{
	string str, tmp;
	EgnimaCoder EC;
	while (1) {
		cout << "1.加密\n2.解密\n3.退出\n";
		int op = 0;
		string ops;
		cin >> ops;
		if (ops.length() != 1) op = -1;
		else op = ops[0] - '0';
		getline(cin, tmp);
		if (op == 1) {
			cout << "请输入需要加密的字符串（仅支持字母及阿拉伯数字）：\n";
			cin >> str;
			tmp = EC.encode(str);
			cout << "加密完成，这是密文：\n" << tmp << '\n';
		}
		else if (op == 2) {
			cout << "请输入需要解密的字符串（仅支持字母及阿拉伯数字）：\n";
			cin >> str;
			tmp = EC.decode(str);
			cout << "解密完成，这是明文：\n" << tmp << '\n';
		}
		else if (op == 3) {
			return 0;
		}
		else {
			cout << "ERROR" << endl;
		}
		cout << "----------------------------------------------------" << endl;
	}
	return 0;
}

