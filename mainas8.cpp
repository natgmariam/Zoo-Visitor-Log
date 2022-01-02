/*
Description: Usues functions, arrays, and files to execute
the daily averages of the zoos visitor log.
Input: the user retrives a set of data from files and runs them
through parallel arrays to find running average
Output:a file is created witht the running daily averages calculated
*/
#include<iostream> //c++ library
#include<fstream> //file library
#include<string> //string libary
#include<cmath> //math library
using namespace std;

//function to find largest average
int largest(int entries[], int size, int range);
//function to find smalles average
int smallest(int entries[], int size, int range);
//function to convert day values
string convert(int);


int main(){
    //declaration of variables to be used
    static const int size = 365;
    int entries[size]={};
    string values;
    //in file streem
    ifstream iFile;
    string file;
    int eMax = 100;
    int count = 0;
    //out file stream
    ofstream largestAttOut, smallestAttOut;
    
    do{
    //prompt user to input file
    cout << "Open attendance file: ";
    cin >> file;
    iFile.open (file); //file beign opened
        //chechking for faliur of file open
        if(!iFile.is_open()){
            iFile.clear();
            iFile.ignore(eMax, '\n');
            //error message if not valid file
            cout << "Could not open " + file;
            break;
        }
        //storing file data into a string
        while(iFile >> values){
            //if we have strings to read them as 0
            if(values == "Closed"){
                entries[count]=0;
            }
            else{
                //to change the string data set into ints
                try{
                  entries[count] = stoi(values);
                }
                catch(exception &err)
                {
                  cout << "Unexpected file format.\n";
                  return 0;
                }
            }
            count++;
            //if data from file is to large
            if(count > size){
                cout << "Excessive attendance values.\n";
                return 0;
            }
        }
            //if data from file is to small
            if(count < size){
                cout << "Insufficient attendance values.\n";
                return 0;
            }


        //opening an outfile for largest averages
        largestAttOut.open("largest-" + file);
        //finding the larges running average for the 30 days
        int largeAve[30];
        for(int range= 0; range < 30; range++){
            largeAve[range] = largest(entries, size, range);

            // //these prints all 30 largest averages in an outfile
            // largestAttOut << "Largest "<< (range+1) << " Day Running Average: "<< convert(largeAve[range]) << " - "
            // << convert(largeAve[range] + range) << endl;

        }

        //opening outfile for smallest averages
        smallestAttOut.open("smallest-" + file);
        //finding the smallest running average for the 30 days
        int small[30];
        for(int range= 0; range < 30; range++){
            small[range] = smallest(entries, size, range);

        //     //these prints all 30 smallest averages
        //    smallestAttOut <<"Smallest "<< (range+1) << " Day Running Average: "<< convert(small[range]) << " - "
        //     << convert(small[range] + range) << endl;
        }
        //closing all infiles and outfiles
        largestAttOut.close();
        smallestAttOut.close();
        iFile.close();
        break;
    }while(true);


    return 0;
}
string convert( int day){
    string date;
    //converting the day to string so i can print it out in main
    //with the MM DD format using my Running Avergaes
    //goes through each condition

     day= day%365+1;
     if (day <= 31){
         date="JAN "+to_string(day);
     }
     else if (day <= 59){
         date="FEB "+to_string(day-31);
     }
     else if (day <= 90){
         date="MAR "+to_string(day-59);
     }
     else if (day <= 120){
         date="APR "+to_string(day-90);
     }
     else if (day <= 151){
         date="MAY "+to_string(day-120);
     }
     else if (day <= 181){
         date="JUN "+to_string(day-151);
     }
     else if (day <= 212){
         date="JUL "+to_string(day-181);
     }
     else if (day <= 243){
         date="AUG "+to_string(day-212);
     }
     else if (day <= 273){
         date="SEP "+to_string(day-243);
     }
     else if (day <= 304){
         date="OCT "+to_string(day-273);
     }
     else if (day <= 334){
         date="NOV "+to_string(day-304);
     }
     else if (day <= 365){
         date="DEC "+to_string(day-334);
     }
    //holds all the conversions
     return date;


}


//functio to calculate all the large ave
int largest(int entries[], int size, int range){

    int index = 0;
    int largestAvr = 0;
        //the largest average is stored in index and called in main
        
        for(int i =0; range + i < size; i++){
            int current = 0,
            endRange = range + i + 1;
            for( int start = i; start < endRange; start++){
                current += entries[start];
            }
            //the average is found here
            current/= range+1;
            if(current > largestAvr){
            largestAvr = current;
            index = i;
            }

        }


    return index;

}
//function to calc the smallest ave
int smallest(int entries[], int size, int range){

    int index = 0;
    int smallest = 1000000;
        //the smallest averages are stored and can be called in main
        for(int i =0; i + range < size; i++){
            int current = 0,
            endRange = range + i + 1;
            for(int start = i; start < endRange; start++){
                current += entries[start];
            }
            //the average found here
            current/= range+1;
            if(current < smallest){
            smallest = current;
            index = i;
            }

        }

        return index;
}
