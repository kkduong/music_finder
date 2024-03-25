#include <iostream>
#include <fstream>

using namespace std;

//a struct to hold info of a Playlist
struct Playlist {
	string name;        //name of the playlist, one word
	int num_song;       //number of songs in the playlist
	struct Song *s;     //an array that holds all songs in the playlist
	float total_len;    //total length of the playlist
};

//a struct to hold info of a Song
struct Song {
	string name;		//name of the song, one word
	string artist;		//name of the artist, one word
	int year_release;	//the year of release
	float length;		//length of the song
	string genre;		//genre of the song, one word
	string res;			//"E" or "none" for restriction level
};


/**************************************************
 * Name: create_playlists()
 * Description: This function will dynamically allocate
				an array of playlists (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Playlist array of requested size is created and return
 ***********************************************/
Playlist* create_playlists(int);


/**************************************************
 * Name: populate_one_list()
 * Description: This function will fill a single playlist struct 
				with information that is read in from the file
 * Parameters:  Playlist* - pointer to the Playlist array
				int - index of the Playlist in the array to be filled 
				ifstream& - input file to get the Playlist information
 * Pre-conditions: Playlist array has been allocated; 
				 provided index is less than the array size
 * Post-conditions: a Playlist at provided index is populated
 ***********************************************/
void populate_one_list(Playlist*, int, ifstream &); 


/**************************************************
 * Name: create_songs()
 * Description: This function will dynamically allocate
				an array of songs (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Song array of requested size is created and return
 ***********************************************/
Song* create_songs(int);


/**************************************************
 * Name: populate_one_song()
 * Description: This function will fill a single song struct 
				with information that is read in from the file
 * Parameters:  Song* - pointer to the Song array
				int - index of the Song in the array to be filled 
				ifstream& - input file to get the Song information
 * Pre-conditions: Song array has been allocated; 
				 provided index is less than the array size
 * Post-conditions: a Song at provided index is populated
 ***********************************************/
void populate_one_song(Song*, int, ifstream &); 


/**************************************************
 * Name: delete_info()
 * Description: This function will  delete all the memory that was dynamically allocated
 * Parameters: Playlist* - the Playlist array
 * Pre-conditions: the provided Playlist array hasn't been freed yet
 * Post-conditions: the Playlist array, with all Songs inside, is freed
 ***********************************************/
void delete_info(Playlist*, int);

/**************************************************
 * Name: collect_info()
 * Description: This function will collect info from user that will be used 
 *              throughout program
 * Parameters: string& - input file name variable
 * 			   ifstream& - input file object for storing file
 *             string& - age variable
 * Pre-conditions: The variables passed into the function have been intialized
 * Post-conditions: all variables passed will have user inputed information 
 * 					stored for use in program
 ***********************************************/
int collect_info(string& , ifstream&, string&);

/**************************************************
 * Name: string_to_int()
 * Description: This function will convert a string to an integer
 * Parameters: string - user input
 * Pre-conditions: user input was given
 * Post-conditions: string has been converted to an integer and returned
 ***********************************************/
int string_to_int(string);

/**************************************************
 * Name: is_int()
 * Description: This function will check if the user input (string) is an integer within
 * 				a range they choose
 * Parameters: string - user input
 *             int - minimum value
 *             int - maximum value
 * Pre-conditions: user input was given
 * Post-conditions: boolean returned based on if user inputed a number in the 
 * 					desired range
 ***********************************************/
bool is_int(string, int, int);

/**************************************************
 * Name: is_positive_int()
 * Description: This function will check if the user input (string) is a positive
 * Parameters: string - user input
 * Pre-conditions: user input was given
 * Post-conditions: boolean returned based on if user inputed a positive int
 ***********************************************/
bool is_positive_int(string input);

/**************************************************
 * Name: print_to_file()
 * Description: This function will print the desired information to a file
 * Parameters: Playlist* - the Playlist array
 * 			   int - index of Playlist with the Song array that is desired
 * 			   int - index of Song that is to be printed
 * 			   ofstream& - output file that the program is writing to
 * 			   int - user's option of information being displayed (playlist length or song info)
 * Pre-conditions: the Playlist and Song arrays have been populated, 
 * 				ofstream object is opened, and the user has chosen an option
 * Post-conditions: The desired information is printed to a file
 ***********************************************/
void print_to_file(Playlist*, int, int, ofstream&, int);

/**************************************************
 * Name: print_to_screen()
 * Description: This function will print the desired information to the screen
 * Parameters: Playlist* - the Playlist array
 * 			   int - index of Playlist with the Song array that is desired
 * 			   int - index of Song that is to be printed
 * 			   int - user's option of information being displayed (playlist length or song info)
 * Pre-conditions: the Playlist and Song arrays have been populated and the 
 * 				   user has chosen an option
 * Post-conditions: The desired information is printed to the screemn
 ***********************************************/
void print_to_screen(Playlist*, int, int, int);

/**************************************************
 * Name: option_choice()
 * Description: This function will print information to file based on users choice and return a 
 *              return a boolean to determine whether the code continues to run
 * Parameters: Playlist* - the Playlist array
 * 			   int - size of PLaylist array
 * 			   int - users choice (either 1-5)
 * 			   int - user's age
 * 			   ofstream& - output file variable
 * Pre-conditions: the Playlist and Song arrays have been populated and user input was given
 * Post-conditions: Song or Playlist information is printed to file or screen based on 
 * 					user choice and a boolean is returned to keep program running
    ***********************************************/
bool option_choice(Playlist*, int, int, int, ofstream&);

/**************************************************
 * Name: print_choice()
 * Description: This function will determine the user's printing choice and open a file 
 * 				for writing if needed
 * Parameters: ofstream& - output file variable
 * Pre-conditions: the ofstream variable is created
 * Post-conditions: return the user's printing choice and output file is opened 
 * 					if it needs to be
 ***********************************************/
int print_choice(ofstream&);

/**************************************************
 * Name: search_song_by_name()
 * Description: This function will search the Song arrays for a user-inputed name and will
 * 				return a boolean on whether the program should continue to run
 * Parameters: Playlist* - the Playlist array
 * 			   int - size of Playlist array
 * 			   int - user's printing choice (to screen or file)
 * 			   ofstream& - output file that the program is writing to
 * Pre-conditions: the Playlist and Song arrays have been populated , 
 * 				   ofstream object is opened, and user input was given
 * Post-conditions: The singular Song the user was looking for is printed to screen or 
 * 					file and a boolean is returned to keep program running
 ***********************************************/
bool search_song_by_title(Playlist*, int, int, ofstream&);

/**************************************************
 * Name: search_song_by_genre()
 * Description: This function will search the Song arrays for a user-inputed genre and will
 * 				return a boolean on whether the program should continue to run
 * Parameters: Playlist* - the Playlist array
 * 			   int - size of Playlist array
 * 			   int - user's printing choice (to screen or file)
 * 			   ofstream& - output file that the program is writing to
 * Pre-conditions: the Playlist and Song arrays have been populated,
 * 			        ofstream object is opened, and user input was given
 * Post-conditions: The all Songs with the user-inputed genre have been printed to screen or
 *                  file and a boolean is returned to keep program running
 ***********************************************/
bool search_song_by_genre(Playlist*, int, int, ofstream&);

/**************************************************
 * Name: display_all_songs()
 * Description: This function will display all songs in every Playlist depending 
 * 				on the song restriction
 * Parameters: Playlist* - the Playlist array
 * 			   int - size of Playlist array
 * 			   int - user's age
 * Pre-conditions: The Playlist and Song arrays have been populated and user input was given
 * Post-conditions: All Songs that are allowed by user's age have been printed to screen
 *                   and a boolean is returned to keep program running.
 ***********************************************/
bool display_all_songs(Playlist*, int, int);

/**************************************************
 * Name: print_total_len()
 * Description: This function will print the total length of all Playlists
 * Parameters: Playlist* - the Playlist array
 * 			   int - size of Playlist array
 * 			   int - user's printing choice (to screen or file)
 * 			   ofstream& - output file that the program is writing to
 * Pre-conditions: the Playlist and Song arrays have been populated,
 * 			        ofstream object is opened, and user input was given
 * Post-conditions: The length of all Playlists is printed to file or screen and
 *                  a boolean is returned to keep program running
 ***********************************************/
bool print_total_len(Playlist*, int, int, ofstream&);

/**************************************************
 * Name: collect_option()
 * Description: This function will determine the user's option choice 
 * Parameters: N/A
 * Pre-conditions: N/A
 * Post-conditions: return the user's choice 
 ***********************************************/
int collect_option();

/**************************************************
 * Name: main()
 * Description: This function will run the music finder program
 * Parameters: N/A
 * Pre-conditions: all functions used have been defined
 * Post-conditions: exit program smoothly should user decide to.
 ***********************************************/
int main();


