#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

string item = "items.csv";

ofstream openOutputFile(string filename,const string mode = "a"){
   ofstream file;

   if(mode == "a"){
      file.open(filename, ios::app);
   }else{
      file.open(filename, ios::out);
   }

   if(!file.is_open()){
      cout << "Couldn't open the file" <<endl;
   }

   return file;
}

ifstream openInputFile(string filename){
   ifstream file(filename);

   if(!file.is_open()){
      cout << "Couldn't open the file" << endl;
   }

   return file;
}

vector<string> separateSentence(const string& sentence) {
    vector<string> words;
    istringstream iss(sentence);
    string word;

    while (getline(iss, word, ',')) {
        words.push_back(word);
    }
    return words;
}


void readFromFile(ifstream& file){
    vector<vector<string>> items;

    string line;
    while(getline(file, line)){
        vector<string> words = separateSentence(line);
        items.push_back(words);
    }

    sort(items.begin(), items.end(), [](const vector<string>& a, const vector<string>& b) {
        int idA = stoi(a[0]);
        int idB = stoi(b[0]);
        return idA < idB; // Sort based on item ID (words[0])
    });

    for (const auto& item : items) {
        cout << "Item ID: " << item[0] << "  Item Name: " << item[1] << "   Quantity: " << item[2] << "   Reg Date: " << item[3] << endl;
    }

    file.close();
}

string finditemById(string& id){
   ifstream inputFile = openInputFile(item);
   string line;
   string item_found = "";
   while(getline(inputFile, line)){
      vector<string> words = separateSentence(line);
      if(words[0] == id){
         item_found += line;
      }
   }

   return item_found;
}

string finditemByName(string& item_name){
   ifstream inputFile = openInputFile(item);
   string line;
   string item_found = "";
   for (size_t i = 0; i < item_name.length(); i++){
         item_name[i] = tolower(item_name[i]);
   }
   while(getline(inputFile, line)){
      vector<string> words = separateSentence(line);
      if(words[1] == item_name){
         item_found += line;
      }
   }

   return item_found;
}

void listItems(){
   cout << "Loading ........" << endl;
   ifstream itemFile = openInputFile(item);
   readFromFile(itemFile);
}

bool isValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isValidDate(const string& str) {
    if (str.length() != 10) {
        return false;
    }

    for (char c : str) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

void addItem(string& item_id, string& item_name, string& item_quantity, string& item_registration_date){
   if(finditemByName(item_name) != "" ){
      cout<<"Item name already exist!"<<endl;
      return;
   }

   if(finditemById(item_id) != ""){
      cout<<"Item id already exist!"<<endl;
      return;
   }
   
   if (!isValidNumber(item_id)) {
      cout << "Invalid item ID "+item_id+" !" << endl;
      return;
   }
      
   if (item_name.empty()) {
      cout << "Item name is required "+item_name+"!" << endl;
      return;
   }
      
   if (!isValidNumber(item_quantity)) {
      cout << "Invalid item quantity "+item_quantity+" !" << endl;
      return;
   }
      
   if (!isValidDate(item_registration_date)) {
      cout << "Invalid registration date "+item_registration_date+" !" << endl;
      return;
   }
      
   cout << "Creating item : " << item_name<<endl;
   ofstream item_file = openOutputFile(item);
   item_file << item_id + "," + item_name + "," + item_quantity + "," + item_registration_date << endl;
   cout << "Item saved successfully!" << endl;

}

void chooseAction(){
   while (true){
      cout <<endl;
      cout << "Console > ";

      string request;
      getline(cin, request);

      for (size_t i = 0; i < request.length(); i++){
         request[i] = tolower(request[i]);
      }
      istringstream iss(request);
      string category;
      iss >> category;   

      if(category == "exit"){
         cout << "-----------------------------------------------"<<endl;
         cout << "*                BYE BYE !!!!                 *"<<endl;
         cout << "-----------------------------------------------"<<endl;
         break;
      }else if(category == "itemslist"){
         listItems();
      }else if(category == "itemadd"){
         string id;
         iss >> id;
         string name;
         iss >> name;
         string quantity;
         iss >> quantity;
         string date;
         iss >> date;
         addItem(id, name, quantity, date);
      }else if(category == "help"){
         cout <<endl;
         cout << "------------------------------------------------------------------"<<endl;
         cout << "*                        Commands syntaxes                       *"<<endl;
         cout << "------------------------------------------------------------------"<<endl;
         cout << "      Itemadd <item_id> <item_name> <quantity> <registration_date>"<<endl;
         cout << "      Itemslist"<<endl;
         cout << "      Exit"<<endl;
         cout << "------------------------------------------------------------------"<<endl;
      }else{
         cout << "Invalid Command! Please use 'help' to see command syntaxes!"<<endl;
      }
   }
}

int main(){
   cout << "------------------------------------------------------------------"<<endl;
   cout << "*                                Welcome!                        *"<<endl;
   cout << "*                       RCA stock management system              *"<<endl;
   cout << "------------------------------------------------------------------"<<endl;
   cout << "If you need help, enter 'help' command"<<endl;
   cout << "Choose an action you want to perform"<<endl;
   
   chooseAction();

   return 0;
}