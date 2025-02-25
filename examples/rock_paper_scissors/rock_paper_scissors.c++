#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    srand(time(NULL));
    std::string player_choice;
    int computer_choice;
    std::cout << "              *********************\n"
              << "              Rock, Paper, Scissors\n"
              << "              *********************\n";

    while (true)
    {
        std::cout << "Enter your choice (type \"exit\" to quit the game): ";
        std::cin >> player_choice;
        std::transform(player_choice.begin(), player_choice.end(), player_choice.begin(), tolower);
        while (!std::cin || player_choice != "rock" && player_choice != "paper" && player_choice != "scissors" && player_choice != "exit")
        {
            std::cin.clear();
            std::cout << "Invalid choice\n"
                      << "Enter your choice (type \"exit\" to quit the game): ";
            std::cin >> player_choice;
            std::transform(player_choice.begin(), player_choice.end(), player_choice.begin(), tolower);
        }

        if (player_choice == "exit")
        {
            std::cout << "Thank you for playing the game!";
            break;
        }

        computer_choice = rand() % 3;
        if (computer_choice == 0)
        {
            std::cout << "The computer chose rock...\n";
            if (player_choice == "rock")
            {
                std::cout << "Tie.\n";
            }
            if (player_choice == "paper")
            {
                std::cout << "You win!!!\n";
            }
            if (player_choice == "scissors")
            {
                std::cout << "You lose...\n";
            }
        }
        else if (computer_choice == 1)
        {
            std::cout << "The computer chose paper...\n";
            if (player_choice == "rock")
            {
                std::cout << "You lose...\n";
            }
            if (player_choice == "paper")
            {
                std::cout << "Tie.\n";
            }
            if (player_choice == "scissors")
            {
                std::cout << "You win!!!\n";
            }
        }
        else if (computer_choice == 2)
        {
            std::cout << "The computer chose scissors...\n";
            if (player_choice == "rock")
            {
                std::cout << "You win!!!\n";
            }
            if (player_choice == "paper")
            {
                std::cout << "You lose...\n";
            }
            if (player_choice == "scissors")
            {
                std::cout << "Tie.\n";
            }
        }
    }

    return 0;
}