#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Song.h"
#include "Tqueue.cpp"

using namespace std;
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

class MusicPlayer{
 public:
  //Name: MusicPlayer - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new MusicPlayer
  MusicPlayer();
  //Name: MusicPlayer - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new MusicPlayer and passes the music filename
  MusicPlayer(string filename);
  //Name: ~MusicPlayer - Destructor
  //Precondition: None
  //Postcondition: Creates a new MusicPlayer
  ~MusicPlayer();
  //Name: LoadCatalog(string filename)
  //Precondition: Requires filename
  //Postcondition: Loads the file into the m_songCatalog (as songs)
  void LoadCatalog(string filename);
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the application and the menu
  void MainMenu();
  //Name: DisplaySongs
  //Precondition: User enters year (1983-2013)
  //Postcondition: Lists all songs (numbered) for that year
  void DisplaySongs();
  //Name: AddSong
  //Precondition: m_songCatalog is populated
  //Postcondition: Displays the current list and adds a song (by year)
  //               to the m_playList
  void AddSong();
  //Name: DisplayPlaylist
  //Precondition: None (can be empty)
  //Postcondition: Displays the playlist
  void DisplayPlaylist();
 private:
  vector<Song*> m_songCatalog; //Holds all songs in file
  Tqueue<Song, 3000> m_playList; //Holds all songs in play list
};


#endif
