#ifndef _GRAPH_HPP_ 
#define _GRAPH_HPP_

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

template<typename T>
struct Edge {
  T from;
  T to;
  int dist;
  Edge(T f, T t, int d): from(f), to(t), dist(d) {
  }
  bool operator<(const Edge<T>& e) const;
  bool operator>(const Edge<T>& e) const;
  template<typename U>
  friend std::ostream& operator<<(std::ostream& out, const Edge<U>& e);
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Edge<T>& e) {
  out << e.from << " -- " << e.to << " (" << e.dist << ")";
  return out;
}

template<typename T>
bool Edge<T>::operator<(const Edge<T>& e) const{
    if(dist<e.dist)
        return true;

    return false;
}

template<typename T>
bool Edge<T>::operator>(const Edge<T>& e) const{

    if(dist>e.dist)
        return true;

    return false;
}

template <typename T>
class Graph {

public:
  int directedGraph;
  vector<pair<T,list<pair<T, int>>>> adjacencyList;

  Graph(bool isDirectedGraph = true);
  bool contains(const T& info);
  bool addVtx(const T& info);
  bool rmvVtx(const T& info);
  bool containsEdg(const T& from, const T& to);
  bool addEdg(const T& from, const T& to, int distance);
  bool rmvEdg(const T& from, const T& to);
  list<T> dfs(const T& info) const;
  list<T> dfs(bool* visited, list<T> dfsList, const T& info) const;
  list<T> bfs(const T& info) const;
  list<Edge<T>> mst();
  template<class U>
  friend int findposition(vector<pair<T,list<pair<T, int>>>> adjacencyList, const U& info);
  
  bool print2DotFile(const char *filename) const;
  list<T> dijkstra(const T& from, const T& to);
};

template <typename T>
Graph<T>::Graph(bool isDirectedGraph){

    if(isDirectedGraph){
        directedGraph=1;
    }
    else{
        directedGraph=0;
    }

}

template <typename T>
bool Graph<T>::contains(const T& info){

    for(unsigned int i=0; i < adjacencyList.size(); i++){
        if(adjacencyList[i].first==info){
            return true;
        }
    }

    return false;
}

template <typename T>
bool Graph<T>::addVtx(const T& info){

    if(this->contains(info)){
        return false;
    }

    list<pair<T, int>> adjacency;
    adjacencyList.push_back(make_pair(info, adjacency));

    return true;
}

template <typename T>
bool Graph<T>::rmvVtx(const T& info){


   for(unsigned int i=0; i < adjacencyList.size(); i++){
        rmvEdg(adjacencyList[i].first, info);
   }

   for(unsigned int i=0; i < adjacencyList.size(); i++){
        if(adjacencyList[i].first==info){
            adjacencyList.erase(adjacencyList.begin()+i);
            return true;
        }
   }

   return false;
}

template <typename T>
bool Graph<T>::addEdg(const T& from, const T& to, int distance){

    int unsigned i;

    if(directedGraph==1){
       if(this->contains(from)&&this->contains(to)&&(!this->containsEdg(from, to))){
        for(i=0; i < adjacencyList.size(); i++){
            if(adjacencyList[i].first==from){
                adjacencyList[i].second.push_back(make_pair(to, distance));
                break;
            }
        }

        list<pair<T, int>> duplicate(adjacencyList[i].second);
        adjacencyList[i].second.clear();

        for(unsigned int j=0; j < adjacencyList.size(); j++){
             for(auto it = duplicate.begin();it != duplicate.end(); ++it){
                if(adjacencyList[j].first==(*it).first){
                   adjacencyList[i].second.push_back(*it);
                }
             }
        }

        return true;
       }
    }
    else if(directedGraph==0){
       if(this->contains(from)&&this->contains(to)&&(!this->containsEdg(from, to))){

        for(i=0; i < adjacencyList.size(); i++){
            if(adjacencyList[i].first==from){
                adjacencyList[i].second.push_back(make_pair(to, distance));
                break;
            }
        }

        list<pair<T, int>> duplicate(adjacencyList[i].second);
        adjacencyList[i].second.clear();

        for(unsigned int j=0; j < adjacencyList.size(); j++){
             for(auto it = duplicate.begin();it != duplicate.end(); ++it){
                if(adjacencyList[j].first==(*it).first){
                   adjacencyList[i].second.push_back(*it);
                }
             }
        }

        for(i=0; i < adjacencyList.size(); i++){
            if(adjacencyList[i].first==to){
                adjacencyList[i].second.push_back(make_pair(from, distance));
                break;
            }
        }

        duplicate=(adjacencyList[i].second);
        adjacencyList[i].second.clear();

        for(unsigned int j=0; j < adjacencyList.size(); j++){
             for(auto it = duplicate.begin();it != duplicate.end(); ++it){
                if(adjacencyList[j].first==(*it).first){
                   adjacencyList[i].second.push_back(*it);
                }
             }
        }

        return true;
       }
    }

    return false;

}

template <typename T>
bool Graph<T>::rmvEdg(const T& from, const T& to){

    if(directedGraph==1){
       if(this->containsEdg(from, to)){
        for(unsigned int i=0; i < adjacencyList.size(); i++){
            for(typename list<pair<T, int>>::iterator it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
                if((adjacencyList[i].first==from)&&((*it).first==to)){
                   adjacencyList[i].second.remove((*it));
                   break;
                }
            }
        }

        return true;
       }
    }
    else if(directedGraph==0){
       if(this->containsEdg(from, to)){
        for(unsigned int i=0; i < adjacencyList.size(); i++){
            for(typename list<pair<T, int>>::iterator it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
                if(((adjacencyList[i].first==from)||(adjacencyList[i].first==to))&&(((*it).first==from)||((*it).first==to))){
                    adjacencyList[i].second.remove((*it));
                    break;
                }
            }
        }

        for(unsigned int i=0; i < adjacencyList.size(); i++){
            for(typename list<pair<T, int>>::iterator it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
                if(((adjacencyList[i].first==from)||(adjacencyList[i].first==to))&&(((*it).first==from)||((*it).first==to))){
                    adjacencyList[i].second.remove((*it));
                    break;
                }
            }
        }

        return true;
       }
    }

    return false;

}

template <typename T>
bool Graph<T>::containsEdg(const T& from, const T& to){

    for(unsigned int i=0; i < adjacencyList.size(); i++){
        for(typename list<pair<T, int>>::iterator it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
            if((adjacencyList[i].first==from)&&((*it).first==to)){
              return true;
            }
        }
    }
    return false;
}

template <typename T>
bool Graph<T>::print2DotFile(const char *filename) const{

    ofstream file1;
    file1.open(filename);

    if(file1.is_open()){

        if(directedGraph==1){
            file1 << "digraph G {\n";
            file1 << "rankdir=LR\n";

            for(unsigned int i=0; i < adjacencyList.size(); i++){
                for(auto it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
                    file1 << adjacencyList[i].first;
                    file1 << (" -> ");
                    file1 << ((*it).first);
                    file1 << (" [label=\"");
                    file1 << ((*it).second);
                    file1 << ("\"]\n");
                }
            }

            file1 << "}";
            file1.close();
        }
        else{
            file1 << "strict graph G {\n";
            file1 << "rankdir=LR\n";

            for(unsigned int i=0; i < adjacencyList.size(); i++){
                for(auto it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
                    file1 << adjacencyList[i].first;
                    file1 << (" -- ");
                    file1 << ((*it).first);
                    file1 << (" [label=\"");
                    file1 << ((*it).second);
                    file1 << ("\"]\n");
                }
            }

            file1 << "}";
            file1.close();
        }

    return true;
    }
    else{
        return false;
    }

}

template <typename T>
int findposition(vector<pair<T,list<pair<T, int>>>> adjacencyList, const T& info){

    for(unsigned int i=0; i < adjacencyList.size(); i++){
        if(adjacencyList[i].first==info){
            return i;
        }
    }

    return -1;
}

template <typename T>
list<T> Graph<T>::bfs(const T& info)const{

  bool* visited = new bool[adjacencyList.size()];
  for (unsigned int i = 0; i < adjacencyList.size(); i++)
    visited[i] = false;

  list<T> bfsList;
  list<T> queue;

  visited[findposition(adjacencyList, info)] = true;
  queue.push_back(adjacencyList[findposition(adjacencyList, info)].first);

  while (!queue.empty()) {
    T currVertex = queue.front();
    queue.pop_front();
    bfsList.push_back(currVertex);

    for(auto it = adjacencyList[findposition(adjacencyList, currVertex)].second.begin();it != adjacencyList[findposition(adjacencyList,currVertex)].second.end(); ++it) {
      T adjVertex = (*it).first;
      if (!visited[findposition(adjacencyList, adjVertex)]) {
        visited[findposition(adjacencyList, adjVertex)] = true;
        queue.push_back(adjVertex);
      }
    }
  }

  return bfsList;
}

template <typename T>
list<T> Graph<T>::dfs(const T& info) const{

  bool* visited = new bool[adjacencyList.size()];
  for (unsigned int i = 0; i < adjacencyList.size(); i++)
    visited[i] = false;

  list<T> dfsList;
  dfsList.push_back(info);

  return dfs(visited, dfsList, info);

}

template <typename T>
list<T> Graph<T>::dfs(bool* visited, list<T> dfsList, const T& info) const{

  visited[findposition(adjacencyList, info)]=true;

  for(auto it = adjacencyList[findposition(adjacencyList, info)].second.begin();it != adjacencyList[findposition(adjacencyList,info)].second.end(); ++it) {
    if (!visited[findposition(adjacencyList,(*it).first)]){
      dfsList.push_back((*it).first);
      dfsList = dfs(visited, dfsList,(*it).first);

    }
  }

  return dfsList;
}

template <typename T>
list<T> Graph<T>::dijkstra(const T& from, const T& to){

    double *distance = new double[adjacencyList.size()];
    T *previous = new T[adjacencyList.size()];
    list<T> dijkstraResult;

    for(unsigned int i=0;i<adjacencyList.size();i++){
        if(adjacencyList[i].first==from){
            distance[i] = 0;
        }
        else{
            distance[i] = std::numeric_limits<double>::infinity();
        }
    }

    for(unsigned int i=0;i<adjacencyList.size();i++){
        previous[i]= {};
    }

    vector<T> queue;
    for(unsigned int i=0;i<adjacencyList.size();i++){
        queue.push_back(adjacencyList[i].first);
    }

    while(!queue.empty()){

        int smallestPosition = findposition(adjacencyList,queue[0]);;
        T smallest;
        for(unsigned int i=0;i<queue.size();i++){
            if(distance[findposition(adjacencyList,queue[i])]< distance[findposition(adjacencyList,adjacencyList[smallestPosition].first)]){
                smallestPosition = findposition(adjacencyList,queue[i]);
            }
        }

        if(distance[smallestPosition]==std::numeric_limits<double>::infinity()){
            break;
        }

        smallest = adjacencyList[smallestPosition].first;

        for(unsigned int n=0;n<queue.size();n++){
            if(queue[n]==adjacencyList[smallestPosition].first){
                queue.erase(queue.begin()+n);
            }
        }

        for(auto it = adjacencyList[findposition(adjacencyList, smallest)].second.begin();it != adjacencyList[findposition(adjacencyList,smallest)].second.end(); ++it) {
            int dist = (*it).second + distance[smallestPosition];

            if(dist < distance[findposition(adjacencyList, (*it).first)]){
                distance[findposition(adjacencyList, (*it).first)] = dist;
                previous[findposition(adjacencyList, (*it).first)] = smallest;
            }
        }
    }

    int position = findposition(adjacencyList, to);
    do{ if(distance[position]==std::numeric_limits<double>::infinity()){
            list<T> empty;
            return empty;
        }
        dijkstraResult.push_back(adjacencyList[position].first);
        position = findposition(adjacencyList, previous[position]);
    }while(distance[position]!=0);

    dijkstraResult.push_back(adjacencyList[position].first);
    dijkstraResult.reverse();

    return dijkstraResult;

}

template <typename T>
list<Edge<T>> Graph<T>::mst(){

    if(directedGraph==1){
       list<Edge<T>> empty;
       return empty;
    }

    list<Edge<T>> mstResult;
    unsigned int numofedges = 0;
    bool* visited = new bool[adjacencyList.size()];
    for (unsigned int i = 0; i < adjacencyList.size(); i++)
        visited[i] = false;

    visited[0] = true;

    T from, to;
    while (numofedges < (adjacencyList.size() - 1)){
        double min = std::numeric_limits<double>::infinity();
        for (unsigned int i = 0; i < adjacencyList.size(); i++) {
            if(visited[i]){
                for(typename list<pair<T, int>>::iterator it = adjacencyList[i].second.begin();it != adjacencyList[i].second.end(); ++it){
                    if(!visited[findposition(adjacencyList, (*it).first)]){
                        if (min > (*it).second){
                            min = (*it).second;
                            from = adjacencyList[i].first;
                            to = (*it).first;
                        }
                    }
                }
            }
        }

        T from_input, to_input;
        for(unsigned int n=0;n<adjacencyList.size();n++){
            if((adjacencyList[n].first == from)||(adjacencyList[n].first == to)){
                from_input = adjacencyList[n].first;
                break;
            }
        }
        for(unsigned int n=0;n<adjacencyList.size();n++){
            if(((adjacencyList[n].first == from)||(adjacencyList[n].first == to))&&(adjacencyList[n].first != from_input)){
                to_input = adjacencyList[n].first;
                break;
            }
        }

        Edge<T> input(from_input, to_input, min);
        mstResult.push_back(input);
        visited[findposition(adjacencyList, to)]= true;

        numofedges++;
    }

    mstResult.sort();

    return mstResult;


}

#endif
