int stringToInt(const string &s){
	stringstream om(s);
	int num=-1;
	om>>num;
	return num;
}
