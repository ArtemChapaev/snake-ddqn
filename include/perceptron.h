#include <math_funcs.h>
#include <neuralNetwork.h>
#include <snake.h>

#include <cstdlib>
#include <vector>

struct Qvalues {
    Qvalues(double up = 0, double down = 0, double left = 0, double right = 0)
        : up(up), down(down), left(left), right(right){};

    double up;
    double down;
    double left;
    double right;
};

Qvalues vector_to_qvalues_struct(const std::vector<double> &);
std::tuple<double, Keys> find_max_qvalue(const Qvalues &);

class Perceptron : public NeuralNetwork {
   public:
    Perceptron(std::vector<int> &layers, double learning_rate = 0.01, double gamma = 0.99);

    void backward(std::vector<double> &, Keys, unsigned, std::vector<double> &) override;
    std::vector<double> forward(std::vector<double> &) override;

    std::vector<std::vector<std::vector<double>>> get_weights();
    std::vector<std::vector<double>> get_biases();

    void set_weights(const std::vector<std::vector<std::vector<double>>> &);
    void set_biases(const std::vector<std::vector<double>> &);

   private:
    std::vector<double> calculate_dEdt_last(std::vector<double> &, Keys, unsigned, std::vector<double> &);

    std::vector<std::vector<double>> calculate_dEdW(const std::vector<double> &, const std::vector<double> &);

    std::vector<int> layers;
    int num_layers;

    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;

    std::vector<std::vector<double>> inputs;   // layer input - t
    std::vector<std::vector<double>> outputs;  // layer output - F(t) or h

    double learning_rate;
    double gamma;
};
