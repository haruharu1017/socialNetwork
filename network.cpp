#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>

//pre: a valid int id
//post: return a pointer of corresponding user
//If no user found, return a nullptr
User* Network::getUser(int id){
    std::vector<User*>::iterator it;
    for(it=users.begin(); it!=users.end(); ++it){
        if((*it)->getId()==id){
            return *it;
        }
    }
    return nullptr;
}

//pre: a valid user object
//post: add the user to network
void Network::addUser(User* user){
    users.push_back(user);
}

//pre: two valid users' name
//post: add connection between those two
//if not found one of both of them, return -1
int Network::addConnection(std::string name1, std::string name2){
    int id1=-1, id2=-1;
    if(name1 != name2){
        for(std::vector<User*>::iterator it=users.begin(); it!=users.end(); ++it){
            if((*it)->getName()==name1){
                id1=(*it)->getId();
            }
            if((*it)->getName()==name2){
                id2=(*it)->getId();
            }
        }
        if(getUser(id1)!=nullptr&&getUser(id2)!=nullptr){
            getUser(id1)->getFriends().insert(id2);
            getUser(id2)->getFriends().insert(id1);
            return 0;
        }
    }
    return -1;
}

//pre: two valid users' name
//post: delete connection between those two
//if not found one of both of them, return -1
int Network::deleteConnection(std::string name1, std::string name2){
    int id1=-1, id2=-1;
    if(name1 != name2){
        for(std::vector<User*>::iterator it=users.begin(); it!=users.end(); ++it){
            if((*it)->getName()==name1) id1=(*it)->getId();
            if((*it)->getName()==name2) id2=(*it)->getId();
        }
        if(getUser(id1)!=nullptr&&getUser(id2)!=nullptr){
            getUser(id1)->getFriends().erase(id2);
            getUser(id2)->getFriends().erase(id1);
            return 0;
        }
    }
    return -1;
}

//pre: a valid user's name
//post: return the corresponding user's id
//if not found, return -1
int Network::getId(std::string name){
    for(std::vector<User*>::iterator it=users.begin();it!=users.end();++it){
        if((*it)->getName()==name){
            return (*it)->getId();
        }
    }
    return -1;
}

//pre: none
//post: return the size of network
int Network::numUsers(){
    return users.size();
}

//pre: a valid filename
//post: read the file's information and store it into the network
int Network::readUsers(char* fileName){
    std::ifstream file(fileName);
    if(!file.is_open()) return -1;

    std::string usersNum;
    getline(file, usersNum);

    std::string line;
    while(getline(file, line)){
        int id = std::stoi(line);
        
        getline(file, line);
        std::stringstream s1(line);
        std::string nameL, nameF, name;
        s1>>nameF; s1>>nameL; 
        name=nameF+" "+nameL;

        getline(file, line);
        int year = std::stoi(line);

        getline(file, line);
        int zc = std::stoi(line);

        getline(file, line);
        std::stringstream ss(line);
        std::set<int> conn;
        int user;
        while(ss>>user){
            conn.insert(user);
        }

        User* u = new User(id, name, year, zc,conn);
        users.push_back(u);
    }

    file.close();
    return 0;
}

//pre: a valid filename
//post: output the information into a new file
int Network::writeUsers(char* fileName){
    std::ofstream file(fileName);
    if(!file.is_open()) return -1;
    file<<users.size()<<std::endl;
    std::string fs;std::vector<User*>::iterator e;
    std::set<int>::iterator x;
    for(e=users.begin();e!=users.end();++e){
        fs="";
        for(x=(*e)->getFriends().begin();x!=(*e)->getFriends().end();++x){
            fs += std::to_string(*x)+" ";
        }

        file<<(*e)->getId()<<"\n\t"<<(*e)->getName()<<"\n\t"
        <<(*e)->getYear()<<"\n\t"<<(*e)->getZip()<<"\n\t"<<fs<<std::endl;
    }
    file.close();
    return 0;
}

//pre: valid user's id
//post: compute the shortest path between those two users
std::vector<int> Network::shortestPath(int from, int to){
    std::vector<bool> visited(numUsers(), 0);
    std::vector<int> prev(numUsers(), -1);
    std::vector<int> output;
    std::queue<int> q;

    if(from==to) {
        output.push_back(from);
        return output;
    }

    visited[from] = true;
    q.push(from);

    while (q.size() > 0) {
      int cur = q.front();
      q.pop();
      std::set<int>::iterator it;
      for (it=users[cur]->getFriends().begin(); it!=users[cur]->getFriends().end(); ++it) {
        if (!visited[(*it)]) {
          prev[(*it)] = cur;
          visited[(*it)] = true;
          q.push((*it));
        }
      }
    }
    
    if(prev[to]==-1) return std::vector<int>();
    else{
        int cur = to;
        while (cur != from) {
        output.push_back(cur);
        cur = prev[cur];
        }
        output.push_back(from);
        return output;
    }

}

//pre: valid user's id and distance
//post: find a user whose relational distance from the given user exactly matches the distance given
std::vector<int> Network::distanceUser(int from, int& to, int distance){
    std::queue<int> q;
    std::vector<bool> visited (numUsers(), 0);
    std::vector<int> dist (numUsers(), -1);
    std::vector<int> prev(numUsers(), -1);

    dist[from] = 0;
    visited[from] = true;
    q.push(from);
    to=-1;

    while (q.size() > 0) {
      int cur = q.front();
      q.pop();
      std::set<int>::iterator it;
      for (it=users[cur]->getFriends().begin(); it!=users[cur]->getFriends().end(); ++it) {
        if (!visited[(*it)]) {
          dist[(*it)] = dist[cur] + 1;
          prev[(*it)] = cur;
          visited[(*it)] = true;
          q.push((*it));
        }
      }
    }
    for(int i=0; i<dist.size(); i++){
        if(dist[i]==distance){
            to = i;
            break;
        }
    }
    
    std::vector<int> output;
    if(to==-1) return std::vector<int>();
    else{
        int cur = to;
        while (cur != from) {
        output.push_back(cur);
        cur = prev[cur];
        }
        output.push_back(from);

        return output;
    }
}

//pre: a valid user's id, no need to initialize score
//post: Compute a list of users who are most likely suggestions for the specified user to add as a friend. 
std::vector<int> Network::suggestFriends(int who, int& score){
    int to;
    std::queue<int> q;
    std::vector<bool> isFriend(numUsers(),0); 
    std::vector<int> numCommFriend(numUsers(), 0);
    std::vector<int> output;
    std::set<int>::iterator it;

    for(it=getUser(who)->getFriends().begin();it!=getUser(who)->getFriends().end();++it){
        isFriend[(*it)]=true;
    }
    
    for(int i=0; i<isFriend.size(); i++){
        if(!isFriend[i]&&i!=who){
            for(it=getUser(i)->getFriends().begin();it!=getUser(i)->getFriends().end();++it){
                if(isFriend[(*it)]) numCommFriend[i]++;
            }
        }
    }
    score=*std::max_element(numCommFriend.begin(),numCommFriend.end());
    if(score==0){
        return output;
        std::cout<<"None"<<std::endl;
    }

    for(int i=0; i<numUsers(); i++){
        if(numCommFriend[i]==score){
            output.push_back(i);
        }
    }
    return output;
}


std::vector<std::vector<int>> Network::groups(){
    std::stack<int> stck;
    std::vector<bool> visited (numUsers(), 0);
    std::vector<std::vector<int>> set;
    std::vector<int> list;
    int source = -1;

    
    while(std::find(visited.begin(), visited.end(), false) != visited.end()){
        list={};
        for(int i=0; i<users.size(); i++){
        if(!visited[i])
            source=i;
        }
        visited[source] = true;
        stck.push(source);
        list.push_back(source);

        while (stck.size() > 0) {
            int cur = stck.top();
            stck.pop();
            std::set<int>::iterator it;
            for (it=users[cur]->getFriends().begin(); it!=users[cur]->getFriends().end(); ++it) {
                if (!visited[(*it)]) {
                visited[(*it)] = true;
                list.push_back(*it);
                stck.push((*it));
                }
            }
        }
        set.push_back(list);
    }
    return set;
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){
    int msgId=0;
    for(int i=0; i<users.size(); i++){
        for(int x=0; x<users[i]->getPosts().size(); x++){
            msgId++;
        }
    }
    if(isIncoming){
        IncomingPost* ip=new IncomingPost(msgId, ownerId, message, likes, isPublic, authorName);
        users[ownerId]->addPost(ip);
    }else{
        Post* post=new Post(msgId, ownerId, message, likes);
        users[ownerId]->addPost(post);
    }
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic){
    return getUser(ownerId)->getPostsString(howMany, showOnlyPublic);
}

int Network::readPosts(char* name){
    std::ifstream file(name);
    if(!file.is_open()) return -1;

    std::string line;
    getline(file, line);

    while(getline(file, line)){
        int msgId=std::stoi(line);
        
        getline(file, line);
        std::string msg = line.substr(1);

        getline(file, line);
        int oId = std::stoi(line);

        getline(file, line);
        int lks = std::stoi(line);

        getline(file, line);
        bool isP=false;
        if(line.empty()){
            // Post
            isP=true;
            getline(file, line);
            addPost(oId, msg, lks, false, "", isP);
        }else{
            if(line.find("public")!=std::string::npos){
                isP=true;
            }
            getline(file, line);
            std::string author=line.substr(1);
            addPost(oId, msg, lks, true, author, isP);
        }
    }

    file.close();

    return 0;
}

bool Network::compare(Post*lhs, Post* rhs){
    return lhs->getMessageId()<rhs->getMessageId();
}

int Network::writePosts(char* name){
    std::vector<Post*> sortedPosts;
    std::ofstream file(name);
    if(!file.is_open()) return -1;

    for(int i=0; i<users.size(); i++){
        for(int x=0; x<users[i]->getPosts().size(); x++){
            sortedPosts.push_back(users[i]->getPosts()[x]);
        }
    }
    std::sort(sortedPosts.begin(), sortedPosts.end(), compare);

    file<<sortedPosts.size()<<std::endl;
    for(int i=0; i<sortedPosts.size(); i++){
        file<<sortedPosts[i]->getMessageId()<<std::endl 
            <<"\t"<<sortedPosts[i]->getMessage()<<std::endl 
            <<"\t"<<sortedPosts[i]->getOwnerId()<<std::endl
            <<"\t"<<sortedPosts[i]->getLikes()<<std::endl;
        if(sortedPosts[i]->getAuthor()=="") file<<"\n\n";
        else{
            if(sortedPosts[i]->getIsPublic()) file<<"\t"<<"public\n";
            else file<<"\t"<<"private\n";

            file<<"\t"<<sortedPosts[i]->getAuthor()<<std::endl;
        }
    }
    return 0;
}
