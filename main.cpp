//
//  main.cpp
//  DS16_hw2
//
//  Created by Tuğba Özkal on 8.11.2016.
//  Copyright © 2016 Tuğba Özkal. All rights reserved.
//

/* @Author
 * Student Name: TUGBA OZKAL
 * Student ID : 150120053
 * Date: 8.11.2016 
 */


#include <iostream>
#include "operations.h"
#include "node.h"

using namespace std;

typedef list DS;
DS book;

// functions
bool operate(char);
void print_menu();
void play_song();
void create_playlist();
void add_song_to_playlist();
void delete_list();
void remove_song_from_playlist();
void save();
void print_playlist();


int main() {
    bool end = true;
    char secim;
    book.create();
    while(end){
        print_menu();
        cin >> secim;
        end = operate(secim);
    }
    book.close();
    return EXIT_SUCCESS;
}


bool operate(char secim){
    switch(secim){
        case 'P': case 'p':
            play_song();
            break;
            
        case 'L': case 'l':
            print_playlist();
            break;
            
        case 'A': case 'a':
            add_song_to_playlist();
            break;
            
        case 'R': case 'r':
            remove_song_from_playlist();
            break;
            
        case 'C': case 'c':
            create_playlist();
            break;
            
        case 'D': case 'd':
            delete_list();
            break;
            
        case 'W': case 'w':
            save();
            break;
            
        case 'E': case 'e':
            cout << "Are you sure to close the application? (Y/N) ";
            cin >> secim;
            if (secim == 'Y' || secim == 'y')
                return false;
            break;

        default:
            cout << "You entered a invalid choice..." << endl;
            break;
    }
    return true;
}


void print_menu(){
    cout << endl << endl << "SONG BOX APPLICATION" << endl <<
    "Choose an operation: " << endl <<
    "P: Play" << endl <<
    "L: Show all playlists" << endl <<
    "A: Add songs to playlists" << endl <<
    "R: Remove songs to a playlist" << endl <<
    "C: Create a new playlist" << endl <<
    "D: Delete a playlist" << endl <<
    "W: Write to file (SAVE)" << endl <<
    "E: Exit" << endl << endl <<
    "Enter the choice: ";
}


void play_song(){
    char choice;
    cout <<
    "L: playing a playlist starting from the first song" << endl <<
    "S: playing a playlist starting from a specific song" << endl <<
    "P: playing a single song" << endl <<
    "E: Exit" << endl <<
    "Choose an option: " ;
    
    cin >> choice;
   
    book.play(choice);
}


void create_playlist(){
    int x;
    song * node = new song;
    
    cout <<
    "1) Songs of a specific style" << endl <<
    "2) Songs of a specific singer" << endl <<
    "3) A combination of existing playlists" << endl <<
    "4) A combination of existing songs" << endl << endl <<
    "Enter an option: " ;
    
    cin >> x;
    
    char pl_name[LNAME_LENGTH];
    cout << "Enter the new playlist name: " << endl;
    cin.ignore(1000, '\n');
    cin.getline(pl_name, LNAME_LENGTH);
    
    switch(x) {
        case 1:         // songs of a specific style
            char style[STYLE_LENGTH];
            cout << "Enter a style name: " << endl;
            cin.ignore(1000, '\n');
            cin.getline(style, STYLE_LENGTH);
            strcpy(node->style, style);
            strcpy(node->singer, "");
            strcpy(node->name, "");
            node->year = 0;
            book.createList(pl_name, x, node);
            break;
            
        case 2:         // songs of a specific singer
            char singer[SNAME_LENGTH];
            cout << "Enter a singer name: " << endl;
            cin.ignore(1000, '\n');
            cin.getline(singer, SNAME_LENGTH);
            strcpy(node->singer, singer);
            strcpy(node->style, "");
            strcpy(node->name, "");
            node->year = 0;
            book.createList(pl_name, x, node);
            break;
            
        case 3:         // a combination of existing playlists
            strcpy(node->style, "");
            strcpy(node->singer, "");
            strcpy(node->name, "");
            node->year = 0;
            book.createList(pl_name, x, node);
            break;
            
        case 4:         // a combination of existing songs
            strcpy(node->style, "");
            strcpy(node->singer, "");
            strcpy(node->name, "");
            node->year = 0;
            book.createList(pl_name, x, node);
            break;
            
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}


void add_song_to_playlist(){
    int n;
    bool check = false;
    playlist * traverse;
    playlist * sol = new playlist;
    song_node * tr = new song_node;
    char listname[LNAME_LENGTH];
    cout << "Enter the name of playlist which you want to add song in: ";
    cin.ignore(1000, '\n');
    cin.getline(listname, LNAME_LENGTH);
    traverse = book.start;
    while(traverse){
        if(strcmp(traverse->name, "SORTED") == 0){
            book.printSongofList(traverse);
            tr = traverse->head;
        }
        if(strcmp(traverse->name, listname) == 0){
            check = true;
            sol = traverse;
        }
        if(traverse->next == book.start)    break;
        traverse = traverse->next;
    }
    if(check){
        cout << "Enter the number of song which you want to add in " << sol->name << " : " ;
        cin >> n;
        for(int i = 0; i < n; i++){
            tr = tr->next;
        }
        book.addSong(tr->data, sol);
    }
    else{
        cout << "There is no playlist as " << listname << "." << endl;
    }
}


void delete_list(){
    int x;
    book.printList();
    cout << "Enter an option which you want to delete: ";
    cin >> x;
    book.deleteList(x);
}


void remove_song_from_playlist(){
    playlist * x = new playlist;
    int n;
    char name[LNAME_LENGTH];
    book.printList();
    cout << "Enter the name of playlist which you want to delete from: ";
    cin.ignore(1000, '\n');
    cin.getline(name, LNAME_LENGTH);
    strcpy(x->name, name);
    x->head = NULL;
    x->next = NULL;
    x->prev = NULL;
    x->songnumber = 0;
    book.printSongofList(x);
    cout << "Enter the number of song which you want to remove: ";
    cin >> n;
    book.removeSong(x, n);
}


void print_playlist(){
    book.printList();
}


void save(){
    book.writeToFile();
}
















