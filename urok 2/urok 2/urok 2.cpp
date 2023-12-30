vector   set    list(список)

list
x <-> x <-> x <-> ...

	set - сортитрует данные - сортировку делай в сет
	multiset = vector + сортировка
	log по основанию 2 всегда


	             vector           set                  list
	------------------------------------------------------------
добавления        О(1)          O(log(n))              O(1)
    ------------------------------------------------------------
  удаление        O(n)          O(log(n))              O(1 или n)
	------------------------------------------------------------
 обращение        O(1)          O(log(n) или  n)       O(n)
	------------------------------------------------------------
     поиск        O(n)          O(log(n))              O(n)
	------------------------------------------------------------
   перебор        O(n)          O(n)                   O(n)



	Структуры

struct My_type {
	int a;
	char c;
	string s;
	vector<int> v;
};

int main() {
	My_type my_type;
	my_type.a = 5;
	my_type.c = 'g';
	my_type.s = 'abcabc';
	my_type.v = {1,2,3,4,5};
}












struct Student {
	string name;
	string sur_name;
	string phone_name;
	int study_group;
};

inline bool cmp(const Student&, const Student& b) {
	return a.sur_name == b.sur_name ? a.name < b.name :
		a.sur_name < b.sur_name;
	//return a.sur_name < b.sur_name                          //1 условие
}




int main() {
	vector<Student> students;
	for (int i = 0; i < 1; ++i) {
		Student temp;
		temp.name = 'Denis';
		temp.sur_name = 'Pletyukhin';
		temp.phone_number = '88805553535';
		temp.study_group = 912;
		students.push_back(temp);
	}
	sort(students.begin(), students.end(), cmp);
	for (int i = 0; i < students.size(); ++i) {
		cout << students[i].name << endl;
	}

}