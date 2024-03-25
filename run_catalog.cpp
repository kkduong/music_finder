/******************************************************
** Program: run_catalog.cpp
** Author: Kaelee Duong
** Date: 2/11/2024
** Description: based on a user-inputed catalog of playlists, allows the user
				to search and print song and playlist information to a file
				or to the screen.
** Input: playlist filename, age, information display option, print option
		  and output filename option should the user choose to print to file
** Output: Based on the user's printing choice, song or playlist information
		   is printed to screen or to file.
******************************************************/

#include "catalog.h"

using namespace std;

int main()
{
	/*declare variables*/
	string filename;
	ifstream fin;
	string age;
	int size;
	bool run = true;
	Playlist* playlists;

	/*collect filename and age*/
	int cont = collect_info(filename, fin, age);

	/*convert the age to an integer*/
	int int_age = string_to_int(age);

	/*check if file has been opened 
	(cont should be 1 if collect_info() could not open the file) */
	if(cont == 1) {
		return cont;
	}

	/*store the amount of playlists in the file*/
	fin >> size;

	/*create a Playlist array to store data*/
	playlists = create_playlists(size);

	/*populate the Playlist array*/
	for (int i = 0; i < size; i++) {
		populate_one_list(playlists, i, fin);
	}


	/*while run is true let user continue to print information*/
	do {

		ofstream fout;

		int int_opt = collect_option();

		run = option_choice(playlists, size, int_opt, int_age, fout);

	} while (run);
	
	/*delete information from the heap*/
	delete_info(playlists, size);

	return 0;
}
