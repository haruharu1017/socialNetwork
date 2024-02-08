#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>

class Network {
public:
  Network(){}
  ~Network(){}
  User* getUser(int id);
  void addUser(User* user);
  int addConnection(std::string name1, std::string name2);
  int deleteConnection(std::string name1, std::string name2);
  int getId(std::string name);
  int numUsers();
  int readUsers(char* fileName);
  int writeUsers(char* fileName);
  std::vector<int> shortestPath(int from, int to);
  std::vector<int> distanceUser(int from, int& to, int distance);
  std::vector<int> suggestFriends(int who, int& score);
  std::vector<std::vector<int>> groups();
  void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);
  std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);
  int readPosts(char* name);
  int writePosts(char* name);
  static bool compare(Post* lhs, Post* rhs);
private:
  std::vector<User*> users;
};

#endif
