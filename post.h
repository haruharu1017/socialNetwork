#ifndef POST_H
#define POST_H

#include <string>

class Post{
private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;
public:
    Post(){
        messageId_=0;
        ownerId_=0;
        message_="";
        likes_=0;
    }
    Post(int messageId, int ownerId, std::string message, int likes):messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes){};
    virtual std::string toString();
    int getMessageId();
    int getOwnerId();
    std::string getMessage();
    int getLikes();
    virtual std::string getAuthor();
    virtual bool getIsPublic();

};

class IncomingPost: public Post{
public:
    IncomingPost():Post(){};
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author):Post(messageId, ownerId, message, likes), author_(author), isPublic_(isPublic){};
    std::string toString();
    std::string getAuthor();
    bool getIsPublic();
private: 
    std::string author_;
    bool isPublic_;
};

#endif