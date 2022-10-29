#include<iostream>
#include <vector>
#include<fstream>
#include<algorithm>
#include<climits>
using namespace std;
typedef long long int ll;
void heapify(vector< pair<ll,ll> > &hT, ll i)
{
    ll smallest = i;
    int size = hT.size();
    int l = 2 * i + 1;
    int r = 2 * i + 2;
   ll t=LONG_LONG_MAX;
    if (l < size && hT[l] < hT[smallest])
    {
        smallest= l;
       t=hT[l].first;
    }
    if (r < size && hT[r] < hT[smallest])
    {
       if(hT[r].first<t)
        smallest = r;
    }
    if (smallest != i)
    {
      swap(hT[i], hT[smallest]);
      heapify(hT, smallest);
    }
}

void insert(vector< pair <ll,ll> > &hT, ll newNum,ll filenum)
{
  int size = hT.size();
  if (size == 0)
  {

    hT.push_back( make_pair(newNum,filenum) );
  }
  else
  {
    hT.push_back(make_pair(newNum,filenum) );
    for (int i = size / 2 ; i >= 0; i--)
    {
      heapify(hT, i);
    }
  }
}
 pair<ll,ll> extract_Min(vector< pair<ll,ll> > &hT, ll num,int flag)
{
  pair<ll,ll>  res=hT[0];
  
  if(flag==2)
  {
    hT[0].first=num;
    heapify(hT,0);
  }
  if(flag==1)
  {
    pair<ll,ll> temp=hT[hT.size()-1];
    hT.pop_back();
    hT[0]=temp;
    heapify(hT,0);
    
  
  }
  return res;
}
void deleteNode(vector< pair<ll,ll> > &hT, ll num)
{
    int size = hT.size();
    int i=0;
    
    for(auto &ele:hT)
    {
      if (num == ele.first)
        break;
      i++;
    }
    if(i!=size)
      swap(hT[i], hT[size - 1]);

    hT.pop_back();
    for (int i = size / 2 - 1; i >= 0; i--)
    {
      heapify(hT, i);
    }
  }
  void printArray(vector< pair <ll,ll> > &hT)
  {
    for (int i = 0; i < hT.size(); ++i)
      cout << hT[i].first<< " "<<hT[i].second<<"\n";
    cout << "\n";
  }
  void createfile(string fname,vector<ll> &arr)
  {
        ofstream file(fname);
        int size=arr.size();
          for (int i = 0; i < size; i++) {
              if (i != size-1)
                  file << arr[i] << ",";
              else
                  file << arr[i];
          }
        file.close();
}
void filetemp(int chunk,string inputpath,string outputpath)
{
    string temp="temp";
    vector<ll> arr;
    ifstream inf(inputpath);
   

    cout << endl;
    int nums=0,i=0;
    while(!inf.eof())                       
    {
        string line;
        nums++;
        if(nums==chunk+1)
        {
          i++;
          sort(arr.begin(),arr.end());
          createfile(temp+to_string(i),arr);
          nums=0;
          arr.clear();
          continue;
        }  
        getline(inf, line, ',');
        ll t=stoll(line);
        arr.push_back(t);                         
    }
     
     if(arr.size()>0)
     {
          i++;
          sort(arr.begin(),arr.end());
          createfile(temp+to_string(i),arr);
          nums=0;
          arr.clear();
     }
     int numfiles=i;
     vector<ifstream> fptrs;
     for(int j=1;j<=numfiles;j++)
     {

       fptrs.push_back(ifstream(temp+to_string(j)));
     }
      vector<pair <ll,ll>> heapTree;
     for(int j=0;j<numfiles;j++)
     {  
        string line;
        getline(fptrs[j], line, ',');
      
        ll t=stoll(line);
        insert(heapTree, t,j);

     }
    ofstream file(outputpath);
    int count=1;
     while(!heapTree.empty())
     {
       string line;
       pair<ll,ll> de=extract_Min(heapTree,0,1);
       if(!heapTree.empty())
       {
           file << de.first<< ",";
       }
       else{
          file << de.first;
       }
       //cout<<de.first<<" : "<<de.second+1<<":"<<count<<"\n";
       count++;
       if(fptrs[de.second].eof())
       {
         continue;
       }
       getline(fptrs[de.second], line, ',');
       ll t=stoll(line);
       insert(heapTree,t,de.second);
       
    
     } 
    for(ll j=1;j<=numfiles;j++)
		{
      fptrs[i-1].close();
     // cout<<"sa";
			string name="temp";
			name+=to_string(j);
		  remove(name.c_str());
		}

}
int main(int argc,char* argv[])
{
  if(argc!=3)
  {
    cout<<"Invalid arguments\n";
    return 0;

  }

  vector<pair <ll,ll>> heapTree;
  string inputp(argv[1]);
  string outputp(argv[2]);
  //cout<<input<<output<<endl;
  filetemp(20000000,inputp,outputp);

}
//10**8