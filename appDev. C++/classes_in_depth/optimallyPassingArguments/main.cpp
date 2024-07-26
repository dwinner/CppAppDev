#include <iostream>
#include <vector>

using namespace std;

class DataHolder
{
public:
   //void setData(const vector<int>& data) { _data = data; }
   //void setData(vector<int>&& data) { _data = move(data); }
   void setData(vector<int> data)
   {
      _data = std::move(data);
   }

private:
   vector<int> _data;
};

int main()
{
   DataHolder wrapper;
   vector myData{11, 22, 33};
   wrapper.setData(myData);
   wrapper.setData({22, 33, 44});

   return 0;
}
