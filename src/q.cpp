#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <list>
#include <chrono>
#include <thread>
#include <fstream>
#include "nlohmann/json.hpp"

std::mutex myMutex;

struct stats{
    std::list<int> cUserIds;
    std::list<int> pUserIds;
    int count = 0;
    double maxcomp = 0.0;
    double avgcost = 0.0;
} stat1;

void setstats(double a, double t, std::list<int> l1, std::list<int> l2){
    std::lock_guard<std::mutex> guard(myMutex);
    if(a>stat1.maxcomp){
    stat1.maxcomp = a;
    }
    stat1.count ++;
    stat1.avgcost += t;
    stat1.pUserIds.splice(stat1.pUserIds.end(),l1);
    stat1.cUserIds.splice(stat1.pUserIds.end(),l2);
}

void findstats(std::list<nlohmann::json> k){
    double maxcostcomp = 0;
    double cost = 0;
    double tcost = 0;
    double c;
    std::list<int> idList1;
    std::list<int> idList2;
    nlohmann::json j;
    do{
        j = k.back();
        k.pop_back();
        cost = (double)j["cost"];
        if(cost>95){
        idList2.push_back((int)j["id"]);
        }
        tcost += cost;
        auto w = j["cost_components"];
        if(w.size()==0){
            continue;
        }
        int lmax = 0;
        for(auto const& vals: w){
            if(vals > maxcostcomp){
                maxcostcomp = vals;
            }
            if(vals > lmax){
                lmax = vals;
            }
        }
        if(lmax > 50){
            idList1.push_back((int)j["id"]);
        }
    }while(!k.empty());
    setstats(maxcostcomp, double(tcost/1000), idList1, idList2);
}


int main()
{
    auto start = std::chrono::steady_clock::now();
    using json = nlohmann::json;
    
    std::thread th[1000];

    std::ifstream i("../data/json_new_format.txt");
    std::string line;
    json j;
    int ii = 0;
    std::list<json> jlist; 
 
    while (getline (i,line)){
        j = json::parse(line);
        jlist.push_back(j);
        if(ii%1000==999){
        th[(int)ii/1000] = std::thread(findstats,jlist);
        jlist.clear();
        }
        ii++;
        }

    for(int jj = 0; jj < (ii/1000); jj++){
        th[jj].join();
    }

    stat1.avgcost /= stat1.count;

    std::cout << "Average cost " << stat1.avgcost << std::endl;
    std::cout << "Maximum of maximum cost-components " << stat1.maxcomp << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : "<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<std::endl;

}
