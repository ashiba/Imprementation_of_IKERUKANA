#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>

class UnionFind{
private:
    std::vector<int> par,rank,elm;
    std::vector<std::vector<int>> elmList; //don't be validated
public:
    int groups;

    UnionFind(int __size):par(__size), rank(__size,0), elm(__size,1), groups(__size), elmList(__size) {
        for (int i=0; i<__size; ++i)elmList[i] = std::vector<int>(1,i);
        for(int i=0;i<__size;i++)par[i]=i;
    }

    // int getElements(int n) {
    //     return elm[find(n)];
    // }

    // std::vector<int> getElementsList(int n) {
    //     return elmList[find(n)];
    // }

    int find(int x) {
        if(par[x]==x) {
            return x;
        }else{
            return par[x]=find(par[x]);
        }
    }

    void unite(size_t x,size_t y) {
        x=find(x);
        y=find(y);
        if(x == y) return;

        groups--;
        size_t parent_node, child_node;
        if (rank[x]<rank[y]) {
            parent_node = y, child_node = x;
        } else {
            parent_node = x, child_node = y;
            if (rank[parent_node] == rank[child_node]) rank[parent_node]++;
        }

        par[child_node] = parent_node;
        elm[parent_node] += elm[child_node];
        for (auto &e:elmList[child_node]) elmList[parent_node].emplace_back(e);

    }

    bool isSame(const size_t& x,const size_t& y) {
        return find(x)==find(y);
    }
};


struct edge {
    size_t from, to;
};

const std::vector<std::vector<size_t>> genHWDenceGridGraph(const size_t& map_height, const size_t& map_width) {
    auto encodeIndex = [map_width](const size_t& y, const size_t& x) { return y*map_width + x; };
    const int additional_node_num = map_height*map_width/4;
    const size_t node_num = map_height*map_width;
    std::vector<std::vector<size_t>> grid_graph(node_num);


    std::vector<edge>all_edges;
    for (size_t i=0; i<map_height; ++i) {
        for (size_t j=0; j<map_width; ++j) {
            if (i+1 < map_height) all_edges.emplace_back( edge{encodeIndex(i, j), encodeIndex(i+1, j+0)} );
            if (j+1 < map_width)  all_edges.emplace_back( edge{encodeIndex(i, j), encodeIndex(i+0, j+1)} );
        }
    }

    const size_t SEED = 1;
    std::mt19937 engine(SEED);
    std::shuffle(all_edges.begin(), all_edges.end(), engine);
int c=0;
    UnionFind uf(node_num);
    int additional_node_count = 0;
    for (const edge& edg: all_edges) {
        if (not uf.isSame(edg.from, edg.to)) {
            uf.unite(edg.from, edg.to);
            grid_graph[edg.from].emplace_back(edg.to);
            grid_graph[edg.to].emplace_back(edg.from);
        } else {
            if (additional_node_count < additional_node_num) {
                additional_node_count++;
                grid_graph[edg.from].emplace_back(edg.to);
                grid_graph[edg.to].emplace_back(edg.from);
            }
        }
    }
    return grid_graph;
}


int main() {
    const int map_height = 10;
    const int map_width = map_height;

    const std::vector<std::vector<size_t>> Graph = genHWDenceGridGraph(map_height, map_width);

    std::ofstream ofs("generated_" + std::to_string(map_height) + "*" + std::to_string(map_height) + "map.csv");

    const int NODE_NUM = map_height*map_height;
    ofs << NODE_NUM << std::endl;
    for (int i=0; i<Graph.size(); ++i) {
        for (int j=0; j<Graph[i].size(); ++j) {
            if (j) ofs << ',';
            ofs << Graph[i][j];
        }
        ofs << std::endl;
    }

    const int PLAYERS_NUM = 4;
    ofs << PLAYERS_NUM << std::endl;

    std::vector<int> node_ids(NODE_NUM);
    node_ids[0] = 0;
    for (int i=1; i<NODE_NUM; ++i) node_ids[i] = i;
    const size_t SEED = 1;
    std::mt19937 engine(SEED);
    std::shuffle(node_ids.begin()+1, node_ids.end(), engine);

    ofs << node_ids[0] << "," << node_ids[1] << "," << node_ids[2] << "," << node_ids[3] << std::endl;
    assert(node_ids[0] == 0);

    ofs << 1 << std::endl;
}