#include <iostream>
#include "MusicPlayer.h"
#include "Song.h"

int main (int argc, char* argv[]) {
  string musicFile;
  cout << "Welcome to UMBC Music Player"<<endl;
  if(argc > 1){
    musicFile = argv[1];
  } else{
    cout << "One music files required - try again" << endl;
    cout << "./proj5 p5_music1.txt" << endl;
    return 0;
  }

  MusicPlayer* myMusic = new MusicPlayer(musicFile);
  myMusic->MainMenu();
  delete myMusic;
  return 0;
}
