#include "file.h"

void file::setDirection(const string& dir) {
    this->Path = dir;
}

string file::getDirection() {
    return this->Path;
}

bool file::writeFile(const string& playerName, const string& str_data) {
    //Bước 1 : Lấy thư mục hiện hành chứa file exe của ứng dụng và xác định tên tập tin ini
 /*   LPSTR Path = NULL;
    Path = (LPSTR)malloc(300);
    if (Path == NULL) {
        return false;
    }

    GetCurrentDirectory(300, (LPTSTR)Path);

    strcat(Path, "\\");
    strcat(Path, INI_FILE);*/
    /*printf("Init Path = %s\n", Path);*/
    //Bước 2: Ghi thông tin vào file ini
    wstring tmp = wstring(section.begin(), section.end());
    LPCWSTR tmp_section = tmp.c_str();
    wstring tmp1 = wstring(playerName.begin(), playerName.end());
    LPCWSTR key = tmp1.c_str();
    wstring tmp2 = wstring(str_data.begin(), str_data.end());
    LPCWSTR str = tmp2.c_str();
    wstring tmp3 = wstring(Path.begin(), Path.end());
    LPCWSTR tmp_path = tmp3.c_str();
    WritePrivateProfileString(tmp_section, key, str, tmp_path);
    //free(Path);
    return true;
}
string file::findInFile(const string& playerName) {
    //Bước 1 : Lấy thư mục hiện hành chứa file exe của ứng dụng và xác định tên tập tin ini
    //LPTSTR Path = NULL;
    //Path = (LPTSTR)malloc(255);
    //if (Path == NULL) {
    //    return false;
    //}
    //GetCurrentDirectoryW(255, Path);
    //strcat_s((char*)Path, 255, "\\");
    //strcat_s((char*)Path, 255, (char*)INI_FILE);
    //Bước 3: Đọc thông tin từ file ini đã ghi
    const char* tmp_section = section.c_str();//section.c_str();
    LPCSTR key = playerName.c_str();
    const char* tmp_path = Path.c_str();// Path.c_str();
    const char* msg = "CANNOT FIND DATA!";

    char* rtValue = (char*)malloc(255);
    int word = 256;
    GetPrivateProfileStringA(tmp_section, key, msg, rtValue, word, tmp_path);
    string tmp(rtValue);
    //Giải phóng bộ nhớ
    free(rtValue);
    //free(Path);
    return tmp;
}


vector<string> file::readFile() {
    //Bước 1 : Lấy thư mục hiện hành chứa file exe của ứng dụng và xác định tên tập tin ini
    /*wstring tmp = wstring(section.begin(), section.end());*/
    const char* tmp_section = section.c_str();//section.c_str();
    /*wstring tmp3 = wstring(Path.begin(), Path.end());*/
    const char* tmp_path = Path.c_str();// Path.c_str();
    //Bước 3: Đọc thông tin từ file ini đã ghi
    char* rtValue = (char*)malloc(255);
    int word = 256;
    GetPrivateProfileSectionA(tmp_section, rtValue, word, tmp_path);
    //cout << strlen(rtValue) << endl;
    //printf("%s\n", rtValue);
    vector<string> output;
    for (int i = 0; i < word; i++) {
        if ((i == 0 && rtValue[i] != '\0') || (i > 0 && rtValue[i] != '\0' && rtValue[i - 1] == '\0')) // chuoi tiep theo
        {
            char* temp = &rtValue[i];
            string str(temp);
            output.push_back(str);
        }
    }
    //cout << output.size() << endl;
    output.pop_back();

    //free(rtValue);
    free(rtValue);
    //free(Path);
    return output;
}

vector<Player> file::loadDataToDB() {
    //Bước 1 : Lấy thư mục hiện hành chứa file exe của ứng dụng và xác định tên tập tin ini
    const char* tmp_section = section.c_str();//section.c_str();
    const char* tmp_path = Path.c_str();// Path.c_str();
    //Bước 3: Đọc thông tin từ file ini đã ghi
    char* rtValue = (char*)malloc(255);
    int word = 256;
    GetPrivateProfileSectionA(tmp_section, rtValue, word, tmp_path);
    
    vector<Player> output;
    vector<string> v_str;
    for (int i = 0; i < word; i++) {
        if ((i == 0 && rtValue[i] != '\0') || (i > 0 && rtValue[i] != '\0' && rtValue[i - 1] == '\0')) // chuoi tiep theo
        {
            char* temp = &rtValue[i];
            string str(temp);
            v_str.push_back(str);
        }
    }
    v_str.pop_back();
    //cout << v_str.size();
    for (int i = 0; i < v_str.size(); i++) {
        char arr[50];
        char tmp_name[50];
        int tmp_win, tmp_lose, tmp_draw;
        strcpy_s(arr, v_str[i].c_str());
        //ket qua doc ve co dang: key=Win: x Lose: x Draw x
        sscanf_s(arr, "%s %d Lose: %d Draw: %d", tmp_name, 50, &tmp_win, &tmp_lose, &tmp_draw);
        //tmp_name = "key=Win:"
        Player tmp_player;
        string name(tmp_name);
        name.erase(name.length() - 5, 6);   //xoa phan "=Win:"
        tmp_player.setName(name);
        tmp_player.setNumberWin(tmp_win);
        tmp_player.setNumberLoss(tmp_lose);
        tmp_player.setNumberDraw(tmp_draw);
        output.push_back(tmp_player);
    }
    //cout << output.size() << endl;

    free(rtValue);
    return output;
}