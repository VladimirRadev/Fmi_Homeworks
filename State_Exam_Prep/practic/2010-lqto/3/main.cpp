#include <iostream>

class Laptop
{
    private:
        static int connectedCount; 


        bool isConnected;
        float storage; //GB
        float cpuRate; //Ghz
        int cpuCount;
    public:
        Laptop():isConnected(false),storage(0.0f),cpuRate(0.0f),cpuCount(0){}
        Laptop(const bool& isConnected, const float& storage,const float& cpuRate
        ,const int& cpuCount):isConnected(isConnected),storage(storage),cpuRate(cpuRate),cpuCount(cpuCount)
        {
            if(this->isConnected)
            {
                connectedCount++;
            }
        }
        Laptop(const Laptop&rhs)
        {
            if(rhs.isConnected)
            {
                connectedCount++;
            }
            this->isConnected=rhs.isConnected;
            this->storage=rhs.storage;
            this->cpuRate=rhs.cpuRate;
            this->cpuCount=rhs.cpuCount;
        }
        ~Laptop()
        {
            if(this->isConnected)
            {
                connectedCount--;
            }
        }

        static int getConnectedCount()
        {
            return connectedCount;
        }

        bool getIsConnected()const
        {
            return this->isConnected;
        }
        void setIsConnected(const bool& value)
        {
            if(this->isConnected && !value)
            {   
               connectedCount--;
            }
            else if(!this->isConnected && value)
            {
                connectedCount++;
            }
            this->isConnected=value;
        }
        float getStorage() const
        {
            return this->storage;
        }
        void setStorage(const float& value)
        {
            this->storage=value;
        }
        float getCpuRate() const
        {
            return this->cpuRate;
        }
        void setCpuRate(const float& value)
        {
            this->cpuRate=value;
        }

        int getCpuCount() const
        {
            return this->cpuCount;
        }
        void setCpuCount(const int& value)
        {
            this->cpuCount=value;
        }

        

};

int Laptop::connectedCount=0;

int main()
{
    Laptop l1;
    l1.setIsConnected(true);
    Laptop l2(l1);

    std::cout<<Laptop::getConnectedCount()<<std::endl; // must be 2

    Laptop l3(1,84.5,2.4,4);
    l2.setIsConnected(0);

    std::cout<<Laptop::getConnectedCount()<<std::endl; // must be 2


    l1.setIsConnected(0);
    l3.setIsConnected(0);

    std::cout<<Laptop::getConnectedCount()<<std::endl; // must be 0

    std::cout<<"\n\n\n";
    l3.setCpuRate(1.8);
    std::cout<<l3.getCpuCount()<<std::endl; // must be 4
    std::cout<<l3.getCpuRate()<<std::endl; // must be 1.8
    std::cout<<l3.getStorage()<<std::endl; // must be 84.5
    std::cout<<l3.getIsConnected()<<std::endl; // must be 0


    l3.setIsConnected(1);

    Laptop l4(l3);
    std::cout<<Laptop::getConnectedCount()<<std::endl; // must be 2



    return 0;
}