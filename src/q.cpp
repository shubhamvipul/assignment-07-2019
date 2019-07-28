#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <chrono>
#include <thread>
#include <fstream>
#include "nlohmann/json.hpp"

struct stats{
    std::list<int> cUserIds;
    std::list<int> pUserIds;
    int count = 0;
    double maxcomp = 0.0;
    double avgcost = 0.0;
};

int no_of_threads;

stats stat1[100];

void findstats(int kk){
    nlohmann::json j;
    std::list<nlohmann::json> jlist;

    std::string line;

    std::string t1 = "../newdata/sample"+std::to_string(kk)+".txt";

    std::ifstream i(t1);

    int ii = 0;

    while (getline (i,line)){
        j = nlohmann::json::parse(line);
        jlist.push_back(j);
        ii++;
        }

    double maxcostcomp = 0;
    double cost = 0;
    double tcost = 0;
    double c;
    std::list<int> idList1;
    std::list<int> idList2;

    int lmax = 0;

    do{
        j = jlist.back();
        jlist.pop_back();
        cost = (double)j["cost"];
        if(cost>95){
        idList2.push_back((int)j["id"]);
        }
        tcost += cost;
        auto w = j["cost_components"];
        if(w.size()==0){
            continue;
        }
        lmax = 0;
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
    }while(!jlist.empty());

    stat1[kk].maxcomp = maxcostcomp;
    stat1[kk].avgcost += tcost;
    stat1[kk].cUserIds = idList1;
    stat1[kk].pUserIds = idList2;

    stat1[kk].avgcost /= ii;
}


int main()
{
    auto start = std::chrono::steady_clock::now();
    using json = nlohmann::json;
    
    std::ifstream nthreads;

    nthreads.open("temp.txt");

    nthreads >> no_of_threads;

    std::thread th[no_of_threads];

    int ii = 0;

    while (ii<no_of_threads){
        th[ii] = std::thread(findstats,ii);
        ii++;
        }

    ii = 0;

    while (ii<no_of_threads){
        th[ii].join();
        ii++;
    }

    double avgcost = 0;
    double maxcomp = 0;

    std::list<int> cUserIds;
    std::list<int> pUserIds;

    for(int jj = 0; jj < no_of_threads; jj++)
    {
        avgcost += stat1[jj].avgcost;
        if (stat1[jj].maxcomp > maxcomp){
            maxcomp = stat1[jj].maxcomp;
        }

        cUserIds.splice(cUserIds.end(),stat1[jj].cUserIds);
        pUserIds.splice(pUserIds.end(),stat1[jj].pUserIds);
    }

    avgcost /= ii;

    std::ofstream mfile;

    mfile.open("../results/results.txt");

    mfile << "1. " << std::to_string(avgcost) << std::endl;
    mfile << "2. " << std::to_string(maxcomp) << std::endl;
    mfile << "3. ";


    for (auto const& i: pUserIds) {
        mfile << i << ", ";
    }

    mfile.seekp(-2, std::ios_base::cur);

    mfile << "\n4. ";


    for (auto const& i: cUserIds) {
        mfile << i << ", ";
    }

    mfile.seekp(-2, std::ios_base::cur);

    mfile << "  ";
    
    std::cout << "Average cost " << avgcost << std::endl;
    std::cout << "Maximum of maximum cost-components " << maxcomp << std::endl;

    std::cout << "Number of users with max cost-components greater than 50: " << std::to_string(cUserIds.size()) << std::endl;

    std::cout << "Number of users with costs greater than 95: " << std::to_string(pUserIds.size()) << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed (in ms) : "<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<std::endl;
}
