// Import all libraries
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip> 
using namespace std;

// Include items.csv file where we will save our data
string item = "items.csv";

// Function to open the output file where we perform write and append operations
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

// Function to open the input file where we perform read operations
ifstream openInputFile(string filename){
   ifstream file(filename);

   if(!file.is_open()){
      cout << "Couldn't open the file" << endl;
   }

   return file;
}

// Function to separate our sentences by ,
vector<string> separateSentence(const string& sentence) {
    vector<string> words;
    istringstream iss(sentence);
    string word;

    while (getline(iss, word, ',')) {
        words.push_back(word);
    }
    return words;
}

// Function to read data from our file items
void readFromFile(ifstream& file){
    vector<vector<string>> items;

    string line;
    while(getline(file, line)){
        vector<string> words = separateSentence(line);
        items.push_back(words);
    }

    sort(items.begin(), items.end(), [](const vector<string>& a, const vector<string>& b) {
        return a[1] < b[1];
    });

    for (const auto& item : items) {
        cout << "Item ID: " << setw(2) << item[0] << "      " << "Item Name:" << setw(10) << item[1] << "     " << "Quantity :" << setw(2) << item[2] << "      " << "Reg Date :" << item[3] << endl;
    }

    file.close();
}

// Function to check if the item id already existed in our file items.
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

// Function to check if the item name already existed in our file items
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

// Function to list items from our file throught readFromFile function.
void listItems(){
   cout << "Loading ........" << endl;
   ifstream itemFile = openInputFile(item);
   readFromFile(itemFile);
}

// Function to check if the id enterered is a number or not.
bool isValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Function to check if the date entered is valid or not.
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

// Function for adding a new item 
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

// Function to help the user enter the command that he/she wants to perform.
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
         cout << "------------------------------------------------------------------"<<endl;
         cout << "*                              BYE BYE !!!!                      *"<<endl;
         cout << "------------------------------------------------------------------"<<endl;
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

// Our entry point main method.
int main(){
   cout << "------------------------------------------------------------------"<<endl;
   cout << "*                                Welcome!                        *"<<endl;
   cout << "*                   RCA inventory management system              *"<<endl;
   cout << "*                           By Esther Umuhoza                    *"<<endl;
   cout << "------------------------------------------------------------------"<<endl;
   cout << "If you need help, enter 'help' command"<<endl;
   cout << "Choose an action you want to perform"<<endl;
   
   chooseAction();

   return 0;
}
