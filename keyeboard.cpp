#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

//extra classes
class Key {
public:
	Point top_left, top_right, bottom_left, bottom_right, text_mid;
	Point text_bound;
	int h, w;
	int border_length;
	bool display;
	string symbol;
	string button_display;
	Point inner_top_left, inner_top_right, inner_bottom_left, inner_bottom_right;
	
	int current_line;
	int max_lines;
	string lines[30];
	int line_height;
	Point lines_coords[30];
	string lines_display[13];
	//groups for line width
	
	//constructors
	
	//empty constructor, the content of the standard constructor is set in extra
	Key (){
	}
	
	//standard constructor
	Key (Point p, Point q){
		top_left = p;
		bottom_right = q;
		top_right = Point(q.x, p.y);
		bottom_left = Point(p.x, q.y);
		calcHW();
		calcBorders();
		display = true;
		symbol = "";
		button_display = "";
		text_mid = Point((int)((q.x + p.x)/2), (int)((q.y + p.y)/2));
	}
	
	void extra(Point p, Point q) {
		top_left = p;
		bottom_right = q;
		top_right = Point(q.x, p.y);
		bottom_left = Point(p.x, q.y);
		calcHW();
		calcBorders();
		display = true;
		symbol = "";
		button_display = "";
		text_mid = Point((int)((q.x + p.x)/2), (int)((q.y + p.y)/2));
		
		//lines calculations
		current_line = 0;
		max_lines = 13;
		line_height = 30;
		
	} // for when use of empty constructor
	
	void calcLinePoints(){
		int temp_height = inner_top_left.y + line_height;
		int temp_width = inner_top_left.x;
		for (int i = 0; i < max_lines; i++) {
			lines_coords[i] = Point(temp_width, temp_height);
			temp_height = temp_height + line_height;
		}
	}
	
	void write() {
		lines[current_line] = symbol;
	}
	
	void prevLine() {
		current_line--;
		symbol = lines[current_line];
	
	}
	
	void nextLine() {
		lines[current_line] = symbol;
		current_line++;
		symbol = lines[current_line];
	}
	
	void shiftDown() {
		//for (int i = 0; i <)
		
	}
	
	void calcHW(){
		h = bottom_left.y - top_left.y;
		w = top_right.x - top_left.x;
		if (h >= 5 && w >= 5) {
			border_length = 2;
		}
		else {
			border_length= 0;
		}
	}
	
	void calcBorders () {
		inner_top_left.x = top_left.x + 2;
		inner_top_left.y = top_left.y + 2;
		
		inner_top_right.x = top_right.x - 2;
		inner_top_right.y = top_right.y + 2;
		
		inner_bottom_left.x = bottom_left.x + 2;
		inner_bottom_left.y = bottom_left.y - 2;
		
		inner_bottom_right.x = bottom_right.x - 2;
		inner_bottom_right.y = bottom_right.y - 2;
		
		
	}
	
	//return location if square button
	void GetLocation(Point p, Point q){
		p = top_left;
		q = bottom_right;
	}
	
	//standard methods to return coords
	Point GetTopLeft(){
		return top_left;
	}
	int GetTopLeftX(){
		return top_left.x;
	}
	int GetTopLeftY(){
		return top_left.y;
	}
	
	Point GetTopRight(){
		return top_right;
	}
	int GetTopRightX(){
		return top_right.x;
	}
	int GetTopRightY(){
		return top_right.y;
	}
	
	Point GetBottomLeft(){
		return bottom_left;
	}
	int GetBottomLeftX(){
		return bottom_left.x;
	}
	int GetBottomLeftY(){
		return bottom_left.y;
	}
	
	Point GetBottomRight(){
		return bottom_right;
	}
	int GetBottomRightX(){
		return bottom_right.x;
	}
	int GetBottomRightY(){
		return bottom_right.y;
	}
};
class regions {
public:
	Point tl, br;
	int w1, h1, w2, h2;
	String identifier;
	
	regions(){
	}
	regions(Point top_left, Point bottom_right){
		tl = top_left;
		br = bottom_right;
		w1 = (int)top_left.x;
		h1 = (int)top_left.y;
		w2 = (int)bottom_right.x;
		h2 = (int)bottom_right.y;
		identifier = "";
	}
	
	void extra(Point top_left, Point bottom_right){
		tl = top_left;
		br = bottom_right;
		w1 = (int)top_left.x;
		h1 = (int)top_left.y;
		w2 = (int)bottom_right.x;
		h2 = (int)bottom_right.y;
		identifier = "";
	}
};

///METHOD DECLARATION
void variableSet(int w, int h);
void onMouse( int event, int x, int y, int, void*);
void setREGIONS();
void drawButton(Mat image, Key k, Scalar inner_color, Scalar outer_color);
void drawButtonSCREEN(Mat image, Key k, Scalar inner_color, Scalar outer_color);

void clickVOWS(Mat image, int x, int y);
void clickCONS(Mat image, int x, int y);
void clickNUMS(Mat image, int x, int y);
void clickTOOLBAR(Mat image, int x, int y);

void drawVOWELS( Key vowelsOUT[]);
void drawNUMBERS(bool display_first, Key numbersOUT[]);
void drawCONSONANTS(bool display_first, Key consonantsOUT[]);
void drawTOOLBAR(bool display_first, Key toolbarOUT[]);
void drawTOOLBAR_OTHER(bool display_first, Key toolbar_otherOUT[]);
void drawHOLD(Key holdOUT[]);
void drawTOGGLES (Key togglesOUT[]);
void drawMENU (Key togglesOUT[]);

void drawCAPITALCONSONANTS(bool display_first, Key consonantsOUT[]);
void drawCAPITALVOWELS(Key vowelsOUT[]);

void switchCons(bool toFirst, Key consonantsOUT[]);
void switchNums(bool toNUMS, Key numsOUT[]);
void switchToolOther(bool toFirtst, Key toolOtherOUT[]);
void switchCAPSON(Key consonantsOUT[], Key vowelsOUT[]);
void switchCAPSOFF(Key consonantsOUT[], Key vowelsOUT[]);

///GLOBAL VARIABLES
int wMax = 1280;
int hMax = 680;
int m = hMax * 0.042;
int h1 = 0.11764705882 * hMax;
int h2 = 0.24411764705 * hMax;
int w1 = 0.072125 * wMax;

int screen_width = wMax - (w1 * 4);
int screen_height = hMax - m - h1 - h2;
int text_height = 30;
double text_size =0.6;

bool showingFIRST_cons = true;
bool showingFIRST_nums = true;
bool showingFIRST_tool_other = true;
bool caps_on = false;

Mat screen(hMax, wMax, CV_8UC3, Scalar(150,150,150));

Scalar grey(140,140,140);
Scalar heatherGrey(180,180,180);
Scalar lightPink(168, 170, 255);
Scalar darkPink(148, 150, 235);
Scalar blue(255, 213, 48);
Scalar darkBlue(221, 177, 0);
Scalar black(0, 0, 0);
Scalar screen_color = grey;
Scalar inner_color = heatherGrey;
Scalar outer_color = grey;
Key list_cons[20];
Key list_vows[6];
Key list_nums[20];
Key list_tools[7];
Key list_tool_other[18];
Key hold[2];
Key toggles[3];
Key screen_key;
regions sections[6];


//MAIN METHOD
int main(int argc, char* argv[]){
	if (argc < 3) {
		//cout << "Please enter two arguments: screen width and height" << endl;
		
	}
	else if (argc > 3) {
		//cout << "Please enter only two arguments: screen width and height" << endl;
	}
	else {
		int tempw = atof(argv[1]);
		int temph = atof(argv[2]);
		variableSet(tempw, temph);
		
	}
	
	///set globals
	setREGIONS();
	
	///set window
	namedWindow("Key", WND_PROP_AUTOSIZE);
	moveWindow("Key", 0, 0);
	
	///init window
	
	imshow("Key", screen);
	
	///local variables
	
	
	/// draw keys
	Key menu (Point(0, 0), Point(wMax, m));
		menu.text_mid.x = 5;
		menu.text_mid.y = menu.text_mid.y + 5;
	menu.button_display = "Menu";
	Key tempD (Point (0, hMax-h2), Point (wMax, hMax));
	screen_key.extra(Point(w1 + w1, m + h1), Point(wMax - w1 - w1, hMax - h2));
	screen_key.text_mid.x = screen_key.top_left.x + 10;
	drawButton(screen, menu, inner_color, outer_color);
	drawButton(screen, tempD, inner_color, outer_color);
	screen_key.calcLinePoints();
	drawButtonSCREEN(screen, screen_key, screen_color, screen_color);
	drawVOWELS(list_vows);
	drawNUMBERS(true,  list_nums);
	drawCONSONANTS(true, list_cons);
	drawTOOLBAR(true, list_tools);
	drawTOOLBAR_OTHER(true, list_tool_other);
	drawHOLD(hold);
	drawTOGGLES (toggles);
	
	
	//TOGGLE BUTTONs
	
	///input
	setMouseCallback( "Key", onMouse, 0 );
	while (true){
		char key = waitKey(33);
		
		if (key == 'q'){
			break;
		}
		
		if (key == 's' || key == 'S'){
			switchCons(!showingFIRST_cons, list_cons);
			showingFIRST_cons = !showingFIRST_cons;
			switchNums( !showingFIRST_nums, list_nums);
			showingFIRST_nums = !showingFIRST_nums;
			switchToolOther(!showingFIRST_tool_other, list_tool_other);
			showingFIRST_tool_other = !showingFIRST_tool_other;
			
		}
		if(key == 'a') {
			if(caps_on) {
				switchCAPSOFF(list_cons, list_vows);
				caps_on = !caps_on;
			}
			else{
				switchCAPSON(list_cons, list_vows);
				caps_on = !caps_on;
			}
		}
		
		
	
	}
	return 0;
}

//when mouse is clicked to broad region analysis
void onMouse( int event, int x, int y, int, void* ){
	String let;
	if(event != EVENT_LBUTTONDOWN ) {
		return;
	}
	regions temp;
	int region = 0;
	
	for (int i = 0; i < 6; i++) {
		temp = sections[i];
		if ((temp.w1 <= x && x <= temp.w2 )&& (temp.h1 <= y && y <= temp.h2)) {
			region = i;
			i = 10;
		}
	}
	//cout << region << endl;
	if (region == 0) {}
	if (region == 1) {
		clickCONS(screen, x, y);
	}
	if (region == 2) {
		clickVOWS(screen, x, y);
	}
	if (region == 3) {
		clickNUMS(screen, x, y);
	}
	if (region == 4) {
		clickTOOLBAR(screen, x, y);
	}
	if (region == 5) {}
}
void variableSet(int w, int h){
	wMax = w;
	hMax = h;
	m = hMax * 0.042;
	h1 = 0.11764705882 * hMax;
	h2 = 0.24411764705 * hMax;
	w1 = 0.072125 * wMax;
	
	
}
//OTHER FUNCTIONS
void setREGIONS() {
	sections[0].extra(Point(0, 0), Point(wMax, m));
	sections[0].identifier = "MENU";
	
	sections[1].extra(Point(0, m), Point(wMax, m+h1));
	sections[1].identifier = "CONSENENTS";
	
	sections[2].extra(Point(0, m + h1), Point(w1 + w1, hMax - h2));
	sections[2].identifier = "VOWELS";
	
	sections[3].extra(Point(wMax - w1 - w1, m + h1), Point(wMax, hMax - h2));
	sections[3].identifier = "NUMBERS";
	
	sections[4].extra(Point(0, hMax - h2), Point(wMax, hMax));
	sections[4].identifier = "TOOLBAR";
	
	sections[5].extra(Point(w1 + w1, m + h1), Point(wMax - w1 - w1, hMax - h2));
	sections[5].identifier = "SECTION_MIDDLE";
}
//clicks to add letter
void clickVOWS(Mat image, int x, int y) {
	Key temp;
	for (int i = 0; i < 6; i++) {
		temp = list_vows[i];
		if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
			screen_key.symbol = screen_key.symbol + temp.symbol;
			screen_key.write();
			drawButtonSCREEN(image, screen_key, screen_color, screen_color);
			i = 6;
		}
	}
}
void clickCONS(Mat image, int x, int y) {
	Key temp;
	for (int i = 0; i < 10; i++) {
		temp = list_cons[i];
		if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
			if(temp.display == true) {
				screen_key.symbol = screen_key.symbol + list_cons[i].symbol;
				screen_key.write();
				drawButtonSCREEN(image, screen_key, screen_color, screen_color);
			}
			else {
				screen_key.symbol = screen_key.symbol + list_cons[i+10].symbol;
				screen_key.write();
				drawButtonSCREEN(image, screen_key, screen_color, screen_color);
			}
			i = 10;
		}
	}
	
}
void clickNUMS(Mat image, int x, int y) {
	Key temp;
	for (int i = 0; i < 10; i++) {
		temp = list_nums[i];
		if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
			if(temp.display == true) {
				screen_key.symbol = screen_key.symbol + list_nums[i].symbol;
				screen_key.write();
				drawButtonSCREEN(image, screen_key, screen_color, screen_color);
				
			}
			else {
				screen_key.symbol = screen_key.symbol + list_nums[i+10].symbol;
				screen_key.write();
				drawButtonSCREEN(image, screen_key, screen_color, screen_color);
			}
			i = 10;
		}
	}
	
}
void clickTOOLBAR(Mat image, int x, int y){
	///FIRST CHECK GENERAL AREA
	
	Key temp;
	
	///CHECK FEWEST SET FIRST (SPACE OR HOLD)
	for (int i = 0; i < 2; i++) {
		temp = hold[i];
		if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
			screen_key.symbol = screen_key.symbol + temp.symbol;
			screen_key.write();
			drawButtonSCREEN(image, screen_key, screen_color, screen_color);
			i = 10;
			
		}
	}
	
	//if shift is pressed
	temp = toggles[0];
	if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
	}
	
	//if enter is pressed
	temp = list_tools[5];
	if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
		screen_key.nextLine();
		drawButtonSCREEN(image, screen_key, screen_color, screen_color);
		
	}
	
	//if tab is pressed
	temp = list_tools[2];
	if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
		screen_key.symbol = screen_key.symbol + "	";
		screen_key.write();
		drawButtonSCREEN(image, screen_key, screen_color, screen_color);
		
		
	}
	
	//if delete is pressed
	temp = list_tools[0];
	if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
		
		if (screen_key.symbol.length() <= 0) {
			if(screen_key)
			//if (screen_key) so that if you press delete first it doesnt crash fix this later!
			screen_key.prevLine();
		}
		screen_key.symbol = screen_key.symbol.substr(0, screen_key.symbol.length() - 1);
		screen_key.write();
		drawButtonSCREEN(screen, screen_key, screen_color, screen_color);
	}
	
	//if caps is pressed
	temp = list_tools[4];
	if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
		if(caps_on) {
			switchCAPSOFF(list_cons, list_vows);
			caps_on = !caps_on;
		}
		else{
			switchCAPSON(list_cons, list_vows);
			caps_on = !caps_on;
		}
	}
	
	//if the toggle button is clicked
	temp  = toggles[1];
	if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y) )) {
		if(caps_on) {
			switchCons(!showingFIRST_cons, list_cons);
			showingFIRST_cons = !showingFIRST_cons;
		}
		else{
			switchCons(!showingFIRST_cons, list_cons);
			showingFIRST_cons = !showingFIRST_cons;
		}
		
		switchNums( !showingFIRST_nums, list_nums);
		showingFIRST_nums = !showingFIRST_nums;
		switchToolOther(!showingFIRST_tool_other, list_tool_other);
		showingFIRST_tool_other = !showingFIRST_tool_other;
		
	}
	
	///IF IN OTHER KEYS SECTION
	for (int i = 0; i < 9; i++) {
		temp = list_tool_other[i];
		if (( (temp.top_left.x <= x)&&(x <= temp.bottom_right.x) )&&( (temp.top_left.y <= y)&&( y <= temp.bottom_right.y))) {
			if(temp.display == true) {
				screen_key.symbol = screen_key.symbol + list_tool_other[i].symbol;
				screen_key.write();
				drawButtonSCREEN(image, screen_key, screen_color, screen_color);
				
			}
			else {
				screen_key.symbol = screen_key.symbol + list_tool_other[i+9].symbol;
				screen_key.write();
				drawButtonSCREEN(image, screen_key, screen_color, screen_color);
			}
			i = 10;
		}
	}
	
}

//draw
void drawButton(Mat image, Key k, Scalar inner_color, Scalar outer_color) {
	//draw shading first
	rectangle(image, k.top_left, k.bottom_right, outer_color, -1, 0);
	//draw inside on top of shading
	rectangle(image, k.inner_top_left, k.inner_bottom_right, inner_color, -1, 0);
	//add text
	//has form: where, what, where, font type, size, color, thick, type, bot left
	putText(image, k.button_display, k.text_mid, 0, text_size, black, 2, LINE_4, false);
	//show drawing
	imshow("Key", image);
}
void drawButtonSCREEN(Mat image, Key k, Scalar inner_color, Scalar outer_color) {
	//draw shading first
	rectangle(image, k.top_left, k.bottom_right, outer_color, -1, 0);
	//draw inside on top of shading
	rectangle(image, k.inner_top_left, k.inner_bottom_right, inner_color, -1, 0);
	//add text
	//has form: where, what, where, font type, size, color, thick, type, bot left
	//putText(image, k.symbol, k.text_mid, 0, 0.75, black, 2, LINE_4, false);
	
	for (int i = 0; i <= k.current_line; i++) {
		putText(image, k.lines[i], k.lines_coords[i], 0, 0.75, black, 2, LINE_4, false);
		
	}
	
	
	
	
	//show drawing
	imshow("Key", image);
}

void drawVOWELS(Key vowelsOUT[]) {
	Point points_of_vowels [6][2];
	String vowel_strings [6] = {"a", "e", "i", "o", "u", "y"};
	//SECTION B (vowels)
	int hscaleVOWEL2 = hMax - h1 - h2 - m;
	hscaleVOWEL2 = (int) (hscaleVOWEL2/3);
	int vw1 = 0;
	int vh1 = m+h1;
	int vw2 = w1;
	int vh2 = m+h1 + hscaleVOWEL2;
	
	for (int i = 0; i < 6; i = i + 2){
		points_of_vowels[i][0] = Point(vw1, vh1);      //w
		points_of_vowels[i][1] = Point(vw2, vh2);      //h
		
		vw1 = vw1 + w1;
		vw2 = vw2 + w1;
		
		points_of_vowels[i+1][0] = Point(vw1, vh1);      //w
		points_of_vowels[i+1][1] = Point(vw2, vh2);      //h
		
		vw1 = vw1 - w1;
		vw2 = vw2 - w1;
		
		vh1 = vh1+hscaleVOWEL2;
		vh2 = vh2+hscaleVOWEL2;
	}//create points for section B
	for (int i = 0; i < 6; i++) {
		vowelsOUT[i].extra(points_of_vowels[i][0], points_of_vowels[i][1]);
		vowelsOUT[i].symbol = vowel_strings[i];
		vowelsOUT[i].button_display = vowel_strings[i];
		vowelsOUT[i].display = true;
		drawButton(screen, vowelsOUT[i], inner_color, outer_color);
	} //set keys
}
void drawNUMBERS(bool display_first, Key numbersOUT[]) {
	
	
	Point points_of_numbers [10][2];
	String number_strings [20] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")" };
	//SECTION C (numbs)
	int nscaleVOWEL2 = hMax - h1 - h2 - m;
	nscaleVOWEL2 = (int) (nscaleVOWEL2/5);
	int nw1 = wMax- w1 - w1;
	int nh1 = m+h1;
	int nw2 = wMax - w1;
	int nh2 = m+h1 + nscaleVOWEL2;
	
	for (int i = 0; i < 10; i = i + 2){
		if (i >= 8) {
			nh2 = hMax - h2;
		}
		points_of_numbers[i][0] = Point(nw1, nh1);      //w
		points_of_numbers[i][1] = Point(nw2, nh2);      //h
		
		nw1 = nw1 + w1;
		nw2 = nw2 + w1;
		
		points_of_numbers[i+1][0] = Point(nw1, nh1);      //w
		points_of_numbers[i+1][1] = Point(nw2, nh2);      //h
		
		nw1 = nw1 - w1;
		nw2 = nw2 - w1;
		
		nh1 = nh1+nscaleVOWEL2;
		nh2 = nh2+nscaleVOWEL2;
		
		
		
	} //create points for section C
	for (int i = 0; i < 10; i++) {
		numbersOUT[i].extra(points_of_numbers[i][0], points_of_numbers[i][1]);
		
		
	} //create keys
	
	for (int i = 10; i < 20; i++) {
		numbersOUT[i].extra(points_of_numbers[i - 10][0], points_of_numbers[i - 10][1]);
		
	}
	
	if (display_first == true) {
		for(int i = 0; i < 10; i++) {
			numbersOUT[i].display = true;
			numbersOUT[i + 10].display = false;
			numbersOUT[i].symbol = number_strings[i];
			numbersOUT[i].button_display = number_strings[i];
			drawButton(screen, numbersOUT[i], inner_color, outer_color);
		}
	}
	else {
		for(int i = 10; i < 20; i++) {
			numbersOUT[i].display = true;
			numbersOUT[i - 10].display = false;
			numbersOUT[i].symbol = number_strings[i];
			numbersOUT[i].button_display = number_strings[i];
			drawButton(screen, numbersOUT[i], inner_color, outer_color);
		}
	}
}
void drawCONSONANTS(bool display_first, Key consonantsOUT[]){
	////SETTING KEYS
	//data organization
	Point points_of_consonants [10][2];
	String consonant_strings [20] = {"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "z"};
	//SECTION A (cons)
	int wscale10 = (int)(wMax/10);
	int cw1 = 0;
	int ch1 = m;
	
	int cw2 = wscale10;
	int ch2 = (m + h1);
	
	for (int i = 0; i < 10; i++) {
		points_of_consonants[i][0] = Point(cw1, ch1);
		points_of_consonants[i][1] = Point(cw2, ch2);
		cw1 = cw1 + wscale10;
		cw2 = cw2 + wscale10;
	} //create points
	
	for (int i = 0; i < 10; i++) {
		consonantsOUT[i].extra(points_of_consonants[i][0], points_of_consonants[i][1]);
		consonantsOUT[i].symbol = consonant_strings[i];
		consonantsOUT[i].button_display = consonant_strings[i];
	}//key first 10 points
	
	
	for (int i = 10; i < 20; i++) {
		consonantsOUT[i].extra(points_of_consonants[i - 10][0], points_of_consonants[i - 10][1]);
		consonantsOUT[i].symbol = consonant_strings[i];
		consonantsOUT[i].button_display = consonant_strings[i];
	}//key second 10 points
	
	
	if (display_first == true) {
		for(int i = 0; i < 10; i++) {
			consonantsOUT[i].display = true;
			consonantsOUT[i + 10].display = false;
			drawButton(screen, consonantsOUT[i], inner_color, outer_color);
		} //dispay b - m
	}
	else {
		for(int i = 10; i < 20; i++) {
			consonantsOUT[i].display = true;
			consonantsOUT[i - 10].display = false;
			drawButton(screen, consonantsOUT[i], inner_color, outer_color);
		} //dispay n - z
		
	}
	
}

void drawTOOLBAR(bool display_first, Key toolbarOUT[]) {
	Point points_of_toolbar[6][2];
	Point points_of_arrows[1][2];
	
	String toolbar_string[6] = {"delete", "ctrl", "tab", "shift", "CAPS", "enter"};
	int hscale4 = (int)(h2 / 3);
	int wscale4 = 2*hscale4;
	int tow1 = wMax - h2 - (2*wscale4) - w1 - w1;
	int toh1 = hMax - h2;
	int tow2 = tow1 + wscale4;
	int toh2 = toh1 + hscale4;
	
	for (int i = 0; i < 6; i= i + 2) {
		if (i >= 4) {
			toh2 = hMax;
		}
		
		points_of_toolbar[i][0] = Point(tow1, toh1);
		points_of_toolbar[i][1] = Point(tow2, toh2);
		
		int tempW = tow1 + wscale4;
		int tempW2 = tow2 + wscale4;
		
		points_of_toolbar[i + 1][0] = Point(tempW, toh1);
		points_of_toolbar[i + 1][1] = Point(tempW2, toh2);
		
		toh1 = toh1 + hscale4;
		toh2 = toh2 + hscale4;
	}
	for (int i = 0; i < 6; i++) {
		toolbarOUT[i].extra(points_of_toolbar[i][0], points_of_toolbar[i][1]);
		toolbarOUT[i].symbol = toolbar_string[i];
		toolbarOUT[i].button_display = toolbar_string[i];
		toolbarOUT[i].text_mid.x = (toolbarOUT[i].text_mid.x + points_of_toolbar[i][0].x) / 2 ;
	}
	
	if (display_first == true) {
		for(int i = 0; i < 6; i++) {
			toolbarOUT[i].display = true;
			drawButton(screen, toolbarOUT[i], inner_color, outer_color);
		}
	}
	else {
		for(int i = 0; i < 6; i++) {
			toolbarOUT[i].display = true;
			drawButton(screen, toolbarOUT[i], inner_color, outer_color);
		}
	}
	
	int arroww1 = w1 + w1;
	int arrowh1 = hMax - h2;
	int arroww2 = w1 + w1 + h2;
	int arrowh2 = hMax;
	
	for (int i = 0; i < 1; i++) {
		
		points_of_arrows[i][0] = Point(arroww1, arrowh1);
		points_of_arrows[i][1] = Point(arroww2, arrowh2);
		toolbarOUT[7].extra(points_of_arrows[i][0], points_of_arrows[i][1]);
		toolbarOUT[7].symbol = "";
		toolbarOUT[7].button_display = "arrows";
		toolbarOUT[7].text_mid.x = toolbarOUT[7].text_mid.x - 15;
		drawButton(screen, toolbarOUT[7], inner_color, outer_color);
		
	}
	
	
}
void drawTOOLBAR_OTHER(bool display_first, Key toolbar_otherOUT[]){
	Point points_of_toolbar_other[9][2];
	
	String toolbar_string[18] = {".", ",", "_", "\"", "'", "?", "+", "-", "=", "\\", "/", "|", "<", ">", ":", "[", "]", ";"};
	
	int hscale3 = (int)(h2 / 3);
	int tow1 = wMax - h2 - w1 - w1; //h2 since square
	int toh1 = hMax - h2;
	
	int tow2 = tow1 + hscale3;
	int toh2 = toh1 + hscale3;
	
	for (int i = 0; i < 9; i= i + 3) {
		if (i >= 6) {
			toh2 = hMax;
		}
		
		points_of_toolbar_other[i][0] = Point(tow1, toh1);
		points_of_toolbar_other[i][1] = Point(tow2, toh2);
		
		int temp = tow1 + hscale3;
		int temp2 = tow2 + hscale3;
		
		points_of_toolbar_other[i + 1][0] = Point(temp, toh1);
		points_of_toolbar_other[i + 1][1] = Point(temp2, toh2);
		
		temp = temp + hscale3;
		temp2 = temp2 + hscale3;
		
		points_of_toolbar_other[i + 2][0] = Point(temp, toh1);
		points_of_toolbar_other[i + 2][1] = Point(temp2, toh2);
		
		toh1 = toh1 + hscale3;
		toh2 = toh2 + hscale3;
		
		
	}
	
	for (int i = 0; i < 9; i++) {
		toolbar_otherOUT[i].extra(points_of_toolbar_other[i][0], points_of_toolbar_other[i][1]);
		toolbar_otherOUT[i].symbol = toolbar_string[i];
		toolbar_otherOUT[i].button_display = toolbar_string[i];
	}
	for (int i = 9; i < 18; i++) {
		toolbar_otherOUT[i].extra(points_of_toolbar_other[i - 9][0], points_of_toolbar_other[i - 9][1]);
		toolbar_otherOUT[i].symbol = toolbar_string[i];
		toolbar_otherOUT[i].button_display = toolbar_string[i];
	}
	
	if (display_first == true) {
		for(int i = 0; i < 9; i++) {
			toolbar_otherOUT[i].display = true;
			toolbar_otherOUT[i + 9].display = false;
			drawButton(screen, toolbar_otherOUT[i], inner_color, outer_color);
		}
	}
	else {
		for(int i = 9; i < 18; i++) {
			toolbar_otherOUT[i].display = true;
			toolbar_otherOUT[i - 9].display = false;
			drawButton(screen, toolbar_otherOUT[i], inner_color, outer_color);
		}
	}
	
	
}
void drawHOLD(Key holdOUT[]) {
	holdOUT[0].extra(Point(wMax - w1 - w1 - 1, hMax - h2 + ((int) h2 / 4)), Point(wMax, hMax));
	holdOUT[1].extra(Point(wMax - w1 - w1 - 1, hMax - h2), Point(wMax, hMax - (int) 3 * h2 / 4) );
	holdOUT[0].symbol = "hold";
	holdOUT[1].symbol = " ";
	holdOUT[0].button_display = "hold";
	holdOUT[1].button_display = "space";
	holdOUT[0].text_mid.x = holdOUT[0].text_mid.x - 15;
	holdOUT[1].text_mid.x = holdOUT[1].text_mid.x - (w1 / 3);
	holdOUT[1].text_mid.y = holdOUT[1].text_mid.y + 10;
	drawButton(screen, holdOUT[0], inner_color, outer_color);
	drawButton(screen, holdOUT[1], inner_color, outer_color);
}
void drawTOGGLES (Key togglesOUT[]){
	// Point shiftPOINTS[1][3] = {Point(0, hMax-h2), Point(0, hMax), Point(w1, hMax)};
	// const Point* shift_points[1] = { shiftPOINTS[0] };
	// int num_points[] = { 3 };
	//
	// polylines(screen, shift_points, num_points, 1, true, blue, 1, 0, 0);
	
	togglesOUT[0].extra(Point(0, hMax-h2),Point(w1 * 2, hMax - (0.5 * h2)));
	togglesOUT[0].symbol = "shift";
	togglesOUT[0].button_display = "shift";
	
	togglesOUT[1].extra(Point(0, hMax - (0.5 * h2)),Point(w1 * 2, hMax));
	togglesOUT[1].symbol = "toggle";
	togglesOUT[1].button_display = "toggle";
	
	togglesOUT[2].extra(Point(0, hMax - (0.5 * h2)),Point(w1 * 2, hMax));
	togglesOUT[2].symbol = "Enter";
	togglesOUT[2].button_display = "\\n";
	
	
	
	drawButton(screen, togglesOUT[0], inner_color, outer_color);
	drawButton(screen, togglesOUT[1], inner_color, outer_color);
	
	
}
void drawMENU (Key togglesOUT[]) {
	
}
void drawCAPITALCONSONANTS(bool display_first, Key consonantsOUT[]){
	////SETTING KEYS
	//data organization
	Point points_of_consonants [10][2];
	String consonant_strings [20] = {"B", "C", "D", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "V", "W", "X", "Z"};
	//SECTION A (cons)
	int wscale10 = (int)(wMax/10);
	int cw1 = 0;
	int ch1 = m;
	
	int cw2 = wscale10;
	int ch2 = (m + h1);
	
	for (int i = 0; i < 10; i++) {
		points_of_consonants[i][0] = Point(cw1, ch1);
		points_of_consonants[i][1] = Point(cw2, ch2);
		cw1 = cw1 + wscale10;
		cw2 = cw2 + wscale10;
	} //create points
	
	for (int i = 0; i < 10; i++) {
		consonantsOUT[i].extra(points_of_consonants[i][0], points_of_consonants[i][1]);
		consonantsOUT[i].symbol = consonant_strings[i];
		consonantsOUT[i].button_display = consonant_strings[i];
	}//key first 10 points
	
	
	for (int i = 10; i < 20; i++) {
		consonantsOUT[i].extra(points_of_consonants[i - 10][0], points_of_consonants[i - 10][1]);
		consonantsOUT[i].symbol = consonant_strings[i];
		consonantsOUT[i].button_display = consonant_strings[i];
	}//key second 10 points
	
	
	if (display_first == true) {
		for(int i = 0; i < 10; i++) {
			consonantsOUT[i].display = true;
			consonantsOUT[i + 10].display = false;
			drawButton(screen, consonantsOUT[i], inner_color, outer_color);
		} //dispay b - m
	}
	else {
		for(int i = 10; i < 20; i++) {
			consonantsOUT[i].display = true;
			consonantsOUT[i - 10].display = false;
			drawButton(screen, consonantsOUT[i], inner_color, outer_color);
		} //dispay n - z
		
	}
	
}
void drawCAPITALVOWELS(Key vowelsOUT[]) {
	Point points_of_vowels [6][2];
	String vowel_strings [6] = {"A", "E", "I", "O", "U", "Y"};
	//SECTION B (vowels)
	int hscaleVOWEL2 = hMax - h1 - h2 - m;
	hscaleVOWEL2 = (int) (hscaleVOWEL2/3);
	int vw1 = 0;
	int vh1 = m+h1;
	int vw2 = w1;
	int vh2 = m+h1 + hscaleVOWEL2;
	
	for (int i = 0; i < 6; i = i + 2){
		points_of_vowels[i][0] = Point(vw1, vh1);      //w
		points_of_vowels[i][1] = Point(vw2, vh2);      //h
		
		vw1 = vw1 + w1;
		vw2 = vw2 + w1;
		
		points_of_vowels[i+1][0] = Point(vw1, vh1);      //w
		points_of_vowels[i+1][1] = Point(vw2, vh2);      //h
		
		vw1 = vw1 - w1;
		vw2 = vw2 - w1;
		
		vh1 = vh1+hscaleVOWEL2;
		vh2 = vh2+hscaleVOWEL2;
	}//create points for section B
	for (int i = 0; i < 6; i++) {
		vowelsOUT[i].extra(points_of_vowels[i][0], points_of_vowels[i][1]);
		vowelsOUT[i].symbol = vowel_strings[i];
		vowelsOUT[i].button_display = vowel_strings[i];
		vowelsOUT[i].display = true;
		drawButton(screen, vowelsOUT[i], inner_color, outer_color);
	} //set keys
}
//switches
void switchCons(bool toFirst, Key consonantsOUT[]) {
	
	if (toFirst == true) {
		if (caps_on) {
			drawCAPITALCONSONANTS(true, consonantsOUT);
		}
		else {
			drawCONSONANTS(true, consonantsOUT);
		}
	}
	else{
		if (caps_on) {
			drawCAPITALCONSONANTS(false, consonantsOUT);
		}
		else {
			drawCONSONANTS(false, consonantsOUT);
		}
	}
}
void switchNums(bool toNUMS, Key numsOUT[]) {
	if (toNUMS == true) {
		drawNUMBERS(true, numsOUT);
	}
	else{
		drawNUMBERS(false, numsOUT);
	}
}
void switchToolOther( bool toFirst, Key toolOtherOUT[]) {
	if (toFirst == true) {
		drawTOOLBAR_OTHER(true, toolOtherOUT);
	}
	else{
		drawTOOLBAR_OTHER(false, toolOtherOUT);
	}
}
void switchCAPSON(Key consonantsOUT[], Key vowelsOUT[]){
	
	drawCAPITALCONSONANTS(showingFIRST_cons, consonantsOUT);
	drawCAPITALVOWELS( vowelsOUT);
	
	
}
void switchCAPSOFF(Key consonantsOUT[], Key vowelsOUT[]){
	
	drawCONSONANTS(showingFIRST_cons, consonantsOUT);
	drawVOWELS(vowelsOUT);
	
	
}
