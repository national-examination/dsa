#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include <vector>
using namespace std;


string product = "products.csv";

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


void readFromFile(ifstream& file){
   string line;
   while(getline(file, line)){
      cout << line << endl;
   }
   file.close();
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

string findProductByName(string& product_name){
   ifstream inputFile = openInputFile(product);
   string line;
   string product_found = "";
   while(getline(inputFile, line)){
      vector<string> words = separateSentence(line);
      if(words[0] == product_name){
         product_found += line;
      }
   }

   return product_found;
}

void ListProducts(){
   cout << "Loading ........" << endl;
   ifstream productFile = openInputFile(product);
   readFromFile(productFile);
}

void listProduct(string& name){
   cout << "Finding product : " << name << endl;
   string product = findProductByName(name);
   if(product == "") {
      cout << "Product not found" << endl;
   }else{
      cout << product <<endl;
   }
}

void createProduct(string& product_name, string& quantity, string& price){
   cout << "Creating product : " << product_name<<endl;
   ofstream product_file = openOutputFile(product);
   product_file << product_name+","+quantity+","+price << endl;
   cout << "Product saved successfully!" << endl;

}

void updateProduct(string& product_name, string& quantity, string& price){
   cout << "Updating product : " << product_name << "...." << endl;
   string product_found = findProductByName(product_name);
   if(product_found == "") {
      cout << "Product not found" << endl;
   }else{
      ofstream outputFile = openOutputFile("temp.csv");
      ifstream inputFile = openInputFile(product);

      string line;
      while(getline(inputFile, line)){
         vector<string> words = separateSentence(line);
         if(words[0] == product_name){
            outputFile << product_name+","+quantity+","+price << endl;
         } else {
            outputFile << line << endl;
         }
      }
      inputFile.close();
      outputFile.close();

      remove(product.c_str());
      rename("temp.csv", product.c_str());
      cout << "Product updated successfully!" <<endl;
   }
}

void deleteProduct(string& product_name){
   cout << "Deleting product " << product_name << "......" <<endl;
   string product_found = findProductByName(product_name);
   if(product_found == "") {
      cout << "Product not found" << endl;
   }else{
      ofstream outputFile = openOutputFile("temp.csv");
      ifstream inputFile = openInputFile(product);

      string line;
      while(getline(inputFile, line)){
         vector<string> words = separateSentence(line);
         if(words[0] != product_name){
            outputFile << line << endl;
         }
      }
      inputFile.close();
      outputFile.close();

      remove(product.c_str());
      rename("temp.csv", product.c_str());
      cout << "Product deleted successfully!" <<endl;
   }
}

void chooseAction(){
   while (true){
      cout <<endl<< "1) List products"<<endl;
      cout << "2) List product <name>"<<endl;
      cout << "3) Create product <name> <quantity> <price>"<<endl;
      cout << "4) Update product <name> <quantity> <price>"<<endl;
      cout << "5) Delete product <name>"<<endl;
      cout << "6) Exit"<<endl;
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
         break;
      }else if(category == "list"){
         string command;
         iss >> command;
         if(command == "products"){
            ListProducts();
         }

         if(command == "product"){
            string product_name;
            iss >> product_name;
            listProduct(product_name);
         }
      }else if(category == "create"){
         string cond;
         iss >> cond;
         if(cond == "product"){
            string name;
            iss >> name;
            string quantity;
            iss >> quantity;
            string price;
            iss >> price;

            createProduct(name, quantity, price);
         }
      }else if(category == "update"){
         string cond;
         iss >> cond;
         if(cond == "product"){
            string name;
            iss >> name;
            string quantity;
            iss >> quantity;
            string price;
            iss >> price;   
            updateProduct(name, quantity, price);
         }
      }else if(category == "delete"){
         string command;
         iss >> command;
         if(command == "products"){
            ListProducts();
         }

         if(command == "product"){
            string product_name;
            iss >> product_name;
            if(findProductByName(product_name) != ""){
               deleteProduct(product_name);
            }else{
               cout<<"Product does not exist!"<<endl;
            }
         }
      }else{
         cout << "Invalid Command"<<endl;
      }
   }
}

int main(){
   cout <<"Welcome to the system developed by Esther" <<endl;
   cout << "Choose an action you want to perform"<<endl;
   
   chooseAction();

   return 0;
}
