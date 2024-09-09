#include <iostream>
using namespace std;

const char sceneData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";//ע���ַ����ж���Ŀո�
const int Width = 8;
const int Height = 5;
enum Object {
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BOX,
	OBJ_BOX_ON_GOAL,
	OBJ_PLAYER,
	OBJ_PLAYER_ON_GOAL,

	OBJ_UNKNOWN,
};

void initialize(Object* state, int width, int height, const char* sceneData);
void draw(const Object* state, int width, int height);
bool checkStatus(const Object* s, int w, int h);
void update(Object* s, char input, int w, int h);

int main() {
	//cout << sceneData << endl;
	//state���ڼ�¼����״̬
	Object* state = new Object[Width * Height];
	char input;
	//��ʼ������
	initialize(state, Width, Height, sceneData);

	//��ѭ��
	while (true) {
		draw(state, Width, Height);

		if (checkStatus(state, Width, Height)) {
			break;
		}

		cout << "Use WASD to move the player" << endl;
		cin >> input;
		update(state, input, Width, Height);
	}

	//��Ϸ��������ʾ
	cout << "Well done!" << endl;

	delete[] state;
	state = nullptr;

	return 0;
}

void initialize(Object* state, int width, int height, const char* sceneData) {
	const char* read = sceneData;
	int x = 0;
	int y = 0;
	Object obj;
	while (*read != '\0') {
		switch (*read) {
			case '#':obj = OBJ_WALL; break;
			case ' ':obj = OBJ_SPACE; break;
			case '.':obj = OBJ_GOAL; break;
			case 'p':obj = OBJ_PLAYER; break;
			case 'P':obj = OBJ_PLAYER_ON_GOAL; break;
			case 'o':obj = OBJ_BOX; break;
			case 'O':obj = OBJ_BOX_ON_GOAL; break;
			case '\n':x = 0; ++y; obj = OBJ_UNKNOWN; break;
			default:obj = OBJ_UNKNOWN; break;
		}
		++read;
		if (obj != OBJ_UNKNOWN) {
			state[y * width + x] = obj;
			x++;
		}
	}
}

void draw(const Object* state, int width, int height) {
	const char font[] = { ' ', '#', '.', 'o', 'O','p','P' };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Object obj = state[y * width + x];
			cout << font[obj];//ö�����ͱ�������int
		}
		cout << endl;
	}
}

void update(Object* s, char input, int w, int h) {
	int dx = 0;
	int dy = 0;
	switch (input)
	{
		case 'a': dx = -1; break;
		case 'd': dx = 1; break;
		case 'w': dy = -1; break;
		case 's': dy = 1; break;
	}
	//�������λ��
	int i = 0;
	for (i = 0; i < w * h; i++) {
		if (s[i] == OBJ_PLAYER || s[i] == OBJ_PLAYER_ON_GOAL)
			break;
	}
	int x = i % w;
	int y = i / w;

	//�ƶ��������
	int tx = x + dx;
	int ty = y + dy;
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}

	int p = y * w + x;//��ҵ�ǰλ��
	int tp = ty * w + tx;//Ŀ��λ��
	//Ŀ��λ��û������
	if (s[tp] == OBJ_SPACE || s[tp] == OBJ_GOAL) {
		//�����һ����Ŀ�ĵ�
		s[tp] = s[tp] == OBJ_GOAL ? OBJ_PLAYER_ON_GOAL : OBJ_PLAYER;
		//�����ҵ�ǰ��Ŀ�ĵأ���һ�����뿪
		s[p] = s[p] == OBJ_PLAYER_ON_GOAL ? OBJ_GOAL : OBJ_SPACE;
	}
	//Ŀ��λ��������
	else if (s[tp] == OBJ_BOX_ON_GOAL || s[tp] == OBJ_BOX) {
		//��Ŀ�귽��ڶ�������
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) {
			return;
		}
		int tp2 = ty2 * w + tx2;
		if (s[tp2] == OBJ_GOAL || s[tp2] == OBJ_SPACE) {
			s[tp2] = s[tp2] == OBJ_GOAL ? OBJ_BOX_ON_GOAL : OBJ_BOX;
			s[tp] = s[tp] == OBJ_BOX_ON_GOAL ? OBJ_PLAYER_ON_GOAL : OBJ_PLAYER;
			s[p] = s[p] == OBJ_PLAYER_ON_GOAL ? OBJ_GOAL : OBJ_SPACE;
		}
	}
}

bool checkStatus(const Object* s,int w, int h) {
	for (int i = 0; i < w * h; i++) {
		//ȫ���Ƶ�Ŀ�ĵغ�Ͳ�����OBJ_BOX�ˣ�����OBJ_BOX_ON_GOAL��
		if (s[i] == OBJ_BOX) return false;
	}
	return true;
}

