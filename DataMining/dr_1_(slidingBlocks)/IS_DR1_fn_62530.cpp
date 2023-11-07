#include <bits/stdc++.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <queue>
#include <deque>

time_t start, end;

int z, n, goalIndex, k, stepsToSuccess;
std::pair<int, int> blankIndexes;

// indexes of the goalState's nums (where gsIndexes[i] = <i_x, i_y>)
std::vector<std::pair<int, int>> gsIndexes;

const int INF = INT_MAX;

class Node
{
public:
    int **matrix;
    int g;
    //manhatton function of the current Node
    int h;
    std::vector<std::string> pathToTheNode;
    std::pair<int, int> blankSquareIndexes;

    Node(int **matrix = nullptr, int g = -1, int h = -1, std::vector<std::string> pathToTheNode = std::vector<std::string>(), std::pair<int, int> blankSquareIndexes = std::pair<int, int>(-1, -1))
    {
        this->matrix = matrix;
        this->g = g;
        this->h = h;
        this->pathToTheNode = pathToTheNode;
        this->blankSquareIndexes = blankSquareIndexes;
    }

    // copy constructor
    Node(const Node &rhs)
    {
        this->matrix = new int *[n];
        for (size_t i = 0; i < n; i++)
        {
            this->matrix[i] = new int[n];
            for (size_t j = 0; j < n; j++)
            {
                this->matrix[i][j] = rhs.matrix[i][j];
            }
        }
        this->g = rhs.g;
        this->h = rhs.h;
        this->pathToTheNode = rhs.pathToTheNode;
        this->blankSquareIndexes.first = rhs.blankSquareIndexes.first;
        this->blankSquareIndexes.second = rhs.blankSquareIndexes.second;
    }
    bool operator==(const Node &rhs)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (this->matrix[i][j] != rhs.matrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    ~Node()
    {

        for (size_t i = 0; i < n; i++)
        {
            delete this->matrix[i];
        }
        delete this->matrix;
    }
    const int getF()
    {
        return this->g + this->h;
    }
    void preComputeH(const std::pair<int, int> &old_, const std::pair<int, int> &new_, const int &val)
    {
        int oldManhh = (abs(gsIndexes[val].first - old_.first) + abs(gsIndexes[val].second - old_.second)) + 
                        (abs(gsIndexes[0].first - new_.first) + abs(gsIndexes[0].second - new_.second));
        int newManhh = (abs(gsIndexes[val].first - new_.first) + abs(gsIndexes[val].second - new_.second)) +
                        (abs(gsIndexes[0].first - old_.first) + abs(gsIndexes[0].second - old_.second));

        newManhh <= oldManhh ? this->h -= abs(oldManhh - newManhh) : this->h += abs(oldManhh - newManhh);
    }
};

// Manhattan
int h(int **matrix)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //|x-x'| + |y - y'|
            sum += abs(gsIndexes[matrix[i][j]].first - i) + abs(gsIndexes[matrix[i][j]].second - j);
        }
    }
    return sum;
}
bool is_goal(Node &node)
{
    return node.h == 0 ? true : false;
}
bool _find(std::deque<Node *> q, Node toFind)
{

    for (auto i = q.begin(); i != q.end(); ++i)
    {
        if (**i == toFind)
        {
            return true;
        }
    }
    return false;
}
class myComparator
{
public:
    int operator()(Node *n1, Node *n2)
    {
        return n1->getF() > n2->getF();
    }
};
std::priority_queue<Node *, std::vector<Node *>, myComparator> successors(const Node *node)
{
    std::priority_queue<Node *, std::vector<Node *>, myComparator> pq;
    // int **matrix;
    // int g;
    // int h;
    // std::vector<std::string> pathToTheNode;
    // std::pair<int,int>blankSquareIndexes;

    // check whether the current node isn't the root of the tree
    if (!node->pathToTheNode.empty())
    {

        // 0 otiva na left , zapisvame right. I trqbva da proverim dali predishniq node ne e hodil na left(za da ne se vrushtame otnovo tam)
        if (node->blankSquareIndexes.second - 1 >= 0 && node->pathToTheNode.back() != "left")
        {
            Node *res = new Node(*node);
            res->blankSquareIndexes.second -= 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("right");
            pq.push(res);
        }
        // 0 otiva na right , zapisvame left .  I trqbva da proverim dali predishniq node ne e hodil na right(za da ne se vrushtame otnovo tam)
        if (node->blankSquareIndexes.second + 1 < n && node->pathToTheNode.back() != "right")
        {
            Node *res = new Node(*node);
            res->blankSquareIndexes.second += 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("left");
            pq.push(res);
        }
        // 0 otiva na up , zapisvame down .  I trqbva da proverim dali predishniq node ne e hodil na up(za da ne se vrushtame otnovo tam)
        if (node->blankSquareIndexes.first - 1 >= 0 && node->pathToTheNode.back() != "up")
        {
            Node *res = new Node(*node);

            res->blankSquareIndexes.first -= 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("down");
            pq.push(res);
        }

        // 0 otiva na down , zapisvame up.  I trqbva da proverim dali predishniq node ne e hodil na down(za da ne se vrushtame otnovo tam)
        if (node->blankSquareIndexes.first + 1 < n && node->pathToTheNode.back() != "down")
        {
            Node *res = new Node(*node);

            res->blankSquareIndexes.first += 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("up");
            pq.push(res);
        }
    }
    //node is the root
    else
    {
        // 0 otiva na left , zapisvame right.
        if (node->blankSquareIndexes.second - 1 >= 0)
        {
            Node *res = new Node(*node);
            res->blankSquareIndexes.second -= 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("right");
            pq.push(res);
        }
        // 0 otiva na right , zapisvame left .
        if (node->blankSquareIndexes.second + 1 < n)
        {
            Node *res = new Node(*node);
            res->blankSquareIndexes.second += 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("left");
            pq.push(res);
        }
        // 0 otiva na up , zapisvame down .
        if (node->blankSquareIndexes.first - 1 >= 0)
        {
            Node *res = new Node(*node);

            res->blankSquareIndexes.first -= 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            res->pathToTheNode.push_back("down");
            pq.push(res);
        }

        // 0 otiva na down , zapisvame up.
        if (node->blankSquareIndexes.first + 1 < n)
        {
            Node *res = new Node(*node);

            res->blankSquareIndexes.first += 1;
            // swapping zero with the other
            int temp = res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second];
            res->matrix[res->blankSquareIndexes.first][res->blankSquareIndexes.second] = 0;
            res->matrix[node->blankSquareIndexes.first][node->blankSquareIndexes.second] = temp;
            res->g += 1;
            res->preComputeH(std::pair<int, int>(res->blankSquareIndexes.first, res->blankSquareIndexes.second), std::pair<int, int>(node->blankSquareIndexes.first, node->blankSquareIndexes.second), temp);
            //res->h = h(res->matrix);
            res->pathToTheNode.push_back("up");
            pq.push(res);
        }
    }
    return pq;
}

//returns pair<valueOfTrashhold,Either FOUND or NOTFOUND a solution>
std::pair<int, bool> search(std::deque<Node *> &path, int bound)
{
    Node *node = path.back();

    if (node->getF() > bound)
    {
        return std::pair<int, bool>(node->getF(), false);
    }
    if (is_goal(*node))
    {
        return std::pair<int, bool>(node->getF(), true);
    }
    int min = INF;
    std::priority_queue<Node *, std::vector<Node *>, myComparator> pq = successors(node);
    while (!pq.empty())
    {
        Node *succ = pq.top();
        if (!_find(path, *succ))
        {
            path.push_back(succ);
            // pair<valueOfTrashhold,Either FOUND or NOTFOUND>
            std::pair<int, bool> t;
            t = search(path, bound);
            if (t.second)
            {
                return t;
            }
            if (t.first < min)
            {
                min = t.first;
            }
            path.pop_back();
        }
        pq.pop();
    }
    return std::pair<int, bool>(min, false);
}
void ida_star(Node *root)
{
    int bound = h(root->matrix);
    std::deque<Node *> path;
    path.push_back(root);

    // pair<valueOfTrashhold,Either FOUND or NOTFOUND>
    std::pair<int, bool> t;
    while (true)
    {
        t = search(path, bound);
        // FOUND
        if (t.second)
        {
            time(&end);
            std::cout << path.back()->g << "\n";
            for (auto x : path.back()->pathToTheNode)
            {
                std::cout << x << "\n";
            }
            break;
        }
        if (t.first == INF)
        {
            std::cout << "It didn't find a solution (min=INF)" << std::endl;
            break;
        }
        bound = t.first;
    }
}
void merge(std::vector<std::pair<int, int>> &v, std::vector<int> &ans,
           int l, int mid, int h)
{

    std::vector<std::pair<int, int>>
        t; // temporary array for merging both halves
    int i = l;
    int j = mid + 1;

    while (i < mid + 1 && j <= h)
    {

        // v[i].first is greater than all
        // the elements from j till h.
        if (v[i].first > v[j].first)
        {
            ans[v[i].second] += (h - j + 1);
            t.push_back(v[i]);
            i++;
        }
        else
        {
            t.push_back(v[j]);
            j++;
        }
    }

    // if any elements left in left array
    while (i <= mid)
        t.push_back(v[i++]);
    // if any elements left in right array
    while (j <= h)
        t.push_back(v[j++]);
    // putting elements back in main array in
    // descending order
    for (int k = 0, i = l; i <= h; i++, k++)
        v[i] = t[k];
}

void mergesort(std::vector<std::pair<int, int>> &v, std::vector<int> &ans,
               int i, int j)
{
    if (i < j)
    {
        int mid = (i + j) / 2;

        // calling mergesort for left half
        mergesort(v, ans, i, mid);

        // calling mergesort for right half
        mergesort(v, ans, mid + 1, j);

        // merging both halves and generating answer
        merge(v, ans, i, mid, j);
    }
}

//caclulates inversions and returns a vector which is containing count of inversions of each element to the end of the vector on its' right.
std::vector<int> constructLowerArray(int *arr, int c)
{

    std::vector<std::pair<int, int>> v;
    for (int i = 0; i < c; i++)
        v.push_back({arr[i], i});

    std::vector<int> ans(c, 0);

    mergesort(v, ans, 0, c - 1);

    return ans;
}
bool isSolvable(int *rowMajorArr)
{

    // board size is odd
    if (n % 2 != 0)
    {
        int c = sizeof(rowMajorArr) / sizeof(rowMajorArr[0]);

        auto ans = constructLowerArray(rowMajorArr, z);
        long long inversions = 0;
        for (auto x : ans)
        {
            inversions += x;
        }
        // std::cout << inversions << std::endl;
        return inversions % 2 == 0 ? true : false;
    }
    // board size is even
    else
    {
        int c = sizeof(rowMajorArr) / sizeof(rowMajorArr[0]);

        auto ans = constructLowerArray(rowMajorArr, z);
        long long inversions = 0;
        for (auto x : ans)
        {
            inversions += x;
        }
        // std::cout << inversions << std::endl;
        return (inversions + blankIndexes.first) % 2 != 0 ? true : false;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cin >> z;
    std::cin >> goalIndex;
    n = sqrt(z + 1);
    int **initialMatrix = new int *[n];
    //it contains the initial input nums but consequently row by row
    int *rowMajorArr = new int[z];
    int l = 0;
    for (size_t i = 0; i < n; i++)
    {
        initialMatrix[i] = new int[n];
        for (size_t j = 0; j < n; j++)
        {
            std::cin >> k;
            if (k == 0)
            {
                blankIndexes = std::pair<int, int>(i, j);
                initialMatrix[i][j] = k;
                continue;
            }
            rowMajorArr[l++] = k;
            initialMatrix[i][j] = k;
        }
    }
    time(&start);   

    int **goalMatrix = new int *[n];
    l = 0;
    if (goalIndex == -1)
    {
        goalIndex = z;
    }
    std::vector<int> nums;
    for (size_t i = 1; i <= z; i++)
    {
        nums.push_back(i);
    }
    nums.insert(nums.begin() + goalIndex, 0);
    l = 0;

    //goalStateIndexes of each num, index is the num , value at index is pair with the coordinates
    gsIndexes = std::vector<std::pair<int, int>>(z + 1, std::pair<int, int>(-1, -1));
    for (size_t i = 0; i < n; i++)
    {
        goalMatrix[i] = new int[n];
        for (size_t j = 0; j < n; j++)
        {
            goalMatrix[i][j] = nums[l++];
            gsIndexes[goalMatrix[i][j]] = std::pair<int, int>(i, j);
        }
    }

    
    if(h(initialMatrix)==0)
    {
        time(&end);
        std::cout << "0\n";
    }

    else if (!isSolvable(rowMajorArr))
    {
        time(&end);
        std::cout << "-1\n";
    }
    else
    {
        Node root(initialMatrix, 0, h(initialMatrix), std::vector<std::string>(), blankIndexes);
        ida_star(&root);
    }
    double time_taken = double(end - start);
    //std::cout << "Time taken by program is : " << std::fixed << std::setprecision(2) << time_taken << " sec " << std::endl;
}