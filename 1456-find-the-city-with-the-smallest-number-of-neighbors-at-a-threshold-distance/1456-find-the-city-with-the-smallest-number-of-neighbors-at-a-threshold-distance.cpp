#include <vector>
#include <climits> // For INT_MAX
using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Initialize the distance matrix
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX / 2));
        
        // Populate the direct edges
        for(auto it : edges) {
            dist[it[0]][it[1]] = it[2];
            dist[it[1]][it[0]] = it[2];
        }
        
        // Set diagonal elements to 0
        for(int i = 0; i < n; i++) 
            dist[i][i] = 0;
        
        // Floyd-Warshall algorithm to find shortest paths
        for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        
        int minCities = n;
        int cityNo = -1;
        for(int city = 0; city < n; city++) {
            int reachableCities = 0;
            for(int adjCity = 0; adjCity < n; adjCity++) {
                if(city != adjCity && dist[city][adjCity] <= distanceThreshold) 
                    reachableCities++;
            }
            if(reachableCities <= minCities) {
                minCities = reachableCities;
                cityNo = city;
            }
        }
        
        return cityNo;
    }
};