#include<iostream>  
#include<algorithm>
#include<map>
#include<vector>
#include<iterator>
#include<string>
#include<set>
#include<bits/stdc++.h>
#define se second
#define fi first
#define fo(i,n) for(int i=0;i<n;i++)
#define ll long long
#define l long
#define vecll vector<ll>
#define vecl vector<l>
#define veci vector<int>
#define mp make_pair
#define bg begin()
#define ed end()
#define ios ios_base::sync_with_stdio(0)
#define pb push_back
using namespace std;
int n,e;
int sum[100000];
float speedlimit(string s)
{
if(s=="light") return 60.0;
else if(s=="medium") return 45.0;
else return 30.0;
}
int dis[100000];    // maximum cities 100000
bool vis[100000];
float tim[100000]; 
//float avgvel[100000];
map<string,int> m;  // mapping city to a number to be used in algorithm
vector<pair<pair<int,int>,float>> v[100000];  // each vertex has connected vertices with weights

void dij(string s)         // for shortest distance so simple silly :)
{
memset(vis,0,sizeof(vis)); // initialising vis array to 0
for(int i=0;i<=n+1;i++) dis[i]=99999999; // infinity
multiset<pair<int,int>> mu;
mu.insert(mp(0,m[s]));
dis[m[s]]=0;        //dist,vertice
while(!mu.empty())
{auto g=mu.bg;
mu.erase(mu.bg);
int x=g->fi;   // weight
int y=g->se;  // vertice
if(vis[y]) continue;
vis[y]=true;
for(int i=0;i<v[y].size();i++)
{int a=v[y][i].fi.fi;  // vertice
int w=v[y][i].fi.se;   // weight of edge	
if(dis[y]+w<dis[a])
{dis[a]=dis[y]+w;
mu.insert(mp(dis[a],a));
}
}
}	
}                           //O(ElogV)   E- no of roads , V-no of cities


void dijt(string s)         // for shortest time 
{
memset(vis,0,sizeof(vis)); // initialising vis array to 0
for(int i=0;i<=n+1;i++) tim[i]=99999999; // infinity
multiset<pair<float,int>> mu;
mu.insert(mp(0.0,m[s])); 
sum[m[s]]=0; 
tim[m[s]]=0.0;        //time,vertice
while(!mu.empty())
{auto g=mu.bg;
mu.erase(mu.bg);
float x=g->fi;   // time
int y=g->se;  // vertice
if(vis[y]) continue;
vis[y]=true;
for(int i=0;i<v[y].size();i++)
{int a=v[y][i].fi.fi;  // vertice
float w=v[y][i].se+0.0;   // velocity of edge
int dist=v[y][i].fi.se;	
if(tim[y]+(float((float)dist+0.0)/w)<tim[a])
{tim[a]=tim[y]+(float((float)dist+0.0)/w)+0.0;
mu.insert(mp(tim[a],a));
sum[a]+=sum[y]+dist;
}
}
}	
}
int main()
{
cout<<"              hello and welcome to xmap system\n";
cout<<"              please enter the number of cities\n";
cin>>n;
cout<<"----------------------------------------------------------------------\n";
cout<<"\n please enter the total number of roads between all of the cities\n";
cin>>e;
cout<<"----------------------------------------------------------------------\n";
cout<<"enter city1 then city2 , and also traffic density on road then distance between them\n";
string s,s2,s3;
int g=0,dist;

fo(i,e)
{
cin>>s;
cin>>s2;
cin>>s3;
cin>>dist;

if(!m[s])
m[s]=++g;
if(!m[s2])
m[s2]=++g;
v[m[s]].emplace_back(mp(mp(m[s2],dist),speedlimit(s3)));  //vector for connecting cities storing their distances and speed limits on their way
v[m[s2]].emplace_back(mp(mp(m[s],dist),speedlimit(s3)));

}
cout<<"----------------------------------------------------------------------\n";

cout<<"enter source\n";
cin>>s;

dij(s);
cout<<"enter destination\n";
cin>>s2;
cout<<"so the shortest distance between the "<<s<<" and "<<s2<<" is "<<dis[m[s2]]<<" metres"<<endl<<endl;
cout<<"----------------------------------------------------------------------\n";
cout<<"wait till we calculate shortest time for you\n";

dijt(s);
cout<<"so the shortest time between the "<<s<<" and "<<s2<<" is "<<tim[m[s2]]<<" hours"<<endl<<endl;

cout<<"----------------------------------------------------------------------\n";


cout<<"so the extra distance travelled is "<<(sum[m[s2]])-dis[m[s2]]<<" metres "<<endl;
cout<<"----------------------------------------------------------------------\n";

cout<<"hence the extra fuel spent is "<<(float(sum[m[s2]])-(float)dis[m[s2]] +0.0)/22.0<<" lites"<<endl;
cout<<"----------------------------------------------------------------------\n";

if(sum[m[s2]]-dis[m[s2]]==0.0)
{
cout<<"wow no extra fuel spent hurray :)\n  have a safe journey  and thank you for using xmaps";
return 0;	
}
cout<<"Drive safe life once gone never comes back :)\n  and thank you for using xmaps";





return 0;	
}