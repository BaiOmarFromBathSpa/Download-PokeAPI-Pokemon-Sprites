#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main(){
    //int PokeCount = 1302;
    string Links[4];
    Links[0] = "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/";    
    Links[1] = "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/back/";

    Links[2] = "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/shiny/";    
    Links[3] = "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/back/shiny/";

    vector<string> AllPokemon;
    ifstream PokeList("AllPokemon.csv");

    if (PokeList.is_open()){
        while (!PokeList.eof()) {
            string CurrPoke = "";
            getline(PokeList, CurrPoke);
            if (CurrPoke != "") AllPokemon.push_back(CurrPoke);
        }
      PokeList.close();  
    } else { 
        cout << "Couldn't find AllPokemon.txt closing" << endl;
        exit(5318008);
    }

    cout << "\nImages Retrieved From PokeAPI's list (and github repo thingy), it claims 1301 Pokemon but only works up to 1025 [Refer to the \"AllPokemon.csv\" file].\nNOTE: There is an extended list of 277 (after the initial 1025 and this program has been updated to account for them so no worries) Pokemon i think they are variants but I'm not sure" << endl;
    
    cout << "\nWhich Pokemon do you want to START from [1-1301]: " << endl;
    int UserChoiceStart;
    cin >> UserChoiceStart;

    while (cin.fail() || UserChoiceStart > 1301 || UserChoiceStart < 1){
        cin.clear(); cin.ignore(10000,'\n');
        cout << "Not Between Range!\nWhich Pokemon do you want to START from [1-1301]: " << endl;
        cin >> UserChoiceStart;
    } cin.clear(); cin.ignore(10000,'\n');
    
    int UserChoiceEnd;
    if (UserChoiceStart == 1301) UserChoiceEnd = 1301;
    else {
        cout << "Use 1025 if you dont want the Extended list\nWhich Pokemon do you want to End with [" << UserChoiceStart << "-1301]: " << endl;
        cin >> UserChoiceEnd;

        while (cin.fail() || UserChoiceEnd > 1301 || UserChoiceEnd < UserChoiceStart){
            cin.clear(); cin.ignore(10000,'\n');
            cout << "Not Between Range!\nWhich Pokemon do you want to start from [" << UserChoiceStart << "-1301]: " << endl;
            cin >> UserChoiceEnd;
        } cin.clear(); cin.ignore(10000,'\n');
    }

    int CustomEnd = 1025; //5
    if (UserChoiceEnd < CustomEnd) CustomEnd = UserChoiceEnd;
    
    ofstream BatchScript("DownloadAllSprites");
    string Command;
    string Download;

    for (int i = UserChoiceStart-1; i < CustomEnd; i++){ //thats where the images stop idk what to tell ya 1025
        cout << AllPokemon[i] << endl;
        Command = "mkdir " + AllPokemon[i] + " && cd " + AllPokemon[i] + "\n";
        BatchScript << Command;

        for (int j = 0; j < 4; j++){
            switch (j)
            {
            case 0:
                Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[i] + "_front.png\n";
                break;
            case 1:
                Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[i] + "_back.png\n";
                break;
            case 2:
                Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[i] + "_front_shiny.png\n";
                break;
            case 3:
                Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[i] + "_back_shiny.png\n";
                break;
            }
            BatchScript << Download;
        }
        BatchScript << "cd ..\n\n";
    }
    if (UserChoiceEnd > 1025){
        int RealStart = 1025;
        if (UserChoiceStart > RealStart) RealStart = UserChoiceStart;

        for (int i = RealStart+8976-1; i < UserChoiceEnd+8976; i++){ //here we go ig
            cout << AllPokemon[RealStart] << endl;
            Command = "mkdir " + AllPokemon[RealStart] + " && cd " + AllPokemon[RealStart] + "\n";
            BatchScript << Command;

            for (int j = 0; j < 4; j++){
                switch (j)
                {
                case 0:
                    Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[RealStart] + "_front.png\n";
                    break;
                case 1:
                    Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[RealStart] + "_back.png\n";
                    break;
                case 2:
                    Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[RealStart] + "_front_shiny.png\n";
                    break;
                case 3:
                    Download = "curl " + Links[j] + to_string(i+1) + ".png -o " + AllPokemon[RealStart] + "_back_shiny.png\n";
                    break;
                }
                BatchScript << Download;
            }
            BatchScript << "cd ..\n\n";
            RealStart++;
        }
    }
    
    BatchScript.close();

    cout << "\nOK Done!! Code mostly untested to inspect file to for defects... and/or rename to add .bat extension" << endl;
    cout << "Oh btw some don't have all 4 images sooo if any come up missing it prolly isnt my fault :p" << endl;
    //system("Curl https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/back/849.png -o test.png");

    return 0;
}