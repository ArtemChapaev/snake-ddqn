#include <mylib.h>
#include <neuralNetwork.h>
#include <snake.h>

#include <cstdlib>
#include <vector>

class Network1 : public NeuralNetwork {
   private:
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;

    std::vector<std::vector<double>> inputs;   // layer input - t
    std::vector<std::vector<double>> outputs;  // layer output - F(t) or h

    std::vector<int> layers;
    int num_layers;

    std::tuple<double, Keys> find_max_qvalue(Qvalues qvalues);
    double calculate_dEdt_last(unsigned s, Keys a, unsigned r, unsigned n_s);

    double learning_rate;

   public:
    Network1(vector<int> layers, double learning_rate);
    void backward(unsigned s, Keys a, unsigned r, unsigned n_s) override;
    std::vector<double> forward(std::vector<double> input) override;
}