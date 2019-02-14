#include <iostream>
#include <cmath>

using namespace std;

//number of neuron
const auto INPUT_NUM = 2;
const auto FIRST = 3;
const auto SECOND = 2;
const auto OUTPUT = 2;


double sigmoid(double x) {
  return 1 / ( 1 + exp(-x));
}


int main(){
    int i, j;
    double temp;

    cout << "first layer" << endl;

    double input[INPUT_NUM] = {1.0, 0.5};
    double weight_1[INPUT_NUM][FIRST]= { {0.1, 0.3, 0.5},{0.2, 0.4, 0.6} };
    double bias_1[FIRST]= {0.1, 0.2, 0.3};
    double layer_1[FIRST] = {};

    for(i=0; i<extent<decltype(weight_1),1>::value; i++){
        temp = 0;
        for(j=0; j<extent<decltype(input),0>::value; j++){
            temp += input[j] * weight_1[j][i];
        }
        temp += bias_1[i];
        layer_1[i] = sigmoid(temp);
        cout << layer_1[i] << endl;
        }

    cout << "second layer" << endl;

    double weight_2[FIRST][SECOND]= { {0.1, 0.4},{0.2, 0.5}, {0.3, 0.6} };
    double bias_2[SECOND]= {0.1, 0.2};
    double layer_2[SECOND] = {};

    for(i=0; i<extent<decltype(weight_2),1>::value; i++){
        temp = 0;
        for(j=0; j<extent<decltype(layer_1),0>::value; j++){
            temp += layer_1[j] * weight_2[j][i];
        }
        temp += bias_2[i];
        layer_2[i] = sigmoid(temp);
        cout << layer_2[i] << endl;
        }

    cout << "output layer" << endl;

    double weight_3[SECOND][OUTPUT]= { {0.1, 0.3},{0.2, 0.4} };
    double bias_3[OUTPUT]= {0.1, 0.2};
    double output[OUTPUT] = {};

    for(i=0; i<extent<decltype(weight_3),1>::value; i++){
        temp = 0;
        for(j=0; j<extent<decltype(layer_2),0>::value; j++){
            temp += layer_2[j] * weight_3[j][i];
        }
        temp += bias_3[i];
        output[i] = temp;   //identity function
        cout << output[i] << endl;
        }

    return 0;
}
