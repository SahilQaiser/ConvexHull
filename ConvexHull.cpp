#include<iostream>
#include<Math.h>
using namespace std;

class Point {
	
	public:
	int x,y;    						//1st Feb
	Point()
	{	
		x=y=0;
	}
	Point(int a,int b)
	{
		x=a;y=b;
	}
	friend istream &operator>>(istream &in, Point &P) {		
		cout<<"Enter x ";
		in>>P.x;
		cout<<"Enter y ";
		in>>P.y;
		return in;
	}
	friend ostream &operator<<(ostream &o, Point &P) {
		o<<"("<<P.x<<", "<<P.y<<")";
		return o;
	}
	int gety(){return y;}
	int getx(){return x;}
	bool operator>(Point p2);
	double dist();
	bool isLE180(Point p2,Point p3){		//1st Feb DS
		if((p2.x-x)*(p3.y-p2.y)<=(p2.y-y)*(p3.x-p2.x))
		{
			return true;
		}
		else 
		return false;
	}
}p0;	
bool Point::operator>(Point p2) {			//1st Feb DS
		if(((x-p0.x)*(p2.y-p0.y))<(((p2.x-p0.x)*(y-p0.y))) || (x-p0.x)*(p2.y-p0.y)==(p2.x-p0.x)*(y-p0.y) && dist()>p2.dist())
		{
			return true;
		}		
		else return false;
	}
double Point::dist(){							//1st Feb
		return (sqrt(((x-p0.x)*(x-p0.x))+((y-p0.y)*(y-p0.y))));
	}
void read(Point a[],int n) {
	cout<<"Read "<<n<<" Points: \n";
	for(int i=0;i<n;i++)
		cin>>a[i];		
}
void print(Point a[],int n) {
	for(int i=0;i<n;i++)
		cout<<a[i];		
}
Point min(Point a[],int n)
{
	Point mn=a[0];
	for(int i=1;i<n;i++) {
		int y=a[i].gety();
		int x=a[i].getx();
		if(y<mn.gety() || (y==mn.gety() && x<mn.getx()))
			mn=a[i];
	}
	return mn;
}
void bubbleSort(Point a[], int n)  			//1st Feb DS
{
	for(int i=1; i<n; i++)
	{
		bool sorted=true;
		for(int j=0; j<n-i; j++)
		{
			if(a[j]>a[j+1]){
				Point temp = a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				sorted=false;
			}
		}
		if(sorted)
		break;
	}
}
class Node{
	public:
	Point data;
	Node *next,*prev;	
};
class DCLL{
	Node *first;
	public:
		DCLL(){
			first = NULL;
		}
		int size();
		Node* getFirst(){
			return first;
		}
		void create(Point a[],int n);
		void del(Node *ad);
		void display();
};
int DCLL::size(){
	if(first==NULL)
		return 0;
	int sz=1;
	Node *cur=first;
	while(cur->next!=first){
		cur=cur->next;
		sz++;
	}
	return sz;
}
void DCLL::create(Point a[],int n){
	Node *cur,*pr;
	for(int i=0; i<n; i++)
	{
		if(i==0)
		{
			first=cur=new Node();
		}
		else {
			cur->next=new Node();
			pr=cur;
			cur=cur->next;
			cur->prev=pr;
		}
		cur->data=a[i];
	}
	first->prev=cur;
	cur->next=first;
}
void DCLL::del(Node *ad){
	Node *dl=ad;
	Node *nxt=dl->next;
	Node *pr=dl->prev;
	if(size()==1)
		first=NULL;
	pr->next=nxt;
	nxt->prev=pr;
	if(first==ad){
		first=nxt;
	}
	dl->next = dl->prev=NULL;
	delete(dl);
}
void DCLL::display()
{
	Node *cur=first;
	cout<<"[";
	while(cur->next!=first)
	{
		cout<<cur->data<<", ";
		cur=cur->next;
	}
	cout<<cur->data<<"]";	
}
void getConvexHull(Point a[],int n)
{
	DCLL l;
	l.create(a,n);
	//l.display();
	Node *x=l.getFirst(),*xr,*xrr,*x0;
	x0=x;
	xr=x->next;
	xrr=xr->next;
	while(xrr!=x0 || xr != xrr)
	{
		xrr=xr->next;
		if(x->data.isLE180(xr->data,xrr->data)){
			l.del(xr);
			xr=x;
			x=x->prev;
		}
		else
		{
			x=xr;
			xr=xrr;
		}
	}
	cout<<endl<<"Vertex of Convex HULL"<<endl;
	l.display();
}
int main()
{
	int n;
	cout<<"How many Points ";
	cin>>n;
	Point *x=new Point[n];
	read(x,n);
	Point m=min(x,n);
	cout<<m<<endl;
	p0=m;
	cout<<endl<<"UnSorted Points : ";
	print(x,n);
	bubbleSort(x,n);
	cout<<endl<<"Sorted Points : ";
	print(x,n);
	getConvexHull(x,n);
	return 0;
}
