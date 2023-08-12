#include "menu.h"

// separate file for logos, so as not to litter the code

void MainMenu::print_logo() {
    // There are often lags on macOS, when menu is swapped
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
          ▄████████ ███▄▄▄▄      ▄████████    ▄█   ▄█▄    ▄████████ 
         ███    ███ ███▀▀▀██▄   ███    ███   ███ ▄███▀   ███    ███ 
         ███    █▀  ███   ███   ███    ███   ███▐██▀     ███    █▀  
         ███        ███   ███   ███    ███  ▄█████▀     ▄███▄▄▄)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ███████████ ███   ███ ▀███████████ ▀▀█████▄    ▀▀███▀▀▀
                ███ ███   ███   ███    ███   ███▐██▄     ███    █▄
          ▄█    ███ ███   ███   ███    ███   ███ ▀███▄   ███    ███
        ▄████████▀   ▀█   █▀    ███    █▀    ███   ▀█▀   ██████████
     )";
}

void PauseMenu::print_logo() {
    std::cout << R"(
           ▄███████▄    ▄████████ ███    █▄     ▄████████    ▄████████
          ███    ███   ███    ███ ███    ███   ███    ███   ███    ███
          ███    ███   ███    ███ ███    ███   ███    █▀    ███    █▀
          ███    ███   ███    ███ ███    ███   ███         ▄███▄▄▄)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀█████████▀  ▀███████████ ███    ███ ▀███████████ ▀▀███▀▀▀
          ███          ███    ███ ███    ███          ███   ███    █▄
          ███          ███    ███ ███    ███    ▄█    ███   ███    ███
         ▄████▀        ███    █▀  ████████▀   ▄████████▀    ██████████
  )";
}

void LeaderboardMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████  ▄████████  ▄██████▄     ▄████████ ████████▄     ▄████████
          ███    ███   ███    ███ ███    ███ ███    ███   ███    ███ ███   ▀███   ███    ███
          ███    ███   ███    █▀  ███    █▀  ███    ███   ███    ███ ███    ███   ███    █▀
         ▄███▄▄▄▄██▀  ▄███▄▄▄     ███        ███    ███  ▄███▄▄▄▄██▀ ███    ███   ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ███        ███    ███ ▀▀███▀▀▀▀▀   ███    ███ ▀███████████
        ▀███████████   ███    █▄  ███    █▄  ███    ███ ▀███████████ ███    ███          ███
          ███    ███   ███    ███ ███    ███ ███    ███   ███    ███ ███   ▄███    ▄█    ███
          ███    ███   ██████████ ████████▀   ▀██████▀    ███    ███ ████████▀   ▄████████▀
          ███    ███                                      ███    ███
    )";
}

void SettingsGeneralMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀
    )";
}

void SettingsSnakeMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀
    )";
}

void SettingsMapMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀
    )";
}

void SettingsGraphicMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀
    )";
}

void SettingsControlMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀
    )";
}

void CustomMapSettingsMenu::print_logo() {}

void SavedSettingsMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀
    )";
}

void ColorsMenu::print_logo() {
    std::cout << R"(
           ▄████████    ▄████████     ███         ███      ▄█  ███▄▄▄▄      ▄██████▄     ▄████████
          ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███  ███▀▀▀██▄   ███    ███   ███    ███
          ███    █▀    ███    █▀     ▀███▀▀██    ▀███▀▀██ ███▌ ███   ███   ███    █▀    ███    █▀
          ███         ▄███▄▄▄         ███   ▀     ███   ▀ ███▌ ███   ███  ▄███          ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ▀███████████ ▀▀███▀▀▀         ███         ███     ███▌ ███   ███ ▀▀███ ████▄  ▀███████████
                 ███   ███    █▄      ███         ███     ███  ███   ███   ███    ███          ███
           ▄█    ███   ███    ███     ███         ███     ███  ███   ███   ███    ███    ▄█    ███
         ▄████████▀    ██████████    ▄████▀      ▄████▀   █▀    ▀█   █▀    ████████▀   ▄████████▀

)";
}

void TitlesMenu::print_logo() {
    std::cout << R"(
         ▄████████    ▄████████    ▄████████ ████████▄   ▄█      ███        ▄████████
        ███    ███   ███    ███   ███    ███ ███   ▀███ ███  ▀█████████▄   ███    ███
        ███    █▀    ███    ███   ███    █▀  ███    ███ ███▌    ▀███▀▀██   ███    █▀
        ███         ▄███▄▄▄▄██▀  ▄███▄▄▄     ███    ███ ███▌     ███   ▀   ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ███        ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ███    ███ ███▌     ███     ▀███████████
        ███    █▄  ▀███████████   ███    █▄  ███    ███ ███      ███              ███
        ███    ███   ███    ███   ███    ███ ███   ▄███ ███      ███        ▄█    ███
        ████████▀    ███    ███   ██████████ ████████▀  █▀      ▄████▀    ▄████████▀
                     ███    ███
    )";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(

                              Educational project at BMSTU for OOP practice

                                          Devs: Misha Fedotov
                                                      &
                                                Artem Chapaev

                                     Team Lead: Alexey Kozov


                                               Enter to exit
    )";
}

void GameInformationMenu::print_logo() {
    std::cout << R"(
         ▄████████    ▄████████  ▄█        ▄█             ▄█  ███▄▄▄▄      ▄████████  ▄██████▄
        ███    ███   ███    ███ ███       ███            ███  ███▀▀▀██▄   ███    ███ ███    ███
        ███    █▀    ███    █▀  ███       ███            ███▌ ███   ███   ███    █▀  ███    ███
        ███         ▄███▄▄▄     ███       ███            ███▌ ███   ███  ▄███▄▄▄     ███    ███)";
    usleep(1);
    std::cout << "\033[0m" << std::flush;
    std::cout << R"(
        ███        ▀▀███▀▀▀     ███       ███            ███▌ ███   ███ ▀▀███▀▀▀     ███    ███ 
        ███    █▄    ███    █▄  ███       ███            ███  ███   ███   ███        ███    ███ 
        ███    ███   ███    ███ ███▌    ▄ ███▌    ▄      ███  ███   ███   ███        ███    ███ 
        ████████▀    ██████████ █████▄▄██ █████▄▄██      █▀    ▀█   █▀    ███         ▀██████▀  
    )" << std::endl;
}
