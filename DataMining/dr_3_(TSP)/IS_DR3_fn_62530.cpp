#include <iostream>
#include <bits/stdc++.h>
#include <sys/time.h>
#include <cmath>
#include <string>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <ranges>
#include <queue>

clock_t start,end;

// global vars for the n random points
int n;
// should be even
const int POPULATION_SIZE = 50;
const int GENERETIONS_COUNT = 10000;
std::pair<double, double> *coordinates;
double **distances;
double lower_bound = -10000;
double upper_bound = 10000;
const long max_rand = 1000000L;
int iter = 0;
struct Chromosome
{
    // stores hromosome's code in format: '01234'
    std::vector<int> code;
    double fitness;
    void calcFitness()
    {
        double path = 0;
        for (size_t i = 0; i < this->code.size() - 1; i++)
        {
            path += distances[this->code[i]][this->code[i + 1]];
        }
        this->fitness = 1.0 / path;
    }
    Chromosome(const std::vector<int> &code = std::vector(n, -1))
    {
        this->code = code;
        this->fitness = 0.00000000000000001;
    }
    Chromosome(const Chromosome &rhs)
    {
        this->code = rhs.code;
        this->fitness = rhs.fitness;
    }
    Chromosome &operator=(const Chromosome &other)
    {
        if (this == &other)
        {
            return *this;
        }
        this->code = other.code;
        this->fitness = other.fitness;

        return *this;
    }
    double getPathDistance()
    {
        return 1.0 / this->fitness;
    }
    void print()
    {
        std::cout << "The code is: ";
        for (auto x : this->code)
        {
            std::cout << x << "-> ";
        }
        std::cout << " with fitness:" << this->fitness << " and path:" << this->getPathDistance() << '\n';
    }
};
Chromosome best;
struct MyComparator
{
    inline bool operator()(const Chromosome &struct1, const Chromosome &struct2)
    {
        return (struct1.fitness < struct2.fitness);
    }
};
std::priority_queue<Chromosome, std::vector<Chromosome>, MyComparator> curPopulation;
std::priority_queue<Chromosome, std::vector<Chromosome>, MyComparator> nextPopulation;

// global vars for the uk case
const std::pair<double, double> uk_coordinates[12] = {
    {0.000190032, -0.000285946},
    {383.458, -0.000608756},
    {-27.0206, -282.758},
    {335.751, -269.577},
    {69.4331, -246.780},
    {168.521, 31.4012},
    {320.350, -160.900},
    {179.933, -318.031},
    {492.671, -131.563},
    {112.198, -110.561},
    {306.320, -108.090},
    {217.343, -447.089},
};
const std::string uk_names[12] = {
    "Aberystwyth",
    "Brighton",
    "Edinburgh",
    "Exeter",
    "Glasgow",
    "Inverness",
    "Liverpool",
    "London",
    "Newcastle",
    "Nottingham",
    "Oxford",
    "Stratford",
};

void calculateUkDistances()
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
            {
                distances[i][j] = 0;
                continue;
            }
            distances[i][j] = sqrt(pow((uk_coordinates[i].first - uk_coordinates[j].first), 2) + pow((uk_coordinates[i].second - uk_coordinates[j].second), 2));
        }
    }
}
void calculateDistances()
{

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
            {
                distances[i][j] = 0;
                continue;
            }
            distances[i][j] = sqrt(pow((coordinates[i].first - coordinates[j].first), 2) + pow((coordinates[i].second - coordinates[j].second), 2));
        }
    }

    // for (size_t i = 0; i < n; i++)
    // {
    //     std::cout<<'[';
    //     for (size_t j = 0; j < n; j++)
    //     {
    //         std::cout<<distances[i][j]<<", ";
    //     }
    //     std::cout<<']';
    //     std::cout<<'\n';

    // }
}
void initialize()
{

    std::vector<int> a;
    for (size_t i = 0; i < n; i++)
    {
        a.push_back(i);
    }

    int i = 0;
    do
    {
        Chromosome input(a);
        input.calcFitness();
        curPopulation.push(input);
        std::random_shuffle(a.begin(), a.end());
    } while (i++ < POPULATION_SIZE - 1);

    // for (size_t i = 0; i < population.size(); i++)
    // {
    //     for (size_t j = 0; j < population[i].code.size(); j++)
    //     {
    //         std::cout << population[i].code[j];
    //     }
    //     std::cout << '\n';
    // }
}
void swap_mutation(Chromosome &child)
{
    int i = (rand() % n);
    int j = (rand() % n);
    std::iter_swap(child.code.begin() + i, child.code.begin() + j);
}
std::pair<Chromosome, Chromosome> twoPointCrossOver(const Chromosome &p1, const Chromosome &p2)
{
    Chromosome ch1, ch2;
    // int i = (int)((20.0 / 100) * n);
    // int j = i + (int)((40.0 / 100) * n);
    int i,j;
    if(n>=3 && n<5)
    {
     i = 1;
     j = i + 1;
    }
    else if(n>=5 && n<=10)
    {
         i = 1;
         j = i + 2;
    }
    else {
     i = (int)(rand() % (int)((10.0 / 100) * n));
     j = i + (int)((30.0 / 100) * n);
    }

    // ch1

    // where ch1 loop starts
    int k = i;
    for (; k <= j; k++)
    {
        ch1.code[k] = p1.code[k];
    }
    // where p2 loop starts
    int l = j + 1;

    // while there is non filled index , continue
    while (std::find(ch1.code.begin(), ch1.code.end(), -1) != ch1.code.end())
    {
        if (std::find(ch1.code.begin(), ch1.code.end(), p2.code[l]) != ch1.code.end())
        {
            l++;
        }
        else
        {
            ch1.code[k++] = p2.code[l++];
        }
        if (k >= n)
        {
            k = 0;
        }
        if (l >= n)
        {
            l = 0;
        }
    }

    // ch2

    // where ch2 loop starts
    k = i;
    for (; k <= j; k++)
    {
        ch2.code[k] = p2.code[k];
    }
    // where p1 loop starts
    l = j + 1;

    // while there is non filled index , continue
    while (std::find(ch2.code.begin(), ch2.code.end(), -1) != ch2.code.end())
    {
        if (std::find(ch2.code.begin(), ch2.code.end(), p1.code[l]) != ch2.code.end())
        {
            l++;
        }
        else
        {
            ch2.code[k++] = p1.code[l++];
        }
        if (k >= n)
        {
            k = 0;
        }
        if (l >= n)
        {
            l = 0;
        }
    }
    return std::pair<Chromosome, Chromosome>(ch1, ch2);
}

std::pair<Chromosome, Chromosome> cycleCrossOver(const Chromosome &p1, const Chromosome &p2)
{
    Chromosome ch1, ch2;

    // stores index of nums, where are the nums in the current state
    std::vector<int> p1IndOfNums(n, -1);
    std::vector<int> p2IndOfNums(n, -1);
    for (size_t i = 0; i < p1.code.size(); i++)
    {
        p1IndOfNums[p1.code[i]] = i;
    }
    for (size_t i = 0; i < p2.code.size(); i++)
    {
        p2IndOfNums[p2.code[i]] = i;
    }
    std::unordered_set<int> used, p1Genes, p2Genes;

    int iter = 0, cur = -1;
    // If it's true means that we are now at p1 code and looking  at p2 code's opposite eleement, otherwise we are at the p2 code and looking for gene at p1 code
    bool lookingAtOppositeIndex = false;
    for (size_t i = 0; i < p1.code.size(); i++)
    {
        if (!used.count(p1.code[i]))
        {
            cur = p1.code[i];
            lookingAtOppositeIndex = true;
            while (!(cur == p1.code[i] && lookingAtOppositeIndex == false))
            {
                if (lookingAtOppositeIndex == true)
                {
                    used.insert(cur);
                    p1Genes.insert(cur);
                    lookingAtOppositeIndex = false;
                    cur = p2.code[p1IndOfNums[cur]];
                }
                else
                {
                    p2Genes.insert(cur);
                    lookingAtOppositeIndex = true;
                }
            }
            p2Genes.insert(cur);

            if (iter % 2 == 0)
            {
                for (const auto &x : p1Genes)
                {
                    ch1.code[p1IndOfNums[x]] = x;
                }
                for (const auto &x : p2Genes)
                {
                    ch2.code[p2IndOfNums[x]] = x;
                }
            }
            else
            {
                for (const auto &x : p1Genes)
                {
                    ch2.code[p1IndOfNums[x]] = x;
                }
                for (const auto &x : p2Genes)
                {
                    ch1.code[p2IndOfNums[x]] = x;
                }
            }
            p1Genes.clear();
            p2Genes.clear();
            ++iter;
        }
    }

    // std::cout<<"Parents: \n\t";
    // for (size_t i = 0; i < p1.code.size(); i++)
    // {
    //     std::cout<<p1.code[i]<<' ';
    // }
    // std::cout<<"\n\t";
    // for (size_t i = 0; i < p2.code.size(); i++)
    // {
    //     std::cout<<p2.code[i]<<' ';
    // }
    // std::cout<<'\n';
    // std::cout<<'\n';
    // std::cout<<"Children: \n\t";
    //   for (size_t i = 0; i < ch1.code.size(); i++)
    // {
    //     std::cout<<ch1.code[i]<<' ';
    // }
    // std::cout<<"\n\t";
    // for (size_t i = 0; i < ch2.code.size(); i++)
    // {
    //     std::cout<<ch2.code[i]<<' ';
    // }
    // std::cout<<'\n';

    return std::pair<Chromosome, Chromosome>(ch1, ch2);
}

void crossOver()
{
    best = curPopulation.top();
    while (!curPopulation.empty())
    {
        Chromosome p1 = curPopulation.top();
        // nextPopulation.push(p1); //(variant 3);
        curPopulation.pop();

        Chromosome p2 = curPopulation.top();
        // nextPopulation.push(p2); //(variant 3);
        curPopulation.pop();

        std::pair<Chromosome, Chromosome> children = twoPointCrossOver(p1, p2);
        // std::pair<Chromosome, Chromosome> children = cycleCrossOver(p1, p2);
        //  std::pair<Chromosome, Chromosome> children;
        //  int k = rand() % 2;
        //  if (k == 0)
        //  {
        //      children = twoPointCrossOver(p1, p2);
        //  }
        //  else if (k == 1)
        //  {
        //      children = cycleCrossOver(p1, p2);
        //  }

        swap_mutation(children.first);
        swap_mutation(children.second);

        children.first.calcFitness();
        children.second.calcFitness();

        nextPopulation.push(children.first);
        nextPopulation.push(children.second);

      
    }
    // variant 4
    //  while (!curPopulation.empty())
    //  {
    //      curPopulation.pop();
    //  }
}

void buildNextGeneration()
{
    // variant 1
    // for (size_t i = 0; i < POPULATION_SIZE; i++)
    // {
    //     curPopulation.push(nextPopulation.top());
    // }
    // while (!nextPopulation.empty())
    // {
    //     nextPopulation.pop();
    // }

    // we should always keep the best from the previus generation (variant 2)
    if (best.fitness > nextPopulation.top().fitness)
    {
        iter++;
        curPopulation.push(best);
        for (size_t i = 0; i < POPULATION_SIZE - 1; i++)
        {
            curPopulation.push(nextPopulation.top());
            nextPopulation.pop();
        }
        while (!nextPopulation.empty())
        {
            nextPopulation.pop();
        }
    }
    else
    {
        best = nextPopulation.top();

        curPopulation = nextPopulation;

        while (!nextPopulation.empty())
        {
            nextPopulation.pop();
        }
    }

    // // get top 10 of the next Population (variant 3)
    // for (size_t i = 0; i < POPULATION_SIZE; i++)
    // {
    //     curPopulation.push(nextPopulation.top());
    // }
    // while (!nextPopulation.empty())
    // {
    //     nextPopulation.pop();
    // }

    // get half of the best , keep best population_size elements (variant 4)
    //  for (size_t i = 0; i < POPULATION_SIZE; i++)
    //  {
    //      curPopulation.push(nextPopulation.top());
    //  }
    //  while (!nextPopulation.empty())
    //  {
    //      nextPopulation.pop();
    //  }
}
int getBest()
{
    Chromosome a = curPopulation.top();
    return a.getPathDistance();
}
void solveTSP()
{
    int generations = 0;
    initialize();
    while (generations < GENERETIONS_COUNT)
    {
        crossOver();
        buildNextGeneration();
        if ((generations == 0) || (generations == (5.0 / 100) * GENERETIONS_COUNT) || (generations == (10.0 / 100) * GENERETIONS_COUNT) || (generations == (15.0 / 100) * GENERETIONS_COUNT) || (generations == (20.0 / 100) * GENERETIONS_COUNT) || (generations == (40.0 / 100) * GENERETIONS_COUNT) || (generations == (60.0 / 100) * GENERETIONS_COUNT) || (generations == (80.0 / 100) * GENERETIONS_COUNT) || (generations == (96.0 / 100) * GENERETIONS_COUNT) || (generations == GENERETIONS_COUNT - 1))
        {
            std::cout << getBest() << std::endl;
        }
        generations++;
    }
}

void n_random_points_run()
{
    std::cin >> n;
    start=clock();
    coordinates = new std::pair<double, double>[n];
    for (size_t i = 0; i < n; i++)
    {
        //random nums
        double x = (upper_bound - lower_bound) * ( (double)rand() / (double)max_rand ) + lower_bound;
        double y = (upper_bound - lower_bound) * ( (double)rand() / (double)max_rand ) + lower_bound;

        // // uk
        // double x, y;
        // std::cin >> x >> y;

        coordinates[i].first = x;
        coordinates[i].second = y;
    }
    if(n==1)
    {
        for (size_t i = 0; i < 10; i++)
        {
            std::cout<<0<<std::endl;
        }
        return;
        
    }
    else if(n==2)
    {
        for (size_t i = 0; i < 10; i++)
        {
           std::cout<<(int)sqrt(pow((coordinates[0].first - coordinates[1].first), 2) + pow((coordinates[0].second - coordinates[1].second), 2))<<std::endl;
        }
        return;
        
    }
    distances = new double *[n];
    for (size_t i = 0; i < n; i++)
    {
        distances[i] = new double[n];
    }

    calculateDistances();
    solveTSP();
}
void printCityPath()
{
    for (size_t i = 0; i < best.code.size(); i++)
    {
        
        std::cout<<uk_names[best.code[i]];
        if(i!=best.code.size()-1)
        {
            std::cout<<" -> ";
        }
    }
    std::cout<<'\n';
    
}
void uk_run()
{
    start=clock();
    n=12;
    
    distances = new double *[n];
    for (size_t i = 0; i < n; i++)
    {
        distances[i] = new double[n];
    }

    calculateUkDistances();
    solveTSP();
    printCityPath();
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    srand(time(NULL));

    
    //n_random_points_run();
    uk_run();

    end=clock();
    double time_taken = ((double)end-start)/CLOCKS_PER_SEC; 
    std::cout << "The program took "<< time_taken <<" seconds to execute\n";


    //std::cout << iter << std::endl;
}