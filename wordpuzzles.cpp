#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
int to[1000500][27],sn=1;
int link[1000050]={0};
int term[1000050]={0};
map<int,string> m;
map<string,pair<int,pair<int,int> > >m2;
int L,C,n;
void add_str(string pat)
{
	int curr=0;
	string s="";
	// cout<<pat<<endl;
	for(unsigned int i=0;i<pat.length();i++)
	{
		s+=pat[i];

		if(to[curr][pat[i]-'A']==-1)
		{
			to[curr][pat[i]-'A']=sn++;

		}
		curr = to[curr][pat[i]-'A'];
		m[curr]=s;

	}
	term[curr]=curr;
	//cout<<m[curr]<<endl;
}
void push_links()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		// cout<<"too much"<<endl;
		int V=q.front();
		q.pop();
		// int V=front;
		int U=link[V];
		// cout<<"V "<<V<<"  "<<"U "<<U<<endl;
		// if(!term[V]){ term[U] = term[V]; }
		for(int i=0;i<26;i++)
		{

			int c = to[V][i];
			if(c!=-1)
			{
				if(V==0)
					link[c]=0;
				else
				{
					// link[c]=max(0,to[U][i]);
					int temp=U;
					while(1)
					{
						if(to[temp][i]!=-1||temp==0)
						{
							link[c]=max(0,to[temp][i]);
							break;
						}
						else if(to[temp][i]==-1)
						{
							temp=link[temp];
							continue;
						}
						 
					}
				}
				q.push(c);
			}
			// else
			// {
			// 	to[V][c] = to[U][c];
			// }
			// cout<<"c is "<<c<<" linkc "<<link[c]<<endl;
		}
	}
}
void process(char s, int direction, int i, int j, int *curr1)
{
	// int curr=0;
	int curr = *curr1;
	int c=s-'A';
	while(to[curr][c]==-1)
	{
		curr=link[curr];
		if(curr==0&&to[curr][c]==-1)
		{
			break;
		}
		// continue;
	}
	// cout<<to[curr][c]<<endl;
	if(to[curr][c]!=-1)
	{
		//cout<<"AT81"<<endl;
		int node = to[curr][c];
		curr=node;
		if(term[node])
		{
			// int lenout = m[node].length();
			// cout<<i-lenout+1<<"to "<<i<<" "<<s[i]<<" index in pattern " << i <<" node is "<<node<<" "<<m[node]<<endl;
			
			// cout<<m[node]<<endl;
				m2[m[node]]=mp(direction,mp(i,j));
			
		}
		// cout<<"link["<<node<<"] "<<link[node]<<endl;
		while(link[node]>0&&term[link[node]]>0)
		{
			// int lenout = m[link[node]].length();
			

				m2[m[link[node]]]=mp(direction,mp(i,j));
				// cout<<i-lenout+1<<"to "<<i<<" "<<s[i]<<" index in pattern " << i <<" node is "<<link[node]<<" "<<m[link[node]]<<endl;
				node = link[node];
		}
	}
	*curr1 = curr;
}
void patternsearch(char text[1010][1010], int direction)
{
	//0--H 1--V 2--L 3--R
	if(direction == 0 )
	{
		for(int i=0;i<L;i++)
		{
			int curr=0;
			for(int j=0;j<C;j++)
			{
				process(text[i][j],direction,i,j,&curr);
			}
		}
	}
	if(direction== 1)
	{
		for(int j=0;j<C;j++)
		{
			int curr=0;
			for(int i=0;i<L;i++)
			{
				process(text[i][j],direction,i,j,&curr);
			}
	}	}
	if(direction== 2)
	{
		int limit1i=0;//fixed initially
		int limit2j=C-1;//fixed initially
		int limit2i=0;
		int limit1j=C-1;
		
		while(1)
		{
			int i=limit1i;
			int j=limit1j;
			int curr=0;
			while(i<=limit2i&&j<=limit2j)
			{
				process(text[i][j],direction,i,j,&curr);
				i++;j++;
			}
			//cout<<endl;
			limit1j--;
			limit2i++;
			if(limit1j<0)
			{
				
				limit1j++;
				limit1i++;
			}
			if(limit2i>=L)
			{
				
				limit2i--;
				limit2j--;
			}
			if(limit1i>=0&&limit1j>=0&&limit2i>=0&&limit2j>=0&&limit1i==limit2i&&limit1j==limit2j)
			{
				process(text[limit1i][limit1j],direction,i,j,&curr);
				break;
			}
		}
		
	}
	if(direction == 3)
	{
		int limit1i=0;
		int limit2i=0;
		int limit1j=0;
		int limit2j=0;
		while(1)
		{
			int i=limit1i;
			int j=limit1j;
			int curr=0;
			while(i<=limit2i&&j>=limit2j)
			{
				process(text[i][j],direction,i,j,&curr);
				i++;j--;
			}
			//cout<<endl;

			limit1j++;
			limit2i++;
			if(limit1j>=C)
			{
				limit1j--;
				limit1i++;
			}
			if(limit2i>=L)
			{
				limit2j++;
				limit2i--;
			}
			if(limit1i>=0&&limit1j>=0&&limit2i>=0&&limit2j>=0&&limit1i==limit2i&&limit1j==limit2j)
			{
				process(text[limit1i][limit1j],direction,i,j,&curr);
				break;
			}
		
		}
	}
		
		
}
string reverse1(string pat)
{
	string s="";
	for(int i=pat.length()-1;i>=0;i--)
	{
		s+=pat[i];
	}
	return s;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{


		memset(to,-1,sizeof(to));
		memset(link,0,sizeof(link));
		memset(term,0,sizeof(term));
		sn=1;
		m.clear();
		m2.clear();
		cin>>L>>C>>n;
		char text[1010][1010];
		for(int i=0;i<L;i++)
		{
			for(int j=0;j<C;j++)
			{
				cin>>text[i][j];
			}
		}
		string pat[n];
		string rev[n];
		memset(to,-1,sizeof(to));
		for(int i=0;i<n;i++)
		{
			cin>>pat[i];
			add_str(pat[i]);
			rev[i]=reverse1(pat[i]);
			if(pat[i]!=rev[i])
			{
				add_str(rev[i]);	
			}
			
		}
		// for(int i=0;i<n;i++)
		// {
		// 	for(int j=0;j<n;j++)
		// 	{
		// 		if(pat[i]==rev[j])
		// 		{
		// 			rev[j]="";
		// 		}
		// 	}
		// }
		
		push_links();
		// for(int i=0;i<sn;i++)
		// {
		// 	cout<<"term["<<i<<"] "<<term[i]<<endl;
		// }
		// for(int i=0;i<sn;i++)
		// {
		// 	cout<<"link["<<i<<"] "<<link[i]<<endl;
		// }
		// for(int i=0;i<sn;i++)
		// {
		// 	for(int j=0;j<26;j++)
		// 	{
		// 		cout<<to[i][j]<<" ";
		// 	}
		// 	cout<<endl;
		// }
		for(int i=0;i<4;i++)
		{
			patternsearch(text,i);
		}
		
		for(int i=0;i<n;i++)
		{
			if(m2.find(pat[i])==m2.end()&&m2.find(rev[i])==m2.end())
			{
				continue;
			}
			bool flag=false;
			if(m2.find(pat[i])!=m2.end())
			{
				flag=true;
			}
			if(flag)
			{
				pair<int,pair<int,int> > v= m2[pat[i]];
				int dir=v.first;
				pair<int,int> rc = v.second;
				int r=rc.first;
				int c=rc.second;
				if(dir==0)
				{
					cout<<r<<" "<<c-pat[i].length()+1<<" C"<<endl;
				}
				if(dir==1)
				{
					cout<<r-pat[i].length()+1<<" "<<c<<" E"<<endl;;
				}
				if(dir==2)
				{
					cout<<r-pat[i].length()+1<<" "<<c-pat[i].length()+1<<" D "<<endl;
				}
				if(dir==3)
				{
					cout<<r-pat[i].length()+1<<" "<<c+pat[i].length()-1<<" F"<<endl;;
				}
	
			}
			else
			{
				
				pair<int,pair<int,int> > v= m2[rev[i]];
				int dir=v.first;
				pair<int,int> rc = v.second;
				int r=rc.first;
				int c=rc.second;
				if(dir==0)
				{
					cout<<r<<" "<<c<<" G"<<endl;
				}
				if(dir==1)
				{
					cout<<r<<" "<<c<<" A"<<endl;
				}
				if(dir==2)
				{
					cout<<r<<" "<<c<<" H"<<endl;
				}
				if(dir==3)
				{
					cout<<r<<" "<<c<<" B"<<endl ;
				}
				
			}
			
			
		}
		
	}
		

	
	
	
}
