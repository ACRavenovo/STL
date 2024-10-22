int count1() {
	static int n = 0;
	n++;
	return n;
}

int& count2() {
	static int n = 0;
	n++;
	return n;
}

bool judgement() {
	return true;
}

//int main() {
//	const int& r1 = count1();
//	int& r2 = count2();
//	int&& c = 10;
//
//}