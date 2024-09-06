#include <iostream>
using namespace std;

const char* sceneData = "########\n\
						 # .. p #\n\
						 # oo   #\n\
						 #	    #\n\
						 ########";
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
void draw(Object* state, int width, int height);
bool checkStatus();
void update();

int main() {
	//state用于记录场景状态
	Object* state = new Object[Width * Height];
	char input;
	//初始化场景
	initialize(state, Width, Height, sceneData);

	//主循环
	while (true) {
		draw(state, Width, Height);

		if (checkStatus()) {
			break;
		}

		cout << "Use WASD to move the player" << endl;
		cin >> input;
		update();
	}

	//游戏结束的提示
	cout << "Well done!" << endl;

	delete[] state;
	state = nullptr;

	return 0;
}

void initialize(Object* state, int width, int height, char* sceneData) {
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

void draw(Object* state, int width, int height) {
	const char font[] = { ' ', '#', '.', 'o', 'O','p','P' };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Object obj = state[y * width + x];
			cout << font[obj];//枚举类型本质上是int
		}
		cout << endl;
	}
}

