#include "post.h"
#include <iostream>

std::string Post::toString(){
    std::string output=message_+" Liked by "+std::to_string(likes_)+" people. ";
    return output;
}

int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}

std::string Post::getMessage(){
    return message_;
}

int Post::getLikes(){
    return likes_;
}

std::string Post::getAuthor(){
    return "";
}

bool Post::getIsPublic(){
    return true;
}

std::string IncomingPost::toString(){
    std::string prvt;
    if(isPublic_) prvt="";
    else prvt=" (private)";
    std::string output=author_+" wrote"+prvt+": "+ Post::toString();
    return output;
}

std::string IncomingPost::getAuthor(){
    return author_;
}

bool IncomingPost::getIsPublic(){
    return isPublic_;
}