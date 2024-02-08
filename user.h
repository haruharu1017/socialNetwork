#ifndef USER_H
#define USER_H
#include <string>
#include <set>
#include "post.h"

class User {
private:
    int id;
    std::string name;
    int year;
    int zipcode;
    std::set<int> connection;
    std::vector<Post*> messages_; 
public:
    User(){};
    ~User(){};
    User(int i, std::string n, int y, int z, std::set<int>c):id(i), name(n), year(y), zipcode(z), connection(c){};

    //pre: noun
    //post: return id
    int getId(){ return id; }

    //pre: noun
    //post: return name
    std::string getName(){ return name; }

    //pre: noun
    //post: return year
    int getYear(){ return year; }

    //pre: noun
    //post: return zipcode
    int getZip(){return zipcode; }
    
    //pre: noun
    //post: return connection
    std::set<int>& getFriends(){ return connection; }
    void addFriend(int i);
    void deleteFriend(int i);

    void addPost(Post* p);
    std::vector<Post*>& getPosts() { return messages_; }
    std::string getPostsString(int howMany, bool showOnlyPublic);
};

#endif
