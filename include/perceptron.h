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

    std::vector<double> calculate_dEdt_last(std::vector<double> s, Keys a, unsigned r,
                                            std::vector<double> n_s);

    double learning_rate;
    double gamma;

   public:
    Network1(std::vector<int> layers, double learning_rate, double gamma);
    void backward(std::vector<double> s, Keys a, unsigned r, std::vector<double> n_s) override;
    std::tuple<double, Keys> find_max_qvalue(std::vector<double> qvalues);
    std::vector<double> forward(std::vector<double> input) override;
};
