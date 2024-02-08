#include <iostream>
#include <sstream>
#include "user.h"
#include "network.h"
using namespace std;

int main(int argc, char* argv[]){
    Network network;
    network.readUsers(argv[1]);
    network.readPosts(argv[2]);
    cout<<"Here are the 7 actions this program supports, enter the "
    <<"indicating number to run your command:\n"
    <<"1. Add a user.\n2. Add friend connection.\n"
    <<"3. Delete friend connection.\n4. Print users.\n"
    <<"5. Print Friends.\n6. Write to file.\n7. Compute the shortest relational distance\n"
    <<"8. Find users at given distance\n9. Friend Suggestions\n"
    <<"10. Groups with DFS\n11. View the posts"
    <<"\n12. Exit\nYour choice: ";
    int choice;cin>>choice;cin.ignore();
    while(choice<=11&&choice>0){
        if(choice==1){
            string info, nameL, nameF, name;
            int year, zc;
            cout<<"——————Add a user——————\nenter user's information (name, birth year, zipcode):";
            getline(cin, info);
            stringstream ss(info);
            ss>>nameF>>nameL>>year>>zc;
            name=nameF+" "+nameL;
            User* newUser = new User(network.numUsers(), name, year, zc, set<int>{});
            network.addUser(newUser);
            cout<<"The command has been successfully executed! "<<endl;
        }else if(choice==2){
            string nameF1, nameL1, nameF2, nameL2, name1, name2, info;
            cout<<"——————Add friend connection——————\nenter the connection (two users' name) you want to connect: ";
            getline(cin, info);
            stringstream ss(info); 
            ss>>nameF1>>nameL1>>nameF2>>nameL2;
            name1=nameF1+" "+nameL1; name2=nameF2+" "+nameL2;
            if(network.addConnection(name1, name2)==-1){
                cout<<"Error: Not found the user(s)\n";
            }else{
                network.addConnection(name1, name2);
                cout<<"The command has been successfully executed! "<<endl;
            }
        }else if(choice==3){
            string nameF1, nameL1, nameF2, nameL2, name1, name2, info;
            cout<<"——————Delete friend connection——————\nenter the connection (two users' name) you want to delete: ";
            getline(cin, info);
            stringstream ss(info); 
            ss>>nameF1; ss>>nameL1; ss>>nameF2; ss>>nameL2;
            name1=nameF1+" "+nameL1; name2=nameF2+" "+nameL2;
            if(network.deleteConnection(name1, name2)==-1){
                cout<<"Error: Not found the user(s)\n";
            }else{
                network.deleteConnection(name1, name2);
                cout<<"The command has been successfully executed! "<<endl;
            }
        }else if(choice==4){
            cout<<"——————Print users——————\n";
            for(int i=0; i<network.numUsers(); i++){
                cout<<network.getUser(i)->getId()<<" "<<network.getUser(i)->getName()<<endl;
            }
        }else if(choice==5){
            string nameF, nameL, name, info;
            cout<<"——————Print friends——————\nenter the user's name to print their friends: ";
            getline(cin, info);
            stringstream ss(info);
            ss>>nameF>>nameL; name=nameF+" "+nameL;
            if(network.getId(name)==-1){
                cout<<"Error: Not found the user\n";
            }else{
                set<int> friends = network.getUser(network.getId(name))->getFriends();
                for(set<int>::iterator it=friends.begin(); it!=friends.end(); ++it){
                    cout<<(*it)<<" "<<network.getUser(*it)->getName()<<endl;
                }
            }
        }else if(choice==6){
            string file=""; char* fileName = new char[file.length()+1]; 
            cout<<"——————Write to file——————\nprovide a filename to write the user data to: ";
            getline(cin, file);
            for(int i=0; i<file.length(); i++) fileName[i]=file[i];
            network.writeUsers(fileName); file=""; delete[] fileName;
            cout<<"The command has been successfully executed! "<<endl;
        }else if(choice==7){
            string nameF1, nameL1, nameF2, nameL2, name1, name2, info;
            cout<<"——————Shortest path——————\nenter two user's names you want to find the distance: ";
            getline(cin, info);
            stringstream ss(info);
            ss>>nameF1>>nameL1>>nameF2>>nameL2;
            name1=nameF1+" "+nameL1; name2=nameF2+" "+nameL2;
            int id1 = network.getId(name1);
            int id2 = network.getId(name2);
            vector<int> output = network.shortestPath(id1, id2);
            if(id1==-1||id2==-1){
                cout<<"None"<<endl;
            }else{
                if(output.size()==0){                        
                    cout<<"None"<<endl;
                }else if(output.size()==1){
                    cout<<"Distance: 0\n"<<name1<<endl;
                }else{
                    cout<<"Distance: "<<output.size()-1<<endl;
                    string arrow="";
                    for(int i=output.size()-1; i>=0; i--){
                        cout<<arrow<<network.getUser(output[i])->getName();                            arrow=" -> ";
                    }
                    cout<<endl;
                }
            }
        }else if(choice==8){
            string nameF, nameL, name, info; int to, dist;
            cout<<"——————User at a given Distance——————\nenter the user's name to print their friends: ";
            getline(cin, info);
            stringstream ss(info);
            ss>>nameF>>nameL>>dist; name=nameF+" "+nameL;
            int id = network.getId(name);
            vector<int> users=network.distanceUser(id, to, dist);
            if(to==-1){
                cout<<"User not found"<<endl;
            }else{
                cout<<name;
                for(int i=network.distanceUser(id, to, dist).size()-2; i>=0; i--){
                    cout<<" -> "<<network.getUser(network.distanceUser(id, to, dist)[i])->getName();                        }
                    cout<<endl;
            }
        }else if(choice==9){
            string nameF, nameL, name, info; int score;
            cout<<"——————Friend Suggestions——————\nenter the user's name to get suggestions: ";
            getline(cin, info);
            stringstream ss(info);
            ss>>nameF>>nameL; name=nameF+" "+nameL;
            int id = network.getId(name);
            vector<int> friends=network.suggestFriends(id, score);
            cout<<"The suggested friend(s) is/are: "<<endl;
            for(int i=0; i<friends.size(); i++){
                cout<<network.getUser(friends[i])->getName()<<" Score: "<<score<<endl;
            }
        }else if(choice==10){

            for(int i=0; i<network.groups().size(); i++){
                cout<<"Set "<<i+1<<" => ";
                string comma="";
                for(int x=0; x<network.groups()[i].size();x++){
                    cout<<comma<<network.getUser(network.groups()[i][x])->getName();
                    comma=", ";
                }
                cout<<endl;
            }
        }else if(choice==11){
            string nameF, nameL, name, info; int num;
            cout<<"——————View the posts——————\nenter the user's name to view their posts: ";
            getline(cin, info);
            stringstream ss(info);
            ss>>nameF>>nameL>>num; name=nameF+" "+nameL;
            int id = network.getId(name);
            cout<<network.getPostsString(id, num, false)<<endl;
        }
    cout<<"Here are the 7 actions this program supports, enter the "
    <<"indicating number to run your command:\n"
    <<"1. Add a user.\n2. Add friend connection.\n"
    <<"3. Delete friend connection.\n4. Print users.\n"
    <<"5. Print Friends.\n6. Write to file.\n7. Compute the shortest relational distance\n"
    <<"8. Find users at given distance\n9. Friend Suggestions\n"
    <<"10. Groups with DFS\n11. View the posts"
    <<"\n12. Exit\nYour choice: ";
        cin>>choice;cin.ignore();
    }
}