#include <iostream>
using namespace std;
#include<string>
class Node
{
    public:
    char info;
    Node *prev;
    Node *next;
    Node(char i)
    {
        info=i;
        prev=next=nullptr;
    }
};
class DLL
{
    public:
    Node *head,*tail;
    int length;
    DLL(){head=tail=nullptr;length=0;}
    // Initialize the list with a string
    void initialize(const string& str) {
        for (char ch : str) {
            append(ch);
        }
    }
    // Append a character to the list
     void append(char c)
     {
    Node *n = new Node(c);
    if (!head) {
        head = tail = n;
    } else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
    length++;
    }
    // Insert a character at a specific position
    void InsertAt(int pos , char c)
    {
        if(pos<0 || pos >length) return;
        Node *n=new Node(c);
        // Insert at the head
        if(pos==0)
        {
            n->next=head;
            if(head) head->prev=n;
            head=n;
            if(!tail) tail=n;
        }
        // Insert at the middle or end
        else
        {
            Node *temp=head;
            for(int i=0 ; i<pos-1;i++)
            {
                temp=temp->next;
            }
            n->next=temp->next;
            n->prev=temp;
            if(temp->next) temp->next->prev=n;
            temp->next=n;
            if(!n->next) tail=n;
        }
        length ++;
    }
    // Remove a character at a specific position
    void removeAt(int pos) {
        if (pos < 0 || pos >= length) return;
        Node* temp = head;
        //remove from the head
        if (pos == 0) {
            head = head->next;
            if (head) head->prev = nullptr;
            delete temp;
        }
         //remove from the middle or end
         else {
            for (int i = 0; i < pos; ++i) temp = temp->next;
            temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            else tail = temp->prev;
            delete temp;
        }
        length--;
    }
    //get the length
    int getLength(){return length;}

    //search for a substring
     int Search(const string &subString)
     {
            if(subString.empty()) return -1;
            Node *temp=head;
            int index=0;
            while(temp)
            {
                Node *n=temp;
                int i=0;
                while(n && i<subString.size() && n->info==subString[i])
                {
                    n=n->next;
                    i++;
                }
                if(i==subString.size()) return index;
                temp=temp->next;
                index++;
            }
            return -1;
     }
  //concatenate 2 lists
   void concatenate(DLL& other) {
        if (!other.head) return;
        if (!head) {
            head = other.head;
            tail = other.tail;
        } else {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
        }
        length += other.length;
    }
  //extract substring from the list
   string extract(int start,int l)
   {
       if(start <0 || start>=length || l<=0)
       {
           return "";
       }
       Node *temp=head;
       for(int i=0 ; i<start ; i++){temp=temp->next;}
       string result;
       for(int i=0 ; i<l && temp ; i++)
       {
           result +=temp->info;
           temp=temp->next;
       }
       return result;
    }
  //replace a substring with another substring
     void ReplaceSub(const string &Old ,const string &New)
     {
         int position=Search(Old);
         while(position!=-1)
         {
             for(int i=0 ; i<Old.size();i++){removeAt(position);}
             for(int i=New.size()-1 ; i>=0 ; i--) {InsertAt(position , New[i]);}
              position=Search(Old);
         }
     }

    //display the list
     void display()
    {
        Node *temp=head;
        while(temp)
        {
            cout<<temp->info<<"";
            temp=temp->next;
        }
    }

};
int main()
{
     DLL L1 , L2;
    string input;
    //Get the first list
    cout<<"Enter String to add to list 1: ";
    cin>>input;
    for(char c:input)
    {
        L1.append(c);
    }
    //Get the second list
    cout<<"Enter String to add to list 2: ";
    cin>>input;
    for(char c:input)
    {
        L2.append(c);
    }

    //concatenate 2 lists
    L1.concatenate(L2);
    cout<<"Concatenated List: ";
    L1.display();
    cout<<endl;

    //Remove character at given index
    int index;
    cout<<"Choose a character by index to remove: ";
    cin>>index;
    L1.removeAt(index);
    cout<<"List after removal :";
    L1.display();
    cout<<endl;

    //Extract a substring
    int startIndex,length;
    cout<<"Enter Start Index and length to get a substring: ";
    cin>>startIndex>>length;
    cout<<"Substring: "<<L1.extract(startIndex,length);
    cout<<endl;

   //search for a substring
    cout<<"Search for a string in the list: ";
    cin>>input;
    int i=L1.Search(input);
    if(i !=-1)
    {
        cout<<"found at index "<<i<<endl;
    }
    else
    {
        cout<<"not found"<<endl;
    }

    // Replace a substring
    string Old , New;
    cout<<"Enter 2 substrings to replace one with another:  ";
    cin>>Old>>New;
    L1.ReplaceSub(Old,New);
    cout<<"List after replacement: ";
    L1.display();
    return 0;
}

