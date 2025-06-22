#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <time.h>
#include <windows.h>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
#define KEY_UP(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 0 : 1)
using namespace std;

// Old angledata to new
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
		default:
			return 180;
			break;
	}
}
int keys;
bool getedmtp, getedbpm;


const char quote = char(34);
const char backslash = char(92);

char lastpressedkey, nextkey;

//get settings
int offset;
double bpm, firstbpm;
bool inputbpm;
int pitch;
bool inputpitch;

//first
queue<double> timedata1;
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
queue<double> timedata3;
double pausebeats;

//holds
bool sethold;
queue<int> holdtile;
queue<int> holdmidspin;

//multiplanet
bool setmultiplanet;
queue<int> multiplanets;
bool threeplanets;
bool threeplanetsinmid;

queue<double> timedata2;

//final tile
queue<double> nums;

//bpm
queue<double> bpms;
bool setbpm;
bool mtp;

//final ms
queue<double> timedata;

bool cbpm;
double totalfinalms;

//input
bool input;
bool inputpause;

queue<double> timedata4;

bool inputangleData;
bool oldversion;
bool setting;
double delta;

bool showbpm, cuslev;

int readykey, pressingkey, startkey;
long double offsetnum;


//7bg level
int bigworld, smallworld;


double mod(double n, double m) {
	if (m == 0) return 0;
	double res = fmod(n, m);
	return res < 0 ? res + m : res;
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
	printf("Ver 1.6.1 (2025-06-22 15:22)\nShow specific information: ");
	cin >> showbpm;
	printf("Is custom level: ");
	cin >> cuslev;
	
	string world;
	if (!cuslev) {
		printf("Level Library:\n  XI-X\n\nPlease enter the level name:");
		cin >> world;
		if (!cuslev) {
			printf("Pitch: ");
			cin >> pitch;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (world == "XI-X") freopen("XI-X.adofai", "r", stdin);
		else {
			printf("Coming soon.");
			return 0;
		}
	}
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if (cuslev) {
		string file;
		printf("File path: ");
		getline(cin, file);
		file.erase(remove(file.begin(), file.end(), quote), file.end());
		string doublebackslash, filebackslash;
		doublebackslash.push_back(backslash);
		doublebackslash.push_back(backslash);
		filebackslash.push_back(backslash);
	
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
	}
	
	
	string input_data;
    double last_degree = 0;

	//Custom level input
	int floor_angledata = 0;
	while (true) {
		// Input Data
		cin >> input_data;

		// Invaild file
		if (input_data == "\0") {
			printf("File was invaild.");
			return 0;
		}


		double now_degree;
		if (inputangleData) {
			//Get New angleData
			if (!oldversion) {
				movechar(input_data, '[');
				movechar(input_data, ']');
    			char* idx;
    			if (input_data != "999,") {
    				now_degree = strtod(input_data.c_str(), &idx);
    				mids = false;
				} else {
					memangle = last_degree;
    				last_degree = memangle - 180;
    				mids = true;
					timedata1.push(-1);
					holdmidspin.push(floor_angledata);
					floor_angledata++;
    				continue;
				}
				if (mod(180 + last_degree - now_degree, 360) != 0) timedata1.push(mod(180 + last_degree - now_degree, 360));
				else timedata1.push(360);
				last_degree = now_degree;	
			} else {
				if (input_data != quoteandcolon("settings")) {
					input_data.erase(remove(input_data.begin(), input_data.end(), quote), input_data.end());
					queue<char> oldangles;
					for (unsigned int i = 0; i < input_data.length(); i++) {
						if (input_data[i] != '!'){
    						now_degree = oldtonew(input_data[i]);
    						mids = false;
						} else {
							memangle = last_degree;
    						last_degree = mod(memangle + 180, 360);
    						mids = true;
							timedata1.push(-1);
							holdmidspin.push(floor_angledata);
    						continue;
						}
						if (mod(180 + last_degree - now_degree, 360)) timedata1.push(mod(180 + last_degree - now_degree, 360));
						else timedata1.push(360);
						last_degree = now_degree;
					}
				}
			}
			floor_angledata++;
		}
		//Get settings
		if (setting) {
			if (inputbpm) {

    			char* idx;
    			firstbpm = strtod(input_data.c_str(), &idx);
				bpm = firstbpm;
				inputbpm = false;
			}
			if (input_data == quoteandcolon("bpm")) inputbpm = true;
			if (inputpitch) {
    			
    			char* idx;
    			if (cuslev) pitch = strtod(input_data.c_str(), &idx);
				inputpitch = false;
			}
			if (input_data == quoteandcolon("pitch")) inputpitch = true;
		}

		//Get actions
		if (action) {
			if (input_data == "]" || input_data == quoteandcolon("decorations")) break;
			if (input_data == "}") break;
			//Get floor
			if (flooring){
    			
    			char* idx;
    			nowfloor = strtod(input_data.c_str(), &idx);
				flooring = false;
			}
			if (input_data == quoteandcolon("floor")) flooring = true;

			//Get Eventtype
			if (Eventtyping) {
				if (input_data == quotes("Twirl")) {
					ts.push(nowfloor);
				} else if (input_data == quoteandcomma("SetSpeed")) {
					setbpm = true;
					getedmtp = false;
					getedbpm = false;
				} else if (input_data == quoteandcomma("Pause")) {
					setpause = true;
				} else if (input_data == quoteandcomma("Hold")) {
					sethold = true;
				} else if (input_data == quoteandcomma("MultiPlanet")) {
					setmultiplanet = true;
				}
				Eventtyping = false; 
			}
			if (input_data == quoteandcolon("eventType")) Eventtyping = true;

			//Get BPM
			if (setbpm) {
				if (input) {
    				char* idx;
    				if (mtp) {
						bpm *= strtod(input_data.c_str(), &idx);
					} else {
						bpm = strtod(input_data.c_str(), &idx);
					}
					bpms.push(int(nowfloor));
					bpms.push(bpm);
					input = false;
					setbpm = false;
				}
				
				if (!getedmtp) {
					mtp = (input_data == quoteandcomma("Multiplier"));
					getedmtp = mtp;
				}
				if (!getedbpm) {
					cout << input_data << endl;
					input = (mtp ? (input_data == quoteandcolon("bpmMultiplier")) : (input_data == quoteandcolon("beatsPerMinute")));
					getedbpm = input;
				}
			}

			//Get Multiplanet
			if (setmultiplanet) {
				if (input) {
					multiplanets.push(nowfloor);
					movechar(input_data, '}');
					input_data.erase(remove(input_data.begin(), input_data.end(), quote), input_data.end());
					if (input_data == "ThreePlanets}," || input_data == "ThreePlanets}") {
						multiplanets.push(3);
					} else {
						multiplanets.push(2);
					}
					input = false;
					setmultiplanet = false;
				}
				if (input_data == quoteandcolon("planets")) {
					input = true;
				}
			}

			//Get Pause
			if (setpause) {
				if (inputpause) {
    				
    				char* idx;
					double nowpause = strtod(input_data.c_str(), &idx);
					pauses.push(nowfloor);
					pauses.push(nowpause);
					inputpause = false;
					setpause = false;
				}
				if (input_data == quoteandcolon("duration")) {
					inputpause = true;
				}
			}
			
			//Get Hold
			if (sethold) {
				if (inputpause) {
    				
    				char* idx;
					double nowpause = strtod(input_data.c_str(), &idx);
					pauses.push(nowfloor);
					holdtile.push(nowfloor);
					pauses.push(nowpause * 2);
					inputpause = false;
					sethold = false;
				}
				if (input_data == quoteandcolon("duration")) {
					inputpause = true;
				}
			}
		}

		//Stop point
		if (input_data == quoteandcolon("decorations")) break;

		//Start to input angle data (new version)
		if (input_data == quoteandcolon("angleData")) {
			inputangleData = true;
    		input_data.erase(remove(input_data.begin(), input_data.end(), '['), input_data.end());
    		input_data.erase(remove(input_data.begin(), input_data.end(), ']'), input_data.end());
    		
    		char* idx;
    		last_degree = strtod(input_data.c_str(), &idx);
			printf("Getting new angledata\n");
		}

		//Start to input angle data (old version)
		if (input_data == quoteandcolon("pathData")) {
			inputangleData = true;
			oldversion = true;
			printf("Getting old angledata\n");
		}

		//Start to input settings
		if (input_data == quoteandcolon("settings")) {
			inputangleData = false;
			setting = true;
			printf("Getting settings\n");
		}

		//Start to input actions
		if (input_data == quoteandcolon("actions")) {
			setting = false;
			action = true;
			printf("Getting actions\n");
		}
	}
	
	printf("Processing data\n");
	//Twirls
	nowfloor = 0;
	while (timedata1.size() > 1) {
		nowfloor++;
		if (timedata1.front() != -1) {
			if (ting) {
				timedata2.push(360 - mod(timedata1.front(), 360));
			} else {
				timedata2.push(timedata1.front());
			}
		} else {
			timedata2.push(-1);
		}
		
		if (nowfloor == ts.front()) {
			ting = !ting;
			ts.pop();
		}
		timedata1.pop();
	} 

	//Pauses
	nowfloor = 0;
	while (!timedata2.empty()) {
		double curps = 0;
		if (!pauses.empty() && nowfloor == pauses.front()) {
        	pauses.pop();
        	curps = pauses.front();
        	pauses.pop();
    	}
		double current_time = timedata2.front();
    	timedata3.push(current_time != -1 ? current_time + curps * 180.0 : -1);
    	timedata2.pop();
    	nowfloor++;
	}

	//Multiplanets
	nowfloor = 0;
	bool midspinafterthreeball = false;
	while (timedata3.size()) {
		//Change
		if (nowfloor == multiplanets.front()) {
			multiplanets.pop();
			threeplanets = (multiplanets.front() == 3);
			multiplanets.pop();
		}

		double curdeg = timedata3.front();
		timedata3.pop();

		//if not midspin
		if (threeplanets && curdeg != -1 && !midspinafterthreeball) {
			timedata4.push(curdeg > 60 ? curdeg - 60 : curdeg + 300);
		} else {
			timedata4.push(curdeg);
			midspinafterthreeball = (timedata3.front() == -1);
		}
		nowfloor++;
	}

	//Change BPM
	bpm = firstbpm;
	nowfloor = 0;
	totalfinalms = 0;
	bool isgetting = false;
	//Get final ms
	while (timedata4.size()) {
		if (nowfloor == bpms.front()) {
			bpms.pop();
			bpm = bpms.front();
			bpms.pop();
		}
		if (isgetting) {
			if (timedata4.front() != -1) {
				totalfinalms += timedata4.front() * 1000 / 3 / bpm;
				timedata.push(totalfinalms);
			}
		}
		timedata4.pop();
		nowfloor++;
		isgetting = true;
	}

	//Hold
	nowfloor = 0;
	int midspins = 0;
	queue<int> lholdtile;
	while (holdtile.size()) {
		if (holdmidspin.front() == nowfloor) {
			midspins++;
			holdmidspin.pop();
		}
		if (holdtile.front() == nowfloor) {
			lholdtile.push(nowfloor - midspins);
			holdtile.pop();
		}
		nowfloor++;
	}
	holdtile = lholdtile;
	
	fclose(stdin); 
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	printf("OK!\nPress [Enter] to ready.\n");
	
	//Get ready
	bool getready = false;
	bool press = false;
	double lastms = 0;
	nowfloor = 0;
	while (true) if (KEY_UP(13)) break;
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
	clock_t start = clock();
	//Press key
	keybd_event('K', 0, 0, 0);

	if (showbpm) {
		while (timedata.size()) {
			clock_t end = clock();
			if (KEY_DOWN(VK_ESCAPE)){
				keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
				keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
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
			if (double(end - start) * pitch / 100 + delta >= timedata.front()) {
				nowfloor++;
				if (nowfloor % 2) {
					if (holdtile.front() != nowfloor) keybd_event('F', 0, 0, 0);
					else holdtile.pop();
					timedata.pop();
					keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
				} else {
					if (holdtile.front() != nowfloor) keybd_event('K', 0, 0, 0);
					else holdtile.pop();
					timedata.pop();
					keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
				}
				printf("%d:\nBPM: %f\nDelta: %fms\nNext hold: %d\n", nowfloor, 60000 / (timedata.front() - lastms), double(end - start) * pitch / 100 + delta - timedata.front(), holdtile.front());
				lastms = timedata.front();
			}
		}
	} else {
		while (timedata.size()) {
			clock_t end = clock();
			if (KEY_DOWN(VK_ESCAPE)){
				keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
				keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
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
			if (double(end - start) * pitch / 100 + delta >= timedata.front()) {
				nowfloor++;
				if (nowfloor % 2) {
					if (holdtile.front() != nowfloor) keybd_event('F', 0, 0, 0);
					else holdtile.pop();
					timedata.pop();
					keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
				} else {
					if (holdtile.front() != nowfloor) keybd_event('K', 0, 0, 0);
					else holdtile.pop();
					timedata.pop();
					keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
				}
			}
		}
	}
	
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
	return 0;
}
