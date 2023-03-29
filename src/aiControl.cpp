#include "aiControl.h"

Keys aiControl::get_direction(unsigned s, Keys a, unsigned r, unsigned n_s) {
    /*
         network.backward(s, a, r, n_s);
         network.update_weights();

         Qvalues next_qvalues = network.forward(n_s);

         Keys next_action = Keys::up;
         // e-greedy algorithm
         if ((rand() % 10) / 10 < epsilon) {
            // rand() % 4 because we pick random direction
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
<type> network::calculate_dE_dt_last(unsigned s, Keys a, unsigned r, unsigned n_s) {
    // find target(y) of current state
    Qvalues predicted_next_qvalues = predict(n_s);
    auto [max_qvalue, next_action] = find_max_qvalue(predicted_next_qvalues);
    double target = r + gamma * max_qvalue;

    // bring to Qvalues for next calculating loss
    // Qvalues target_qvalues{target, target, target, target};


    // calculate sequentially for each dE_dt_last = dE_dz_i * dz_dt_last

    Qvalues predicted_current_qvalues = predict(s);

    <type> dE_dt_last;
    for (int i = 0;i < 4;++i) {
        double dE_dz_i = predicted_current_qvalues[i] * (predicted_current_qvalues[i] - target) / 2;
        double dz_dt_last = predicted_current_qvalues[i] * (1 - predicted_current_qvalues[i]);
        dE_dt_last[i] = dE_dz_i * dz_dt_last;
    }

    return dE_dt_last;
}
*/

/*
void network::backward(unsigned s, Keys a, unsigned r, unsigned n_s) {
    <type> dE_dt_last = calculate_dE_dt_last(s, a, r, n_s);
    // TO DO

}
*/