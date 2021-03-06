
/*
 +   1) detect note on
 +   2) detect note off
 +   3) detect delay in ms beetwen notes
 +   4) detect tempo
 +   5) detect ppqn
 +   6) add octave shift
 +   7) add note shift
 +   8) add multitrack decoding
 +   9) add BPM change
 +  10) auto detect note channel
 +  11) add flag -c for writing note comments in file
 +  12) detect more note length bytes before 0x90 or 0x80
+/- 13) detect first/intro delay bytes (works but some times not so good)
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include "./include/MidiFile.h"
#include "./include/MTrkChunk.h"

int main(int argc, char *argv[]){
    int result = 0;
    int octaveShift = 0;
    int noteShift = 0;
    std::string fileName = "";
    int newBpm = -1;
    int debugLevel = 0;
    bool enableCommentsFlag = false;
    bool predelayFlag = false;

    while ( (result = getopt(argc,argv,"o:n:f:b:d:cp")) != -1){
        switch (result){
            case 'o': octaveShift = atoi(optarg);           break; //octave shift
            case 'n': noteShift = atoi(optarg);             break; //note shift
            case 'f': fileName = optarg;                    break; //midi file
            case 'b': newBpm = atoi(optarg);                break; //set new bpm for all files
            case 'd': debugLevel = atoi(optarg);            break; //sets debug level
            case 'c': enableCommentsFlag = true;            break; //enable note comments in output file
            case 'p': predelayFlag = true;                  break; //enable pre-delay / delay before first note
            case '?': printf("Error argument found !\n");   break; //Error handler
        };
    };

    if( fileName != "" ){
        MidiFile midiObj;
        midiObj.setFilePath(fileName);
        midiObj.setOctaveShift(octaveShift);
        midiObj.setNoteShift(noteShift);
        midiObj.setNewBpm(newBpm);
        midiObj.setDebugLevel(debugLevel);
        midiObj.setEnableCommentsTo(enableCommentsFlag);
        midiObj.setPredelayFlag(predelayFlag);
        midiObj.parseFile();
    } else {
        std::cout << "Error: No file specified" << std::endl;
    }

    return 0;
}
