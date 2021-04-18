#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>


SceneID scene1, scene2, scene5, scene6, scene7, scene8, scene9, scene10;
ObjectID man1, objject[5], enter[5], clear[3], end;
ObjectID puzzle[9], start, start2, ori_puzzle[9];
ObjectID quiz[3], next, next2, quiz2[3], quiz3[3];
ObjectID man2, crush, start3, color[3], start4;
TimerID timer1, timer2, timer3;
int manX = 550;
int manY = 510;
int blank = 8;
bool game1 = false;
bool game2 = false;
bool game3 = false;
bool game4 = false;
bool game5 = false;
bool game6 = false;


ObjectID createObject2(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}

TimerID createTimer2(Second second, bool shown) {
	TimerID timer = createTimer(second);
	if (shown) {
		showTimer(timer);
	}
	return timer;
}

// 퍼즐
int puzzle_index(ObjectID object) {
	for (int i = 0; i < 9; i++){
		if (puzzle[i] == object) return i;
	}
	return -1;
}

void puzzle_move(int i) {
	ObjectID object = puzzle[i];
	puzzle[i] = puzzle[blank];
	locateObject(puzzle[i], scene2, 350 + 150 * (i % 3), 450 - 150 * (i / 3));
	puzzle[blank] = object;
	locateObject(puzzle[blank], scene2, 350 + 150 * (blank % 3), 450 - 150 * (blank / 3));

	blank = i;
}

bool possible(int i) {
	if (i % 3 > 0 && blank == i - 1) return true;
	if (i % 3 < 2 && blank == i + 1) return true;
	if (i / 3 > 0 && blank == i - 3) return true;
	if (i / 3 < 2 && blank == i + 3) return true;

	return false;
}

int	random_move() {
	int i = -1;
	while (i == -1) {
		switch (rand() % 4) {
			case 0: if (blank % 3 > 0) i = blank - 1;
				break;
			case 1: if (blank % 3 < 2) i = blank + 1;
				break;
			case 2: if (blank / 3 > 0) i = blank - 3;
				break;
			case 3: if (blank / 3 < 2) i = blank + 3;
				break;
		}
	}
	return i;
}

void puzzlestart() {
	hideObject(puzzle[blank]);
	for (int i = 0; i < 30; i++) {
		puzzle_move(random_move());
	}
}

bool puzzleend() {
	for (int i = 0; i < 9; i++) {
		if (puzzle[i] != ori_puzzle[i]) {
			return false;
		}
	}
	return true;
}

//퀴즈
void quizstart() {
	showMessage("유비쿼터스와 유목민을 합성한 신조어, 네트워크 접속만으로 모든일을 처리할 수 있는 사람은?   1. 유비노마드  2. 유비시티즌  3. 유비페이스");
}

void quizstart2() {
	showMessage("최영 장군은 평생 이것보기를 돌처럼 하라는 아버지 유언을 지키며 살았는데, 이것은?        1. 시간  2. 지식  3. 황금");
}

void quizstart3() {
	showMessage("다음 보기 중에 시계바늘이 도는 방향과 같은 방향인 것은 무엇인가요?\n1. 야구주자가 도는 방향 2. 나사 조이는 방향  3.병뚜껑 여는 방향");
}

int quiz_index(ObjectID object) {
	for (int i = 0; i < 3; i++) {
		if (quiz[i] == object) return i;
	}
	return -1;
}

int quiz2_index(ObjectID object) {
	for (int i = 0; i < 3; i++) {
		if (quiz2[i] == object) return i;
	}
	return -1;
}

int quiz3_index(ObjectID object) {
	for (int i = 0; i < 3; i++) {
		if (quiz3[i] == object) return i;
	}
	return -1;
}

bool quiz_answer(int i, int y) {
	switch (y) {
		case 1: if (i == 1) return true;
			break;
		case 2: if (i == 3) return true;
			break;
		case 3: if (i == 2) return true;
			break;
	}
	return false;
}

//폭탄
void endbomb(bool success) {
	if (success) {
		enterScene(scene9);
		showMessage("폭탄이 너무 어려워 찍어야겠어\n색깔 둘 중 하나를 고르세요.(무조건 하나만 안 터짐)");
		hideObject(crush);
		stopTimer(timer1);
		hideTimer();
	}
	else {
		showMessage("폭탄 폭발 ~ 실패");
		hideObject(crush);
		showObject(start3);
		manY = 510;
		game2 = false;
		locateObject(man2, scene8, manX, manY);
		stopTimer(timer1);
		enterScene(scene1);
	}
}

int color_index(ObjectID object) {
	for (int i = 0; i < 2; i++) {
		if (color[i] == object) return i;
	}
	return -1;
}

bool random_bomb(int j) {
	
	switch (rand() % 2) {
		case 0: if (j == 0) return true;
			break;
		case 1: if (j == 1) return true;
			break;
	}
	return false;

}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == objject[0]) {
		locateObject(man1, scene1, 430, 220);
		hideObject(objject[0]);
		showObject(enter[0]);
	}
	if (object == objject[1]) {
		locateObject(man1, scene1, 730, 220);
		hideObject(objject[1]);
		showObject(objject[0]);
		showObject(enter[1]);

	}
	if (object == objject[2]) {
		locateObject(man1, scene1, 730, 520);
		hideObject(objject[2]);
		showObject(objject[1]);
		showObject(objject[0]);
		showObject(enter[2]);
	}
	if (object == enter[0]) {
		enterScene(scene2);
		showMessage("집 모니터가 퍼즐모양으로 깨졌어요ㅠㅠ 매뤼오쒸 헬프미\n퍼즐을 푸세요!!");
	}
	if (game1) {
		int i = puzzle_index(object);
		if (possible(i)) {
			puzzle_move(i);

			if (puzzleend()) {
				game1 = false;
				showObject(start);
				showObject(puzzle[blank]);
				enterScene(scene1);
				showMessage("첫번째 미션 성공 ~ 다음 문제상황까지 기다리세요");
				hideObject(enter[0]);
				showObject(clear[0]);
				setTimer(timer2, 5.0f);
				startTimer(timer2);
				showTimer(timer2);
			}
		}
	}
	else if (object == start) {
		game1 = true;
		hideObject(start);
		puzzlestart();
	}

	if (object == enter[1]) {
		enterScene(scene5);
		showMessage("아파트비번이 갑자기 퀴즈로 바꼈어요.ㅠㅠ ~ 매뤼오쒸 헬프미\n퀴즈를 푸세요!!");
	}
	if (game4) {
		int i = quiz_index(object) + 1;
		if (object) {
			printf("%d", i);
		}
		if (quiz_answer(i, 1)) {
			showMessage("정답입니다");
			showObject(next);
			game4 = false;
		}

		else {
			enterScene(scene1);
			showMessage("오답입니다");
			showObject(start2);
			game4 = false;
		}
	}

	else if (object == start2) {
		game4 = true;
		hideObject(start2);
		quizstart();
	}

	if (game5) {
		int i = quiz2_index(object) + 1;
		if (object) {
			printf("%d", i);
		}
		if (quiz_answer(i, 2)) {
			showMessage("정답입니다");
			showObject(next2);
			game5 = false;
		}

		else {
			enterScene(scene1);
			showMessage("오답입니다");
			game5 = false;
		}
	}

	else if (object == next) {
		game5 = true;
		enterScene(scene6);
		showObject(start2);
		hideObject(next);
		quizstart2();
	}

	if (game6) {
		int i = quiz3_index(object) + 1;
		if (quiz_answer(i, 3)) {
			showMessage("두번째 미션 성공 ~ 다음 문제상황까지 기다리세요");
			enterScene(scene1);
			hideObject(enter[1]);
			showObject(clear[1]);
			startTimer(timer3);
			showTimer(timer3);
			game6 = false;
		}

		else {
			enterScene(scene1);
			showMessage("오답입니다");
			hideObject(next2);
			game6 = false;
		}
	}

	else if (object == next2) {
		game6 = true;
		enterScene(scene7);
		quizstart3();
	}

	if (object == enter[2]) {
		enterScene(scene8);
		showMessage("누가 맨홀 아래에 폭탄을 던졌어요 ~ 우리 다 죽게 생겼어요우 ~ 헬프 미\n아래의 위험구역까지 가서 제거해주세요.");
		showTimer(timer1);
	}

	if (game2) {
		if (object == crush) {
			manY = manY - 500;
			locateObject(man2, scene8, manX, manY);

			if (manY < 100) {
				endbomb(true);
				game2 = false;
			}
		}
	}
	else if (object == start3) {
		game2 = true;
		hideObject(start3);
		showObject(crush);
		setTimer(timer1, 10.0f);
		startTimer(timer1);
	}

	if (game3) {
		int i = color_index(object);
		if (random_bomb(i)) {
			enterScene(scene10);
			showMessage("마지막 미션 성공 ~ 운도 좋은 나는 이 도시의 영웅, 매뤼오\n MARIIIIIIOOOOOOO!");
			game3 = false;
		}
		else {
			showMessage("폭탄 폭발 ~ 실패");
			enterScene(scene1);
			showObject(start4);
			hideObject(color[0]);
			hideObject(color[1]);
			game3 = false;
			showObject(start3);
			manY = 510;
			locateObject(man2, scene8, manX, manY);
		}
	}
	else if (object == start4) {
		game3 = true;
		showObject(color[0]);
		showObject(color[1]);
		hideObject(start4);
	}

	if (object == end) {
		endGame();
	}
}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		endbomb(false);
	}
	if (timer == timer2) {
		showObject(objject[1]);
		hideTimer();
		setTimer(timer3, 5.0f);
	}
	if (timer == timer3) {
		showObject(objject[2]);
		hideTimer();
	}
}

int main() {
	srand(time(NULL));
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	scene1 = createScene("도시", "city.png");
	scene2 = createScene("퍼즐", "squad-b.png");
	scene5 = createScene("퀴즈 1번", "quiz-b.png");
	scene6 = createScene("퀴즈 2번", "quiz-b.png");
	scene7 = createScene("퀴즈 3번", "quiz-b.png");
	scene8 = createScene("폭탄 도달", "bomb-b.png");
	scene9 = createScene("폭탄 해체", "colorbomb-b.png");
	scene10 = createScene("성공", "successcity.png");

// 퍼즐
	char path[50];
	for (int i = 0; i < 9; i++) {
		sprintf(path, "squad%d.png", i + 1);
		puzzle[i] = createObject2(path, scene2, 350 + 150 * (i % 3), 450 - 150 * (i / 3), true);
		ori_puzzle[i] = puzzle[i];
	}
	start = createObject2("start.png", scene2, 590, 100, true);

// 지도
	man1 = createObject2("face.png",scene1, 450, 530, true);
	objject[0] = createObject2("n.png", scene1, 420, 220, true);
	objject[1] = createObject2("n.png", scene1, 720, 220, false);
	objject[2] = createObject2("n.png", scene1, 720, 520, false);
	enter[0] = createObject2("enter.png", scene1, 420, 180, false);
	enter[1] = createObject2("enter.png", scene1, 720, 180, false);
	enter[2] = createObject2("enter.png", scene1, 720, 480, false);
	clear[0] = createObject2("clear.png", scene1, 420, 180, false);
	clear[1] = createObject2("clear.png", scene1, 720, 180, false);
	clear[2] = createObject2("clear.png", scene1, 720, 480, false);
	end = createObject2("end.png", scene10, 350, 10, true);
	timer2 = createTimer2(5.0f, false);
	timer3 = createTimer2(5.0f, false);


// 퀴즈
	char ath[50];
	for (int j = 0; j < 3; j++) {
		sprintf(ath, "%d.png", j + 1);
		quiz[j] = createObject2(ath, scene5, 420 * j - 35, 120 , true);
		quiz2[j] = createObject2(ath, scene6, 420 * j - 35, 120, true);
		quiz3[j] = createObject2(ath, scene7, 420 * j - 35, 120, true);
	}
	next = createObject2("play.png", scene5, 590, 100, false);
	next2 = createObject2("play.png", scene6, 590, 100, false);
	start2 = createObject2("start.png", scene5, 590, 100, true);

// 폭탄
	man2 = createObject2("face-b.png", scene8, manX, manY, true);
	crush = createObject2("crush.png", scene8, 625, 0, false);
	start3 = createObject2("start.png", scene8, 620, 15, true);
	start4 = createObject2("start.png", scene9, 590, 100, true);
	timer1 = createTimer2(10.0f, false);

	char cth[50];
	for (int z = 0; z < 2; z++) {
		sprintf(cth, "color%d.png", z + 1);
		color[z] = createObject2(cth, scene9, 200 + z * 600, 0, false);
	}

	showMessage("매뤼오쒸 ~ 도시의 문제점을 바로잡아주세요!! 느낌표를 향해 돌격!!");
	startGame(scene1);
}
