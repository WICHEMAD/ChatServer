#include "json.hpp"
using json = nlohmann::json;
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

string func1()
{
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello, what are you doing now?";
    string sendBuf=js.dump();//json数据对象=》序列化 json字符串
    cout<<sendBuf<<endl;
    //cout<<js<<endl;
    return sendBuf;
}
string func2()
{
    json js;
    js["id"]={1,2,3,4,5};

    js["name"]["zhang san"]="hello world";
    js["msg"]={{"zhang san","hello world"},{"liu shuo","hello china"}};
    return js.dump();
}
string func3()
{
    json js;

    vector<int>vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    js["list"]=vec;

    map<int,string>m;
    m.insert({1,"黄山"});
    m.insert({2,"华山"});
    m.insert({3,"泰山"});

    js["path"]=m;
    string sendBuf=js.dump();
    return sendBuf;
}
int main()
{
    string recvBuf=func3();

    json jsbuf=json::parse(recvBuf);
    //cout<<jsbuf["msg_type"]<<endl;
    //cout<<jsbuf["from"]<<endl;
    //cout<<jsbuf["to"]<<endl;
    //cout<<jsbuf["msg"]<<endl;


    //cout<<jsbuf["id"]<<endl;
    //auto arr=jsbuf["id"];
    //cout<<arr[4]<<endl;

    //auto msjs=jsbuf["msg"];
    //cout<<msjs["zhang san"]<<endl;

    vector<int>vec=jsbuf["list"];
    for(int &v:vec)
    {
        cout<<v<<" ";
    }
    cout<<endl;
 
    map<int,string>m=jsbuf["path"];
    for(auto &s:m)
    {
        cout<<s.first<<" "<<s.second<<endl;
    }

    return 0;
}