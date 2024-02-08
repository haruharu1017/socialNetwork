output: social_network.o user.o network.o post.o
	g++ -std=c++11 $^ -o $@
social_network.o: social_network.cpp
	g++ -std=c++11 -c $< -o $@
user.o: user.cpp
	g++ -std=c++11 -c $< -o $@
network.o: network.cpp
	g++ -std=c++11 -c $< -o $@
post.o: post.cpp
	g++ -std=c++11 -c $< -o $@
clean:
	rm *.o output

# output: main.o user.o network.o post.o
# 	g++ -std=c++11 $^ -o $@
# main.o: main.cpp
# 	g++ -std=c++11 -c $< -o $@
# user.o: user.cpp
# 	g++ -std=c++11 -c $< -o $@
# network.o: network.cpp
# 	g++ -std=c++11 -c $< -o $@
# post.o: post.cpp
# 	g++ -std=c++11 -c $< -o $@
# clean:
# 	rm *.o output