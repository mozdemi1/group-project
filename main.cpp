#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <vector>
using namespace std;

//getopt function that takes teams -i <input-filename> -s <player1-name> \ -d <player2-name> -t <team-name> as the terminal input.
string inputFile;
string player1Name;
string player2Name;
string teamName;

class Node {
    public:
        string nodePlayerName;
        string nodeTeamName;
        string nodeYearData;
    private:
};

class playerNode {
    public:
        string playerName;
        bool visited;
        vector<teamNode>teamEdges;
    private:
};

class teamNode {
    public:
        string teamName;
        bool visited;
        string year;
        vector<playerNode> playerEdges;
    private:
};
class Graph{
    
};

vector<Node> nodes;
vector<playerNode> playerNodes;
vector<teamNode> teamNodes;

//function to sort the vector of nodes from highest to lowest year.
void sortNodes() {
    for(long unsigned int i = 0; i < nodes.size(); i++) {
        for(long unsigned int j = 0; j < nodes.size(); j++) {
            if(nodes[i].nodeYearData > nodes[j].nodeYearData) {
                Node temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }
}

void getopt(int argc, char *argv[], const char *optstring)
{
    int c;
    int option_index = 0;
    static struct option long_options[] =
    {
        {"input", required_argument, 0, 'i'},
        {"player1", required_argument, 0, 's'},
        {"player2", required_argument, 0, 'd'},
        {"team", required_argument, 0, 't'},
        {0, 0, 0, 0}
    };
    while((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        switch(c)
        {
            case 'i':
            {
                inputFile = optarg;
                ifstream inFile(inputFile);
                //case 0a solved here.
                if(!inFile) //rejects if file not found
                {
                    cout << "Unable to open file";
                    exit(1);
                }

                else if(inFile.peek() == EOF) //rejects if file is empty
                {
                    cout << "File is empty" << endl;
                }
                break;
            }
            case 's':
            {
                player1Name = optarg;
                break;
            }
            case 'd':
            {
                player2Name = optarg;
                break;
            }
            case 't':
            {
                teamName = optarg;
                break;
            }
            default:
            {
                cout << "Usage: teams [-i <input-filename>] [-s <player1-name>] \\ [-d <player2-name>] [-t <team-name>]\n" << endl;
            }
        }
    }
}


void checkCases()
{
    //case 0a. working.
    if(inputFile == "")
    {
        cout<< "A file is required at minimum." << endl;
        cout << "Usage: teams [-i <input-filename>] [-s <player1-name>] \\ [-d <player2-name>] [-t <team-name>]\n" << endl;
        exit(1);
    }
    //case 0b. working.
    if(player2Name != "")\
    {
        if(player1Name == "" && teamName == "")
        {
            cout << "If player2 is provided, player1 is required as well!" << endl;
            cout << "Usage: teams [-i <input-filename>] [-s <player1-name>] \\ [-d <player2-name>] [-t <team-name>]\n" << endl;
        }
    }

    //case 1. working.
    if(inputFile != "")
    {
        if(player1Name == "" && player2Name == "" && teamName == "")
        {
            //print out file contents exactly to terminal.
            ifstream inFile(inputFile);
            string line;
            while(getline(inFile, line))
            {
                cout << line << endl;
            }
        }
    }

    //case 2a solved here. working.
    if(player1Name != "")
    {
        if(player2Name == "" && teamName == "")
        {
            //sortNodes();
            //print out all nodes with player1Name
            for(long unsigned int i = 0; i < nodes.size(); i++)
            {
                if(nodes[i].nodePlayerName == player1Name)
                {
                    cout << nodes[i].nodePlayerName << " played for the " << nodes[i].nodeTeamName << " " << nodes[i].nodeYearData << endl;
                }
                // else {
                //     cout << player1Name << " does not appear in the input file." << endl;
                // }
            }
        }
    }

    //case 2b solved here.
    if(player1Name != "" && player2Name == "" && teamName != "")
    {
        //print out all nodes where both player1Name and teamName are the same.
        //sortNodes();
        int flag =0;
        for(long unsigned int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i].nodePlayerName == player1Name && nodes[i].nodeTeamName == teamName)
            {
                cout << nodes[i].nodePlayerName << " played for the " << nodes[i].nodeTeamName << " " << nodes[i].nodeYearData << endl;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            cout << player1Name << " has never played for the " << teamName << endl;
        }
    }

    //case 3 solved here.
    if(player1Name == "" && player2Name == "" && teamName != "")
    {
        //keep a vector and store all nodes with teamName.
        int flag = 0;
        vector<Node> teamNodes;
        for(long unsigned int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i].nodeTeamName == teamName)
            {
                teamNodes.push_back(nodes[i]);
            }
        }

        //find how many uniquie players are in the teamNodes vector.
        vector<string> uniquePlayers;
        for(long unsigned int i = 0; i < teamNodes.size(); i++)
        {
            int flag = 0;
            for(long unsigned int j = 0; j < uniquePlayers.size(); j++)
            {
                if(teamNodes[i].nodePlayerName == uniquePlayers[j])
                {
                    flag = 1;
                }
            }
            if(flag == 0)
            {
                uniquePlayers.push_back(teamNodes[i].nodePlayerName);
            }
        }

        //find how many times each player appears in the teamNodes vector.
        vector<int> playerAppearances;
        for(long unsigned int i = 0; i < uniquePlayers.size(); i++)
        {
            int appearances = 0;
            for(long unsigned int j = 0; j < teamNodes.size(); j++)
            {
                if(uniquePlayers[i] == teamNodes[j].nodePlayerName)
                {
                    appearances++;
                }
            }
            playerAppearances.push_back(appearances);
        }

        //print out the player and number of appearances.
        for(long unsigned int i = 0; i < uniquePlayers.size(); i++)
        {
            cout << uniquePlayers[i] << " played " << playerAppearances[i] << " years for the " << teamName << "." << endl;
        }
    }

    //case 4a solved here.
    if(player1Name != "" && player2Name != "" && teamName == "")
    {
        //testing functions
        for (long unsigned int i = 0; i < teamNodes.size(); i++)
        {
            cout << teamNodes[i].teamName << " " << teamNodes[i].year << endl;
            //print out each teamNodes playerEdges vector.
            for (long unsigned int j = 0; j < teamNodes[i].playerEdges.size(); j++)
            {
                cout << teamNodes[i].playerEdges[j].playerName << endl;
            }
        }


    }
    vector<playerNode>given2;
    int flgd=0;
    //case 4b solved
    if(player1Name != "" && player2Name!=""&& teamName!=""){
        for ( unsigned int i = 0; i<playerNodes.size();i++){
            if (playerNodes[i].playerNode.playerName==player1Name||playerNodes[i].playerNode.playerName==player2Name){
                given2.push_back(playerNodes[i]);
            }
        }
        
            for(unsigned int k = 0 ; k<given2[0].teamEdges.size();k++){
                for(unsigned int l = 0; l<given2[1].teamEdges.size();l++){
                    if(given2[0].teamEdges[k].teamName==given2[1].teamEdges[l].teamName&&given2[0].teamEdges[k].year==given2[1].teamEdges[l].year){
                        cout<<given2[0].playerName<<" and "<<given2[1].playerName<<" played together on "<<given2[0].teamEdges[k].year<<" for "<< given2[0].teamEdges[k].teamName<< endl;
                        flgd=1;
                    }
                    
                }
            }
            if (flgd=0){
                cout<<" They never played together for "<<given2[0].teamEdges[k].teamName<<endl;
            }
        }
        

        
    
    


    

}

//parser works. DO NOT TOUCH.
void parser(string inputFile) {

    ifstream inFile(inputFile);
    string line;
    stringstream ss(line);

    while(getline(inFile, line)) {
        size_t pos = line.find(",");
        string name = line.substr(0, pos);
        string str2 = line.substr(pos+1, line.size());
        size_t pos2 = str2.find(",");
        string team = str2.substr(0, pos2);
        string year = str2.substr(pos2+1, str2.size());

        // cout << name << endl;
        // cout << team << endl;
        // cout << year << endl;

        //create a new node with the name, team, and year for each line.
        Node newNode;
        newNode.nodePlayerName = name;
        newNode.nodeTeamName = team;
        newNode.nodeYearData = year;
        //push the new node into the vector of nodes.
        nodes.push_back(newNode);

        //create a teamNode for each unique team and each year they existed.
        int flag = 0;
        for(long unsigned int i = 0; i < teamNodes.size(); i++)
        {
            if(teamNodes[i].teamName == team && teamNodes[i].year == year)
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            teamNode newTeamNode;
            newTeamNode.teamName = team;
            newTeamNode.year = year;
            teamNodes.push_back(newTeamNode);
        }

        //create a playerNode for each unique player.
        flag = 0;
        for(long unsigned int i = 0; i < playerNodes.size(); i++)
        {
            if(playerNodes[i].playerName == name)
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            playerNode newPlayerNode;
            newPlayerNode.playerName = name;
            playerNodes.push_back(newPlayerNode);
        }
        //if a player played for a team in a year, add that playerNode to the respective teams playerEdges vector.
        for(long unsigned int i = 0; i < teamNodes.size(); i++)
        {
            if(teamNodes[i].teamName == team && teamNodes[i].year == year)
            {
                for(long unsigned int j = 0; j < playerNodes.size(); j++)
                {
                    if(playerNodes[j].playerName == name)
                    {
                        teamNodes[i].playerEdges.push_back(playerNodes[j]);
                        playerNodes[j].teamEdges.push_back(teamNodes[i]);
                    }
                }
            }
        }

    }
    


}

int main(int argc, char *argv[])
{
    getopt(argc, argv, "i:s:d:t:");
    sortNodes();
    parser(inputFile);
    checkCases();

}//main closing bracket

//test
