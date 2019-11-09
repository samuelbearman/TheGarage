/*
 * Name: Samuel Bearman
 * File: MusicPlayer.cpp CMSC 202, Fall 2017
 * Date: 12/1/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is the controler and user of the 'Tqueue' class. It controls the
 * loading of the catalog and actual Tqueue methods.
 * */

#include "MusicPlayer.h"

// MusicPlayer Constructor
// This is the defualt constructor for music player, it does not have any thing since the 
// queue needs to have a file to load.
MusicPlayer::MusicPlayer() {}

// MusicPlayer overloaded constructor
// Uses LoadCatalog method to construct catalog 
MusicPlayer::MusicPlayer(string filename) {

    LoadCatalog(filename);

}

// MusicPlayer destructor
// Destructor for MusicPlayer, doesnt call anything becuase both vector and Tqueue have their 
// own destructors
MusicPlayer::~MusicPlayer() {}

// LoadCatalog
// Loads in all possible songs into catalog from file
void MusicPlayer::LoadCatalog(string filename) {
// this method uses the file io to make a new song and push into vector
    string title;
    string artist;
    int year;
    int rank;

    // used in converting ranks 
    int rankMultiplier = 0;

    // opens file 
    ifstream catalog(filename.c_str());

    Song* curr = new Song();
    // While not end of file
    while(!catalog.eof()) {
        string yearConversion;
        string rankConversion;

        // gets each data value for line
        getline(catalog, rankConversion, ','); 
        getline(catalog, title, ','); 
        getline(catalog, artist, ','); 
        getline(catalog, yearConversion, '\n'); 


        // converts to ints for year and rank
        year = atoi(yearConversion.c_str());
        rank = atoi(rankConversion.c_str());

        rank += rankMultiplier; 
       
        // new Song to be pushed
        curr = new Song(title, artist, year, rank);

        // push to catalog
        m_songCatalog.push_back(curr); 

        // converts the rank
        if(rank % 100 == 0) {
            rankMultiplier += 100;
        }
    }
    delete curr;
    catalog.close();
}

// MainMenu
// Outputs MainMenu to screen for user selection
void MusicPlayer::MainMenu() {

    int choice;

    bool screenSelect = true;

    while(screenSelect) {
        cout << "What would you like to do? " << endl;
        cout << "1. Display Songs by Year" << endl;
        cout << "2. Add Song" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Quit" << endl;
        cin >> choice;
        
        if(choice > 4 || choice < 0) {
            cout << "Please enter a value of 1-4" << endl;
        } else {

            switch(choice) {
                case 1:
                    DisplaySongs();
                    break;
                case 2:
                    AddSong();
                    break;
                case 3:
                    DisplayPlaylist();  
                    break;
                case 4:
                    screenSelect = false;
                    break;
                default:
                    cout << "something went wrong" ;
            }
        }
    }
}

// DisplaySongs
// Displays all songs from user selected year
void MusicPlayer::DisplaySongs() {

    bool pickYear = true;
    int displayYear = 0;

    while(pickYear != false) {
        displayYear = 0;
        cout << "What year would you like to see? (1983-2013) " << endl;
        cin >> displayYear;

        if(displayYear > 2013 || displayYear < 1983) {
            cout << "You have entered a year that is not availible, please try again" << endl; 
        } else {
            // Displays iteration of all songs in given year
            for(unsigned int i = 0; i < m_songCatalog.size(); i++) {
                if(m_songCatalog[i]->getYear() == displayYear) {
                    cout << m_songCatalog[i]->getRank() << ". ";
                    cout << m_songCatalog[i]->getTitle() << " by ";
                    cout << m_songCatalog[i]->getArtist() << endl;
                }
            }
            pickYear = false;
        }
    }
}

// AddSong
// User prompt for adding a new song to the Tqueue
void MusicPlayer::AddSong() {
    
    bool pickSong = true;
    int choice = 0;

    while(pickSong != false) {
        choice = 0;
        if(m_playList.size() == 0) {
            cout << "Playlist is currently empty" << endl;
        }
        DisplaySongs();
        cout << "Enter the number of the song you would like to add" << endl;
        cin >> choice; 
        if(choice > 3100 || choice < 0) {
            cout << "That is not a number for a song, try again" << endl;
        } else {
            // makes new song and pushes specified song into Tqueue  
            for(unsigned int i = 0; i < m_songCatalog.size(); i++) {
                if(m_songCatalog[i]->getRank() == choice) {
                    
                    Song* newSong = new Song(m_songCatalog[i]->getTitle(), m_songCatalog[i]->getArtist(), m_songCatalog[i]->getYear(), m_playList.size() + 1);
                    m_playList.enqueue(*newSong);
                    delete newSong;
                    pickSong = false;
                }
            }
        }
    }
}

// DisplayPlaylist
// Displays the current playlist elements
void MusicPlayer::DisplayPlaylist() {

    if(m_playList.size() == 0) {
        cout << "Current playlist is empty" << endl;
    } else {
        // outputs form front to back whats in the queue
        for(int i = m_playList.getFront(); i < m_playList.getBack(); i++ ) {
            cout << m_playList[i].getRank() << ". ";
            cout << m_playList[i].getTitle() << " by ";
            cout << m_playList[i].getArtist() << " from ";
            cout << m_playList[i].getYear() << endl;
        }
    }
}


