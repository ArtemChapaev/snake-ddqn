#include <vector>
#include <cstdlib>

#include <snake.h>
#include <neuralNetwork.h>

class Network1 : public NeuralNetwork {
    private:
        std::vector<std::vector<std::vector<double>>> weights;
        std::vector<std::vector<double>> biases;

        std::vector<std::vector<double>> outputs;
        std::vector<std::vector<double>> errors;

        std::vector<int> layers;
        int num_layers;

        std::tuple<double, Keys> find_max_qvalue(Qvalues qvalues);
        double calculate_dEdt_last(unsigned s, Keys a, unsigned r, unsigned n_s);
        double relu(double x);
    public:
        Network1(vector<int> layers);
        void backward(unsigned s, Keys a, unsigned r, unsigned n_s) override;
        std::vector<double> forward(std::vector<double> input) override;
        void update_weights() override;
}