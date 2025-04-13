#include <queue>
#include <iostream>
#include <conio.h>
#include <cerrno>
#include <cstdlib>
#include <windows.h>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <time.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
#define KEY_UP(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 0 : 1)
using namespace std;
double oldtonew (char now) {
	switch (now) {
		case 'R':
			return 0;
			break;
		case 'p':
			return 15;
			break;
		case 'J':
			return 30;
			break;
		case 'E':
			return 45;
			break;
		case 'T':
			return 60;
			break;
		case 'o':
			return 75;
			break;
		case 'U':
			return 90;
			break;
		case 'q':
			return 105;
			break;
		case 'G':
			return 120;
			break;
		case 'Q':
			return 135;
			break;
		case 'H':
			return 150;
			break;
		case 'W':
			return 165;
			break;
		case 'L':
			return 180;
			break;
		case 'x':
			return 195;
			break;
		case 'N':
			return 210;
			break;
		case 'Z':
			return 225;
			break;
		case 'F':
			return 240;
			break;
		case 'V':
			return 255;
			break;
		case 'D':
			return 270;
			break;
		case 'Y':
			return 285;
			break;
		case 'B':
			return 300;
			break;
		case 'C':
			return 315;
			break;
		case 'M':
			return 330;
			break;
		case 'A':
			return 345;
			break;
		case '5':
			return 108;
			break;
		case '7':
			return 900 / 7;
			break;
		case '!':
			return 999;
			break;
	}
}
int keys;

//get settings
int offset;
double bpm, firstbpm;
bool inputoffset;
bool inputbpm;
int pitch;
bool inputpitch;

//first
queue<double> mss1;
bool mids;
double memangle;

//actions
bool action;
int nowfloor;
bool flooring;
bool Eventtyping;

//twirl
queue<bool> bts;
queue<int> ts;
bool ting;

//pauses
queue<double> pauses;
bool setpause;
queue<double> mss3;
double pausebeats;

//holds
bool sethold;

//multiplanet
bool setmultiplanet;
queue<int> multiplanets;
bool threeplanets;
bool threeplanetsinmid;

queue<double> mss2;

//final tile
queue<double> nums;

//bpm
queue<double> bpms;
bool setbpm;
bool mtp;

//final ms
queue<double> mss;

const char quote = char(34);
const char backslash = char(92);
bool cbpm;
double totalfinalms;

//input
bool input;
bool inputpause;

queue<double> mss4;

bool inputangleData;
bool oldversion;
bool setting;
double delta;

int readykey, pressingkey, startkey;
long double offsetnum;

long double mod(long double n, long double m) {
	while (n < 0 || n >= m) if (n < 0) n += m; else n -= m;
	return n;
}
string quoteandcolon(string s) {
	s.push_back(quote);
	s.push_back(':');
	return quote + s;
}
string quotes(string s) { 
	s.push_back(quote);
	return quote + s;
}
string quoteandcomma(string s) {
	s.push_back(quote);
	s.push_back(',');
	return quote + s;
}
void movechar(string str, char c) {
	str.erase(remove(str.begin(), str.end(), c), str.end());
}
int main() {
	printf("Ver 1.3.0\n");
	string file;
	printf("File path: ");
	getline(cin, file);
	file.erase(remove(file.begin(), file.end(), quote), file.end());
	string doublebackslash, filebackslash;
	doublebackslash.push_back(backslash);
	doublebackslash.push_back(backslash);
	filebackslash.push_back(backslash);
	const char* cdoublebackslash = doublebackslash.c_str();

	//To c++ path form
	size_t start_pos = 0;
    while (true) {
        size_t pos = file.find(filebackslash, start_pos);
        if (pos == string::npos) break;
        file.replace(pos, filebackslash.length(), doublebackslash);
        start_pos = pos + doublebackslash.length();
    }
    movechar(file, quote);

	//Open file
	const char* cfile = file.c_str();
	freopen(cfile, "r", stdin);
	
	string inputline;
    double lastangle = 0;

	//Input
	while (1) {
		cin >> inputline;
		if (inputline == "\0") {
			cout << file << " is invaild.";
			return 0;
		}
		double nowangle;

		//Get angle data (new version)
		if (inputangleData) {
			if (!oldversion) {
				movechar(inputline, '[');
				movechar(inputline, ']');
				movechar(inputline, ',');
    			char* idx;
    			if (strtod(inputline.c_str(), &idx) != 999){
    				nowangle = strtod(inputline.c_str(), &idx);
    				mids = false;
				} else {
					memangle = lastangle;
    				lastangle = memangle - 180;
    				mids = true;
					mss1.push(-1);
    				continue;
				}
				if (mod(180 + lastangle - nowangle, 360) != 0) mss1.push(mod(180 + lastangle - nowangle, 360));
				else mss1.push(360);
				lastangle = nowangle;
			}
		}

		//Get angle data (old version)
		if (inputangleData) {
			if (oldversion) {
				if (inputline != quoteandcolon("settings")) {
					inputline.erase(remove(inputline.begin(), inputline.end(), quote), inputline.end());
    				movechar(inputline, ',');
					queue<char> oldangles;
					for (int i = 0; i < inputline.length(); i++) {
						if (oldtonew(inputline[i]) != 999){
    						nowangle = oldtonew(inputline[i]);
    						mids = false;
						} else {
							memangle = lastangle;
    						lastangle = mod(memangle + 180, 360);
    						mids = true;
							mss1.push(-1);
    						continue;
						}
						if (mod(180 + lastangle - nowangle, 360)) mss1.push(mod(180 + lastangle - nowangle, 360));
						else mss1.push(360);
						lastangle = nowangle;
					}
				}
			}
			
		}
		//Get settings
		if (setting) {
			if (inputoffset) {
    			movechar(inputline, ',');
    			char* idx;
    			offset = strtod(inputline.c_str(), &idx);
				inputoffset = false;
			}
			if (inputline == quoteandcolon("offset")) inputoffset = true;
			if (inputbpm) {
    			movechar(inputline, ',');
    			char* idx;
    			firstbpm = strtod(inputline.c_str(), &idx);
				bpm = firstbpm;
				inputbpm = false;
			}
			if (inputline == quoteandcolon("bpm")) inputbpm = true;
			if (inputpitch) {
    			movechar(inputline, ',');
    			char* idx;
    			pitch = strtod(inputline.c_str(), &idx);
				inputpitch = false;
			}
			if (inputline == quoteandcolon("pitch")) inputpitch = true;
		}

		//Get actions
		if (action){
			int oldversiontoquitfile = 0;
			if (inputline == "]" || inputline == quoteandcolon("decorations")) break;
			if (inputline == "}") break;
			//Get floor
			if (flooring){
    			movechar(inputline, ',');
    			char* idx;
    			nowfloor = strtod(inputline.c_str(), &idx);
				flooring = false;
			}
			if (inputline == quoteandcolon("floor")) flooring = true;

			//Get Eventtype
			if (Eventtyping){
				if (inputline == quotes("Twirl")) {
					ts.push(nowfloor);
				} else if (inputline == quoteandcomma("SetSpeed")) {
					setbpm = true;
				} else if (inputline == quoteandcomma("Pause")) {
					setpause = true;
				} else if (inputline == quoteandcomma("Hold")) {
					sethold = true;
				} else if (inputline == quoteandcomma("MultiPlanet")) {
					setmultiplanet = true;
				}
				Eventtyping = false; 
			}
			if (inputline == quoteandcolon("eventType")) Eventtyping = true;

			//Get BPM
			if (setbpm) {
				if (input) {
    				movechar(inputline, ',');
    				char* idx;
    				if (mtp) {
						bpm *= strtod(inputline.c_str(), &idx);
					} else {
						bpm = strtod(inputline.c_str(), &idx);
					}
					bpms.push(int(nowfloor));
					bpms.push(bpm);
					input = false;
					setbpm = false;
				}
				if (inputline == quoteandcomma("Multiplier")) {
					mtp = true;
				} else if (inputline == quoteandcomma("Bpm")) {
					mtp = false;
				}
				if (mtp) {
					if (inputline == quoteandcolon("bpmMultiplier")) {
						input = true;
					}
				} else {
					if (inputline == quoteandcolon("beatsPerMinute")) {
						input = true;
					}
				}
			}

			//Get Multiplanet
			if (setmultiplanet) {
				if (input) {
					multiplanets.push(nowfloor);
					movechar(inputline, '}');
					movechar(inputline, ',');
					inputline.erase(remove(inputline.begin(), inputline.end(), quote), inputline.end());
					if (inputline == "ThreePlanets") {
						multiplanets.push(3);
					} else {
						multiplanets.push(2);
					}
					input = false;
					setmultiplanet = false;
				}
				if (inputline == quoteandcolon("planets")) {
					input = true;
				}
			}

			//Get Pause
			if (setpause) {
				if (inputpause) {
    				movechar(inputline, ',');
    				char* idx;
					double nowpause = strtod(inputline.c_str(), &idx);
					pauses.push(nowfloor);
					pauses.push(nowpause);
					inputpause = false;
					setpause = false;
				}
				if (inputline == quoteandcolon("duration")) {
					inputpause = true;
				}
			}
			
			//Get Hold
			if (sethold) {
				if (inputpause) {
    				movechar(inputline, ',');
    				char* idx;
					double nowpause = strtod(inputline.c_str(), &idx);
					pauses.push(nowfloor);
					pauses.push(nowpause * 2);
					inputpause = false;
					sethold = false;
				}
				if (inputline == quoteandcolon("duration")) {
					inputpause = true;
				}
			}
		}

		//Stop point
		if (inputline == quoteandcolon("decorations")) break;

		//Start to input angle data (new version)
		if (inputline == quoteandcolon("angleData")) {
			inputangleData = true;
    		inputline.erase(remove(inputline.begin(), inputline.end(), '['), inputline.end());
    		inputline.erase(remove(inputline.begin(), inputline.end(), ']'), inputline.end());
    		movechar(inputline, ',');
    		char* idx;
    		lastangle = strtod(inputline.c_str(), &idx);
			printf("Getting new angledata\n");
		}

		//Start to input angle data (old version)
		if (inputline == quoteandcolon("pathData")) {
			inputangleData = true;
			oldversion = true;
			printf("Getting old angledata\n");
		}

		//Start to input settings
		if (inputline == quoteandcolon("settings")) {
			inputangleData = false;
			setting = true;
			printf("Getting settings\n");
		}

		//Start to input actions
		if (inputline == quoteandcolon("actions")) {
			setting = false;
			action = true;
			printf("Getting actions\n");
		}
	}

	//Twirls
	nowfloor = 0;
	while (mss1.size()) {
		nowfloor++;
		if (mss1.front() != -1) {
			if (ting) {
				mss2.push(360 - mod(mss1.front(), 360));
			} else {
				mss2.push(mss1.front());
			}
		} else {
			mss2.push(-1);
		}
		
		if (nowfloor == ts.front()) {
			ting = !ting;
			ts.pop();
		}
		mss1.pop();
	} 

	//Pauses
	nowfloor = 0;
	while (mss2.size()) {
		if (nowfloor == pauses.front()) {
			pauses.pop();
			pausebeats = pauses.front();
			pauses.pop();
		} else {
			pausebeats = 0;
		}
		if (mss2.front() != -1) mss3.push(mss2.front() + pausebeats * 180.0);
		else mss3.push(-1);
		mss2.pop();
		nowfloor++;
	}

	//Multiplanets
	nowfloor = 0;
	while (mss3.size()) {
		if (nowfloor == multiplanets.front()) {
			multiplanets.pop();
			if (multiplanets.front() == 3) threeplanets = true;
			else threeplanets = false;
			multiplanets.pop();
		}
		if (mss3.front() != -1) {
			if (threeplanets) {
				if (!threeplanetsinmid) {
					if (mss3.front() > 60) mss4.push(mss3.front() - 60);
					else mss4.push(mss3.front() + 300);
				} else {
					mss4.push(mss3.front());
					if (threeplanetsinmid) threeplanetsinmid = false;
				}
			} else {
				mss4.push(mss3.front());
				if (threeplanetsinmid) threeplanetsinmid = false;
			}
		} else {
			mss4.push(-1);
			threeplanetsinmid = true;
		} 
		mss3.pop();
		nowfloor++;
	}
	
	//Change BPM
	bpm = firstbpm;
	nowfloor = 0;
	totalfinalms = 0;
	bool isgetting = false;
	//Get final ms
	while (mss4.size()) {
		if (nowfloor == bpms.front()) {
			bpms.pop();
			bpm = bpms.front();
			bpms.pop();
		}
		if (isgetting) {
			if (mss4.front() != -1) {
				totalfinalms += mss4.front() / 180 * 60000 / bpm;
				mss.push(totalfinalms);
			}
		}
		mss4.pop();
		nowfloor++;
		isgetting = true;
	}

	cout << "OK!\n";

	//Get ready
	bool getready = false;
	bool press = false;
	while (true) {
		if (KEY_DOWN(13)) {
			if (!press) {
				press = true;
				getready = !getready;
				if (getready) printf("Ready.\n");
				else printf("Cancel.\n");
			}
		} else {
			press = false;
		}
		if (KEY_DOWN(45)) if (getready) break;
	}

	//insert 45
	keybd_event('F', 0, 0, 0);
	clock_t start = clock();
	//Press key
	while (mss.size()) {
		clock_t end = clock();
		if (KEY_DOWN(VK_ESCAPE)){
			return 0;
		}
		if (KEY_DOWN(VK_LEFT)){
			delta -= 0.002;
			printf("Offset %.15f\n", delta); 
		}
		if (KEY_DOWN(VK_RIGHT)){
			delta += 0.002;
			printf("Offset %.15f\n", delta); 
		}
		if (double(end - start) * pitch / 100 + delta >= mss.front()) {
			keybd_event('K', 0, 0, 0);
			mss.pop();
			keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
		}
	}
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	keybd_event('D', 0, KEYEVENTF_KEYUP, 0);
	fclose(stdin); 
	return 0;
}
