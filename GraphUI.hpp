
#ifndef _GRAPH_UI_
#define _GRAPH_UI_

template <typename T>
int graphUI() {
  
  string option, line;
  //int distance;
  bool digraph = false;
  
  cin >> option;
  if(!option.compare("digraph"))
    digraph = true;
  Graph<T> g(digraph);
  
  while(true) {
    
    std::stringstream stream;
    cin >> option;
    
    if(!option.compare("av")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      if(g.addVtx(vtx))
        cout << "av " << vtx << " OK\n";
      else
        cout << "av " << vtx << " NOK\n";
    }
    else if(!option.compare("rv")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      if(g.rmvVtx(vtx))
        cout << "rv " << vtx << " OK\n";
      else
        cout << "rv " << vtx << " NOK\n";

    }
    else if(!option.compare("ae")) {
      getline(std::cin, line);

      stream << line;
      T from(stream);

      stream << line;
      T to(stream);

      stream << line;
      int cost;
      stream >> cost;

      if(g.addEdg(from, to, cost))
        cout << "ae " << from << " " << to << " OK\n";
      else
        cout << "ae " << from << " " << to << " NOK\n";
      
    }
    else if(!option.compare("re")) {

      getline(std::cin, line);

      stream << line;
      T from(stream);

      stream << line;
      T to(stream);

      if(g.rmvEdg(from, to))
        cout << "re " << from << " " << to << " OK\n";
      else
        cout << "re " << from << " " << to << " NOK\n";

    }
    else if(!option.compare("dot")) {

      getline(std::cin, line);

      stream << line;
      char* file = new char[50];
      stream >> file;

      if(g.print2DotFile(file))
        cout << "dot " << file << " OK\n";
      else
        cout << "dot " << file << " NOK\n";

    }
    else if(!option.compare("bfs")) {

      getline(std::cin, line);
      stream << line;
      T vtx(stream);

      list<T> bfsList = g.bfs(vtx);
      
      cout << "\n----- BFS Traversal -----\n";

      typename list<T>::iterator it = bfsList.begin();
      cout<<(*it);
      ++it;

      for(;it != bfsList.end(); ++it){
          cout<<" -> "<<(*it);
      }
      
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dfs")) {

      getline(std::cin, line);
      stream << line;
      T vtx(stream);

      list<T> dfsList = g.dfs(vtx);
      
      cout << "\n----- DFS Traversal -----\n";

      typename list<T>::iterator it = dfsList.begin();
      cout<<(*it);
      ++it;

      for(;it != dfsList.end(); ++it){
          cout<<" -> "<<(*it);
      }
      
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dijkstra")) {
      getline(std::cin, line);
      stream << line;
      T from(stream);
      T to(stream);

      list<T> DijkstraList = g.dijkstra(from, to);
      cout << "Dijkstra (" << from << " - " << to <<"): ";

      typename list<T>::iterator it = DijkstraList.begin();
      cout<<(*it);
      ++it;

      for(;it != DijkstraList.end(); ++it){
          cout<<", "<<(*it);
      }
      cout<<"\n";
    }
    else if(!option.compare("mst")) {

      cout << "\n--- Min Spanning Tree ---\n";
      list <Edge<T>> mst = g.mst();
      typename list <Edge<T>>::iterator it = mst.begin();
      cout<<(*it)<<endl;;
      ++it;

      for(;it != mst.end(); ++it){
          cout<<(*it)<<endl;
      }

      int sum = 0;
      for(typename list <Edge<T>>::iterator it = mst.begin();it != mst.end(); ++it){
         sum = sum + (*it).dist;
      }
      cout << "MST Cost: " <<sum<< endl;
    }
    else if(!option.compare("q")) {
      cerr << "bye bye...\n";
      return 0;
    }
    else if(!option.compare("#")) {
      string line;
      getline(cin,line);
      cerr << "Skipping line: " << line << endl;
    }
    else {
      cout << "INPUT ERROR\n";
      return -1;
    }
  }
  return -1;  
}

#endif
