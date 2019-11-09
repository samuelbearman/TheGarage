/*
 * Name: Samuel Bearman
 * File: Song.cpp CMSC 202, Fall 2017
 * Date: 12/1/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is the class that holds information about each song from the
 * file including the song name, artist, rank, and year it came out.
 *
 * */
#include "Song.h"

// Song Constructor
// Default Song constructor that sets all values of song class 
Song::Song() {

    m_title = " ";
    m_artist = " ";
    m_year = 0;
    m_rank = 0;

}

// Overloaded Song constructor
// Fills Song memeber variables to input parameters
Song::Song(string title, string artist, int year, int rank) {

    m_title = title;
    m_artist = artist;
    m_year = year;
    m_rank = rank;

}

// getTitle
// returns the current title of the song
string Song::getTitle()const {

    return m_title;

}

// getArtist
// returns the current artist of the song
string Song::getArtist()const {

    return m_artist;

}

// getYear
// returns the year of the song 
int Song::getYear()const {

    return m_year;

}

// getRank
// returns the rank of the song
int Song::getRank()const {

    return m_rank;

}

// setTitle
// sets the title of the song
void Song::setTitle(string title) {

    m_title = title;

}

// setArtist
// sets the artist of the song
void Song::setArtist(string artist) {

    m_artist = artist;

}

// setYear
// sets the year of the song
void Song::setYear(int year) {

    m_year = year;

}

// setRank
// sets the rank of the song
void Song::setRank(int rank) {

    m_rank = rank;

}
