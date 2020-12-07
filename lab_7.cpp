#include <iostream>
using namespace std;

template <class T>
struct data{
	T number;
};

template <class T>
class object{
public:
	data<T> info;
	object<T> *left;
	object<T> *right;

	static int sum;
	static int count;

public:
	object(){
		left = NULL;
		right = NULL;
	}
	object(data<T> i){
		info = i;
		left = NULL;
		right = NULL;
		object<T>::count++;
		sum += i.number;
	};

	static void Average();

	void operator+=(data<T>& num); //Add new object
	friend std::ostream& operator<< (std::ostream &out, const object<T> &obj); //Show tree
	void operator-=(int num); //Find and delete the number
};

template <class T>
int object<T>::count = 0;
template <class T>
int object<T>::sum = 0;
template <class T>
object<T>* root = NULL;

template <class T>
object<T>* Find_place(object<T>* to_add, object<T>* temp){
	object<T>* temp2 = temp;

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

template <class T>
void object<T>::operator +=(data<T>& num){
	object* new_obj = new object(num);

	if(root<T> == NULL){
		root<T> = new_obj;
	} else {
		object* place = Find_place(new_obj, root<T>);

		if(place->info.number > new_obj->info.number){
			place->left = new_obj;
		} else if (place->info.number < new_obj->info.number){
			place->right = new_obj;
		} else {
			cout << "The number is already in the tree" << endl;
		}
	}
}

template <class T>
void Del_object(object<T>* obj){
	if(obj == NULL){
		return;
	}

	Del_object(obj->left);
	Del_object(obj->right);
	object<T>::count--;
	object<T>::sum -= obj->info.number;
	delete obj;
}

template <class T>
void object<T>::operator-=(int num){
	if(root<T> == NULL){
		cout << "Tree is empty!";
		return;
	}
	if(root<T>->info.number == num){
		Del_object(root<T>->left);
		Del_object(root<T>->right);
		root<T> = NULL;
		object<T>::sum = 0;
		object<T>::count = 0;
		cout << endl << "Whole tree is deleted" << endl;
	} else{
		object<T>* obj = root<T>;
		object<T>* temp = obj;

		while(obj!= NULL && obj->info.number != num){
			temp = obj;
			if(obj->info.number > num){
				obj = obj->left;
			} else if(obj->info.number < num){
				obj = obj->right;
			}
		}

		if(obj == NULL){
			cout << endl << "There's no such a number to delete!" << endl;
			return;
		} else{
			obj = temp;
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

template <class T>
void Show_obj(object<T>* obj){
	if(obj == NULL){
		return;
	}

	cout << ", " << obj->info.number;

	Show_obj(obj->left);
	Show_obj(obj->right);
}

template <class T>
std::ostream& operator<< (std::ostream &out, object<T> &obj){
	if(root<T> == NULL){
		cout << "Tree is empty!";
		return out;
	}

	cout << endl << endl << "Hi! I'm a tree!" << endl;
	cout << root<T>->info.number;

	Show_obj(root<T>->left);
	Show_obj(root<T>->right);
	return out;
}

template <class T>
void object<T>::Average(){
	if(root<T> == NULL){
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
	data<int> d_root = {50};
	object<int> o_root;
	o_root += d_root;

	for(int i = 0; i < 10; i++){
		int rand_num = rand() % 100;

		data<int> d_el = {rand_num};
		object<int> o_el;
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
			object<int>::Average();
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
