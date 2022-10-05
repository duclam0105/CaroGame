#pragma once
//#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <map>
//#include <thread>
//#include <mutex>

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


typedef enum { side_O, side_X, other }typeXO_t;
typedef enum { is_playing, X_win, O_win, draw }result_t;
typedef enum { disable_t, enable_t }en_t;
typedef enum { cmd_NaN, cmd_newgame, cmd_continue, cmd_savegame, cmd_loadgame, cmd_showdata, 
				cmd_findperson, cmd_host, cmd_join, cmd_quitgame, cmd_exit }game_cmd;
typedef enum { st_waiting, st_playing }game_state;

struct vCoord {
	COORD p;
	bool en;
};

struct mCoord {
	COORD p;
};
