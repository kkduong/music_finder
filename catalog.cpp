#include "catalog.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//function definitions go here

Playlist* create_playlists(int size) {
    /*creates an array of Playlists on the heap*/
    Playlist* playlists = new Playlist[size];
    return playlists;
}

Song* create_songs(int size) {
    /*creates an array of Songs on the heap*/
    Song* songs = new Song[size];
    return songs;
}

void populate_one_song(Song* song_arr, int index, ifstream& file) {
    /*intializes the member variables of Song with information from 
    the file inputed by the user. */
    file >> song_arr[index].name;
    file >> song_arr[index].artist;
    file >> song_arr[index].year_release;
    file >> song_arr[index].length;
    file >> song_arr[index].genre;
    file >> song_arr[index].res;
}


void populate_one_list(Playlist* play_arr, int index, ifstream& file){ 

    file >> play_arr[index].name;
 
    file >> play_arr[index].num_song;

    play_arr[index].total_len = 0;

    play_arr[index].s = create_songs(play_arr[index].num_song);

    /*populates each Song with information from the user inputed file*/
    for (int i = 0; i < play_arr[index].num_song; i++) {
        populate_one_song(play_arr[index].s, i, file);

        play_arr[index].total_len += play_arr[index].s[i].length;
    }
}

void delete_info(Playlist* play_arr, int size){
    /*loop through each Playlist to get delete each Song array*/
    for (int i = 0; i < size; i++) {
            delete [] play_arr[i].s;
    }

    /*delete the Playlist array*/
    delete [] play_arr;
    play_arr = nullptr;
}

int collect_info(string& name, ifstream& fin, string& a){
    cout << endl;
    cout << "Enter the filename: ";
	cin >> name;

    /*open file for reading information to populate Playlists*/
    fin.open(name);

    /*check if file exists and exit program if it does not*/
	if(!fin.is_open()) {
		cout << "Error loading file" << endl;
		return 1;
	}

    cout << endl;

    // consistently check if the
	while(!is_positive_int(a)) {
		cout << "Enter your age: ";
		cin >> a;

	} 

    return 0;

}


int string_to_int(string input){
	int sum = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		//convert input[i] to int (48-57)
		//and subtract the ascii value of '0' == 48
		//then value will be in range 0-9
		int value = (int)input[i] - 48;
		sum = sum * 10 + value;
	}

	return sum;

}

bool is_int(string input, int min, int max) {
	//edge cases
	if (input == "0")
		return false;

	if (input == "") //empty string
		return false;

    if (input.size() > 1) {
        return false;
    }

    if (!(input[0] >= min && input[0] <= max)) {
        return false;
    }

	return true;
}

bool is_positive_int(string input) {
	//edge cases
	if (input == "0")
		return false;

	if (input == "") //empty string
		return false;

	//loop thru every char in "input"
	//check if the ascii value of that
	//if all char's ascii values are within
	//the min and max ascii values depending on what is being checked
	for (int i = 0; i < input.size(); ++i)
	{
		if (!(input[i] >= 48 && input[i] <= 57))
			return false;
	}

	return true;
}

void print_to_file(Playlist* play_arr, 
                   int play_index, 
                   int song_index, 
                   ofstream& file, 
                   int option) {
    
    /*check if we are printing playlist length rather than song info*/
    if(option == 4) {
        file << play_arr[play_index].name << ": " << play_arr[play_index].total_len << endl;
    }
    else {
        /*appends all information to a file*/
        file << "Name: " << play_arr[play_index].s[song_index].name << endl;
        file << "Artist: " << play_arr[play_index].s[song_index].artist << endl;
        file << "Year of Release: " << play_arr[play_index].s[song_index].year_release << endl;
        file << "Song Length: " << play_arr[play_index].s[song_index].length << endl;
        file << "Genre: " << play_arr[play_index].s[song_index].genre << endl;
        file << "Restriction: " << play_arr[play_index].s[song_index].res << endl;
    }

    file << endl;
}

void print_to_screen(Playlist* play_arr, 
                   int play_index, 
                   int song_index, 
                   int option) {

     /*check if we are printing playlist length rather than song info*/
    if(option == 4) {
        cout << play_arr[play_index].name << ": " << play_arr[play_index].total_len << endl;
    }
    else {
        /*print all information to the terminal*/
        cout << "Name: " << play_arr[play_index].s[song_index].name << endl;
        cout << "Artist: " << play_arr[play_index].s[song_index].artist << endl;
        cout << "Year of Release: " << play_arr[play_index].s[song_index].year_release << endl;
        cout << "Song Length: " << play_arr[play_index].s[song_index].length << endl;
        cout << "Genre: " << play_arr[play_index].s[song_index].genre << endl;
        cout << "Restriction: " << play_arr[play_index].s[song_index].res << endl;
    }

}

bool option_choice(Playlist* arr, int size, int option, int age, ofstream& file) {
    int p_choice;

    /*check if the point is either 1 or 5 as you don't have to ask for printing method for either*/
    if(option == 1) {
        return display_all_songs(arr, size, age);
    }
    else if (option == 5) {
        cout << endl;
        cout << "Quiting program. Thank you!" << endl;
        cout << endl;
        return false;
    }
    else {
        /*with options 2-4 check for printing method first and open file if needed*/
        int p_choice = print_choice(file);

        if(option == 2) {
            return search_song_by_title(arr, size, p_choice, file);
        }
        if (option == 3) {
            return search_song_by_genre(arr, size, p_choice, file);
        }
        else {
            return print_total_len(arr, size, p_choice, file);
        }
        
    }
}

int print_choice(ofstream& file) {
    string choice;
    string outfile;

    cout << endl;
    cout << "How would you like the information displayed?" << endl;
    cout << "1. Print to screen (Press 1)" << endl;
    cout << "2. Print to file (Press 2)" << endl;
    cout << endl;

    /*check if the choice is either 1 or 2*/
    while (!is_int(choice, 49, 50)) {
        cout << "Your Choice: ";
        cin >> choice;
    }
    
    /*if option is 2-4 ask user to enter the ouput file they would like to use*/
    if (string_to_int(choice) > 1 && string_to_int(choice)< 5) {
        cout << endl;
        cout << "What file do you want to print to: ";
        cin >> outfile;

        file.open(outfile, ios::app);
        
    }

    return string_to_int(choice);
}

bool search_song_by_title(Playlist* arr, int size, int print, ofstream& file) {
    string title;

    cout << endl;
    cout << "Enter the name of the song you are looking for: ";
    cin >> title;

    /*loop through all song arrays to find the sigular song the user is looking for*/
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < arr[i].num_song; j++) {
            if(arr[i].s[j].name == title) {
                /*if user chooses to print to screen*/
                if(print == 1) {
                    cout << endl;
                    cout << "Here is the info of the song: " << endl;
                    cout << "------------------------------" << endl;
                    print_to_screen(arr, i, j, 2);
                    cout << "------------------------------" << endl;
                }
                /*if user chooses to print to file*/
                else {
                    print_to_file(arr, i, j, file, 2);
                    cout << endl;
                    cout << "Appended information to file successfully." << endl;   
                }
            
                return true;
            }

        }
    }
    /*let user know if the song is not found*/
    cout << "Song not found." << endl;
    return true;
}

bool search_song_by_genre(Playlist* arr, int size, int print, ofstream& file) {
    /*ask user to input the genre they are looking for*/
    string genre;
    cout << endl;
    cout << "Enter the genre of songs you are looking for: ";
    cin >> genre;

    /*count how many times the program has printed information for the purpose of print to screen layout*/
    int print_count = 0;

    for (int i = 0; i < size; i++) {
        for(int j = 0; j < arr[i].num_song; j++) {
            if(arr[i].s[j].genre == genre) {
                
                /*if the user chooses to print to screen*/
                if(print == 1) {
                    if (print_count == 0) {
                        cout << endl;
                        cout << "Here is the song info:" << endl;
                        cout << "-----------------------" << endl;
                    }

                    print_to_screen(arr, i, j, 3);
                    cout << "--------------------" << endl;

                    print_count++;
                }
                /*if the user chooses to print to a file*/
                else {
                    print_to_file(arr, i, j, file, 3);
                    print_count ++;
                }
            }

            if(print != 1 && i == size - 1 && j == arr[i].num_song - 1) {
                    cout << endl;
                    cout << "Appended information successfully." << endl;
            } 
        }
    }
    /*if no songs were printed at least once, let user know there are no songs in this genre*/
    if (print_count == 0) {
        cout << "No songs of this genre found." << endl;
    }
    return true;
}

bool display_all_songs(Playlist* arr, int size, int age) {
    /*print counter for the purpose of displaying songs to screen*/
    int print_count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < arr[i].num_song; j++) {
            /*if the song is restricted check if the user's age is greater than 19*/
            if (arr[i].s[j].res == "E") {
                if (age > 19) {
                    if (print_count == 0) {
                        cout << endl;
                        cout << "Here is the song info:" << endl;
                        cout << "-----------------------" << endl;
                    }

                    print_to_screen(arr, i, j, 1);
                    cout << "--------------------" << endl;

                    print_count++;
                }
            }
            /*for all other songs that are not restricted*/
            else {
                if (print_count == 0) {
                        cout << endl;
                        cout << "Here is the song info:" << endl;
                        cout << "-----------------------" << endl;
                }

                print_to_screen(arr, i, j, 3);
                cout << "--------------------" << endl;

                print_count++;
            }

        }
    }
    return true;
}

bool print_total_len(Playlist* arr, int size, int print, ofstream& file) {
    /*print counter for displaying purposes on screen*/
    int print_count = 0;

    for (int i = 0; i < size; i++) {
        /*if user chooses to print to screen*/
        if (print == 1) {
            if (print_count == 0) {
                cout << endl;
                cout << "Here is the playlist info:" << endl;
                cout << "-----------------------" << endl;
            }
            print_to_screen(arr, i, 0, 4);
            cout << "-----------------------" << endl;
            print++
        }
        /*if user chooses to print to file*/
        else {
            print_to_file(arr, i, 0, file, 4);
            if (i == size-1) {
                cout << endl;
                cout << "Appended information successfully." << endl;
            } 
        }
    }
    return true;
}

int collect_option() {
    string option = "";

	cout << endl;
	cout << "Which option would you like to choose?" << endl;
	cout << "1. Display all songs" << endl;
	cout << "2. Search for a song to play" << endl;
	cout << "3. Search Songs by Genre" << endl;
	cout << "4. Display length of all playlists" << endl;
	cout << "5. Quit" << endl;
    cout << endl;

    /*checks if the option is between the 1-5 inclusive*/
	while (!is_int(option, 49, 53)) {
		cout << "Your Choice: ";
		cin >> option;

	}

    return string_to_int(option);
}



