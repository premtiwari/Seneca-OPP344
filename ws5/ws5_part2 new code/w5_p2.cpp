#include <sstream>
#include <iostream>
#include<fstream>
#include <string>
#include <cmath>

using namespace std;

//Definition of Linked List
struct Node {

int data;

struct Node *next; //Next element in that row

struct Node *bottom;//Bottom element, i.e, next row
};


typedef struct Node node;


void insert(node* LL, int newdata, int r, int c) {


node* newnode = (node*) malloc(sizeof(node));

newnode->next = NULL; newnode->bottom = NULL;

newnode->data = newdata;

 

if(LL->next == NULL){  //Assume we have control of top left element of matrix


 

   LL->next = newnode;


 

}


 

else{


 

   node* tmp = LL->next;


 

   if(c==0){


 

     while(tmp->bottom){tmp = tmp->bottom;}


 

     tmp->bottom = newnode;


 

   }


 

   else{


 

     if(r == 0){


 

       while(tmp->next){tmp = tmp->next;}


 

       tmp->next = newnode;


 

     }


 

     else{


 

       while(tmp->bottom){tmp = tmp->bottom;}


 

     while(tmp->next){tmp = tmp->next;}


 

     tmp->next = newnode;


 

     }


 

   }


 

 


 

}


 

}



 

 


 

node* access(node *LL, int row, int col){


 

node *tmp = LL->next;


 

while(row-- > 0){


 

  tmp = tmp->bottom;


 

}


 

while(col-- > 0){


 

  tmp = tmp->next;


 

}


 

return tmp;


 

}



 

 


 

//Get input from file


 

void inputLL(node* LL, int *row, int *col, string name){


 

fstream file(&name[0], ios::in);


 

int r = 0, c = 0;


 

//int value;


 

 


 

if (file){


 

  file.clear();


 

  file.seekg(0);


 

  string line;


 

  while (getline(file, line)){


 

  stringstream ss;


 

  ss<<line;


 

  string tmp = "";


 

  int found;


 

  c=0;


 

  while(!ss.eof()){


 

    ss>>tmp;


 

    if(stringstream(tmp) >> found){


 

      insert(LL, found, r, c);


 

      c++;


 

    }


 

    tmp = "";


 

  }


 

  r++;


 

  }


 

}


 

*row = r;


 

*col = c;


 

file.close();


 

}




 

 


 

//Save input to file


 

void saveLL(node *LL, int row, int col, string name){


 

fstream file(&name[0], ios::out);


 

 


 

for(int r=0;r<row;r++){


 

  for(int c=0;c<col;c++){


 

    node *tmp = access(LL, r, c);


 

    file << tmp->data;


 

    if(c == col-1){


 

      file << endl;


 

    }


 

    else{


 

      file << " ";


 

    }


 

  }


 

}


 

}



 

 


 

void displayLL(node *LL, int row, int col){


 

 


 

for(int i=0;i<row;i++){


 

  for(int j=0;j<col;j++){


 

  node *tmp = access(LL, i, j);


 

  //while(tmp != NULL){


 

    cout<<tmp->data<<" ";


 

    //tmp = tmp->next;


 

  }


 

  cout<<endl;


 

}


 

}



 

 


 

void addLL(node *mat1, node* mat2, node* mat3, int row, int col){


 

node* btm1 = mat1->next;


 

node* btm2 = mat2->next;


 

node* btm3 = mat3->next;


 

while(btm1 != NULL && btm2 != NULL && btm3 != NULL){


 

  node* nxt1 = btm1;node* nxt2 = btm2; node* nxt3 = btm3;


 

  while(nxt1 != NULL && nxt2!= NULL && nxt3 != NULL){


 

    nxt3->data = nxt1->data + nxt2->data;


 

    nxt1 = nxt1->next;nxt2 = nxt2->next;nxt3 = nxt3->next;


 

  }


 

  btm1 = btm1->bottom;btm2 = btm2->bottom;btm3 = btm3->bottom;


 

}


 

}



 

 


 

void subLL(node *mat1, node* mat2, node* mat3, int row, int col){


 

node* btm1 = mat1->next;


 

node* btm2 = mat2->next;


 

node* btm3 = mat3->next;


 

while(btm1 != NULL && btm2 != NULL && btm3 != NULL){


 

  node* nxt1 = btm1;node* nxt2 = btm2; node* nxt3 = btm3;


 

  while(nxt1 != NULL && nxt2!= NULL && nxt3 != NULL){


 

    nxt3->data = nxt1->data - nxt2->data;


 

    nxt1 = nxt1->next;nxt2 = nxt2->next;nxt3 = nxt3->next;


 

  }


 

  btm1 = btm1->bottom;btm2 = btm2->bottom;btm3 = btm3->bottom;


 

}


 

}



 

 


 

void mulLL(node *mat1, node* mat2, node* mat3, int r1, int c1, int r2, int c2){


 

node* btm1 = mat1->next;


 

node* btm2 = mat2->next;


 

node* btm3 = mat3->next;


 

for(int i=0;i<r1;i++){


 

  for(int j=0; j<c2;j++){


 

    for(int k=0;k<r2;k++){


 

      node* element3 = access(mat3, i, j);


 

      node* element1 = access(mat2, i, k);


 

      node* element2 = access(mat1, k, j);


 

     


 

      element3->data += (element1->data * element2->data);


 

    }


 

  }


 

}


 

}


 

 


 

 


 

int determinantLL(node* mat, int row, int col){


 

int d = 0;


 

//Handlers for each row


 

 


 

node* tmp1 = mat->next->bottom;


 

node* tmp2 = mat->next->bottom->bottom;


 

for(int i=0;i<row;i++){


 

  node* tmp0 = access(mat, 0, i);


 

  node* tmp11 = access(mat, 1, (i+1)%3);node* tmp12 = access(mat, 1, (i+2)%3);


 

  node* tmp22 = access(mat, 2, (i+2)%3);node* tmp21 = access(mat, 2, (i+1)%3);


 

  d += (tmp0->data * (tmp11->data * tmp22->data - tmp12->data * tmp21->data));


 

}


 

cout << "Determinant of given matrix is: " << d << endl;


 

return d;


 

}



 

 


 

void transposeLL(node* mat, node* tmat, int row, int col){


 

for(int i=0;i<col;i++){


 

  for(int j=0;j<row;j++){


 

    node* transpose = access(tmat, i, j);


 

    node* element = access(mat, j, i);


 

    transpose->data = element->data;


 

  }


 

}


 

}



 

 


 

void inverseLL(node* mat, int row, int col){


 

float d = determinantLL(mat, row, col);


 

 


 

cout << "\n Inverse of given matrix is: \n";



 

 


 

for (int i = 0; i < row; i++){


 

  for (int j = 0; j < col; j++) {


 

    node* tmp11 = access(mat, (j + 1) %3, (i + 1) %3);


 

    node* tmp22 = access(mat, (j + 2) %3, (2 + 1) %3);


 

    node* tmp21 = access(mat, (j + 1) %3, (i + 2) %3);


 

    node* tmp12 = access(mat, (j + 2) %3, (i + 1) %3);


 

   


 

    cout << ((tmp11->data * tmp22->data) - (tmp12->data * tmp21->data))/d << "\t";


 

  }


 

  cout<<"\n";


 

}


 

}



 

 


int main(int argc, char** argv) {

    int r1, c1, r2, c2;
    node* mat1 = (node*) malloc(sizeof(node));mat1->next = NULL; mat1->bottom = NULL; mat1->data = 0;
    node* mat2 = (node*) malloc(sizeof(node));mat2->next = NULL; mat2->bottom = NULL; mat2->data = 0;
    node* mat3 = (node*) malloc(sizeof(node));mat3->next = NULL; mat3->bottom = NULL; mat3->data = 0;
    r1 = c1 = 0;

    if (argv[1] == "add")
    {

        inputLL (mat1, &r1, &c1, argv[2]);
        cout << "Your input is:" << endl;
        displayLL (mat1, r1, c1);
        r2 = c2 = 0;
        inputLL (mat2, &r2, &c2, argv[3]);
        cout << "Your input is:" << endl;
        displayLL (mat2, r2, c2);

        for(int i=0;i<r1;i++){
            for(int j=0;j<c1;j++){
                insert(mat3, 0, i, j);
            }
        }

        if (r1 == r2 && c1 == c2)
        {
        // call the function
            addLL (mat1, mat2, mat3, r1, c1);
            saveLL (mat3, r1, c1, argv[4]);
            cout << "The result is:" << endl;
            displayLL (mat3, r1, c1);
        }

        else cout << "Matrix addition not possible" ;
        
    }
    else if (argv[1] == "sub")
    {

        inputLL (mat1, &r1, &c1, argv[2]);
        cout << "Your input is:" << endl;
        displayLL (mat1, r1, c1);
        r2 = c2 = 0;
        inputLL (mat2, &r2, &c2, argv[3]);
        cout << "Your input is:" << endl;
        displayLL (mat2, r2, c2);

        for(int i=0;i<r1;i++){
            for(int j=0;j<c1;j++){
                insert(mat3, 0, i, j);
            }
        }

        if (r1 == r2 && c1 == c2)
        {
            subLL (mat1, mat2, mat3, r1, c1);
            saveLL (mat3, r1, c2, argv[4]);
            cout << "The result is:" << endl;
            displayLL (mat3, r1, c2);
        }
        else cout << "Matrix addition not possible";

    }
    else if (argv[1] == "mul")
    {

        inputLL (mat1, &r1, &c1, argv[2]);
        cout << "Your input is:" << endl;
        displayLL (mat1, r1, c1);
        r2 = c2 = 0;
        inputLL (mat2, &r2, &c2, argv[3]);
        cout << "Your input is:" << endl;
        displayLL (mat2, r2, c2);

        if (c1 == r2)
        {

            mulLL (mat1, mat2, mat3, r1, c1, r2, c2);
            saveLL (mat3, r1, c1, argv[4]);
            cout << "The result is:" << endl;
            displayLL (mat3, r1, c1);
        }
        else
        cout << "Matrix multiplication not possible";
    }
    else if (argv[1] == "det")
    {
    
        inputLL (mat1, &r1, &c1, argv[2]);
        cout << "Your input is:" << endl;
        displayLL (mat1, r1, c1);

        int d;
        if (r1 == 3 && c1 == 3)
        {
            d=determinantLL (mat1, r1, c1);
            fstream file(argv[3],ios::out);
            file << d << endl;
            file.close();
    
        }
        else cout << "Matrix determinant not possible";
    }
    else if (argv[1] == "tra")
    {
        inputLL (mat1, &r1, &c1, argv[2]);
        cout << "Your input is:" << endl;
        displayLL (mat1, r1, c1);

        transposeLL (mat1, mat3, r1, c1);
        saveLL (mat3, r1, c1, argv[3]);
        cout << "The result is:" << endl;
        displayLL (mat3, r1, c1);

    }
    else 
    {
        exit(0);
        cout << " Quit " << endl;
    }

return 0;
}