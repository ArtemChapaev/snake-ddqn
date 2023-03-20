#include "aiControl.h"

Keys aiControl::get_direction(unsigned s, Keys a, unsigned r, unsigned n_s) {
    /*
         double loss = network.compute_loss(s, a, r, n_s);
         network.update_weights(s, a, r, n_s);

         Qvalues next_qvalues = network.predict(n_s);

         Keys next_action = Keys::up;
         // e-greedy algorithm
         if ((rand() % 10) / 10 < epsilon) {
             rand() % 4 because we pick random direction
         next_action = static_cast<Keys>(rand() % 4);
         } else {
             double max_qvalue = 0;
             [max_qvalue, next_action] = find_max_qvalue(next_qvalues);
         }
         epsilon *= 0.99;

         return next_action;
    */
}

/*
std::tuple<double, Keys> find_max_qvalue(Qvalues qvalues) {
    double max_qvalue = qvalues.up_qvalue;
    Keys next_action = Keys::up;

    if (next_qvalues.right_qvalue > max_qvalue) {
        max_qvalue = next_qvalues.right_qvalue;
        next_action = Keys::right;
    }
    if (next_qvalues.down_qvalue > max_qvalue) {
        max_qvalue = next_qvalues.down_qvalue;
        next_action = Keys::down;
    }
    if (next_qvalues.left_qvalue > max_qvalue) {
        max_qvalue = next_qvalues.left_qvalue;
        next_action = Keys::left;
    }
    return std::make_tuple(max_qvalue, next_action);
}
*/

/*
double calculate_mean_MSE(Qvalues predicted_qvalues, Qvalues target_qvalues) {
    double up_qvalue_delta = predicted_qvalues.up_qvalue - target_qvalues.up_qvalue;
    double right_qvalue_delta = predicted_qvalues.right_qvalue - target_qvalues.right_qvalue;
    double down_qvalue_delta = predicted_qvalues.down_qvalue - target_qvalues.down_qvalue;
    double left_qvalue_delta = predicted_qvalues.left_qvalue - target_qvalues.left_qvalue;

    double mean_MSE = (up_qvalue_delta * up_qvalue_delta + right_qvalue_delta * right_qvalue_delta +
                        down_qvalue_delta * down_qvalue_delta + left_qvalue_delta * left_qvalue_delta) / 4;
}
*/

/*
double Network::compute_loss(unsigned s, Keys a, unsigned r, unsigned n_s) {
    Qvalues predicted_next_qvalues = network.predict(n_s);
    auto [max_qvalue, next_action] = find_max_qvalue(predicted_next_qvalues);
    double target = r + gamma * next_qvalue;

    // bring to Qvalues for next calculating loss
    Qvalues target_qvalues{target, target, target, target};
    Qvalues predicted_current_qvalues = network.predict(s);

    return calculate_mean_MSE(predicted_current_qvalues, target_qvalues);
}
*/