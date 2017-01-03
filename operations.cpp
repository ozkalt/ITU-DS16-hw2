//
//  operations.cpp
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

#include <iostream>
#include <stdio.h>
#include "operations.h"

using namespace std;

void list::create(){
    
    // random list olusturulacak
    
    playlist * chr = new playlist;
    strcpy(chr->name, "CHRONOLOGICAL");
    chr->head = NULL;
    chr->songnumber = 0;
    
    playlist * srt = new playlist;
    strcpy(srt->name, "SORTED");
    srt->head = NULL;
    srt->songnumber = 0;
    
    playlist * temp = new playlist;
    strcpy(temp->name, "temp");
    temp->head = NULL;
    temp->songnumber = 0;
    
    chr->next = srt;
    chr->prev = temp;
    temp->next = chr;
    temp->prev = srt;
    srt->next = temp;
    srt->prev = chr;
    
    start = srt;
    
    musicbook = fopen("songbook.txt", "r");
    fseek(musicbook, 0, SEEK_SET);
    
    while (!feof(musicbook)){
        if (feof(musicbook)) break;
        
        song * k = new song;
        
        fscanf(musicbook, "%[^\t]\t%[^\t]\t%d\t%[^\n]\n", k->name, k->singer, &k->year, k->style);
        
        cout << endl << k->name << "   " << k->singer << "   " << k->year << "   " << k->style << endl;
        
        addSong(k, chr);
        addSong(k, srt);
        addSong(k, temp);
        
        delete k;
    }
    fclose(musicbook);
}


void list::play(char x){
    int num;
    playlist * traverse;
    song_node * tr;

    traverse = start;
    

    switch(x){
        case 'L': case 'l':         // playing a playlist starting from the first song
            printList();
            
            cout << endl << "Choose a playlist: " ;
            cin >> num;
            
            for (int i = 1; i < num; i++){
                traverse = traverse->next;
            }
            
            tr = traverse->head;
            
            if(tr){
                bool son;
                son = true;
                char choice;
                
                while(son){
                    cout << "Playing . . ." << endl << tr->data->name << "    " << tr->data->singer << "  " << tr->data->year << "    " << tr->data->style << endl;
                    
                    cout << "PREV (P)" << "  " << "NEXT (N)" << "   " << "EXIT (E)" << endl << "Enter an option (P, N, E): ";
                    
                    cin >> choice;
                    if(choice == 'E' || choice == 'e')
                        son = false;
                    
                    else if(choice == 'P' || choice == 'p')
                        
                        tr = tr->prev;
                    else if(choice == 'N' || choice == 'n')
                        tr = tr->next;
                    
                    else{
                        cout << "Invalid choice! Please try again: " ;
                    }
                }
            }
            
            break;
            
        case 'S': case 's':         // playing a playlist starting from a specific song
            printList();
            
            cout << endl << "Choose a playlist: " << endl;
            cin >> num;
            
            for (int i = 0; i < num; i++){
                traverse = traverse->next;
            }
            
            tr = traverse->head;
            
            printSongofList(traverse);
            
            if(tr){
                cout << "Enter a song number: " ;
                cin >> num;
                
                for (int i = 1; i < num; i++){
                    tr = tr->next;
                }
                
                bool son;
                son = true;
                char choice;
                
                while(son){
                    cout << "Playing . . ." << endl << tr->data->name << "    " << tr->data->singer << "  " << tr->data->year << "    " << tr->data->style << endl;
                    
                    cout << "PREV (P)" << "  " << "NEXT (N)" << "   " << "EXIT (E)" << endl << "Enter an option (P, N, E): ";
                    
                    cin >> choice;
                    if(choice == 'E' || choice == 'e')
                        son = false;
                    else if(choice == 'P' || choice == 'p')
                        tr = tr->prev;
                    else if(choice == 'N' || choice == 'n')
                        tr = tr->next;
                    else{
                        cout << "Invalid choice! Please try again: " ;
                    }
                }
            }
            break;
            
        case 'P': case 'p':         // playing a single song
            while(traverse){
                if(strcmp(traverse->name, "SORTED") == 0){
                    break;
                }
                
                if(traverse->next == start) break;
                traverse = traverse->next;
            }
            
            printSongofList(traverse);
            
            cout << "Enter a song number: " ;
            cin >> num;
            tr = traverse->head;
            
            for (int i = 1; i < num; i++){
                tr = tr->next;
            }
            
            cout << "Playing . . ." << endl << tr->data->name << "    " << tr->data->singer << "  " << tr->data->year << "    " << tr->data->style << endl;
            break;
            
        case 'E': case 'e':         // Exit
            cout << "Main Menu . . ." << endl;
            break;
            
        default:
            cout << "Invalid choice..." << endl;
            break;
    }
    
}


void list::addSong(song * ns, playlist * x){
    song_node * sn = new song_node;
    sn->data = ns;
    sn->parent = x;
    
    playlist * traverse;
    traverse = start;
    
    bool check = true;
    
    while(traverse){
        if(strcmp(traverse->name, x->name) == 0 && strcmp(traverse->name, "SORTED") == 0){
            if(traverse->head == NULL){
                traverse->head = sn;
                traverse->head->next = traverse->head;
                traverse->head->prev = traverse->head;
            }
            else{
                song_node * tr;
                tr = traverse->head;
                while(strcmp(sn->data->singer, tr->data->singer) > 0){
                    check = false;
                    tr = tr->next;
                    if(tr == traverse->head)    break;
                }
            
                while(strcmp(tr->data->singer, sn->data->singer) == 0 && strcmp(sn->data->name, tr->data->name) >= 0){
                    check = false;
                    tr = tr->next;
                    if(tr == traverse->head)    break;
                }
            
                sn->next = tr;
                sn->prev = tr->prev;
                tr->prev->next = sn;
                tr->prev = sn;
                if(check){
                    if(tr == traverse->head){
                        traverse->head = sn;
                    }
                }
            }
            traverse->songnumber++;
        }
        
        else if(strcmp(traverse->name, x->name) == 0){
            if(traverse->head == NULL){
                traverse->head = sn;
                traverse->head->next = traverse->head;
                traverse->head->prev = traverse->head;
                traverse->songnumber++;
            }
            else{
                traverse->head->prev->next = sn;
                sn->next = traverse->head;
                sn->prev = traverse->head->prev;
                traverse->head->prev = sn;
                traverse->songnumber++;
            }
        }
    
        if (traverse->next == start) break;
        traverse = traverse->next;
    }
}


void list::createList(char * ln, int x, song * nsn){
    playlist * npl = new playlist;      // new playlist
    strcpy(npl->name, ln);
    npl->songnumber = 0;
    npl->head = NULL;
    
    start->prev->next = npl;
    npl->prev = start->prev;
    npl->next = start->next;
    start->prev = npl;
    
    playlist * traverse;
    song_node * tr;

    int input;
    bool end = false;
    
    switch(x) {
        case 1:         // songs of a specific style
            traverse = start;
            while(traverse){
                if(strcmp(traverse->name, "SORTED") == 0){
                    tr = traverse->head;
                    while(tr){
                        if(strcmp(tr->data->style, nsn->style) == 0){
                            strcpy(nsn->singer, tr->data->singer);
                            nsn->year = tr->data->year;
                            strcpy(nsn->name, tr->data->name);
                            addSong(nsn, npl);
                        }
                        if(tr->next == traverse->head)  break;
                        tr = tr->next;
                    }
                    return;
                }
                if(traverse->next == start) break;
                traverse = traverse->next;
            }
            break;
        case 2:         // songs of a specific singer
            traverse = start;
            while(traverse){
                if(strcmp(traverse->name, "SORTED") == 0){
                    tr = traverse->head;
                    while(tr){
                        if(strcmp(tr->data->singer, nsn->singer) == 0){
                            strcpy(nsn->style, tr->data->style);
                            nsn->year = tr->data->year;
                            strcpy(nsn->name, tr->data->name);
                            addSong(nsn, npl);
                        }
                        if(tr->next == traverse->head)  break;
                        tr = tr->next;
                    }
                    return;
                }
                if(traverse->next == start) break;
                traverse = traverse->next;
            }
            break;
            
        case 3:         // a combination of existing playlists
            break;
            
        case 4:         // a combination of existing songs
            traverse = start;
            while(traverse){
                if(strcmp(traverse->name, "SORTED") == 0){
                    printSongofList(traverse);
                    cout << endl << "Enter the number of songs which you want to add list you created (to end enter zero): " << endl;
                    while(!end){
                        cin >> input;
                        if(input == 0){
                            end = true;
                            break;
                        }
                        
                        tr = traverse->head;
                        for(int i = 0; i < input; i++){
                            tr = tr->next;
                        }
                        strcpy(nsn->singer, tr->data->singer);
                        strcpy(nsn->style, tr->data->style);
                        nsn->year = tr->data->year;
                        strcpy(nsn->name, tr->data->name);
                        addSong(nsn, npl);

                    }
                }
                if(traverse->next == start) break;
                traverse = traverse->next;
            }
            break;
            
        default:
            
            break;
    }

}


void list::removeSong(playlist * fl, int x){
    playlist * traverse = start;
    
    if(strcmp(fl->name, "SORTED") == 0 || strcmp(fl->name, "CHRONOLOGICAL") == 0 || strcmp(fl->name, "RANDOM") == 0){
        cout << "You cannot remove any song from SORTED, CHRONOLOGICAL or RANDOM playlists." << endl;
    }
    else{
        while(traverse){
            if(strcmp(traverse->name, fl->name) == 0){
                song_node * tr;
                tr = traverse->head;
                
                for(int j = 1; j < x; j++){
                    tr = tr->next;
                }
                
                traverse->songnumber--;
                
                tr->prev->next = tr->next;
                tr->next->prev = tr->prev;
                
                tr = NULL;
            }
            if(traverse->next == start) break;
            traverse = traverse->next;
        }
    }
}


void list::deleteList(int dpl){
    playlist * traverse = start;
    bool check = true;
    
    for(int i = 1; i < dpl; i++){
        if(traverse->next == start){
            cout << "Too big number." << endl;
            check = false;
            break;
        }
        traverse = traverse->next;
    }
    
    if(check){
        if(strcmp(traverse->name, "SORTED") == 0 || strcmp(traverse->name, "CHRONOLOGICAL") == 0 || strcmp(traverse->name, "RANDOM") == 0){
            cout << "You cannot delete SORTED, CHRONOLOGICAL or RANDOM playlists." << endl;
        }
        else{
            traverse->prev->next = traverse->next;
            traverse->next->prev = traverse->prev;
            
            for(int j = 0; j<traverse->songnumber; j++){
                removeSong(traverse, j);
            }
        
        delete traverse;
        }
    }
}


void list::printList(){
    playlist * traverse = start;
    
    int i;
    i = 1;
    
    cout << "PLAYLISTS:" << endl;
    
    while(traverse){
        cout << i << ". " << traverse->name << endl;
        printSongofList(traverse);
        if(traverse->next == start)    break;
        traverse = traverse->next;
        i++;
    }
}


void list::printSongofList(playlist * pl){
    playlist * traverse = start;
    
    int i;
    i = 1;
    
    cout << "PLAYLIST: " << pl->name << endl;
    
    while(traverse){
        if(strcmp(traverse->name, pl->name) == 0){
            song_node * tr;
            tr = traverse->head;
            for(int j = 1; j <= traverse->songnumber; j++){
                cout << j << ". " << tr->data->name << "    " << tr->data->singer << "  " << tr->data->year << "    " << tr->data->style << endl;
                tr = tr->next;
            }
        }
        
        if(traverse->next == start)    break;
        traverse = traverse->next;
    }
}


void list::writeToFile(){
    playlist * traverse = start;
    song_node * tr;
    musicbook = fopen("songbook.txt", "a+");
    fseek(musicbook, 0, SEEK_SET);

    
    while(traverse){
        if(traverse->next == start) break;
        if(strcmp(traverse->name, "SORTED") != 0 && strcmp(traverse->name, "CHRONOLOGICAL") != 0 && strcmp(traverse->name, "RANDOM") != 0){
            fprintf(musicbook, "\n***\n%s\n", traverse->name);
            tr = traverse->head;
            for(int i = 0; i < traverse->songnumber; i++){
                fprintf(musicbook, "%s\t%s\t%d\t%s\n", tr->data->name, tr->data->singer, tr->data->year, tr->data->style);
                tr = tr->next;
            }
        }
        
        traverse = traverse->next;
    }
    
    fclose(musicbook);
}


void list::close(){
    writeToFile();
    playlist * traverse, * deleted;
    song_node * tr, * del;
    traverse = start;
    traverse->prev->next = NULL;
    while(traverse){
        if(traverse->head){
            tr = traverse->head;
            tr->prev->next = NULL;
            while(tr){
                del = tr;
                tr = tr->next;
                delete del;
            }
        }
        deleted = traverse;
        traverse = traverse->next;
        delete deleted;
    }
}


















