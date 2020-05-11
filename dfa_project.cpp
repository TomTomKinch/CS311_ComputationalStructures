/*******************************
* dfa_project.cpp
* Thomas Kinch
* 5/23/18
*******************************/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

//7) Post exponent, number check
bool exp_num_check( char num_arr[], int length){
	bool valid;
	//Check if value 0 - 9
	if(num_arr[0] >= 48 && num_arr[0] <= 57){
		//Make sure length is > 1
		if(length <= 1){
			return true; //string can end in a number
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			//Repeat number check
			valid = exp_num_check(temp, length);
		}	
	}
	else{
		valid = false;
	}	
	return valid;

}

//6) Post exponent, sign check
bool post_exp_sign(char num_arr[], int length){
	bool valid;
	//Check for sign +/-
	if(num_arr[0] == '+' || num_arr[0] == '-'){
		//Make sure length is > 1
		if(length <= 1){
			return false; //string can't end in a +/-
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			//Move States to number check
			valid = exp_num_check(temp, length);
		}
	}
	//Check if value is a number
	else if(num_arr[0] >= 48 && num_arr[0] <= 57){ 
		valid = exp_num_check(num_arr, length);		
	}
	//No valid values
	else{
		valid = false;
	}
	return valid;
}

//5) check Exponent
bool exp_check(char num_arr[], int length){
	bool valid;
	//Check For an e/E
	if(num_arr[0] == 'e' || num_arr[0] == 'E'){
		//Make sure length is > 1
		if(length <= 1){
			return false; //string can't end on e/E
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			valid = post_exp_sign(temp, length); 
		}
	}
	else{
		valid = false;
	}
	return valid;
}

//4) check numbers after the decimal
bool dec_num_check(char num_arr[], int length, bool one_number){
	bool valid;
	//Check if value 0 - 9
	if(num_arr[0] >= 48 && num_arr[0] <= 57){
		//Make sure length is > 1
		if(length <= 1){
			return true; //string can end in a number
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			//Repeat number check
			valid = dec_num_check(temp, length, true);
		}	
	}
	else if(num_arr[0] == 'e' || num_arr[0] == 'E'){
			if(one_number == true){
				valid = exp_check(num_arr, length);
			}
			else{
				valid = false;
			}
		}
	else{
		valid = false;
	}	
	return valid;
}

//3) Check decimal
bool dec_check(char num_arr[], int length, bool one_number){
	bool valid;
	if(num_arr[0] == '.'){
		if(length <= 1){
			return true; //string can end in a decimal
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			valid = dec_num_check(temp, length, one_number);
		}
	}
	else{
		return false;
	}
	return valid;
}

//2) Check for numbers
bool num_check(char num_arr[], int length, bool one_number){
	bool valid;
	//Check if value 0 - 9
	if(num_arr[0] >= 48 && num_arr[0] <= 57){
		//Make sure length is > 1
		if(length <= 1){
			return true; //string can end in a number
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			//Repeat number check
			valid = num_check(temp, length, true);
		}	
	}
	else if(num_arr[0] == '.'){
		valid = dec_check(num_arr, length, one_number);
	}
	else if(num_arr[0] == 'e' || num_arr[0] == 'E'){
		valid = exp_check(num_arr, length);
	}

	else{
		valid = false;
	}	
	return valid;
}

//1) Check for sign +/-
bool sign_check(char num_arr[], int length){
	bool valid;
	if(num_arr[0] == '+' || num_arr[0] == '-'){
		//Make sure length is > 1
		if(length <= 1){
			return false; //string can't end in a +/-
		}
		else{
			//Consume
			char temp[length - 1];
			for(int i = 0; i < length - 1; i++){
				temp[i] = num_arr[i + 1];	
			}
			length--;
			//Move States to number check
			valid = num_check(temp, length, false);
		}
	}
	//Check if value is a number
	else if(num_arr[0] >= 48 && num_arr[0] <= 57){
		valid = num_check(num_arr, length, true);		
	}
	//Check if value is a decimal
	else if(num_arr[0] == '.'){
		valid = dec_check(num_arr, length, false);
	}
	//No valid values
	else{
		valid = false;
	}
	return valid;
}

/***************
* Main
***************/
int main(){
	//Get filename
	string filename;
	cout << "Enter in filename: ";
	getline(cin, filename);
	
	//Declare File
	ifstream num_file;
	num_file.open(filename.c_str());
	
	//Check if file is open
	if(!num_file){
		cerr << "Unable to Open File \n";
		return 0;
	}
	//Declare string array	
	int row = 0;
	string string_arr[100];

	//Fill String Array
	while(!(num_file >> string_arr[row]).eof()){ 
		row++;
	}

	//Loop: Convert string to char array, test through states
	for(int i = 0; i < row; i++){
		bool valid = true;
		int length = string_arr[i].length();
		char num_arr[length];
		strcpy(num_arr, string_arr[i].c_str());

		//Send Through the states
		valid = sign_check(num_arr, length);
		
		if(valid == true){
			cout << num_arr << "		is a valid floating point string. :)" << endl;
		}
		else{
			cout << num_arr << "		is not valid. :(" << endl;
		}
	}
	//Close File
	num_file.close();
	
	return 0;
}
