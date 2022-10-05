#include "Controller.h"

//Controller::Controller() {
//	/*client.client_init();*/
//}
//Controller::~Controller() {
//	//client.~client_sock();*/
//}

bool Controller::MtoVCoordConvert(mCoord mNode, vCoord& output) {
	if ((mNode.p.X < mView.getTableSize()) && (mNode.p.Y < mView.getTableSize())) {
		output.p.X = mNode.p.X * CELL_WIDTH + CELL_WIDTH / 2 + TABLE_POS_X;				//can ra giua o
		output.p.Y = mNode.p.Y * CELL_HEIGHT + CELL_HEIGHT / 2 + TABLE_POS_Y;
		return true;
	}
	else {
		return false;
	}
}

bool Controller::VtoMCoordConvert(vCoord vNode, mCoord& output) {
	//xac dinh xem o nay co nam trong table hay khong
	SHORT w = TABLE_POS_X + CELL_WIDTH * mView.getTableSize();
	SHORT h = TABLE_POS_Y + CELL_HEIGHT * mView.getTableSize();
	if ((vNode.p.X > TABLE_POS_X - 1) && (vNode.p.X < w) && (vNode.p.Y > TABLE_POS_Y - 1) && (vNode.p.Y < h)) {
		output.p.X = (vNode.p.X - TABLE_POS_X) / CELL_WIDTH;
		output.p.Y = (vNode.p.Y - TABLE_POS_Y) / CELL_HEIGHT;
		return true;
	}
	else {
		return false;
	}
}

void Controller::viewDisplayTable(int size) {
	mView.displayTable(size);
}

void Controller::viewDisplayMenu() {
	mView.displayMenu();
}

game_cmd Controller::readButton(vCoord vNode) {
	if (vNode.p.Y == 1) {
		if ((vNode.p.X > 0) && (vNode.p.X < 6)) {
			return cmd_newgame;
		}
		else if ((vNode.p.X > 6) && (vNode.p.X < 13)) {
			return cmd_savegame;
		}
		else if ((vNode.p.X > 13) && (vNode.p.X < 20)) {
			return cmd_loadgame;
		}
		else if ((vNode.p.X > 20) && (vNode.p.X < 27)) {
			return cmd_quitgame;
		}
		else if ((vNode.p.X > 27) && (vNode.p.X < 38)) {
			return cmd_showdata;
		}
		else if ((vNode.p.X > 38) && (vNode.p.X < 45)) {
			return cmd_findperson;
		}
		else if ((vNode.p.X > 71) && (vNode.p.X < 79)) {
			return cmd_exit;
		}
		else if ((vNode.p.X > 45) && (vNode.p.X < 52)) {
			return cmd_host;
		}
		else if ((vNode.p.X > 52) && (vNode.p.X < 59)) {
			return cmd_join;
		}
	}
	if (vNode.p.Y == 6) {
		if ((vNode.p.X > 24) && (vNode.p.X < 37)) {
			return cmd_continue;
		}
	}
	else return cmd_NaN;
}
//========================================//

void Controller::newGame() {
	//init temp variable
	game_run = true;
	tmp_p1.clear();
	tmp_p2.clear();
	tmp_gameid.clear();
	//Init game data
	mView.deleteTable();	//xoa du lieu cu neu co
	mView.clearNortifiBox();
	int tmp_size;
	mView.gotoXY(25, 4);
	cout << "Nhap kich thuoc cua ban co: ";
	cin >> tmp_size;
	viewDisplayTable(tmp_size);
	mView.displayName();
	mView.changeTextColor(ColorCode_Cyan);
	//string p1, p2, gameid;
	mView.gotoXY(15, 3);
	cout << "_";
	mView.gotoXY(15, 3);
	cin >> tmp_p1;
	mView.gotoXY(15, 4);
	cout << "_";
	mView.gotoXY(15, 4);
	cin >> tmp_p2;
	mView.changeTextColor(ColorCode_Grey);
	mView.gotoXY(10, 5);
	cout << "_";
	mView.gotoXY(10, 5);
	cin >> tmp_gameid;
	mView.changeTextColor(default_ColorCode);
	mModel.createGameTable(mView.getTableSize());
}

void Controller::saveGame() {
	mView.clearNortifiBox();
	if (gameMode == 1) {	//play offline
		mModel.setPlayerGameName(tmp_p1, tmp_p2);
		mModel.insertCurrGameToDB(tmp_gameid);
		mModel.insertPlayerToDB(tmp_p1, tmp_p2);
		mModel.updatePlayerResult(tmp_p1, tmp_p2, tmp_result);
		//write data to file ini
		file1.writeFile(tmp_p1, mModel.pushPlayerDataToINI(tmp_p1));
		file1.writeFile(tmp_p2, mModel.pushPlayerDataToINI(tmp_p2));
		mView.displayMsg(25, 6, "Done!");
	}
	else {	//playe online: game is autosave to Database when the game has result		
		//client.client_send("Save");
	}
}

void Controller::continueGame() {
	mModel.resetGameTable();
	mView.clearNortifiBox();
	mView.deleteTable();
	mView.displayMsg(25, 6, "                                 ");	//xoa msg
	mView.displayName();
	viewDisplayTable(mView.getTableSize());
	mModel.createGameTable(mView.getTableSize());
	game_run = true;
}

void Controller::loadGame(){
	mView.clearNortifiBox();
	mView.deleteTable();
	mModel.resetGameTable();
	string tmp_id;
	mView.displayMsg(26, 4, "Nhap game ID: ");
	cin >> tmp_id;
	// ===
	//check xem trong database co Game ID nay hay k
	map<string, Game>::iterator i;
	int count = 0;
	for (i = mModel.getMapBegin(); i != mModel.getMapEnd(); i++) {
		if (mModel.getGameIDFromDB(i) == tmp_id) {
			count++;
		}
	}
	if (count == 0) {
		mView.clearNortifiBox();
		mView.displayMsg(26, 4, "Cannot find Game: " + tmp_id + "!");
		return;
	}
	//tim kiem thanh cong. chay replay
	mView.displayName();
	mView.gotoXY(15, 3);
	cout << mModel.getP1Name();
	mView.gotoXY(15, 4);
	cout << mModel.getP2Name();
	mView.gotoXY(10, 5);
	cout << tmp_id;
	//===
	mView.clearNortifiBox();
	Game tmp_game = mModel.readGameFromDB(tmp_id);
	mModel.setCurrGame_Replay(tmp_game);
	viewDisplayTable(mModel.getGameTable_Replay());
	for (int i = 1; i < mModel.getGameTurn()+1; i++) {
		mCoord tmp = mModel.getNode_Replay(i);
		if (i % 2 == 1) {
			vCoord vNode;
			if (MtoVCoordConvert(tmp, vNode)) {
				mView.printX(vNode);
			}
		}
		else if (i % 2 == 0) {
			vCoord vNode;
			if (MtoVCoordConvert(tmp, vNode)) {
				mView.printO(vNode);
			}
		}
		Sleep(500);
	}
}

void Controller::quitGame(){
	mView.clearNortifiBox();
	mView.deleteTable();
	mView.deleteNameBox();
	mModel.resetGameTable();
	mView.displayMsg(25, 6, "                                 ");	//xoa msg
	game_run = false;
	client.client_cleanup();
}

void Controller::showDatabase() {
	mView.clearNortifiBox();
	mView.displayMsg(25, 6, "                                 ");	//xoa msg
	mView.deleteTable();
	mView.displayDBBox();
	if (!mModel.checkDBEmpty()) {
		SHORT x = 61, y = 10;
		map<string, Game>::iterator j;
		for (j = mModel.getMapBegin(); j != mModel.getMapEnd(); j++) {
			mView.gotoXY(x, y);
			cout << mModel.getGameIDFromDB(j);
			y += 2;
		}
	}
	//=== GET PLAYER DATABASE FROM SERVER
	client.client_cleanup();		//Dong ket noi neu co	
	//Ket noi den Server
	if (!client.client_init()) {
		mView.displayMsg(26, 5, "Cannot connect to Game server!");
		return;
	}
	string conn;
	client.client_receive(conn);
	mView.gotoXY(26, 5);
	cout << conn;
	Sleep(100);
	//Gui yeu cau shoe DB
	client.client_send("ShowDB");
	//Lay duong dan cua thu muc chua file INI
	string rMsg;
	if (!client.client_recv(rMsg, "Dir")) {
		mView.displayMsg(25, 6, "ERROR. BREAK!");
		return;
	}
	string dir = rMsg.erase(0, 12);
	file1.setDirection(dir);
	vector<Player> tmp = file1.loadDataToDB();
	mModel.loadDataFromIni(tmp);
	if (mModel.getPlayerDBSize() > 0) {
		SHORT x = 7, y = 10;
		for (int i = 0; i < mModel.getPlayerDBSize(); i++) {
			mView.gotoXY(x, y);
			mModel.getPlayerData(i);
			y += 2;
		}
	}
	//mView.displayMsg(26, 4, file1.getDirection());
}

void Controller::findPerson() {
	//=== GET PLAYER DATABASE FROM SERVER
	client.client_cleanup();		//Dong ket noi neu co	
	//Ket noi den Server
	if (!client.client_init()) {
		mView.displayMsg(26, 5, "Cannot connect to Game server!");
		return;
	}
	string conn;
	client.client_receive(conn);
	mView.gotoXY(26, 5);
	cout << conn;
	Sleep(100);
	//Gui yeu cau shoe DB
	client.client_send("ShowDB");
	//Lay duong dan cua thu muc chua file INI
	string rMsg;
	if (!client.client_recv(rMsg, "Dir")) {
		mView.displayMsg(25, 6, "ERROR. BREAK!");
		return;
	}
	string dir = rMsg.erase(0, 12);
	file1.setDirection(dir);
	//mView.displayMsg(26, 4, dir);
	//Find player data
	mView.clearNortifiBox();
	string tmp_name;
	mView.displayMsg(26, 6, "Nhap ten Player: ");
	cin >> tmp_name;
	string value = file1.findInFile(tmp_name);
	mView.clearNortifiBox();
	mView.gotoXY(26, 6);
	if (value != "CANNOT FIND DATA!") {
		cout << tmp_name << " " << value;
	}
	else cout << value;
}

//=====CHECK RESULT
//case1: 5 diem cung hang ngang (-) cung chat voi nhau VD: XXXXX

//case2: 5 diem cung hang doc (|) cung chat voi nhau VD: XXXXX

//case3: 5 diem hang cheo len tren (/) chat voi nhau VD: XXXXX

//case4: 5 diem cung hang cheo xuong (\) cung chat voi nhau VD: XXXXX

bool Controller::caseWin1(int row, int col){
	bool case1 =	(mModel.getNodeType(row, col) == mModel.getNodeType(row, col + 1)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row, col + 2)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row, col + 3)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row, col + 4));
	return case1;
}
bool Controller::caseWin2(int row, int col){
	bool case2 =	(mModel.getNodeType(row, col) == mModel.getNodeType(row + 1, col)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row + 2, col)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row + 3, col)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row + 4, col));
	return case2;
}
bool Controller::caseWin3(int row, int col){
	bool case3 =	(mModel.getNodeType(row, col) == mModel.getNodeType(row - 1, col + 1)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row - 2, col + 2)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row - 3, col + 3)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row - 4, col + 4));
	return case3;
}
bool Controller::caseWin4(int row, int col){
	bool case4 =	(mModel.getNodeType(row, col) == mModel.getNodeType(row + 1, col + 1)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row + 2, col + 2)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row + 3, col + 3)) &&
					(mModel.getNodeType(row, col) == mModel.getNodeType(row + 4, col + 4));
	return case4;
}

result_t Controller::checkResult() {
	int count = 0;
	bool end = false;
	for (int row = 0; row < mView.getTableSize(); row++) {
		for (int col = 0; col < mView.getTableSize(); col++) {
			if (mModel.getNodeType(row, col) != other) {	//size of vector = size table
				if (col < mView.getTableSize() - RULE + 1) {		//dieu kien can va du de xay ra case1, dk can de xay ra case 3, 4
					if (row < mView.getTableSize() - RULE +1) {	//dieu kien du de xay ra case 4
						if (caseWin4(row, col)) {
							//mView.displayMsg(0, 0, "End game case4!");
							/*return true;*/
							end = true;
						}
					}
					if (row > RULE - 1 - 1) {			//dieu kien du de xay ra case 3
						if (caseWin3(row, col)) {
							//mView.displayMsg(0, 0, "End game case3!");
							/*return true;*/
							end = true;
						}
					}
					if (caseWin1(row, col)) {			//check case 1
						//mView.displayMsg(0, 0, "End game case1!");
						/*return true;*/
						end = true;
					}
				}
				if (row < mView.getTableSize() - RULE + 1) {		//dieu kien can va du de xay ra case 2
					if (caseWin2(row, col)) {
						//mView.displayMsg(0, 0, "End game case2!");
						/*return true;*/
						end = true;
					}
				}
			}
			else if (mModel.getNodeType(row, col) == other) {
				count++;
			}
		}
	}
	if (end) {
		if (mModel.getGameTurn() % 2 == 1) {
			return X_win;
		}
		else if (mModel.getGameTurn() % 2 == 0) {
			return O_win;
		}
	}
	if (count == 0) {		//tat ca cac o trong table deu duoc tich
		return draw;		//draw
	}
	return is_playing;
}

void Controller::runGame() {
	vCoord vNode;// = mView.mouse();
	vNode.p.X = 0;
	vNode.p.Y = 0;
	mView.mouse3(vNode);
	mCoord tmp_mNode;
	vCoord tmp_vNode;
	if (VtoMCoordConvert(vNode, tmp_mNode)) {
		//put data to Game
		//typeXO_t side = other;
		if (mModel.getGameTurn() % 2 == 1) {
			if (mModel.pushXtoGame(tmp_mNode)) {
				if (MtoVCoordConvert(tmp_mNode, tmp_vNode)) {
					mView.printX(tmp_vNode);
					//side = side_X;
				}
			}
		}
		else if (mModel.getGameTurn() % 2 == 0) {
			if (mModel.pushOtoGame(tmp_mNode)) {
				if (MtoVCoordConvert(tmp_mNode, tmp_vNode)) {
					mView.printO(tmp_vNode);
					//side = side_O;
				}
			}
		}
		//check Win
		if (mModel.getGameTurn() > 8) {
			result_t tmp = Controller::checkResult();
			tmp_result = tmp;
			switch (tmp){
			case X_win: {
				mView.displayMsg(30, 4, "X Win!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				game_run = false;
				break;
			}
			case O_win: {
				mView.displayMsg(30, 4, "O Win!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				game_run = false;
				break;
			}
			case draw: {
				mView.displayMsg(30, 4, "Draw!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				game_run = false;
				break;
			}
			default:
				break;
			}
		}
		//update Game Data
		mView.displayTurn(mModel.getGameTurn());
		if (game_run) {
			mModel.incGameTurn();
		}
	}
	//mView.displayMsg(1, 15, "haha");
}
// ONLINE GAME
void Controller::creatHost() {
	//init temp variable
	game_run = true;
	tmp_p1.clear();
	tmp_p2.clear();
	tmp_gameid.clear();
	//Init game data
	mView.deleteTable();	//xoa du lieu cu neu co
	mModel.resetGameTable();
	//Ket noi den server
	if (!client.client_init()) {
		mView.displayMsg(26, 5, "Cannot connect to Game server!");
		return;
	}
	string conn;
	client.client_receive(conn);
	mView.gotoXY(26, 5);
	cout << conn;
	//gui yeu cau tao game den server
	client.client_send("Host P1");
	string rMsg;
	string rep;
	int len = 0;
	len = client.client_receive(rMsg);
	if (len > 0) {
		char msg[32];
		sscanf_s(rMsg.c_str(), "SERVER: %s",msg, 32);
		rep = string(msg);
	}

	if (rep == "Matching") {
		//=================
		mView.displayName();
		mView.changeTextColor(ColorCode_Cyan);
		//string p1, p2, gameid;
		mView.gotoXY(15, 3);
		cout << "_";
		mView.gotoXY(15, 3);
		cin >> tmp_p1;
		//mView.changeTextColor(ColorCode_Grey);
		mView.gotoXY(10, 5);
		cout << "_";
		mView.gotoXY(10, 5);
		cin >> tmp_gameid;
		string temp = "Player1 " + tmp_p1 + " " + tmp_gameid;
		client.client_send(temp);
		mView.displayMsg(26, 5, "Waiting for other player...");
		//doi nguoi choi 2 tra loi
		len = 0;
		//do {
		//	rMsg.clear();
		//	rep.clear();
		//	tmp_p2.clear();
		//	len = client.client_receive(rMsg);
		//	if (len > 0) {
		//		char msg[32];
		//		sscanf_s(rMsg.c_str(), "SERVER: %s", msg, 32);
		//		rep = string(msg);
		//	}
		//	if (rep == "Error") {
		//		mView.displayMsg(25, 6, "ERROR. BREAK!");
		//		return;
		//	}
		//} while (rep != "Player2");
		rMsg.clear();
		if (!client.client_recv(rMsg, "Player2")) {
			mView.displayMsg(25, 6, "ERROR. BREAK!");
			return;
		}
		char name2[32];
		sscanf_s(rMsg.c_str(), "SERVER: Player2 %s", name2, 32);
		tmp_p2 = string(name2);
		mView.gotoXY(15, 4);
		cout << tmp_p2;
		//ve ban co
		//CREATE TABLE
		mView.clearNortifiBox();
		int tmp_size;
		mView.gotoXY(25, 6);
		cout << "Nhap kich thuoc cua ban co: ";
		cin >> tmp_size;
		mView.clearNortifiBox();
		mView.changeTextColor(default_ColorCode);
		//mModel.createGameTable(mView.getTableSize());
		//gui du lieu ban co cho nguoi choi con lai
		string str = "Size " + to_string(tmp_size);
		if (client.client_send(str)) {
			viewDisplayTable(tmp_size);
			mModel.createGameTable(tmp_size);
		}
	}
	else {
		mView.displayMsg(26, 5, "Cannot create online game. Try again!");
		client.client_cleanup();
		return;
	}
}

void Controller::runHost() {
	if (game_run == true) {
		mCoord tmp_mNode;
		vCoord tmp_vNode;
		//if turn X		-> read mouse event
		if (mModel.getGameTurn() % 2 == 1) {
			mView.displayMsg(26, 5, "Your turn!");
			vCoord tmp = mView.mouse();
			//tmp.p.X = NULL;
			//tmp.p.Y = NULL;
			//if (mView.mouse3(tmp)) {
				if (VtoMCoordConvert(tmp, tmp_mNode)) {
					if (mModel.pushXtoGame(tmp_mNode)) {
						if (MtoVCoordConvert(tmp_mNode, tmp_vNode)) {
							mView.printX(tmp_vNode);
							//send message to other player
							string str = "Move1 " + to_string(mModel.getGameTurn()) + " " + to_string(tmp_mNode.p.X) + " " + to_string(tmp_mNode.p.Y);
							if (client.client_send(str)) {
								//do something or dont do anything
							}
						}
					}
				}
				else if (!VtoMCoordConvert(tmp, tmp_mNode)) {
					return;
				}
			//}
			//else if (!mView.mouse3(tmp)) {
			//	return;
			//}
		}
		//if turn O		-> read message from other player
		else if (mModel.getGameTurn() % 2 == 0) {
			mView.displayMsg(26, 4, "Opponent turn!");
			string rMsg;
			int len = 0;
			if (!client.client_recv(rMsg, "Move2")) {
				mView.displayMsg(25, 6, "ERROR. BREAK!");
				return;
			}
			//len = client.client_receive(rMsg);
			//if (len > 0) {
			int turn, pX, pY;
			sscanf_s(rMsg.c_str(), "SERVER: Move2 %d %d %d", &turn, &pX, &pY);
			mCoord tmpNode;
			tmpNode.p.X = pX;
			tmpNode.p.Y = pY;
			if (mModel.pushOtoGame(tmpNode)) {
				if (MtoVCoordConvert(tmpNode, tmp_vNode)) {
					mView.printO(tmp_vNode);
					if (turn != mModel.getGameTurn()) {
						mModel.setGameTurn(turn);
					}
				}
			}
			//}
			//else {
			//	return;
			//}
		}
		mView.clearNortifiBox();
		//check Win
		if (mModel.getGameTurn() > 8) {
			result_t tmp = Controller::checkResult();
			tmp_result = tmp;
			switch (tmp) {
			case X_win: {
				mView.displayMsg(30, 4, "X Win!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				client.client_send("Result X_win");
				game_run = false;
				break;
			}
			case O_win: {
				mView.displayMsg(30, 4, "O Win!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				client.client_send("Result O_win");
				game_run = false;
				break;
			}
			case draw: {
				mView.displayMsg(30, 4, "Draw!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				client.client_send("Result Draw");
				game_run = false;
				break;
			}
			default:
				break;
			}
		}
		//update Game Data
		mView.displayTurn(mModel.getGameTurn());
		if (game_run) {
			mModel.incGameTurn();
		}
	}
}

void Controller::joinGame() {
	//init temp variable
	game_run = true;
	tmp_p1.clear();
	tmp_p2.clear();
	tmp_gameid.clear();
	//Init game data
	mView.deleteTable();	//xoa du lieu cu neu co
	//Ket noi den server
	if (!client.client_init()) {
		mView.displayMsg(26, 5, "Cannot connect to Game server!");
		return;
	}
	string conn;
	client.client_receive(conn);
	mView.gotoXY(26, 5);
	cout << conn;
	//=================
	//gui yeu cau tao game den server
	client.client_send("Join P2");
	string rMsg;
	string rep;
	int len = 0;
	len = client.client_receive(rMsg);
	if (len > 0) {
		char msg[32];
		sscanf_s(rMsg.c_str(), "SERVER: %s", msg, 32);
		rep = string(msg);
	}
	if (rep == "Accept") {
		mView.displayName();
		mView.changeTextColor(ColorCode_Grey);
		rMsg.clear();
		if (!client.client_recv(rMsg, "Player1")) {
			mView.displayMsg(25, 6, "ERROR. BREAK!");
			return;
		}
		char name1[32];
		char gameid[32];
		sscanf_s(rMsg.c_str(), "SERVER: Player1 %s %s", name1, 32, gameid, 32);
		tmp_p1 = string(name1);
		tmp_gameid = string(gameid);
		mView.gotoXY(15, 3);
		cout << tmp_p1;
		mView.gotoXY(10, 5);
		cout << tmp_gameid;
		//=================
		mView.changeTextColor(ColorCode_Cyan);
		mView.gotoXY(10, 5);
		cout << "_";
		mView.gotoXY(10, 5);
		cin >> tmp_gameid;
		string id = "Gameid " + tmp_gameid;
		client.client_send(id);
		mView.gotoXY(15, 4);
		cout << "_";
		mView.gotoXY(15, 4);
		cin >> tmp_p2;
		mView.gotoXY(15, 4);
		cout << tmp_p2;
		string p2 = "Player2 " + tmp_p2 + " " + tmp_gameid;
		client.client_send(p2);
		//ve ban co
		mView.displayMsg(26, 5, "Waiting for host...");
		//==Receive message
		rMsg.clear();
		if (!client.client_recv(rMsg, "Size")) {
			mView.displayMsg(25, 6, "ERROR. BREAK!");
			return;
		}
		int tmp_size;
		sscanf_s(rMsg.c_str(), "SERVER: Size %d", &tmp_size);
		viewDisplayTable(tmp_size);
		mModel.createGameTable(tmp_size);
	}
	else {
		mView.displayMsg(26, 5, "Cannot find online game. Try again!");
		client.client_cleanup();
		return;
	}
}

void Controller::runGameJoined() {
	if (game_run) {
		mCoord tmp_mNode;
		vCoord tmp_vNode;
		//if turn X		-> read message from other player
		if (mModel.getGameTurn() % 2 == 1) {
			mView.displayMsg(26, 4, "Opponent turn!");
			string rMsg;
			//int len = 0;
			//len = client.client_receive(rMsg);
			//if (len > 0) {
			rMsg.clear();
			if (!client.client_recv(rMsg, "Move1")) {
				mView.displayMsg(25, 6, "ERROR. BREAK!");
				return;
			}
			int turn, pX, pY;
			sscanf_s(rMsg.c_str(), "SERVER: Move1 %d %d %d", &turn, &pX, &pY);
			mCoord tmpNode;
			tmpNode.p.X = pX;
			tmpNode.p.Y = pY;
			if (mModel.pushXtoGame(tmpNode)) {
				if (MtoVCoordConvert(tmpNode, tmp_vNode)) {
					mView.printX(tmp_vNode);
					if (turn != mModel.getGameTurn()) {
						mModel.setGameTurn(turn);
					}
				}
			}
			//}
		}
		//if turn O		-> read mouse event
		else if (mModel.getGameTurn() % 2 == 0) {
			mView.displayMsg(26, 4, "Your turn!");
			vCoord tmp = mView.mouse(); //-> vcoord -> rungame(vcoord)
			//tmp.p.X = NULL;
			//tmp.p.Y = NULL;
			//if (mView.mouse3(tmp)) {
			if (VtoMCoordConvert(tmp, tmp_mNode)) {
				if (mModel.pushOtoGame(tmp_mNode)) {
					if (MtoVCoordConvert(tmp_mNode, tmp_vNode)) {
						mView.printO(tmp_vNode);
						//send message to other player
						string str = "Move2 " + to_string(mModel.getGameTurn()) + " " + to_string(tmp_mNode.p.X)
							+ " " + to_string(tmp_mNode.p.Y);
						if (client.client_send(str)) {
							//do something or dont do anything
						}
					}
				}
			}
			else if (!VtoMCoordConvert(tmp, tmp_mNode)) {
				return;
			}
			//}
			//else if (!mView.mouse3(tmp)) {
			//	return;
			//}
		}
		mView.clearNortifiBox();
		//check Win
		if (mModel.getGameTurn() > 8) {
			result_t tmp = Controller::checkResult();
			tmp_result = tmp;
			switch (tmp) {
			case X_win: {
				mView.displayMsg(30, 4, "X Win!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				game_run = false;
				break;
			}
			case O_win: {
				mView.displayMsg(30, 4, "O Win!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				game_run = false;
				break;
			}
			case draw: {
				mView.displayMsg(30, 4, "Draw!");
				mView.displayMsg(26, 6, "< CONTINUE >");
				game_run = false;
				break;
			}
			default:
				break;
			}
		}
		//update Game Data
		mView.displayTurn(mModel.getGameTurn());
		if (game_run) {
			mModel.incGameTurn();
		}
	}
}

//===============================
void Controller::runProgram() {
	viewDisplayMenu();
	game_state state = st_waiting;
	gameMode = 0;
	while (true) {
		vCoord tmp;// = mView.mouse(); //-> vcoord -> rungame(vcoord)
		tmp.p.X = NULL;
		tmp.p.Y = NULL;
		if (mView.mouse2(tmp)) {
			game_cmd cmd = readButton(tmp);
			switch (cmd) {
			case cmd_exit: {
				return;
			}
			case cmd_newgame: {
				newGame();
				state = st_playing;
				gameMode = 1;
				break;
			}
			case cmd_continue: {
				if (game_run == false) {
					continueGame();
					gameMode = 1;
				}
				break;
			}
			case cmd_savegame: {
				if (game_run == false) {
					saveGame();
					gameMode = 0;
				}
				break;
			}
			case cmd_loadgame: {
				if (game_run == false) {
					loadGame();
					gameMode = 0;
				}
				break;
			}
			case cmd_quitgame: {
				quitGame();
				state = st_waiting;
				client.client_cleanup();
				gameMode = 0;
				break;
			}
			case cmd_showdata: {
				if (game_run == false) {
					showDatabase();
					gameMode = 0;
				}
				break;
			}
			case cmd_findperson: {
				if (game_run == false) {
					findPerson();
					gameMode = 0;
				}
				break;
			}
			case cmd_host: {
				if (game_run == false) {
					creatHost();
					gameMode = 2;
					state = st_playing;
				}
				break;
			}
			case cmd_join: {
				if (game_run == false) {
					joinGame();
					gameMode = 3;
					state = st_playing;
				}
				break;
			}
			default:
				break;
			}
		}
		if ((state == st_playing) && (gameMode == 1)) {
			runGame();
		}
		if ((state == st_playing) && (gameMode == 2)) {
			runHost();
		}
		if ((state == st_playing) && (gameMode == 3)) {
			runGameJoined();
		}
	}
}

