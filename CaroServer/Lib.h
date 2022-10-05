#pragma once
//#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <ostream>
#include <sstream>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

#define disable			false
#define enable			true
#define TABLE_POS_X		12	//4
#define TABLE_POS_Y		8	//3
#define CELL_WIDTH		4
#define CELL_HEIGHT		2
#define RULE			5	//dieu kien thang khi co 5 vi tri thang hang hoac theo duong cheo
#define MIN_TABLE_SIZE	5
#define MAX_TABLE_SIZE	13

typedef enum {
	cmd_NaN,
	cmd_p1,
	cmd_gameid,
	cmd_p2,
	cmd_host,
	cmd_join,
	cmd_size,
	cmd_p1_move,
	cmd_p2_move,
	cmd_showDB,
	cmd_result
}msg_cmd;

typedef enum { side_O, side_X, other }typeXO_t;
typedef enum { is_playing, X_win, O_win, draw }result_t;

struct vCoord {
	COORD p;
	bool en;
};

struct mCoord {
	COORD p;
	int turn;
};
