#include <iostream>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

const auto INPUT = 2;
const auto HIDDEN = 30;
const auto LR = 0.01;
const auto EPOCH = 1000000;


double sigmoid(double x) {
  return 1 / ( 1 + exp(-x));
}

constexpr double d_sigmoid(double x) {
  return x * (1 - x);
}

vector<vector<double>>matmul(vector<vector<double>> vv1, vector<vector<double>> vv2){
  int i, j ,k;
  double temp;

  const size_t vv1_row = vv1.size();
  const size_t vv1_column = vv1[0].size();
  if(vv1_column!=vv2.size()) cout << "error" << endl;
  const size_t vv2_column = vv2[0].size();

  vector<vector<double>>result (vv1_row, vector<double>(vv2_column));

  for(i=0; i<vv1_row; i++){
    for(j=0; j<vv2_column; j++){
      temp = 0;
      for(k=0; k<vv1_column; k++){
        temp += vv1[i][k] * vv2[k][j];
      }
      result[i][j] = sigmoid(temp);
    }
  }
  return result;
}


int main(){
    int i, j, k, l;
    double temp;

    //XOR train data
    vector<vector<double>>train_x = {{0,0},{0,1},{1,0},{1,1}};
    vector<double>train_y = {0,1,1,0};

    //network
    vector<vector<double>>w1 (INPUT, vector<double>(HIDDEN));
    vector<double>w2 (HIDDEN);
    vector<vector<double>>o1 (4, vector<double>(HIDDEN));
    vector<double>output (4);

    //initialize weights with random value
    for(i=0; i<INPUT; i++){
      for(j=0; j<HIDDEN; j++){
        w1[i][j] = (double)rand() / (double)RAND_MAX;
      }
    }

    for(i=0; i<HIDDEN; i++){
      w2[i] = (double)rand() / (double)RAND_MAX;
    }

    //train
    cout << "XOR INPUT" << endl;
    cout << " (0, 0)   (1, 0)   (0, 1)   (1, 1)" << endl;

    cout << "-----------------------------------"  << endl;
    cout << "XOR OUTPUT" << endl;
    cout << "-----------------------------------"  << endl;

    for(l=0; l<EPOCH+1; l++){
      if(l%100000==0) {
        for(i=0; i<4; i++){
          cout << fixed << output[i] << ' ';
        }
        cout << " / EPOCH : " << l << endl;
      }

      //forward
      //input layer
      o1 = matmul(train_x, w1);

      //hidden layer
      for(i=0; i<4; i++){
          temp = 0;
          for(k=0; k<HIDDEN; k++){
            temp += o1[i][k] * w2[k];
          }
        output[i] = sigmoid(temp);
        }

      //backword
      //hidden layer
      for(i=0; i<4; i++){
        for(j=0; j<HIDDEN; j++){
            w2[j] -= LR * o1[i][j] * d_sigmoid(output[i]) * (output[i] - train_y[i]);
        }
      }
      //input layer
      for(i=0; i<4; i++){
        for(j=0; j<INPUT; j++){
          for(k=0; k<HIDDEN; k++){
            w1[j][k] -= LR * train_x[i][j] * d_sigmoid(o1[i][k]) * d_sigmoid(output[i]) * (output[i] - train_y[i]) * w2[k];
          }
        }
      }
    }

  return 0;
}
