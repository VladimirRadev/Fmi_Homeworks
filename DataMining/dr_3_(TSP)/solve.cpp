#include <iostream>
#include <bits/stdc++.h>
#include <sys/time.h>
#include <cmath>
#include <unordered_map>
#include <string>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <ranges>

// global vars for the n random points
int n;
std::pair<double, double> *coordinates;
double **distances;
double lower_bound = -10;
double upper_bound = 1000;
const long max_rand = 1000000L;
struct Chromosome
{
    // stores hromosome's code in format: '01234'
    std::vector<int> code;
    double fitness;
    Chromosome(const std::vector<int> &code = std::vector(n, -1))
    {
        this->code = code;
        this->fitness = -1;
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
    void calcFitness()
    {
        double path = 0;
        for (size_t i = 0; i < this->code.size() - 1; i++)
        {
            path += distances[this->code[i]][this->code[i + 1]];
        }
        this->fitness = 1.0 / path;
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
struct MyComparator
{
    inline bool operator()(const Chromosome &struct1, const Chromosome &struct2)
    {
        return (struct1.fitness > struct2.fitness);
    }
};
std::vector<Chromosome> population;
std::vector<int> parentsIndexes;
Chromosome best;

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
double **uk_dist;

void calculateUkDistances()
{
    // todo
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
long factorial(const int n)
{
    long f = 1;
    for (int i = 1; i <= n; ++i)
        f *= i;
    return f;
}
void initialize()
{
    int populationSize = 0;
    // if (n <= 4)
    // {
    //     populationSize = factorial(n);
    //     std::vector<int> a;
    //     for (size_t i = 0; i < n; i++)
    //     {
    //         a.push_back(i);
    //     }

    //     int i = 0;
    //     do
    //     {
    //         population.push_back(Chromosome(a));
    //     } while (i++ < populationSize && std::next_permutation(a.begin(), a.end()));
    // }
    // else
    // {
    //     populationSize = 100;
    //     std::vector<int> a;
    //     for (size_t i = 0; i < n; i++)
    //     {
    //         a.push_back(i);
    //     }

    //     int i = 0;
    //     do
    //     {
    //         population.push_back(Chromosome(a));
    //         std::random_shuffle(a.begin(), a.end());
    //     } while (i++ < populationSize);
    // }

    populationSize = 100;
    std::vector<int> a;
    for (size_t i = 0; i < n; i++)
    {
        a.push_back(i);
    }

    int i = 0;
    do
    {
        population.push_back(Chromosome(a));
        std::random_shuffle(a.begin(), a.end());
    } while (i++ < populationSize);

    // for (size_t i = 0; i < population.size(); i++)
    // {
    //     for (size_t j = 0; j < population[i].code.size(); j++)
    //     {
    //         std::cout << population[i].code[j];
    //     }
    //     std::cout << '\n';
    // }
}
void evaluate()
{
    for (size_t i = 0; i < population.size(); i++)
    {
        population[i].calcFitness();
    }
    std::sort(population.begin(), population.end(), MyComparator());

    // for (size_t i = 0; i < population.size(); i++)
    // {
    //     std::cout << population[i].fitness << '\n';
    // }
    if (best.fitness < population[0].fitness)
    {
        best = population[0];
    }
    //best.print();
}
void selectParents()
{
    // the best always has to participate !!!
    parentsIndexes.push_back(0);
    int offset = 1;
    // High quality +19 parents (top ~40% of all)
    for (size_t i = 1; i < 20; i++)
    {
        parentsIndexes.push_back(i);
    }

    offset = 40;
    // Medium quality +20 (top 40% to 80% of all)
    for (size_t i = offset; i < offset + 20; i++)
    {
        parentsIndexes.push_back(i);
    }

    offset = 80;
    // Low quality + 10 (20%)
    for (size_t i = 0; i < 10; i++)
    {
        int parentIndex = offset + (rand() % 20);
        parentsIndexes.push_back(parentIndex);
    }

    // for (size_t i = 0; i < parentsIndexes.size(); i++)
    // {
    //     std::cout << parentsIndexes[i] << '\n';
    // }
}
std::pair<Chromosome, Chromosome> twoPointCrossOver(std::pair<Chromosome, Chromosome> parents)
{
    Chromosome p1 = parents.first, p2 = parents.second;
    Chromosome ch1, ch2;
    int i = (int)((20.0 / 100) * n);
    int j = i + (int)((40.0 / 100) * n);

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
// returns children after the crossOver
std::vector<Chromosome> crossOver()
{
    std::vector<Chromosome> children;

    // 10 H parents by 10 H parents = 20 children
    // the best always has to participate ! ! ! (The best H with the second best H)
    int p1 = 0, p2 = 1;
    std::pair<Chromosome, Chromosome> res = twoPointCrossOver(std::pair<Chromosome, Chromosome>(population[p1], population[p2]));
    children.push_back(res.first);
    children.push_back(res.second);

    // std::cout<<"Parents: \n";
    // population[p1].print();
    // population[p2].print();
    // std::cout<<"\n\n";
    // std::cout<<"Children: \n";
    // children[0].print();
    // children[1].print();

    int offset = 1;
    for (size_t i = 1; i < 10; i++)
    {
        int p1 = offset + (rand() % 19), p2 = offset + (rand() % 19);
        std::pair<Chromosome, Chromosome> res = twoPointCrossOver(std::pair<Chromosome, Chromosome>(population[parentsIndexes[p1]], population[parentsIndexes[p2]]));
        children.push_back(res.first);
        children.push_back(res.second);
    }

    // 10 H parents by 10 M parents = 20 children
    // the best always has to participate ! ! ! (the best H with the best M )
    p1 = 0, p2 = 20;
    res = twoPointCrossOver(std::pair<Chromosome, Chromosome>(population[p1], population[p2]));
    children.push_back(res.first);
    children.push_back(res.second);

    int other_offset = 21;
    for (size_t i = 1; i < 10; i++)
    {
        int p1 = offset + (rand() % 19), p2 = other_offset + (rand() % 19);
        std::pair<Chromosome, Chromosome> res = twoPointCrossOver(std::pair<Chromosome, Chromosome>(population[parentsIndexes[p1]], population[parentsIndexes[p2]]));
        children.push_back(res.first);
        children.push_back(res.second);
    }

    // 5 H parents by 5 L parents = 10 children
    // the best always has to participate ! ! ! (the best H with the best L )
    p1 = 0, p2 = 40;
    res = twoPointCrossOver(std::pair<Chromosome, Chromosome>(population[p1], population[p2]));
    children.push_back(res.first);
    children.push_back(res.second);

    other_offset = 41;
    for (size_t i = 1; i < 5; i++)
    {
        int p1 = offset + (rand() % 19), p2 = other_offset + (rand() % 9);
        std::pair<Chromosome, Chromosome> res = twoPointCrossOver(std::pair<Chromosome, Chromosome>(population[parentsIndexes[p1]], population[parentsIndexes[p2]]));
        children.push_back(res.first);
        children.push_back(res.second);
    }

    // for (size_t i = 0; i < children.size(); i++)
    // {
    //     children[i].print();
    // }

    return children;
}
void swap_mutation(Chromosome& child)
{
    int i = (int)((20.0 / 100) * n);
    int j = (int)((80.0 / 100) * n);
    std::iter_swap(child.code.begin() + i, child.code.begin() + j);
}
void mutation(std::vector<Chromosome>& children)
{
    for (size_t i = 0; i < children.size(); i++)
    {   
        //std::cout<<"Before: \n";
       // children[i].print();
        //std::cout<<"Now: \n";
        swap_mutation(children[i]);
       // children[i].print();
       // std::cout<<'\n';
    }

}
void evaluateChildren(std::vector<Chromosome>& children)
{
    for (size_t i = 0; i < children.size(); i++)
    {
        children[i].calcFitness();
    }
}
void buildNextGeneration(std::vector<Chromosome>& children)
{
    for (size_t i = 0; i < children.size(); i++)
    {
        population.push_back(children[i]);
    }
    std::sort(population.begin(), population.end(), MyComparator());

    //tuka trqbva da mi e logikata za terminirane , neshto ot sorta ako besta se zapazva 3 puti kato ot minaloto pokolenie spiram
    if(best.fitness < population[0].fitness)
    {
        best=population[0];
    }
   
    population=std::vector<Chromosome>(population.begin(),population.begin()+100);
}
void solveTSP()
{
    int generations = 0;
    initialize();
    evaluate();

    while (generations < 10)
    {
        parentsIndexes.clear();
        selectParents();
        std::vector<Chromosome> children = crossOver();
        mutation(children);
        evaluateChildren(children);
        buildNextGeneration(children);
        best.print();
        generations++;
    }
}

void n_random_points_run()
{
    std::cin >> n;
    coordinates = new std::pair<double, double>[n];
    for (size_t i = 0; i < n; i++)
    {
        // //random nums
        // double x = (upper_bound - lower_bound) * ( (double)rand() / (double)max_rand ) + lower_bound;
        // double y = (upper_bound - lower_bound) * ( (double)rand() / (double)max_rand ) + lower_bound;

        // uk
        double x, y;
        std::cin >> x >> y;

        coordinates[i].first = x;
        coordinates[i].second = y;
    }
    distances = new double *[n];
    for (size_t i = 0; i < n; i++)
    {
        distances[i] = new double[n];
    }

    calculateDistances();
    solveTSP();
    //best.print();
}
// void uk_run()
// {

// }
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    srand(time(NULL));

    n_random_points_run();
    // uk_run();
}