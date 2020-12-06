#include <iostream>
using namespace std;

class data{
public:
	int number;

	data(){
		number = 0;
	}

	data(int num){
		number = num;
	}
};


class object{
public:
	data info;
	object *left;
	object *right;

	static int sum;
	static int count;

public:
	object(){
		left = NULL;
		right = NULL;
	}
	object(data i){
		info = i;
		left = NULL;
		right = NULL;
		object::count++;
		sum += i.number;
	};

	static void Average();

	void operator+=(data& num); //Add new object
	friend std::ostream& operator<< (std::ostream &out, const object &obj); //Show tree
	void operator-=(int num); //Find and delete the number
};

int object::count = 0;
int object::sum = 0;

object* root = NULL;

object* Find_place(object* to_add, object* temp){
	object* temp2 = temp;

	while(temp != NULL){
		temp2 = temp;

		if(temp->info.number > to_add->info.number){
			temp = temp->left;
		} else if (temp->info.number < to_add->info.number){
			temp = temp->right;
		} else {
			break;
		}
	}
	return temp2;
}

void object::operator +=(data& num){
	object* new_obj = new object(num);

	if(root == NULL){
		root = new_obj;
	} else {
		object* place = Find_place(new_obj, root);

		if(place->info.number > new_obj->info.number){
			place->left = new_obj;
		} else if (place->info.number < new_obj->info.number){
			place->right = new_obj;
		} else {
			cout << "The number is already in the tree" << endl;
		}
	}
}

object* FindToDel(int num){
	object* temp = root;
	object* temp2 = temp;

	while(temp != NULL && temp->info.number != num){
		temp2 = temp;
		if(temp->info.number > num){
			temp = temp->left;
		} else if(temp->info.number < num){
			temp = temp->right;
		}
	}

	if(temp == NULL){
		return NULL;
	}

	return temp2;
}

void Del_object(object* obj){
	if(obj == NULL){
		return;
	}

	Del_object(obj->left);
	Del_object(obj->right);
	object::count--;
	object::sum -= obj->info.number;
	delete obj;
}

void object::operator-=(int num){
	if(root == NULL){
		cout << "Tree is empty!";
		return;
	}
	if(root->info.number == num){
		Del_object(root->left);
		Del_object(root->right);
		root = NULL;
		object::sum = 0;
		object::count = 0;
		cout << endl << "Whole tree is deleted" << endl;
	} else{
		object* obj = FindToDel(num);

		if(obj == NULL){
			cout << endl << "There's no such a number to delete!" << endl;
			return;
		}

		if(obj->info.number > num){
			Del_object(obj->left);
			obj->left = NULL;
		} else{
			Del_object(obj->right);
			obj->right = NULL;
		}

		cout << endl << "Object deleted" << endl;
	}
}

void Show_obj(object* obj){
	if(obj == NULL){
		return;
	}

	cout << ", " << obj->info.number;

	Show_obj(obj->left);
	Show_obj(obj->right);
}

std::ostream& operator<< (std::ostream &out, const object &obj){
	if(root == NULL){
		cout << "Tree is empty!";
		return out;
	}

	cout << endl << endl << "Hi! I'm a tree!" << endl;
	cout << root->info.number;

	Show_obj(root->left);
	Show_obj(root->right);
	return out;
}

void object::Average(){
	if(root == NULL){
		cout << "Tree is empty";
	} else{
		cout << endl << endl << "The average = " << (double)object::sum/object::count << endl;
	}
}


bool IsNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
string IsCorrect(string request){
	string item;
	do{
		cout << request;
		getline(cin, item);
		while(IsNumber(item) == false){
				cout << "\nINCORRECT" << endl;
				cout << request;
				getline(cin, item);
		}
	}while(stoi(item) < 1);
	return item;
}

int main(){
	cout << "The generated numbers: 50";
	data d_root(50);
	object o_root;
	o_root += d_root;

	for(int i = 0; i < 10; i++){
		int rand_num = rand() % 100;

		data d_el(rand_num);
		object o_el;
		o_el += d_el;
		cout << ", " << rand_num ;
	}
	cout << o_root;
	string answer, new_num, del_num;
	int choice;

	do{
		cout << endl << endl << "1 - for add; \n2 - for delete; \n3 - for average; \n4 - for print; \n5 - for exit..." << endl;
		answer = IsCorrect("Your choice: ");

		choice = stoi(answer);

		switch(choice){
		case 1:
			cout << "Adding the element.";
			new_num = IsCorrect("Your number = ");

			d_root.number = stoi(new_num);
			o_root += d_root;
			break;
		case 2:
			cout << "Deleting the element.";
			del_num = IsCorrect("Your number = ");

			o_root-=stoi(del_num);
			break;
		case 3:
			object::Average();
			break;
		case 4:
			cout << o_root;
			break;
		case 5:
			break;
		}
	}while(choice != 5);

	cout << "Goodbye";
	return 0;
}

