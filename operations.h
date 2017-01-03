//
//  operations.hpp
//  DS16_hw2
//
//  Created by Tuğba Özkal on 9.11.2016.
//  Copyright © 2016 Tuğba Özkal. All rights reserved.
//

/* @Author
 * Student Name: TUGBA OZKAL
 * Student ID : 150120053
 * Date: 9.11.2016 
 */


#ifndef operations_h
#define operations_h

#include <stdio.h>
#include "node.h"

struct song {
    char name[SNAME_LENGTH];
    char singer[SINGER_LENGTH];
    char style[STYLE_LENGTH];
    int year;
};

struct song_node {
    song* data;
    song_node* next;
    song_node* prev;
    playlist* parent;
};

struct playlist {
    int songnumber;
    char name[LNAME_LENGTH];
    song_node* head;
    playlist* next;
    playlist* prev;
};

//add file definitions and functions as needed.
struct list {
    int playlist_count;
    playlist * start;
    FILE * musicbook;
    
    void create();
    void close();
    void createList(char *, int, song *);
    void addSong( song *, playlist * );
    void play(char);
    void deleteList(int);
    void removeSong(playlist *, int);
    void printList();
    void printSongofList(playlist *);
    void writeToFile();
};


#endif /* operations_h */
