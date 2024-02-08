#include "user.h"

//pre: a valid user's id
//post: add the corresponding user to friend connection
void User::addFriend(int i){
    if(connection.find(i)==connection.end()){
        connection.insert(i);
    }
}

//pre: a valid user's id
//post: delete the corresponding user from friend connection
void User::deleteFriend(int i){
    if(connection.find(i)!=connection.end()){
        connection.erase(i);
    }
}

void User::addPost(Post* p){
    messages_.push_back(p);
}


std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string output="";

    if(showOnlyPublic){
            int count=0;
            for(int i=messages_.size()-1; i>=0&&count<howMany; i--){
                if(messages_[i]->getIsPublic()){
                    output+=messages_[i]->toString()+"\n\n";
                    count++;
                }
            }
    }
    else{
        if(howMany<messages_.size()){
            for(int i=messages_.size()-1; i>=messages_.size()-howMany; i--){
                output+=messages_[i]->toString()+"\n\n";
            }
        }else{
            for(int i=messages_.size()-1; i>=0; i--){
                output+=messages_[i]->toString()+"\n\n";
            }
        }
    }
    return output;
}

