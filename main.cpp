#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <math.h>
struct node{
//     true == leaf
//     false == non_leaf
    bool type;
    string code=NULL;
    long ascii;
    long size;
    char symbol;
    double frequency;
    node *left=NULL;
    node *right=NULL;
    string binary;
};

struct merge_tree{
    struct node* root = (struct node*)malloc(sizeof(struct node));
    //node * root;
    merge_tree(){
        root->left=NULL;
        root->right=NULL;
    }

};

vector<char> read();
void write(vector<char> write);
void heapify(vector<char> &arr, int n, int i);
void build_heap(vector<char> &arr, int n);
void heap_sort(vector<char> &arr, int n);
void heapify2(vector<pair<char,int> > &arr, int n, int i);
void build_heap2(vector<pair<char,int> > &arr, int n);
void heap_sort2(vector<pair<char,int> > &arr, int n);
// read sends vector<char> to frequency
//after reading call freq
void frequincies(vector<char> a);
struct node* newNode(char symb, long freq, bool type, long size,struct node *left, struct node * right);
struct node* merge(struct node* one, struct node* two);
vector<node*>  create_huffman_tree(vector<pair<char , int > > input);
void encode( vector<char> input, vector<pair<char , int > > freq );
void read_decode(string huff, string code, string decompress);
void decode(vector<char> coded_txt, vector<pair<char, string> > huffman, string decompress);
merge_tree build_decode_tree(pair<char, string> huffmantxt);
void preorder(node* n,string x, string mothercode);
//---------------------------------------------------------------
//------------------------------------------------------------------
//---------------------------------------------------------------------
void preorder(node* n,string x, string mothercode){
    if (n == NULL)
        return;
    n->code= mothercode+ x;
    preorder(n->left,"0",n->code);
    preorder(n->right,"1", n->code);
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

vector<char> read( string one){

    vector<char> input;
    fstream read1;

    read1.open(one,ios::in);
        char c=NULL;

    while (read1.get(c)) {
        input.push_back(c);
            
        }
    read1.close();
    
    return input;
}

//------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

//void write(vector<char> write){
//
//    auto end = std::chrono::system_clock::now();
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//
//    ofstream file;
//    string c= std::ctime(&end_time);
//    file.open("output_file_"+c+".txt");
//
//    for (int i=0; i<write.size(); i++) {
//         file<< write[i];
//
//       }
//
//
//      file.close();
//}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

void heapify(vector<char> &arr, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void build_heap(vector<char> &arr, int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

void heap_sort(vector<char> &arr, int n){
        build_heap(arr, n);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


void heapify2(vector<node*> &arr, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l]->frequency > arr[largest]->frequency)
        largest = l;

    if (r < n && arr[r]->frequency> arr[largest]->frequency)
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify2(arr, n, largest);
    }
}

void build_heap2(vector<node*> &arr, int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify2(arr, n, i);
}

void heap_sort2(vector<node*> &arr, int n){
    build_heap2(arr, n);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify2(arr, i, 0);
    }
}
//---------------------------------------------------------------
//------------------------------------------------------------------
//---------------------------------------------------------------------

void frequincies(vector<char> a){
    vector<pair<char,int> > b;

    for(int i=0;i<a.size();i++){
        if ( b.size()==0) {
            pair<char,int> temp;
            temp.first= a[i];
            temp.second=1;
            b.push_back(temp);
        }else{
            bool flag=false;
        for(int j=0;j<b.size();j++){
            if (a[i]==b[j].first) {
                flag=true;
                b[j].second++;
            }

        }
            if (flag==false) {
                pair<char,int> temp;
                 temp.first= a[i];
                temp.second=1;
              b.push_back(temp);
            }
            
    }
}
    
    encode(a,b);

}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

struct node* newNode(char symb, long freq, bool type, long size,struct node *left, struct node * right){
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->type=type;
    new_node->size= size;
    new_node->symbol = symb;
    new_node->frequency = freq;
    new_node->left =left;
    new_node->right = right;
    //always b null
    return new_node;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

struct node* merge(struct node* one, struct node* two){
    struct node* new_node = (struct node*)malloc(sizeof(struct node));


    new_node->type=false;
    new_node->size= one->frequency+two->frequency;
    new_node->symbol = '\0';
    new_node->frequency = new_node->size;


    if (one->frequency>two->frequency) {
         new_node->left =two;
            new_node->right = one;
    }else{
        new_node->left =one;
            new_node->right = two;

    }

    return new_node;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

    vector<node*> create_huffman_tree(vector<pair<char , int > > input){

    vector<node*> input_nodes;
        // input_nodes1 should be written into the file
    vector<node*> input_nodes1;
    struct node* temp;
    merge_tree tree;

    for (int i=0; i<input.size(); i++) {
        input_nodes.push_back(newNode(input[i].first, input[i].second, true, NULL, NULL, NULL));

    }
    
    input_nodes1=input_nodes;
  

    while (input_nodes.size()>1) {

       
        heap_sort2(input_nodes, input_nodes.size());
        
        
        temp=merge(input_nodes[1], input_nodes[0]);
        input_nodes.erase(input_nodes.begin());
        input_nodes[0]=temp;
//
        temp=NULL;

    }

    tree.root=input_nodes[0];

    preorder(tree.root,"","");

//write huffman

        

    return input_nodes1;
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

long binary_to_decimal (long num){
    long temp,rem,dec=0,b=1;
    temp=num;
    while (temp > 0)
    {
        rem = temp % 10;
        dec = dec + rem * b;
        b *= 2;
        temp /= 10;
    }
  //  cout<<dec<<endl;
    return dec;
}


void encode( vector<char> input, vector<pair<char , int > > freq ){

//    create output vector

    vector<node*> nodes = create_huffman_tree(freq);
    
    string preout="";
    for (int i=0; i<input.size(); i++) {
        for (int j=0; j<nodes.size(); j++) {
            if (nodes[j]->symbol==input[i]) {
                preout+=nodes[j]->code;
            }
        }
    }
    cout<<preout<<endl<<endl;

    vector<char> outfinal;
    
    string temp="";
    int counter=0;
    for (int j=0; j<preout.size(); j++) {
        counter++;
        temp+= preout[j];
        if(counter==8){
            long asciiVal = binary_to_decimal(stol(temp));
            unsigned char asciiChar = asciiVal;
        
            outfinal.push_back(asciiChar);
            temp="";
            counter=0;
        }
    }
    if(counter!=0){
        for(int i=8-counter;i>0;i--){
            temp='0'+temp;
        }
        long asciiVal = binary_to_decimal(stol(temp));
        unsigned  char asciiChar = asciiVal;
   
        outfinal.push_back(asciiChar);
    }
    

    
        ofstream file;
        file.open("huff.txt");
    file.ios_base::clear();
    for(int i = 0; i < nodes.size(); i++){
       unsigned char ch_symbol = nodes[i]->symbol;
        long ascii= ch_symbol;
        string str_abv = nodes[i]->code ;
        file<<ascii<<","<<str_abv;
         if (i<(nodes.size()-1)) {
             file<<endl;
        }
         
        
    }
      file.close();
        
    file.open("code.txt");
    file.ios_base::clear();
      for (int i=0; i<outfinal.size(); i++) {
           file<< outfinal[i];

         }
    file.close();

    
    double l=0;
    
//    for (int i=0; i<nodes.size(); i++) {
//         double prob=nodes[i]->frequency/input.size();
//        l+= nodes[i]->frequency *nodes[i]->code.length();
//    }
//
    double h=0;
    for (int i=0; i<nodes.size(); i++) {
       long double prob=nodes[i]->frequency/input.size();
        l+= prob *nodes[i]->code.length();
        h+= prob * log2(1.0/prob);
       }
    
    
    double eff=h/l;
    cout<<endl<<endl;
    cout<<"Average Code Word Length:  "<<l<<endl;
    cout<<"Entropy:  "<<h<<endl;
    cout<<"Coding Efficiency:  "<<eff<<endl;
    cout<<"Coding Redundancy:  "<<1-eff<<endl;

    double compression_ratio=0;
    
    compression_ratio= l/8;
    
    cout<<"compression ratio: "<<compression_ratio<<endl<<endl;
    
}

//---------------------------------------------------------------
//------------------------------------------------------------------
//---------------------------------------------------------------------

void build_rec(node * nod,char c, string s, int i){
    if(i==(s.size())){

         nod->type=true;
        nod->symbol=c;
        return;
    }else{
        if (s[i]=='1') {
            if (nod->right==NULL) {
                   struct node* newnode = newNode('-', 0, false, 0,NULL, NULL);

                nod->right=newnode;
                nod->type=false;
            }
            build_rec(nod->right, c, s, ++i);
            
        }else{
            if (nod->left==NULL) {
              struct node* newnode = newNode('-', 0, false, 0,NULL, NULL);
                nod->left=newnode;
                nod->type=false;
            }
             build_rec(nod->left, c, s, ++i);
            
        }
    }
}

void build_decode_tree(node* root,vector<pair<char, string> > huffmantxt){
 
   

     for (int i=0; i<huffmantxt.size(); i++) {
        build_rec(root, huffmantxt[i].first, huffmantxt[i].second, 0);
        
    }

 
}
// read for decoding returns vector<char>

void read_decode(string huff, string code, string decompress){
    
   
    fstream read1;
    vector<pair<char, string> > huffman;
    read1.open(huff,ios::in);
        string line="";

    while (getline(read1 , line)) {
     
            pair <char, string> x;
            stringstream m(line);
            string temp="";
            getline(m, temp, ',');
          unsigned char symbol= stol(temp);
            x.first=symbol;
            getline(m, x.second, ',');

            huffman.push_back(x);
        }
    read1.close();
    
vector<char> input;

   
    
  


      read1.open(code,ios::in);
          char c=NULL;

      while (read1.get(c)) {
          input.push_back(c);
              
          }
     
    

    read1.close();

    decode(input,  huffman, decompress);
    
}

long dec_to_bin(long n){
    string numm="";
    int binaryNum[8];
    int i = 0;
    if(n==0){
        numm="0";
    }
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
        numm+=to_string(binaryNum[j]);
    return stol(numm);
}


void decode(vector<char> coded_txt111, vector<pair<char, string> > huffman, string decompress){
    vector<char> coded_txt;
    
    merge_tree tree;
  
    for (int i=0; i<coded_txt111.size(); i++) {
        unsigned char temp =coded_txt111[i];
        long temp2= temp;

    
        long temp4= dec_to_bin(temp2);
        string temp3= to_string(temp4);
        if (temp3.size()==8) {
            for (int k=0; k<8; k++) {
                coded_txt.push_back(temp3[k]);
               
            }
             
            }else if(i!=(coded_txt111.size()-1)){
                for(int k=8-temp3.size();k>0;k--){
                temp3='0'+temp3;
                }
                for (int k=0; k<8; k++) {
                  coded_txt.push_back(temp3[k]);
             
                }
            }else{
                
                for (int k=0; k<temp3.length(); k++) {
                              coded_txt.push_back(temp3[k]);
                
            }
        
            }
        
        }
  
    build_decode_tree(tree.root, huffman);
    
    int k=0;
   
    
    vector<char> output;
    

    
while (coded_txt.size()!=0) {
    node * temp = tree.root;
        int i=0;
        char c= coded_txt[i];
         bool flag =false;
    while (flag == false) {
        switch (c) {
            case '0':
                if (temp->left != NULL && temp->left->type== false) {
                    temp = temp->left;
                    i++;
                    k++;
                    c=coded_txt[i];
    
                }else if (temp->left != NULL && temp->left->type== true){
                    flag=true;
                    output.push_back(temp->left->symbol);
//                     cout<<temp->left->symbol;
                    coded_txt.erase(coded_txt.begin(), coded_txt.begin()+i+1);
         
                }
                break;
            case '1':
                if (temp->right != NULL && temp->right->type== false) {
                    temp = temp->right;
                    i++;
                    k++;
                    c=coded_txt[i];
        
                }else if (temp->right != NULL && temp->right->type== true){
                     flag=true;
                     output.push_back(temp->right->symbol);
//                     cout<<temp->right->symbol;
                   coded_txt.erase(coded_txt.begin(), coded_txt.begin()+i+1);
            
                }
                break;
    }    }
 
}
        ofstream file;
            file.open(decompress);
    file.ios_base::clear();
                for (int s=0; s<output.size(); s++) {
                file<< output[s];
                
            }
        file.close();
     

}

int main() {
    
  //  goto c;
     pos1:
    cout<<"Please specify the service you like..."<<endl<<"for compressing press: 1"<<endl<<"for decompressing press: 2"<<endl;
    cout<<"...";
    int x;
    cin>>x;
    
    if (x==1) {
       pos2:
        cout<<"press:1 to compress a chosen file"<<endl;
        cout<<"press:2 to compress the test file"<<endl;
        int in;
        cin>>in;
        if (in ==1) {
            string name;
            cout<<"enter the path name"<<endl;
            
            cin.ignore();
            getline(cin, name);
            vector<char> test = read(name);
            frequincies(test);
        } else if(in ==2) {
            c:
            cout<<"the following file is going to be compressed"<<endl;
            cout<<"/Users/andrewsinout/Desktop/text.txt"<<endl<<endl;
            vector<char> test = read("/Users/andrewsinout/Desktop/text.txt");
            frequincies(test);
      //      goto pos4;
        }else{
            goto pos2;
        }
        
       
    } else if(x==2){
            pos3:
                cout<<"press:1 to decompress in a chosen file"<<endl;
               cout<<"press:2 to decompress in the test file"<<endl;
               int in;
               cin>>in;
        
        if (in ==1) {
                string huff="huff.txt";
                string code="code.txt";
            
            cout<<"please enter decompression file"<<endl;
            string decompress;
            cin.ignore();
            getline(cin, decompress);

//                    getline(cin, decompress);
                    read_decode(huff,code, decompress);

               } else if(in ==2) {
                   pos4:
                   cout<<"the following file was compressed"<<endl;
                   cout<<"/Users/andrewsinout/Desktop/text.txt"<<endl<<endl;
                   
                   string huff="huff.txt";
                   string code="code.txt";
                           
                          read_decode(huff,code, "out4.txt");
                          cout<<"the following is the address of the decompressed file"<<endl;
                          cout<<"/Users/andrewsinout/Desktop/Project ALGO/Project ALGO/out4.txt"<<endl;
                   
               }else{
                   goto pos3;
               }
        
         
    }else{
        goto pos1;
        
    }
  
    return 0;
}
