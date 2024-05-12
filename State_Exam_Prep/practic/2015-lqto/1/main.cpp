#include <iostream>

void subsample(const int &M, const int &N, float **img)
{
    int s_i = (M + 1) / 2;
    int s_j = (N + 1) / 2;
    float** s = new float*[s_i];
    for (int i = 0; i < s_i; i++)
    {
        s[i] = new float[s_j];
        for (int j = 0; j < s_j; j++)
        {
            float sum=0.0f;
            float count=0.0f;
            for (int y = 0; y < M; y++)
            {
                for (int x = 0; x < N; x++)
                {
                    if( ((2*i) <= y && y <= (2*i + 1) ) &&
                        ((2*j) <= x && x <= (2*j + 1)) )
                        {
                            sum+=img[y][x];
                            count++;
                        }
                }
                
            }
            s[i][j]=(float)(sum/count);
        }
    }

    for (int i = 0; i < s_i; i++)
    {
        for (int j = 0; j < s_j; j++)
        {
            std::cout<<s[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
    

    for (int i = 0; i < s_i; i++)
    {
        delete[] s[i];
    }
    delete s;
}

int main()
{
    int M, N;
    std::cin >> M >> N;
    if (M > 10 || M <= 0 || N > 10 || N <= 0)
    {
        std::cout << "Invalid input\n";
        return 1;
    }
    float **img = new float *[M];
    float k;
    for (int i = 0; i < M; i++)
    {
        img[i] = new float[N];
        for (int j = 0; j < N; j++)
        {
            std::cin >> k;
            img[i][j] = k;
        }
    }
    subsample(M, N, img);

    for (int i = 0; i < M; i++)
    {
        delete[] img[i];
    }
    delete img;
}